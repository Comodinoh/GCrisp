module gcrisp::engine::script;

import gcrisp::engine::data;
import gcrisp::engine::logger;
import std::collections::list;
import std::collections::map;
import raylib5::rl;

def ActionPair = Pair(<any[], Action>);
def ActionList = List(<ActionPair>);
def SceneList = List(<Scene>);

struct Script
{
  SceneList scenes;
  usz currentScene;
}

struct Scene
{
  Timeline timeline;
  List(<Character>) characters;
}

struct Timeline
{
  ActionList actions;
  usz currentAction;
}

/**
* Subject to change
**/
struct Character
{
  Texture2D texture;
  String name;
}


interface Action
{
  fn void execute(any[] args);
}

struct VoidAction(Action)
{
  int t; // Can't declare empty structs

}


fn bool Script.update(&self)
{
  Scene currentScene = self.scenes.get(self.currentScene);

  Timeline timeline = currentScene.timeline;
  ActionPair actionPair = timeline.actions.get(timeline.currentAction);

  actionPair.second.execute(actionPair.first);

  return currentScene.nextAction() || self.nextScene(); 
}

fn bool Script.nextScene(&self)
{
  usz scenes = self.scenes.len();
  self.currentScene++;
  return self.currentScene < scenes;
}

fn bool Scene.nextAction(&self)
{
  Timeline timeline = self.timeline;
  usz actions = timeline.actions.len();
  timeline.currentAction++;
  return timeline.currentAction < actions;
}

/**
* @require args.len > 0, "Action arguments must at least have an element" 
* @ensure return.len > 0
*/
fn void VoidAction.execute(&self, any[] args) @dynamic
{
  // Do nothing (Testing purposes)
}

fn Scene Scene.unregister(&self, int position)
{
  self.timeline.actions.remove_at(position);
  return *self;
}

fn Scene Scene.register(&self, ActionPair... actions)
{
  if(actions.len == 0) 
  {
    logger::log("Called Scene.register on empty actions", .log_level = TraceLogLevel.DEBUG);
    return *self;
  }
  self.timeline.actions.add_array(actions);
  return *self;
}
