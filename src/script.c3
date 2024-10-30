module gcrisp::engine::script;

import std::collections::list;
import std::collections::map;
import raylib5::rl;

interface Action
{
  fn void execute(any... args);
}

struct VoidAction(Action)
{
  int t; // Can't declare empty structs

}

/**
* @require args.len > 0, "Action arguments must at least have an element" 
* @ensure return.len > 0
*/
fn void VoidAction.execute(&self, any... args) @dynamic
{
  // Do nothing (Testing purposes)
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

/**
* Subject to change
**/
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

fn Scene Scene.unregister(&self, int position)
{
  self.timeline.actions.remove_at(position);
  return *self;
}

fn Scene Scene.register(&self, Action... actions)
{
  if(actions.len == 0) return *self;
  self.timeline.actions.add_array(actions);
  return *self;
}
