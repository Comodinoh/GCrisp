module gcrisp::engine::logger;

import gcrisp::engine::constants;
import raylib5::rl;


fn void log(String msg, args..., TraceLogLevel log_level = TraceLogLevel.INFO)
{ 
  String pfx = constants::ENGINE_NAME;
  String display = std::core::string::new_format("%s: %s", pfx, msg);

  rl::traceLog(log_level, (ZString)display, args);
}

