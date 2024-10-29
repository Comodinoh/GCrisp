module gcrisp::engine::script;

import std::collections::list;
import raylib5::rl;

interface Action
{
  fn void execute(any... args);
}

struct Scene
{
  Timeline timeline;
  List(<Character>) characters;
}

struct Timeline
{
  List(<Action>) actions;
  uint128 currentAction;
}

struct Character
{
  Texture2D texture;
  String name;
}

fn void Scene.update(&self)
{
  
}

fn void Scene.render(&self)
{

}

fn Scene Scene.register(&self, Action action)
{
  self.timeline.actions.push(action);
  return *self;
}
