module gcrisp::engine::script;

import gcrisp::engine::data;
import gcrisp::engine::logger;
import gcrisp::engine::script::actions;
import std::collections::list;
import std::collections::map;
import raylib5::rl;

def Scenes = List(<Scene>);
def Scripts = HashMap(<String, Script>);

struct ScriptProgram
{
  Scripts scripts;
  String currentScript;
}

struct Script
{
  Scenes scenes;
  usz currentScene;
  bool* done;
}

struct Scene
{
  Timeline timeline;
  List(<Character>) characters;
}

struct Timeline
{
  Actions actions;
  usz currentAction;
}

fn void ScriptProgram.changeScript(&self, String script)
{
  assert(self.scripts.has_key(script), "Tried changing to a null script");
  
  self.currentScript = script;
}

fn void ScriptProgram.update(&self)
{
  Script currentScript = self.scripts[self.currentScript]!!;
  
  if(*currentScript.done)
  {
    return;
  }

  currentScript.update();
}

fn void ScriptProgram.dispose(&self)
{
  foreach(script : self.scripts.value_tlist())
  {
    script.dispose();
  }
  self.scripts.free();
}


fn void Script.update(&self)
{
  Scene currentScene = self.scenes.get(self.currentScene);
  Timeline timeline = currentScene.timeline;
  ActionPair actionPair = timeline.actions.get(timeline.currentAction);
  ArgPair argPair = actionPair.second;
  
  if(argPair.second(&currentScene)) actionPair.first(...argPair.first);

  if(!currentScene.nextAction())
  {
    logger::log("Done with current scene, switching...");
    if(!self.nextScene())
    {
      *self.done = true;
    }
  }
}

fn void Script.dispose(&self)
{
  foreach(scene : self.scenes)
  {
    scene.dispose();
  }
  self.scenes.free();
}

fn bool Script.nextScene(&self)
{
  usz scenes = self.scenes.len();
  self.currentScene++;
  return self.currentScene < scenes;
}

fn void Timeline.clear(&self)
{
  self.actions.free();
}

fn void Scene.dispose(&self)
{
  self.timeline.clear();
  self.characters.free();
}

fn bool Scene.nextAction(&self)
{
  Timeline timeline = self.timeline;
  usz actions = timeline.actions.len();
  timeline.currentAction++;
  return timeline.currentAction < actions;
}

fn Scene Scene.unregister(&self, int position)
{
  self.timeline.actions.remove_at(position);
  return *self;
}

fn Scene* Scene.register(&self, ActionPair... actions)
{
  if(actions.len == 0) 
  {
    logger::log("Tried calling Scene.register on empty actions", .log_level = TraceLogLevel.WARNING);
    return self;
  }
  self.timeline.actions.add_array(actions);
  return self;
}
