//
//  Copyright (c) 2023 Huawei Device Co., Ltd.
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
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