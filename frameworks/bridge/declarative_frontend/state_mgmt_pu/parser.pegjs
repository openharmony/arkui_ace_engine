/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

program
 = code:code+ { return code.join(""); }

code
 = s:skipConsole { return s; }
  / c:. { return c; }

// Add "error" and/or "warn" if needed
func
 = f:("log" / "info" / "debug" ) { return f; }

console
 = head:"console" dot:(_ "." _) func:func _ { return head + '.' + func }

skipConsole
 = console:console "(" c:(!")" c:logChar { return c; })* ")"_";"? { return `/* ${console}(${c.join("")}); */`}

logChar
 = "(" c:logChar* ")" { return `(${c.join("")})`; }
 / "/*" c:logChar* "*/" { return `**${c.join("")}**`; }
 / !")"!"*/" c:. { return c; }

_ "whitespace"
  = [ ' '\t\n\r]*