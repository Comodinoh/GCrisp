module gcrisp::engine::script::actions;

import gcrisp::engine::data::pair;
import std::collections::list;

def Action = fn void(any...);
def Condition = fn bool(Scene*);
def ArgPair = Pair(<any[], Condition>);
def ActionPair = Pair(<Action, ArgPair>);
def Actions = List(<ActionPair>);

fn ActionPair createAction(Action actionFunc, any... args)
{
  return createActionC(actionFunc, noCondition(), ...args);
}

fn ActionPair createActionC(Action actionFunc, Condition condition, any... args)
{
  ArgPair argPair = {args, condition};
  return {actionFunc, argPair};
}

fn Condition noCondition()
{
  return fn(args) => true;
}
