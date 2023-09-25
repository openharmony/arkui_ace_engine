program
 = code:code+ { return code.join(""); }

code
 = s:( skipProfiler ) { return s; }
  / c:. { return c; }

profilerCall
 = f:("begin" / "end") { return f; }

profiler
 = head:"stateMgmtProfiler" dot:(_ "." _) func:profilerCall _ { return head + '.' + func }
 
skipProfiler
 = profiler:profiler "(" c:(!")" c:logChar { return c; })* ")" ";"? { return ``}

logChar
 = "(" c:logChar* ")" { return `(${c.join("")})`; }
 / "/*" c:logChar* "*/" { return `**${c.join("")}**`; }
 / !")"!"*/" c:. { return c; }

_ "whitespace"
  = [ ' '\t\n\r]*