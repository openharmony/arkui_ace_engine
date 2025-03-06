#!/usr/bin/env node
/******/ (() => { // webpackBootstrap
/******/ 	var __webpack_modules__ = ({

/***/ "../../node_modules/balanced-match/index.js":
/*!**************************************************!*\
  !*** ../../node_modules/balanced-match/index.js ***!
  \**************************************************/
/***/ ((module) => {

"use strict";

module.exports = balanced;
function balanced(a, b, str) {
  if (a instanceof RegExp) a = maybeMatch(a, str);
  if (b instanceof RegExp) b = maybeMatch(b, str);

  var r = range(a, b, str);

  return r && {
    start: r[0],
    end: r[1],
    pre: str.slice(0, r[0]),
    body: str.slice(r[0] + a.length, r[1]),
    post: str.slice(r[1] + b.length)
  };
}

function maybeMatch(reg, str) {
  var m = str.match(reg);
  return m ? m[0] : null;
}

balanced.range = range;
function range(a, b, str) {
  var begs, beg, left, right, result;
  var ai = str.indexOf(a);
  var bi = str.indexOf(b, ai + 1);
  var i = ai;

  if (ai >= 0 && bi > 0) {
    if(a===b) {
      return [ai, bi];
    }
    begs = [];
    left = str.length;

    while (i >= 0 && !result) {
      if (i == ai) {
        begs.push(i);
        ai = str.indexOf(a, i + 1);
      } else if (begs.length == 1) {
        result = [ begs.pop(), bi ];
      } else {
        beg = begs.pop();
        if (beg < left) {
          left = beg;
          right = bi;
        }

        bi = str.indexOf(b, i + 1);
      }

      i = ai < bi && ai >= 0 ? ai : bi;
    }

    if (begs.length) {
      result = [ left, right ];
    }
  }

  return result;
}


/***/ }),

/***/ "../../node_modules/brace-expansion/index.js":
/*!***************************************************!*\
  !*** ../../node_modules/brace-expansion/index.js ***!
  \***************************************************/
/***/ ((module, __unused_webpack_exports, __webpack_require__) => {

var balanced = __webpack_require__(/*! balanced-match */ "../../node_modules/balanced-match/index.js");

module.exports = expandTop;

var escSlash = '\0SLASH'+Math.random()+'\0';
var escOpen = '\0OPEN'+Math.random()+'\0';
var escClose = '\0CLOSE'+Math.random()+'\0';
var escComma = '\0COMMA'+Math.random()+'\0';
var escPeriod = '\0PERIOD'+Math.random()+'\0';

function numeric(str) {
  return parseInt(str, 10) == str
    ? parseInt(str, 10)
    : str.charCodeAt(0);
}

function escapeBraces(str) {
  return str.split('\\\\').join(escSlash)
            .split('\\{').join(escOpen)
            .split('\\}').join(escClose)
            .split('\\,').join(escComma)
            .split('\\.').join(escPeriod);
}

function unescapeBraces(str) {
  return str.split(escSlash).join('\\')
            .split(escOpen).join('{')
            .split(escClose).join('}')
            .split(escComma).join(',')
            .split(escPeriod).join('.');
}


// Basically just str.split(","), but handling cases
// where we have nested braced sections, which should be
// treated as individual members, like {a,{b,c},d}
function parseCommaParts(str) {
  if (!str)
    return [''];

  var parts = [];
  var m = balanced('{', '}', str);

  if (!m)
    return str.split(',');

  var pre = m.pre;
  var body = m.body;
  var post = m.post;
  var p = pre.split(',');

  p[p.length-1] += '{' + body + '}';
  var postParts = parseCommaParts(post);
  if (post.length) {
    p[p.length-1] += postParts.shift();
    p.push.apply(p, postParts);
  }

  parts.push.apply(parts, p);

  return parts;
}

function expandTop(str) {
  if (!str)
    return [];

  // I don't know why Bash 4.3 does this, but it does.
  // Anything starting with {} will have the first two bytes preserved
  // but *only* at the top level, so {},a}b will not expand to anything,
  // but a{},b}c will be expanded to [a}c,abc].
  // One could argue that this is a bug in Bash, but since the goal of
  // this module is to match Bash's rules, we escape a leading {}
  if (str.substr(0, 2) === '{}') {
    str = '\\{\\}' + str.substr(2);
  }

  return expand(escapeBraces(str), true).map(unescapeBraces);
}

function embrace(str) {
  return '{' + str + '}';
}
function isPadded(el) {
  return /^-?0\d/.test(el);
}

function lte(i, y) {
  return i <= y;
}
function gte(i, y) {
  return i >= y;
}

function expand(str, isTop) {
  var expansions = [];

  var m = balanced('{', '}', str);
  if (!m) return [str];

  // no need to expand pre, since it is guaranteed to be free of brace-sets
  var pre = m.pre;
  var post = m.post.length
    ? expand(m.post, false)
    : [''];

  if (/\$$/.test(m.pre)) {    
    for (var k = 0; k < post.length; k++) {
      var expansion = pre+ '{' + m.body + '}' + post[k];
      expansions.push(expansion);
    }
  } else {
    var isNumericSequence = /^-?\d+\.\.-?\d+(?:\.\.-?\d+)?$/.test(m.body);
    var isAlphaSequence = /^[a-zA-Z]\.\.[a-zA-Z](?:\.\.-?\d+)?$/.test(m.body);
    var isSequence = isNumericSequence || isAlphaSequence;
    var isOptions = m.body.indexOf(',') >= 0;
    if (!isSequence && !isOptions) {
      // {a},b}
      if (m.post.match(/,.*\}/)) {
        str = m.pre + '{' + m.body + escClose + m.post;
        return expand(str);
      }
      return [str];
    }

    var n;
    if (isSequence) {
      n = m.body.split(/\.\./);
    } else {
      n = parseCommaParts(m.body);
      if (n.length === 1) {
        // x{{a,b}}y ==> x{a}y x{b}y
        n = expand(n[0], false).map(embrace);
        if (n.length === 1) {
          return post.map(function(p) {
            return m.pre + n[0] + p;
          });
        }
      }
    }

    // at this point, n is the parts, and we know it's not a comma set
    // with a single entry.
    var N;

    if (isSequence) {
      var x = numeric(n[0]);
      var y = numeric(n[1]);
      var width = Math.max(n[0].length, n[1].length)
      var incr = n.length == 3
        ? Math.abs(numeric(n[2]))
        : 1;
      var test = lte;
      var reverse = y < x;
      if (reverse) {
        incr *= -1;
        test = gte;
      }
      var pad = n.some(isPadded);

      N = [];

      for (var i = x; test(i, y); i += incr) {
        var c;
        if (isAlphaSequence) {
          c = String.fromCharCode(i);
          if (c === '\\')
            c = '';
        } else {
          c = String(i);
          if (pad) {
            var need = width - c.length;
            if (need > 0) {
              var z = new Array(need + 1).join('0');
              if (i < 0)
                c = '-' + z + c.slice(1);
              else
                c = z + c;
            }
          }
        }
        N.push(c);
      }
    } else {
      N = [];

      for (var j = 0; j < n.length; j++) {
        N.push.apply(N, expand(n[j], false));
      }
    }

    for (var j = 0; j < N.length; j++) {
      for (var k = 0; k < post.length; k++) {
        var expansion = pre + N[j] + post[k];
        if (!isTop || isSequence || expansion)
          expansions.push(expansion);
      }
    }
  }

  return expansions;
}



/***/ }),

/***/ "../../node_modules/commander/index.js":
/*!*********************************************!*\
  !*** ../../node_modules/commander/index.js ***!
  \*********************************************/
/***/ ((module, exports, __webpack_require__) => {

const { Argument } = __webpack_require__(/*! ./lib/argument.js */ "../../node_modules/commander/lib/argument.js");
const { Command } = __webpack_require__(/*! ./lib/command.js */ "../../node_modules/commander/lib/command.js");
const { CommanderError, InvalidArgumentError } = __webpack_require__(/*! ./lib/error.js */ "../../node_modules/commander/lib/error.js");
const { Help } = __webpack_require__(/*! ./lib/help.js */ "../../node_modules/commander/lib/help.js");
const { Option } = __webpack_require__(/*! ./lib/option.js */ "../../node_modules/commander/lib/option.js");

// @ts-check

/**
 * Expose the root command.
 */

exports = module.exports = new Command();
exports.program = exports; // More explicit access to global command.
// Implicit export of createArgument, createCommand, and createOption.

/**
 * Expose classes
 */

exports.Argument = Argument;
exports.Command = Command;
exports.CommanderError = CommanderError;
exports.Help = Help;
exports.InvalidArgumentError = InvalidArgumentError;
exports.InvalidOptionArgumentError = InvalidArgumentError; // Deprecated
exports.Option = Option;


/***/ }),

/***/ "../../node_modules/commander/lib/argument.js":
/*!****************************************************!*\
  !*** ../../node_modules/commander/lib/argument.js ***!
  \****************************************************/
/***/ ((__unused_webpack_module, exports, __webpack_require__) => {

const { InvalidArgumentError } = __webpack_require__(/*! ./error.js */ "../../node_modules/commander/lib/error.js");

// @ts-check

class Argument {
  /**
   * Initialize a new command argument with the given name and description.
   * The default is that the argument is required, and you can explicitly
   * indicate this with <> around the name. Put [] around the name for an optional argument.
   *
   * @param {string} name
   * @param {string} [description]
   */

  constructor(name, description) {
    this.description = description || '';
    this.variadic = false;
    this.parseArg = undefined;
    this.defaultValue = undefined;
    this.defaultValueDescription = undefined;
    this.argChoices = undefined;

    switch (name[0]) {
      case '<': // e.g. <required>
        this.required = true;
        this._name = name.slice(1, -1);
        break;
      case '[': // e.g. [optional]
        this.required = false;
        this._name = name.slice(1, -1);
        break;
      default:
        this.required = true;
        this._name = name;
        break;
    }

    if (this._name.length > 3 && this._name.slice(-3) === '...') {
      this.variadic = true;
      this._name = this._name.slice(0, -3);
    }
  }

  /**
   * Return argument name.
   *
   * @return {string}
   */

  name() {
    return this._name;
  }

  /**
   * @api private
   */

  _concatValue(value, previous) {
    if (previous === this.defaultValue || !Array.isArray(previous)) {
      return [value];
    }

    return previous.concat(value);
  }

  /**
   * Set the default value, and optionally supply the description to be displayed in the help.
   *
   * @param {any} value
   * @param {string} [description]
   * @return {Argument}
   */

  default(value, description) {
    this.defaultValue = value;
    this.defaultValueDescription = description;
    return this;
  }

  /**
   * Set the custom handler for processing CLI command arguments into argument values.
   *
   * @param {Function} [fn]
   * @return {Argument}
   */

  argParser(fn) {
    this.parseArg = fn;
    return this;
  }

  /**
   * Only allow argument value to be one of choices.
   *
   * @param {string[]} values
   * @return {Argument}
   */

  choices(values) {
    this.argChoices = values.slice();
    this.parseArg = (arg, previous) => {
      if (!this.argChoices.includes(arg)) {
        throw new InvalidArgumentError(`Allowed choices are ${this.argChoices.join(', ')}.`);
      }
      if (this.variadic) {
        return this._concatValue(arg, previous);
      }
      return arg;
    };
    return this;
  }

  /**
   * Make argument required.
   */
  argRequired() {
    this.required = true;
    return this;
  }

  /**
   * Make argument optional.
   */
  argOptional() {
    this.required = false;
    return this;
  }
}

/**
 * Takes an argument and returns its human readable equivalent for help usage.
 *
 * @param {Argument} arg
 * @return {string}
 * @api private
 */

function humanReadableArgName(arg) {
  const nameOutput = arg.name() + (arg.variadic === true ? '...' : '');

  return arg.required
    ? '<' + nameOutput + '>'
    : '[' + nameOutput + ']';
}

exports.Argument = Argument;
exports.humanReadableArgName = humanReadableArgName;


/***/ }),

/***/ "../../node_modules/commander/lib/command.js":
/*!***************************************************!*\
  !*** ../../node_modules/commander/lib/command.js ***!
  \***************************************************/
/***/ ((__unused_webpack_module, exports, __webpack_require__) => {

const EventEmitter = (__webpack_require__(/*! events */ "events").EventEmitter);
const childProcess = __webpack_require__(/*! child_process */ "child_process");
const path = __webpack_require__(/*! path */ "path");
const fs = __webpack_require__(/*! fs */ "fs");
const process = __webpack_require__(/*! process */ "process");

const { Argument, humanReadableArgName } = __webpack_require__(/*! ./argument.js */ "../../node_modules/commander/lib/argument.js");
const { CommanderError } = __webpack_require__(/*! ./error.js */ "../../node_modules/commander/lib/error.js");
const { Help } = __webpack_require__(/*! ./help.js */ "../../node_modules/commander/lib/help.js");
const { Option, splitOptionFlags, DualOptions } = __webpack_require__(/*! ./option.js */ "../../node_modules/commander/lib/option.js");
const { suggestSimilar } = __webpack_require__(/*! ./suggestSimilar */ "../../node_modules/commander/lib/suggestSimilar.js");

// @ts-check

class Command extends EventEmitter {
  /**
   * Initialize a new `Command`.
   *
   * @param {string} [name]
   */

  constructor(name) {
    super();
    /** @type {Command[]} */
    this.commands = [];
    /** @type {Option[]} */
    this.options = [];
    this.parent = null;
    this._allowUnknownOption = false;
    this._allowExcessArguments = true;
    /** @type {Argument[]} */
    this._args = [];
    /** @type {string[]} */
    this.args = []; // cli args with options removed
    this.rawArgs = [];
    this.processedArgs = []; // like .args but after custom processing and collecting variadic
    this._scriptPath = null;
    this._name = name || '';
    this._optionValues = {};
    this._optionValueSources = {}; // default, env, cli etc
    this._storeOptionsAsProperties = false;
    this._actionHandler = null;
    this._executableHandler = false;
    this._executableFile = null; // custom name for executable
    this._executableDir = null; // custom search directory for subcommands
    this._defaultCommandName = null;
    this._exitCallback = null;
    this._aliases = [];
    this._combineFlagAndOptionalValue = true;
    this._description = '';
    this._summary = '';
    this._argsDescription = undefined; // legacy
    this._enablePositionalOptions = false;
    this._passThroughOptions = false;
    this._lifeCycleHooks = {}; // a hash of arrays
    /** @type {boolean | string} */
    this._showHelpAfterError = false;
    this._showSuggestionAfterError = true;

    // see .configureOutput() for docs
    this._outputConfiguration = {
      writeOut: (str) => process.stdout.write(str),
      writeErr: (str) => process.stderr.write(str),
      getOutHelpWidth: () => process.stdout.isTTY ? process.stdout.columns : undefined,
      getErrHelpWidth: () => process.stderr.isTTY ? process.stderr.columns : undefined,
      outputError: (str, write) => write(str)
    };

    this._hidden = false;
    this._hasHelpOption = true;
    this._helpFlags = '-h, --help';
    this._helpDescription = 'display help for command';
    this._helpShortFlag = '-h';
    this._helpLongFlag = '--help';
    this._addImplicitHelpCommand = undefined; // Deliberately undefined, not decided whether true or false
    this._helpCommandName = 'help';
    this._helpCommandnameAndArgs = 'help [command]';
    this._helpCommandDescription = 'display help for command';
    this._helpConfiguration = {};
  }

  /**
   * Copy settings that are useful to have in common across root command and subcommands.
   *
   * (Used internally when adding a command using `.command()` so subcommands inherit parent settings.)
   *
   * @param {Command} sourceCommand
   * @return {Command} `this` command for chaining
   */
  copyInheritedSettings(sourceCommand) {
    this._outputConfiguration = sourceCommand._outputConfiguration;
    this._hasHelpOption = sourceCommand._hasHelpOption;
    this._helpFlags = sourceCommand._helpFlags;
    this._helpDescription = sourceCommand._helpDescription;
    this._helpShortFlag = sourceCommand._helpShortFlag;
    this._helpLongFlag = sourceCommand._helpLongFlag;
    this._helpCommandName = sourceCommand._helpCommandName;
    this._helpCommandnameAndArgs = sourceCommand._helpCommandnameAndArgs;
    this._helpCommandDescription = sourceCommand._helpCommandDescription;
    this._helpConfiguration = sourceCommand._helpConfiguration;
    this._exitCallback = sourceCommand._exitCallback;
    this._storeOptionsAsProperties = sourceCommand._storeOptionsAsProperties;
    this._combineFlagAndOptionalValue = sourceCommand._combineFlagAndOptionalValue;
    this._allowExcessArguments = sourceCommand._allowExcessArguments;
    this._enablePositionalOptions = sourceCommand._enablePositionalOptions;
    this._showHelpAfterError = sourceCommand._showHelpAfterError;
    this._showSuggestionAfterError = sourceCommand._showSuggestionAfterError;

    return this;
  }

  /**
   * Define a command.
   *
   * There are two styles of command: pay attention to where to put the description.
   *
   * @example
   * // Command implemented using action handler (description is supplied separately to `.command`)
   * program
   *   .command('clone <source> [destination]')
   *   .description('clone a repository into a newly created directory')
   *   .action((source, destination) => {
   *     console.log('clone command called');
   *   });
   *
   * // Command implemented using separate executable file (description is second parameter to `.command`)
   * program
   *   .command('start <service>', 'start named service')
   *   .command('stop [service]', 'stop named service, or all if no name supplied');
   *
   * @param {string} nameAndArgs - command name and arguments, args are `<required>` or `[optional]` and last may also be `variadic...`
   * @param {Object|string} [actionOptsOrExecDesc] - configuration options (for action), or description (for executable)
   * @param {Object} [execOpts] - configuration options (for executable)
   * @return {Command} returns new command for action handler, or `this` for executable command
   */

  command(nameAndArgs, actionOptsOrExecDesc, execOpts) {
    let desc = actionOptsOrExecDesc;
    let opts = execOpts;
    if (typeof desc === 'object' && desc !== null) {
      opts = desc;
      desc = null;
    }
    opts = opts || {};
    const [, name, args] = nameAndArgs.match(/([^ ]+) *(.*)/);

    const cmd = this.createCommand(name);
    if (desc) {
      cmd.description(desc);
      cmd._executableHandler = true;
    }
    if (opts.isDefault) this._defaultCommandName = cmd._name;
    cmd._hidden = !!(opts.noHelp || opts.hidden); // noHelp is deprecated old name for hidden
    cmd._executableFile = opts.executableFile || null; // Custom name for executable file, set missing to null to match constructor
    if (args) cmd.arguments(args);
    this.commands.push(cmd);
    cmd.parent = this;
    cmd.copyInheritedSettings(this);

    if (desc) return this;
    return cmd;
  }

  /**
   * Factory routine to create a new unattached command.
   *
   * See .command() for creating an attached subcommand, which uses this routine to
   * create the command. You can override createCommand to customise subcommands.
   *
   * @param {string} [name]
   * @return {Command} new command
   */

  createCommand(name) {
    return new Command(name);
  }

  /**
   * You can customise the help with a subclass of Help by overriding createHelp,
   * or by overriding Help properties using configureHelp().
   *
   * @return {Help}
   */

  createHelp() {
    return Object.assign(new Help(), this.configureHelp());
  }

  /**
   * You can customise the help by overriding Help properties using configureHelp(),
   * or with a subclass of Help by overriding createHelp().
   *
   * @param {Object} [configuration] - configuration options
   * @return {Command|Object} `this` command for chaining, or stored configuration
   */

  configureHelp(configuration) {
    if (configuration === undefined) return this._helpConfiguration;

    this._helpConfiguration = configuration;
    return this;
  }

  /**
   * The default output goes to stdout and stderr. You can customise this for special
   * applications. You can also customise the display of errors by overriding outputError.
   *
   * The configuration properties are all functions:
   *
   *     // functions to change where being written, stdout and stderr
   *     writeOut(str)
   *     writeErr(str)
   *     // matching functions to specify width for wrapping help
   *     getOutHelpWidth()
   *     getErrHelpWidth()
   *     // functions based on what is being written out
   *     outputError(str, write) // used for displaying errors, and not used for displaying help
   *
   * @param {Object} [configuration] - configuration options
   * @return {Command|Object} `this` command for chaining, or stored configuration
   */

  configureOutput(configuration) {
    if (configuration === undefined) return this._outputConfiguration;

    Object.assign(this._outputConfiguration, configuration);
    return this;
  }

  /**
   * Display the help or a custom message after an error occurs.
   *
   * @param {boolean|string} [displayHelp]
   * @return {Command} `this` command for chaining
   */
  showHelpAfterError(displayHelp = true) {
    if (typeof displayHelp !== 'string') displayHelp = !!displayHelp;
    this._showHelpAfterError = displayHelp;
    return this;
  }

  /**
   * Display suggestion of similar commands for unknown commands, or options for unknown options.
   *
   * @param {boolean} [displaySuggestion]
   * @return {Command} `this` command for chaining
   */
  showSuggestionAfterError(displaySuggestion = true) {
    this._showSuggestionAfterError = !!displaySuggestion;
    return this;
  }

  /**
   * Add a prepared subcommand.
   *
   * See .command() for creating an attached subcommand which inherits settings from its parent.
   *
   * @param {Command} cmd - new subcommand
   * @param {Object} [opts] - configuration options
   * @return {Command} `this` command for chaining
   */

  addCommand(cmd, opts) {
    if (!cmd._name) {
      throw new Error(`Command passed to .addCommand() must have a name
- specify the name in Command constructor or using .name()`);
    }

    opts = opts || {};
    if (opts.isDefault) this._defaultCommandName = cmd._name;
    if (opts.noHelp || opts.hidden) cmd._hidden = true; // modifying passed command due to existing implementation

    this.commands.push(cmd);
    cmd.parent = this;
    return this;
  }

  /**
   * Factory routine to create a new unattached argument.
   *
   * See .argument() for creating an attached argument, which uses this routine to
   * create the argument. You can override createArgument to return a custom argument.
   *
   * @param {string} name
   * @param {string} [description]
   * @return {Argument} new argument
   */

  createArgument(name, description) {
    return new Argument(name, description);
  }

  /**
   * Define argument syntax for command.
   *
   * The default is that the argument is required, and you can explicitly
   * indicate this with <> around the name. Put [] around the name for an optional argument.
   *
   * @example
   * program.argument('<input-file>');
   * program.argument('[output-file]');
   *
   * @param {string} name
   * @param {string} [description]
   * @param {Function|*} [fn] - custom argument processing function
   * @param {*} [defaultValue]
   * @return {Command} `this` command for chaining
   */
  argument(name, description, fn, defaultValue) {
    const argument = this.createArgument(name, description);
    if (typeof fn === 'function') {
      argument.default(defaultValue).argParser(fn);
    } else {
      argument.default(fn);
    }
    this.addArgument(argument);
    return this;
  }

  /**
   * Define argument syntax for command, adding multiple at once (without descriptions).
   *
   * See also .argument().
   *
   * @example
   * program.arguments('<cmd> [env]');
   *
   * @param {string} names
   * @return {Command} `this` command for chaining
   */

  arguments(names) {
    names.split(/ +/).forEach((detail) => {
      this.argument(detail);
    });
    return this;
  }

  /**
   * Define argument syntax for command, adding a prepared argument.
   *
   * @param {Argument} argument
   * @return {Command} `this` command for chaining
   */
  addArgument(argument) {
    const previousArgument = this._args.slice(-1)[0];
    if (previousArgument && previousArgument.variadic) {
      throw new Error(`only the last argument can be variadic '${previousArgument.name()}'`);
    }
    if (argument.required && argument.defaultValue !== undefined && argument.parseArg === undefined) {
      throw new Error(`a default value for a required argument is never used: '${argument.name()}'`);
    }
    this._args.push(argument);
    return this;
  }

  /**
   * Override default decision whether to add implicit help command.
   *
   *    addHelpCommand() // force on
   *    addHelpCommand(false); // force off
   *    addHelpCommand('help [cmd]', 'display help for [cmd]'); // force on with custom details
   *
   * @return {Command} `this` command for chaining
   */

  addHelpCommand(enableOrNameAndArgs, description) {
    if (enableOrNameAndArgs === false) {
      this._addImplicitHelpCommand = false;
    } else {
      this._addImplicitHelpCommand = true;
      if (typeof enableOrNameAndArgs === 'string') {
        this._helpCommandName = enableOrNameAndArgs.split(' ')[0];
        this._helpCommandnameAndArgs = enableOrNameAndArgs;
      }
      this._helpCommandDescription = description || this._helpCommandDescription;
    }
    return this;
  }

  /**
   * @return {boolean}
   * @api private
   */

  _hasImplicitHelpCommand() {
    if (this._addImplicitHelpCommand === undefined) {
      return this.commands.length && !this._actionHandler && !this._findCommand('help');
    }
    return this._addImplicitHelpCommand;
  }

  /**
   * Add hook for life cycle event.
   *
   * @param {string} event
   * @param {Function} listener
   * @return {Command} `this` command for chaining
   */

  hook(event, listener) {
    const allowedValues = ['preSubcommand', 'preAction', 'postAction'];
    if (!allowedValues.includes(event)) {
      throw new Error(`Unexpected value for event passed to hook : '${event}'.
Expecting one of '${allowedValues.join("', '")}'`);
    }
    if (this._lifeCycleHooks[event]) {
      this._lifeCycleHooks[event].push(listener);
    } else {
      this._lifeCycleHooks[event] = [listener];
    }
    return this;
  }

  /**
   * Register callback to use as replacement for calling process.exit.
   *
   * @param {Function} [fn] optional callback which will be passed a CommanderError, defaults to throwing
   * @return {Command} `this` command for chaining
   */

  exitOverride(fn) {
    if (fn) {
      this._exitCallback = fn;
    } else {
      this._exitCallback = (err) => {
        if (err.code !== 'commander.executeSubCommandAsync') {
          throw err;
        } else {
          // Async callback from spawn events, not useful to throw.
        }
      };
    }
    return this;
  }

  /**
   * Call process.exit, and _exitCallback if defined.
   *
   * @param {number} exitCode exit code for using with process.exit
   * @param {string} code an id string representing the error
   * @param {string} message human-readable description of the error
   * @return never
   * @api private
   */

  _exit(exitCode, code, message) {
    if (this._exitCallback) {
      this._exitCallback(new CommanderError(exitCode, code, message));
      // Expecting this line is not reached.
    }
    process.exit(exitCode);
  }

  /**
   * Register callback `fn` for the command.
   *
   * @example
   * program
   *   .command('serve')
   *   .description('start service')
   *   .action(function() {
   *      // do work here
   *   });
   *
   * @param {Function} fn
   * @return {Command} `this` command for chaining
   */

  action(fn) {
    const listener = (args) => {
      // The .action callback takes an extra parameter which is the command or options.
      const expectedArgsCount = this._args.length;
      const actionArgs = args.slice(0, expectedArgsCount);
      if (this._storeOptionsAsProperties) {
        actionArgs[expectedArgsCount] = this; // backwards compatible "options"
      } else {
        actionArgs[expectedArgsCount] = this.opts();
      }
      actionArgs.push(this);

      return fn.apply(this, actionArgs);
    };
    this._actionHandler = listener;
    return this;
  }

  /**
   * Factory routine to create a new unattached option.
   *
   * See .option() for creating an attached option, which uses this routine to
   * create the option. You can override createOption to return a custom option.
   *
   * @param {string} flags
   * @param {string} [description]
   * @return {Option} new option
   */

  createOption(flags, description) {
    return new Option(flags, description);
  }

  /**
   * Add an option.
   *
   * @param {Option} option
   * @return {Command} `this` command for chaining
   */
  addOption(option) {
    const oname = option.name();
    const name = option.attributeName();

    // store default value
    if (option.negate) {
      // --no-foo is special and defaults foo to true, unless a --foo option is already defined
      const positiveLongFlag = option.long.replace(/^--no-/, '--');
      if (!this._findOption(positiveLongFlag)) {
        this.setOptionValueWithSource(name, option.defaultValue === undefined ? true : option.defaultValue, 'default');
      }
    } else if (option.defaultValue !== undefined) {
      this.setOptionValueWithSource(name, option.defaultValue, 'default');
    }

    // register the option
    this.options.push(option);

    // handler for cli and env supplied values
    const handleOptionValue = (val, invalidValueMessage, valueSource) => {
      // val is null for optional option used without an optional-argument.
      // val is undefined for boolean and negated option.
      if (val == null && option.presetArg !== undefined) {
        val = option.presetArg;
      }

      // custom processing
      const oldValue = this.getOptionValue(name);
      if (val !== null && option.parseArg) {
        try {
          val = option.parseArg(val, oldValue);
        } catch (err) {
          if (err.code === 'commander.invalidArgument') {
            const message = `${invalidValueMessage} ${err.message}`;
            this.error(message, { exitCode: err.exitCode, code: err.code });
          }
          throw err;
        }
      } else if (val !== null && option.variadic) {
        val = option._concatValue(val, oldValue);
      }

      // Fill-in appropriate missing values. Long winded but easy to follow.
      if (val == null) {
        if (option.negate) {
          val = false;
        } else if (option.isBoolean() || option.optional) {
          val = true;
        } else {
          val = ''; // not normal, parseArg might have failed or be a mock function for testing
        }
      }
      this.setOptionValueWithSource(name, val, valueSource);
    };

    this.on('option:' + oname, (val) => {
      const invalidValueMessage = `error: option '${option.flags}' argument '${val}' is invalid.`;
      handleOptionValue(val, invalidValueMessage, 'cli');
    });

    if (option.envVar) {
      this.on('optionEnv:' + oname, (val) => {
        const invalidValueMessage = `error: option '${option.flags}' value '${val}' from env '${option.envVar}' is invalid.`;
        handleOptionValue(val, invalidValueMessage, 'env');
      });
    }

    return this;
  }

  /**
   * Internal implementation shared by .option() and .requiredOption()
   *
   * @api private
   */
  _optionEx(config, flags, description, fn, defaultValue) {
    if (typeof flags === 'object' && flags instanceof Option) {
      throw new Error('To add an Option object use addOption() instead of option() or requiredOption()');
    }
    const option = this.createOption(flags, description);
    option.makeOptionMandatory(!!config.mandatory);
    if (typeof fn === 'function') {
      option.default(defaultValue).argParser(fn);
    } else if (fn instanceof RegExp) {
      // deprecated
      const regex = fn;
      fn = (val, def) => {
        const m = regex.exec(val);
        return m ? m[0] : def;
      };
      option.default(defaultValue).argParser(fn);
    } else {
      option.default(fn);
    }

    return this.addOption(option);
  }

  /**
   * Define option with `flags`, `description` and optional
   * coercion `fn`.
   *
   * The `flags` string contains the short and/or long flags,
   * separated by comma, a pipe or space. The following are all valid
   * all will output this way when `--help` is used.
   *
   *     "-p, --pepper"
   *     "-p|--pepper"
   *     "-p --pepper"
   *
   * @example
   * // simple boolean defaulting to undefined
   * program.option('-p, --pepper', 'add pepper');
   *
   * program.pepper
   * // => undefined
   *
   * --pepper
   * program.pepper
   * // => true
   *
   * // simple boolean defaulting to true (unless non-negated option is also defined)
   * program.option('-C, --no-cheese', 'remove cheese');
   *
   * program.cheese
   * // => true
   *
   * --no-cheese
   * program.cheese
   * // => false
   *
   * // required argument
   * program.option('-C, --chdir <path>', 'change the working directory');
   *
   * --chdir /tmp
   * program.chdir
   * // => "/tmp"
   *
   * // optional argument
   * program.option('-c, --cheese [type]', 'add cheese [marble]');
   *
   * @param {string} flags
   * @param {string} [description]
   * @param {Function|*} [fn] - custom option processing function or default value
   * @param {*} [defaultValue]
   * @return {Command} `this` command for chaining
   */

  option(flags, description, fn, defaultValue) {
    return this._optionEx({}, flags, description, fn, defaultValue);
  }

  /**
  * Add a required option which must have a value after parsing. This usually means
  * the option must be specified on the command line. (Otherwise the same as .option().)
  *
  * The `flags` string contains the short and/or long flags, separated by comma, a pipe or space.
  *
  * @param {string} flags
  * @param {string} [description]
  * @param {Function|*} [fn] - custom option processing function or default value
  * @param {*} [defaultValue]
  * @return {Command} `this` command for chaining
  */

  requiredOption(flags, description, fn, defaultValue) {
    return this._optionEx({ mandatory: true }, flags, description, fn, defaultValue);
  }

  /**
   * Alter parsing of short flags with optional values.
   *
   * @example
   * // for `.option('-f,--flag [value]'):
   * program.combineFlagAndOptionalValue(true);  // `-f80` is treated like `--flag=80`, this is the default behaviour
   * program.combineFlagAndOptionalValue(false) // `-fb` is treated like `-f -b`
   *
   * @param {Boolean} [combine=true] - if `true` or omitted, an optional value can be specified directly after the flag.
   */
  combineFlagAndOptionalValue(combine = true) {
    this._combineFlagAndOptionalValue = !!combine;
    return this;
  }

  /**
   * Allow unknown options on the command line.
   *
   * @param {Boolean} [allowUnknown=true] - if `true` or omitted, no error will be thrown
   * for unknown options.
   */
  allowUnknownOption(allowUnknown = true) {
    this._allowUnknownOption = !!allowUnknown;
    return this;
  }

  /**
   * Allow excess command-arguments on the command line. Pass false to make excess arguments an error.
   *
   * @param {Boolean} [allowExcess=true] - if `true` or omitted, no error will be thrown
   * for excess arguments.
   */
  allowExcessArguments(allowExcess = true) {
    this._allowExcessArguments = !!allowExcess;
    return this;
  }

  /**
   * Enable positional options. Positional means global options are specified before subcommands which lets
   * subcommands reuse the same option names, and also enables subcommands to turn on passThroughOptions.
   * The default behaviour is non-positional and global options may appear anywhere on the command line.
   *
   * @param {Boolean} [positional=true]
   */
  enablePositionalOptions(positional = true) {
    this._enablePositionalOptions = !!positional;
    return this;
  }

  /**
   * Pass through options that come after command-arguments rather than treat them as command-options,
   * so actual command-options come before command-arguments. Turning this on for a subcommand requires
   * positional options to have been enabled on the program (parent commands).
   * The default behaviour is non-positional and options may appear before or after command-arguments.
   *
   * @param {Boolean} [passThrough=true]
   * for unknown options.
   */
  passThroughOptions(passThrough = true) {
    this._passThroughOptions = !!passThrough;
    if (!!this.parent && passThrough && !this.parent._enablePositionalOptions) {
      throw new Error('passThroughOptions can not be used without turning on enablePositionalOptions for parent command(s)');
    }
    return this;
  }

  /**
    * Whether to store option values as properties on command object,
    * or store separately (specify false). In both cases the option values can be accessed using .opts().
    *
    * @param {boolean} [storeAsProperties=true]
    * @return {Command} `this` command for chaining
    */

  storeOptionsAsProperties(storeAsProperties = true) {
    this._storeOptionsAsProperties = !!storeAsProperties;
    if (this.options.length) {
      throw new Error('call .storeOptionsAsProperties() before adding options');
    }
    return this;
  }

  /**
   * Retrieve option value.
   *
   * @param {string} key
   * @return {Object} value
   */

  getOptionValue(key) {
    if (this._storeOptionsAsProperties) {
      return this[key];
    }
    return this._optionValues[key];
  }

  /**
   * Store option value.
   *
   * @param {string} key
   * @param {Object} value
   * @return {Command} `this` command for chaining
   */

  setOptionValue(key, value) {
    return this.setOptionValueWithSource(key, value, undefined);
  }

  /**
    * Store option value and where the value came from.
    *
    * @param {string} key
    * @param {Object} value
    * @param {string} source - expected values are default/config/env/cli/implied
    * @return {Command} `this` command for chaining
    */

  setOptionValueWithSource(key, value, source) {
    if (this._storeOptionsAsProperties) {
      this[key] = value;
    } else {
      this._optionValues[key] = value;
    }
    this._optionValueSources[key] = source;
    return this;
  }

  /**
    * Get source of option value.
    * Expected values are default | config | env | cli | implied
    *
    * @param {string} key
    * @return {string}
    */

  getOptionValueSource(key) {
    return this._optionValueSources[key];
  }

  /**
    * Get source of option value. See also .optsWithGlobals().
    * Expected values are default | config | env | cli | implied
    *
    * @param {string} key
    * @return {string}
    */

  getOptionValueSourceWithGlobals(key) {
    // global overwrites local, like optsWithGlobals
    let source;
    getCommandAndParents(this).forEach((cmd) => {
      if (cmd.getOptionValueSource(key) !== undefined) {
        source = cmd.getOptionValueSource(key);
      }
    });
    return source;
  }

  /**
   * Get user arguments from implied or explicit arguments.
   * Side-effects: set _scriptPath if args included script. Used for default program name, and subcommand searches.
   *
   * @api private
   */

  _prepareUserArgs(argv, parseOptions) {
    if (argv !== undefined && !Array.isArray(argv)) {
      throw new Error('first parameter to parse must be array or undefined');
    }
    parseOptions = parseOptions || {};

    // Default to using process.argv
    if (argv === undefined) {
      argv = process.argv;
      // @ts-ignore: unknown property
      if (process.versions && process.versions.electron) {
        parseOptions.from = 'electron';
      }
    }
    this.rawArgs = argv.slice();

    // make it a little easier for callers by supporting various argv conventions
    let userArgs;
    switch (parseOptions.from) {
      case undefined:
      case 'node':
        this._scriptPath = argv[1];
        userArgs = argv.slice(2);
        break;
      case 'electron':
        // @ts-ignore: unknown property
        if (process.defaultApp) {
          this._scriptPath = argv[1];
          userArgs = argv.slice(2);
        } else {
          userArgs = argv.slice(1);
        }
        break;
      case 'user':
        userArgs = argv.slice(0);
        break;
      default:
        throw new Error(`unexpected parse option { from: '${parseOptions.from}' }`);
    }

    // Find default name for program from arguments.
    if (!this._name && this._scriptPath) this.nameFromFilename(this._scriptPath);
    this._name = this._name || 'program';

    return userArgs;
  }

  /**
   * Parse `argv`, setting options and invoking commands when defined.
   *
   * The default expectation is that the arguments are from node and have the application as argv[0]
   * and the script being run in argv[1], with user parameters after that.
   *
   * @example
   * program.parse(process.argv);
   * program.parse(); // implicitly use process.argv and auto-detect node vs electron conventions
   * program.parse(my-args, { from: 'user' }); // just user supplied arguments, nothing special about argv[0]
   *
   * @param {string[]} [argv] - optional, defaults to process.argv
   * @param {Object} [parseOptions] - optionally specify style of options with from: node/user/electron
   * @param {string} [parseOptions.from] - where the args are from: 'node', 'user', 'electron'
   * @return {Command} `this` command for chaining
   */

  parse(argv, parseOptions) {
    const userArgs = this._prepareUserArgs(argv, parseOptions);
    this._parseCommand([], userArgs);

    return this;
  }

  /**
   * Parse `argv`, setting options and invoking commands when defined.
   *
   * Use parseAsync instead of parse if any of your action handlers are async. Returns a Promise.
   *
   * The default expectation is that the arguments are from node and have the application as argv[0]
   * and the script being run in argv[1], with user parameters after that.
   *
   * @example
   * await program.parseAsync(process.argv);
   * await program.parseAsync(); // implicitly use process.argv and auto-detect node vs electron conventions
   * await program.parseAsync(my-args, { from: 'user' }); // just user supplied arguments, nothing special about argv[0]
   *
   * @param {string[]} [argv]
   * @param {Object} [parseOptions]
   * @param {string} parseOptions.from - where the args are from: 'node', 'user', 'electron'
   * @return {Promise}
   */

  async parseAsync(argv, parseOptions) {
    const userArgs = this._prepareUserArgs(argv, parseOptions);
    await this._parseCommand([], userArgs);

    return this;
  }

  /**
   * Execute a sub-command executable.
   *
   * @api private
   */

  _executeSubCommand(subcommand, args) {
    args = args.slice();
    let launchWithNode = false; // Use node for source targets so do not need to get permissions correct, and on Windows.
    const sourceExt = ['.js', '.ts', '.tsx', '.mjs', '.cjs'];

    function findFile(baseDir, baseName) {
      // Look for specified file
      const localBin = path.resolve(baseDir, baseName);
      if (fs.existsSync(localBin)) return localBin;

      // Stop looking if candidate already has an expected extension.
      if (sourceExt.includes(path.extname(baseName))) return undefined;

      // Try all the extensions.
      const foundExt = sourceExt.find(ext => fs.existsSync(`${localBin}${ext}`));
      if (foundExt) return `${localBin}${foundExt}`;

      return undefined;
    }

    // Not checking for help first. Unlikely to have mandatory and executable, and can't robustly test for help flags in external command.
    this._checkForMissingMandatoryOptions();
    this._checkForConflictingOptions();

    // executableFile and executableDir might be full path, or just a name
    let executableFile = subcommand._executableFile || `${this._name}-${subcommand._name}`;
    let executableDir = this._executableDir || '';
    if (this._scriptPath) {
      let resolvedScriptPath; // resolve possible symlink for installed npm binary
      try {
        resolvedScriptPath = fs.realpathSync(this._scriptPath);
      } catch (err) {
        resolvedScriptPath = this._scriptPath;
      }
      executableDir = path.resolve(path.dirname(resolvedScriptPath), executableDir);
    }

    // Look for a local file in preference to a command in PATH.
    if (executableDir) {
      let localFile = findFile(executableDir, executableFile);

      // Legacy search using prefix of script name instead of command name
      if (!localFile && !subcommand._executableFile && this._scriptPath) {
        const legacyName = path.basename(this._scriptPath, path.extname(this._scriptPath));
        if (legacyName !== this._name) {
          localFile = findFile(executableDir, `${legacyName}-${subcommand._name}`);
        }
      }
      executableFile = localFile || executableFile;
    }

    launchWithNode = sourceExt.includes(path.extname(executableFile));

    let proc;
    if (process.platform !== 'win32') {
      if (launchWithNode) {
        args.unshift(executableFile);
        // add executable arguments to spawn
        args = incrementNodeInspectorPort(process.execArgv).concat(args);

        proc = childProcess.spawn(process.argv[0], args, { stdio: 'inherit' });
      } else {
        proc = childProcess.spawn(executableFile, args, { stdio: 'inherit' });
      }
    } else {
      args.unshift(executableFile);
      // add executable arguments to spawn
      args = incrementNodeInspectorPort(process.execArgv).concat(args);
      proc = childProcess.spawn(process.execPath, args, { stdio: 'inherit' });
    }

    if (!proc.killed) { // testing mainly to avoid leak warnings during unit tests with mocked spawn
      const signals = ['SIGUSR1', 'SIGUSR2', 'SIGTERM', 'SIGINT', 'SIGHUP'];
      signals.forEach((signal) => {
        // @ts-ignore
        process.on(signal, () => {
          if (proc.killed === false && proc.exitCode === null) {
            proc.kill(signal);
          }
        });
      });
    }

    // By default terminate process when spawned process terminates.
    // Suppressing the exit if exitCallback defined is a bit messy and of limited use, but does allow process to stay running!
    const exitCallback = this._exitCallback;
    if (!exitCallback) {
      proc.on('close', process.exit.bind(process));
    } else {
      proc.on('close', () => {
        exitCallback(new CommanderError(process.exitCode || 0, 'commander.executeSubCommandAsync', '(close)'));
      });
    }
    proc.on('error', (err) => {
      // @ts-ignore
      if (err.code === 'ENOENT') {
        const executableDirMessage = executableDir
          ? `searched for local subcommand relative to directory '${executableDir}'`
          : 'no directory for search for local subcommand, use .executableDir() to supply a custom directory';
        const executableMissing = `'${executableFile}' does not exist
 - if '${subcommand._name}' is not meant to be an executable command, remove description parameter from '.command()' and use '.description()' instead
 - if the default executable name is not suitable, use the executableFile option to supply a custom name or path
 - ${executableDirMessage}`;
        throw new Error(executableMissing);
      // @ts-ignore
      } else if (err.code === 'EACCES') {
        throw new Error(`'${executableFile}' not executable`);
      }
      if (!exitCallback) {
        process.exit(1);
      } else {
        const wrappedError = new CommanderError(1, 'commander.executeSubCommandAsync', '(error)');
        wrappedError.nestedError = err;
        exitCallback(wrappedError);
      }
    });

    // Store the reference to the child process
    this.runningCommand = proc;
  }

  /**
   * @api private
   */

  _dispatchSubcommand(commandName, operands, unknown) {
    const subCommand = this._findCommand(commandName);
    if (!subCommand) this.help({ error: true });

    let hookResult;
    hookResult = this._chainOrCallSubCommandHook(hookResult, subCommand, 'preSubcommand');
    hookResult = this._chainOrCall(hookResult, () => {
      if (subCommand._executableHandler) {
        this._executeSubCommand(subCommand, operands.concat(unknown));
      } else {
        return subCommand._parseCommand(operands, unknown);
      }
    });
    return hookResult;
  }

  /**
   * Check this.args against expected this._args.
   *
   * @api private
   */

  _checkNumberOfArguments() {
    // too few
    this._args.forEach((arg, i) => {
      if (arg.required && this.args[i] == null) {
        this.missingArgument(arg.name());
      }
    });
    // too many
    if (this._args.length > 0 && this._args[this._args.length - 1].variadic) {
      return;
    }
    if (this.args.length > this._args.length) {
      this._excessArguments(this.args);
    }
  }

  /**
   * Process this.args using this._args and save as this.processedArgs!
   *
   * @api private
   */

  _processArguments() {
    const myParseArg = (argument, value, previous) => {
      // Extra processing for nice error message on parsing failure.
      let parsedValue = value;
      if (value !== null && argument.parseArg) {
        try {
          parsedValue = argument.parseArg(value, previous);
        } catch (err) {
          if (err.code === 'commander.invalidArgument') {
            const message = `error: command-argument value '${value}' is invalid for argument '${argument.name()}'. ${err.message}`;
            this.error(message, { exitCode: err.exitCode, code: err.code });
          }
          throw err;
        }
      }
      return parsedValue;
    };

    this._checkNumberOfArguments();

    const processedArgs = [];
    this._args.forEach((declaredArg, index) => {
      let value = declaredArg.defaultValue;
      if (declaredArg.variadic) {
        // Collect together remaining arguments for passing together as an array.
        if (index < this.args.length) {
          value = this.args.slice(index);
          if (declaredArg.parseArg) {
            value = value.reduce((processed, v) => {
              return myParseArg(declaredArg, v, processed);
            }, declaredArg.defaultValue);
          }
        } else if (value === undefined) {
          value = [];
        }
      } else if (index < this.args.length) {
        value = this.args[index];
        if (declaredArg.parseArg) {
          value = myParseArg(declaredArg, value, declaredArg.defaultValue);
        }
      }
      processedArgs[index] = value;
    });
    this.processedArgs = processedArgs;
  }

  /**
   * Once we have a promise we chain, but call synchronously until then.
   *
   * @param {Promise|undefined} promise
   * @param {Function} fn
   * @return {Promise|undefined}
   * @api private
   */

  _chainOrCall(promise, fn) {
    // thenable
    if (promise && promise.then && typeof promise.then === 'function') {
      // already have a promise, chain callback
      return promise.then(() => fn());
    }
    // callback might return a promise
    return fn();
  }

  /**
   *
   * @param {Promise|undefined} promise
   * @param {string} event
   * @return {Promise|undefined}
   * @api private
   */

  _chainOrCallHooks(promise, event) {
    let result = promise;
    const hooks = [];
    getCommandAndParents(this)
      .reverse()
      .filter(cmd => cmd._lifeCycleHooks[event] !== undefined)
      .forEach(hookedCommand => {
        hookedCommand._lifeCycleHooks[event].forEach((callback) => {
          hooks.push({ hookedCommand, callback });
        });
      });
    if (event === 'postAction') {
      hooks.reverse();
    }

    hooks.forEach((hookDetail) => {
      result = this._chainOrCall(result, () => {
        return hookDetail.callback(hookDetail.hookedCommand, this);
      });
    });
    return result;
  }

  /**
   *
   * @param {Promise|undefined} promise
   * @param {Command} subCommand
   * @param {string} event
   * @return {Promise|undefined}
   * @api private
   */

  _chainOrCallSubCommandHook(promise, subCommand, event) {
    let result = promise;
    if (this._lifeCycleHooks[event] !== undefined) {
      this._lifeCycleHooks[event].forEach((hook) => {
        result = this._chainOrCall(result, () => {
          return hook(this, subCommand);
        });
      });
    }
    return result;
  }

  /**
   * Process arguments in context of this command.
   * Returns action result, in case it is a promise.
   *
   * @api private
   */

  _parseCommand(operands, unknown) {
    const parsed = this.parseOptions(unknown);
    this._parseOptionsEnv(); // after cli, so parseArg not called on both cli and env
    this._parseOptionsImplied();
    operands = operands.concat(parsed.operands);
    unknown = parsed.unknown;
    this.args = operands.concat(unknown);

    if (operands && this._findCommand(operands[0])) {
      return this._dispatchSubcommand(operands[0], operands.slice(1), unknown);
    }
    if (this._hasImplicitHelpCommand() && operands[0] === this._helpCommandName) {
      if (operands.length === 1) {
        this.help();
      }
      return this._dispatchSubcommand(operands[1], [], [this._helpLongFlag]);
    }
    if (this._defaultCommandName) {
      outputHelpIfRequested(this, unknown); // Run the help for default command from parent rather than passing to default command
      return this._dispatchSubcommand(this._defaultCommandName, operands, unknown);
    }
    if (this.commands.length && this.args.length === 0 && !this._actionHandler && !this._defaultCommandName) {
      // probably missing subcommand and no handler, user needs help (and exit)
      this.help({ error: true });
    }

    outputHelpIfRequested(this, parsed.unknown);
    this._checkForMissingMandatoryOptions();
    this._checkForConflictingOptions();

    // We do not always call this check to avoid masking a "better" error, like unknown command.
    const checkForUnknownOptions = () => {
      if (parsed.unknown.length > 0) {
        this.unknownOption(parsed.unknown[0]);
      }
    };

    const commandEvent = `command:${this.name()}`;
    if (this._actionHandler) {
      checkForUnknownOptions();
      this._processArguments();

      let actionResult;
      actionResult = this._chainOrCallHooks(actionResult, 'preAction');
      actionResult = this._chainOrCall(actionResult, () => this._actionHandler(this.processedArgs));
      if (this.parent) {
        actionResult = this._chainOrCall(actionResult, () => {
          this.parent.emit(commandEvent, operands, unknown); // legacy
        });
      }
      actionResult = this._chainOrCallHooks(actionResult, 'postAction');
      return actionResult;
    }
    if (this.parent && this.parent.listenerCount(commandEvent)) {
      checkForUnknownOptions();
      this._processArguments();
      this.parent.emit(commandEvent, operands, unknown); // legacy
    } else if (operands.length) {
      if (this._findCommand('*')) { // legacy default command
        return this._dispatchSubcommand('*', operands, unknown);
      }
      if (this.listenerCount('command:*')) {
        // skip option check, emit event for possible misspelling suggestion
        this.emit('command:*', operands, unknown);
      } else if (this.commands.length) {
        this.unknownCommand();
      } else {
        checkForUnknownOptions();
        this._processArguments();
      }
    } else if (this.commands.length) {
      checkForUnknownOptions();
      // This command has subcommands and nothing hooked up at this level, so display help (and exit).
      this.help({ error: true });
    } else {
      checkForUnknownOptions();
      this._processArguments();
      // fall through for caller to handle after calling .parse()
    }
  }

  /**
   * Find matching command.
   *
   * @api private
   */
  _findCommand(name) {
    if (!name) return undefined;
    return this.commands.find(cmd => cmd._name === name || cmd._aliases.includes(name));
  }

  /**
   * Return an option matching `arg` if any.
   *
   * @param {string} arg
   * @return {Option}
   * @api private
   */

  _findOption(arg) {
    return this.options.find(option => option.is(arg));
  }

  /**
   * Display an error message if a mandatory option does not have a value.
   * Called after checking for help flags in leaf subcommand.
   *
   * @api private
   */

  _checkForMissingMandatoryOptions() {
    // Walk up hierarchy so can call in subcommand after checking for displaying help.
    for (let cmd = this; cmd; cmd = cmd.parent) {
      cmd.options.forEach((anOption) => {
        if (anOption.mandatory && (cmd.getOptionValue(anOption.attributeName()) === undefined)) {
          cmd.missingMandatoryOptionValue(anOption);
        }
      });
    }
  }

  /**
   * Display an error message if conflicting options are used together in this.
   *
   * @api private
   */
  _checkForConflictingLocalOptions() {
    const definedNonDefaultOptions = this.options.filter(
      (option) => {
        const optionKey = option.attributeName();
        if (this.getOptionValue(optionKey) === undefined) {
          return false;
        }
        return this.getOptionValueSource(optionKey) !== 'default';
      }
    );

    const optionsWithConflicting = definedNonDefaultOptions.filter(
      (option) => option.conflictsWith.length > 0
    );

    optionsWithConflicting.forEach((option) => {
      const conflictingAndDefined = definedNonDefaultOptions.find((defined) =>
        option.conflictsWith.includes(defined.attributeName())
      );
      if (conflictingAndDefined) {
        this._conflictingOption(option, conflictingAndDefined);
      }
    });
  }

  /**
   * Display an error message if conflicting options are used together.
   * Called after checking for help flags in leaf subcommand.
   *
   * @api private
   */
  _checkForConflictingOptions() {
    // Walk up hierarchy so can call in subcommand after checking for displaying help.
    for (let cmd = this; cmd; cmd = cmd.parent) {
      cmd._checkForConflictingLocalOptions();
    }
  }

  /**
   * Parse options from `argv` removing known options,
   * and return argv split into operands and unknown arguments.
   *
   * Examples:
   *
   *     argv => operands, unknown
   *     --known kkk op => [op], []
   *     op --known kkk => [op], []
   *     sub --unknown uuu op => [sub], [--unknown uuu op]
   *     sub -- --unknown uuu op => [sub --unknown uuu op], []
   *
   * @param {String[]} argv
   * @return {{operands: String[], unknown: String[]}}
   */

  parseOptions(argv) {
    const operands = []; // operands, not options or values
    const unknown = []; // first unknown option and remaining unknown args
    let dest = operands;
    const args = argv.slice();

    function maybeOption(arg) {
      return arg.length > 1 && arg[0] === '-';
    }

    // parse options
    let activeVariadicOption = null;
    while (args.length) {
      const arg = args.shift();

      // literal
      if (arg === '--') {
        if (dest === unknown) dest.push(arg);
        dest.push(...args);
        break;
      }

      if (activeVariadicOption && !maybeOption(arg)) {
        this.emit(`option:${activeVariadicOption.name()}`, arg);
        continue;
      }
      activeVariadicOption = null;

      if (maybeOption(arg)) {
        const option = this._findOption(arg);
        // recognised option, call listener to assign value with possible custom processing
        if (option) {
          if (option.required) {
            const value = args.shift();
            if (value === undefined) this.optionMissingArgument(option);
            this.emit(`option:${option.name()}`, value);
          } else if (option.optional) {
            let value = null;
            // historical behaviour is optional value is following arg unless an option
            if (args.length > 0 && !maybeOption(args[0])) {
              value = args.shift();
            }
            this.emit(`option:${option.name()}`, value);
          } else { // boolean flag
            this.emit(`option:${option.name()}`);
          }
          activeVariadicOption = option.variadic ? option : null;
          continue;
        }
      }

      // Look for combo options following single dash, eat first one if known.
      if (arg.length > 2 && arg[0] === '-' && arg[1] !== '-') {
        const option = this._findOption(`-${arg[1]}`);
        if (option) {
          if (option.required || (option.optional && this._combineFlagAndOptionalValue)) {
            // option with value following in same argument
            this.emit(`option:${option.name()}`, arg.slice(2));
          } else {
            // boolean option, emit and put back remainder of arg for further processing
            this.emit(`option:${option.name()}`);
            args.unshift(`-${arg.slice(2)}`);
          }
          continue;
        }
      }

      // Look for known long flag with value, like --foo=bar
      if (/^--[^=]+=/.test(arg)) {
        const index = arg.indexOf('=');
        const option = this._findOption(arg.slice(0, index));
        if (option && (option.required || option.optional)) {
          this.emit(`option:${option.name()}`, arg.slice(index + 1));
          continue;
        }
      }

      // Not a recognised option by this command.
      // Might be a command-argument, or subcommand option, or unknown option, or help command or option.

      // An unknown option means further arguments also classified as unknown so can be reprocessed by subcommands.
      if (maybeOption(arg)) {
        dest = unknown;
      }

      // If using positionalOptions, stop processing our options at subcommand.
      if ((this._enablePositionalOptions || this._passThroughOptions) && operands.length === 0 && unknown.length === 0) {
        if (this._findCommand(arg)) {
          operands.push(arg);
          if (args.length > 0) unknown.push(...args);
          break;
        } else if (arg === this._helpCommandName && this._hasImplicitHelpCommand()) {
          operands.push(arg);
          if (args.length > 0) operands.push(...args);
          break;
        } else if (this._defaultCommandName) {
          unknown.push(arg);
          if (args.length > 0) unknown.push(...args);
          break;
        }
      }

      // If using passThroughOptions, stop processing options at first command-argument.
      if (this._passThroughOptions) {
        dest.push(arg);
        if (args.length > 0) dest.push(...args);
        break;
      }

      // add arg
      dest.push(arg);
    }

    return { operands, unknown };
  }

  /**
   * Return an object containing local option values as key-value pairs.
   *
   * @return {Object}
   */
  opts() {
    if (this._storeOptionsAsProperties) {
      // Preserve original behaviour so backwards compatible when still using properties
      const result = {};
      const len = this.options.length;

      for (let i = 0; i < len; i++) {
        const key = this.options[i].attributeName();
        result[key] = key === this._versionOptionName ? this._version : this[key];
      }
      return result;
    }

    return this._optionValues;
  }

  /**
   * Return an object containing merged local and global option values as key-value pairs.
   *
   * @return {Object}
   */
  optsWithGlobals() {
    // globals overwrite locals
    return getCommandAndParents(this).reduce(
      (combinedOptions, cmd) => Object.assign(combinedOptions, cmd.opts()),
      {}
    );
  }

  /**
   * Display error message and exit (or call exitOverride).
   *
   * @param {string} message
   * @param {Object} [errorOptions]
   * @param {string} [errorOptions.code] - an id string representing the error
   * @param {number} [errorOptions.exitCode] - used with process.exit
   */
  error(message, errorOptions) {
    // output handling
    this._outputConfiguration.outputError(`${message}\n`, this._outputConfiguration.writeErr);
    if (typeof this._showHelpAfterError === 'string') {
      this._outputConfiguration.writeErr(`${this._showHelpAfterError}\n`);
    } else if (this._showHelpAfterError) {
      this._outputConfiguration.writeErr('\n');
      this.outputHelp({ error: true });
    }

    // exit handling
    const config = errorOptions || {};
    const exitCode = config.exitCode || 1;
    const code = config.code || 'commander.error';
    this._exit(exitCode, code, message);
  }

  /**
   * Apply any option related environment variables, if option does
   * not have a value from cli or client code.
   *
   * @api private
   */
  _parseOptionsEnv() {
    this.options.forEach((option) => {
      if (option.envVar && option.envVar in process.env) {
        const optionKey = option.attributeName();
        // Priority check. Do not overwrite cli or options from unknown source (client-code).
        if (this.getOptionValue(optionKey) === undefined || ['default', 'config', 'env'].includes(this.getOptionValueSource(optionKey))) {
          if (option.required || option.optional) { // option can take a value
            // keep very simple, optional always takes value
            this.emit(`optionEnv:${option.name()}`, process.env[option.envVar]);
          } else { // boolean
            // keep very simple, only care that envVar defined and not the value
            this.emit(`optionEnv:${option.name()}`);
          }
        }
      }
    });
  }

  /**
   * Apply any implied option values, if option is undefined or default value.
   *
   * @api private
   */
  _parseOptionsImplied() {
    const dualHelper = new DualOptions(this.options);
    const hasCustomOptionValue = (optionKey) => {
      return this.getOptionValue(optionKey) !== undefined && !['default', 'implied'].includes(this.getOptionValueSource(optionKey));
    };
    this.options
      .filter(option => (option.implied !== undefined) &&
        hasCustomOptionValue(option.attributeName()) &&
        dualHelper.valueFromOption(this.getOptionValue(option.attributeName()), option))
      .forEach((option) => {
        Object.keys(option.implied)
          .filter(impliedKey => !hasCustomOptionValue(impliedKey))
          .forEach(impliedKey => {
            this.setOptionValueWithSource(impliedKey, option.implied[impliedKey], 'implied');
          });
      });
  }

  /**
   * Argument `name` is missing.
   *
   * @param {string} name
   * @api private
   */

  missingArgument(name) {
    const message = `error: missing required argument '${name}'`;
    this.error(message, { code: 'commander.missingArgument' });
  }

  /**
   * `Option` is missing an argument.
   *
   * @param {Option} option
   * @api private
   */

  optionMissingArgument(option) {
    const message = `error: option '${option.flags}' argument missing`;
    this.error(message, { code: 'commander.optionMissingArgument' });
  }

  /**
   * `Option` does not have a value, and is a mandatory option.
   *
   * @param {Option} option
   * @api private
   */

  missingMandatoryOptionValue(option) {
    const message = `error: required option '${option.flags}' not specified`;
    this.error(message, { code: 'commander.missingMandatoryOptionValue' });
  }

  /**
   * `Option` conflicts with another option.
   *
   * @param {Option} option
   * @param {Option} conflictingOption
   * @api private
   */
  _conflictingOption(option, conflictingOption) {
    // The calling code does not know whether a negated option is the source of the
    // value, so do some work to take an educated guess.
    const findBestOptionFromValue = (option) => {
      const optionKey = option.attributeName();
      const optionValue = this.getOptionValue(optionKey);
      const negativeOption = this.options.find(target => target.negate && optionKey === target.attributeName());
      const positiveOption = this.options.find(target => !target.negate && optionKey === target.attributeName());
      if (negativeOption && (
        (negativeOption.presetArg === undefined && optionValue === false) ||
        (negativeOption.presetArg !== undefined && optionValue === negativeOption.presetArg)
      )) {
        return negativeOption;
      }
      return positiveOption || option;
    };

    const getErrorMessage = (option) => {
      const bestOption = findBestOptionFromValue(option);
      const optionKey = bestOption.attributeName();
      const source = this.getOptionValueSource(optionKey);
      if (source === 'env') {
        return `environment variable '${bestOption.envVar}'`;
      }
      return `option '${bestOption.flags}'`;
    };

    const message = `error: ${getErrorMessage(option)} cannot be used with ${getErrorMessage(conflictingOption)}`;
    this.error(message, { code: 'commander.conflictingOption' });
  }

  /**
   * Unknown option `flag`.
   *
   * @param {string} flag
   * @api private
   */

  unknownOption(flag) {
    if (this._allowUnknownOption) return;
    let suggestion = '';

    if (flag.startsWith('--') && this._showSuggestionAfterError) {
      // Looping to pick up the global options too
      let candidateFlags = [];
      let command = this;
      do {
        const moreFlags = command.createHelp().visibleOptions(command)
          .filter(option => option.long)
          .map(option => option.long);
        candidateFlags = candidateFlags.concat(moreFlags);
        command = command.parent;
      } while (command && !command._enablePositionalOptions);
      suggestion = suggestSimilar(flag, candidateFlags);
    }

    const message = `error: unknown option '${flag}'${suggestion}`;
    this.error(message, { code: 'commander.unknownOption' });
  }

  /**
   * Excess arguments, more than expected.
   *
   * @param {string[]} receivedArgs
   * @api private
   */

  _excessArguments(receivedArgs) {
    if (this._allowExcessArguments) return;

    const expected = this._args.length;
    const s = (expected === 1) ? '' : 's';
    const forSubcommand = this.parent ? ` for '${this.name()}'` : '';
    const message = `error: too many arguments${forSubcommand}. Expected ${expected} argument${s} but got ${receivedArgs.length}.`;
    this.error(message, { code: 'commander.excessArguments' });
  }

  /**
   * Unknown command.
   *
   * @api private
   */

  unknownCommand() {
    const unknownName = this.args[0];
    let suggestion = '';

    if (this._showSuggestionAfterError) {
      const candidateNames = [];
      this.createHelp().visibleCommands(this).forEach((command) => {
        candidateNames.push(command.name());
        // just visible alias
        if (command.alias()) candidateNames.push(command.alias());
      });
      suggestion = suggestSimilar(unknownName, candidateNames);
    }

    const message = `error: unknown command '${unknownName}'${suggestion}`;
    this.error(message, { code: 'commander.unknownCommand' });
  }

  /**
   * Set the program version to `str`.
   *
   * This method auto-registers the "-V, --version" flag
   * which will print the version number when passed.
   *
   * You can optionally supply the  flags and description to override the defaults.
   *
   * @param {string} str
   * @param {string} [flags]
   * @param {string} [description]
   * @return {this | string} `this` command for chaining, or version string if no arguments
   */

  version(str, flags, description) {
    if (str === undefined) return this._version;
    this._version = str;
    flags = flags || '-V, --version';
    description = description || 'output the version number';
    const versionOption = this.createOption(flags, description);
    this._versionOptionName = versionOption.attributeName();
    this.options.push(versionOption);
    this.on('option:' + versionOption.name(), () => {
      this._outputConfiguration.writeOut(`${str}\n`);
      this._exit(0, 'commander.version', str);
    });
    return this;
  }

  /**
   * Set the description.
   *
   * @param {string} [str]
   * @param {Object} [argsDescription]
   * @return {string|Command}
   */
  description(str, argsDescription) {
    if (str === undefined && argsDescription === undefined) return this._description;
    this._description = str;
    if (argsDescription) {
      this._argsDescription = argsDescription;
    }
    return this;
  }

  /**
   * Set the summary. Used when listed as subcommand of parent.
   *
   * @param {string} [str]
   * @return {string|Command}
   */
  summary(str) {
    if (str === undefined) return this._summary;
    this._summary = str;
    return this;
  }

  /**
   * Set an alias for the command.
   *
   * You may call more than once to add multiple aliases. Only the first alias is shown in the auto-generated help.
   *
   * @param {string} [alias]
   * @return {string|Command}
   */

  alias(alias) {
    if (alias === undefined) return this._aliases[0]; // just return first, for backwards compatibility

    /** @type {Command} */
    let command = this;
    if (this.commands.length !== 0 && this.commands[this.commands.length - 1]._executableHandler) {
      // assume adding alias for last added executable subcommand, rather than this
      command = this.commands[this.commands.length - 1];
    }

    if (alias === command._name) throw new Error('Command alias can\'t be the same as its name');

    command._aliases.push(alias);
    return this;
  }

  /**
   * Set aliases for the command.
   *
   * Only the first alias is shown in the auto-generated help.
   *
   * @param {string[]} [aliases]
   * @return {string[]|Command}
   */

  aliases(aliases) {
    // Getter for the array of aliases is the main reason for having aliases() in addition to alias().
    if (aliases === undefined) return this._aliases;

    aliases.forEach((alias) => this.alias(alias));
    return this;
  }

  /**
   * Set / get the command usage `str`.
   *
   * @param {string} [str]
   * @return {String|Command}
   */

  usage(str) {
    if (str === undefined) {
      if (this._usage) return this._usage;

      const args = this._args.map((arg) => {
        return humanReadableArgName(arg);
      });
      return [].concat(
        (this.options.length || this._hasHelpOption ? '[options]' : []),
        (this.commands.length ? '[command]' : []),
        (this._args.length ? args : [])
      ).join(' ');
    }

    this._usage = str;
    return this;
  }

  /**
   * Get or set the name of the command.
   *
   * @param {string} [str]
   * @return {string|Command}
   */

  name(str) {
    if (str === undefined) return this._name;
    this._name = str;
    return this;
  }

  /**
   * Set the name of the command from script filename, such as process.argv[1],
   * or require.main.filename, or __filename.
   *
   * (Used internally and public although not documented in README.)
   *
   * @example
   * program.nameFromFilename(require.main.filename);
   *
   * @param {string} filename
   * @return {Command}
   */

  nameFromFilename(filename) {
    this._name = path.basename(filename, path.extname(filename));

    return this;
  }

  /**
   * Get or set the directory for searching for executable subcommands of this command.
   *
   * @example
   * program.executableDir(__dirname);
   * // or
   * program.executableDir('subcommands');
   *
   * @param {string} [path]
   * @return {string|Command}
   */

  executableDir(path) {
    if (path === undefined) return this._executableDir;
    this._executableDir = path;
    return this;
  }

  /**
   * Return program help documentation.
   *
   * @param {{ error: boolean }} [contextOptions] - pass {error:true} to wrap for stderr instead of stdout
   * @return {string}
   */

  helpInformation(contextOptions) {
    const helper = this.createHelp();
    if (helper.helpWidth === undefined) {
      helper.helpWidth = (contextOptions && contextOptions.error) ? this._outputConfiguration.getErrHelpWidth() : this._outputConfiguration.getOutHelpWidth();
    }
    return helper.formatHelp(this, helper);
  }

  /**
   * @api private
   */

  _getHelpContext(contextOptions) {
    contextOptions = contextOptions || {};
    const context = { error: !!contextOptions.error };
    let write;
    if (context.error) {
      write = (arg) => this._outputConfiguration.writeErr(arg);
    } else {
      write = (arg) => this._outputConfiguration.writeOut(arg);
    }
    context.write = contextOptions.write || write;
    context.command = this;
    return context;
  }

  /**
   * Output help information for this command.
   *
   * Outputs built-in help, and custom text added using `.addHelpText()`.
   *
   * @param {{ error: boolean } | Function} [contextOptions] - pass {error:true} to write to stderr instead of stdout
   */

  outputHelp(contextOptions) {
    let deprecatedCallback;
    if (typeof contextOptions === 'function') {
      deprecatedCallback = contextOptions;
      contextOptions = undefined;
    }
    const context = this._getHelpContext(contextOptions);

    getCommandAndParents(this).reverse().forEach(command => command.emit('beforeAllHelp', context));
    this.emit('beforeHelp', context);

    let helpInformation = this.helpInformation(context);
    if (deprecatedCallback) {
      helpInformation = deprecatedCallback(helpInformation);
      if (typeof helpInformation !== 'string' && !Buffer.isBuffer(helpInformation)) {
        throw new Error('outputHelp callback must return a string or a Buffer');
      }
    }
    context.write(helpInformation);

    this.emit(this._helpLongFlag); // deprecated
    this.emit('afterHelp', context);
    getCommandAndParents(this).forEach(command => command.emit('afterAllHelp', context));
  }

  /**
   * You can pass in flags and a description to override the help
   * flags and help description for your command. Pass in false to
   * disable the built-in help option.
   *
   * @param {string | boolean} [flags]
   * @param {string} [description]
   * @return {Command} `this` command for chaining
   */

  helpOption(flags, description) {
    if (typeof flags === 'boolean') {
      this._hasHelpOption = flags;
      return this;
    }
    this._helpFlags = flags || this._helpFlags;
    this._helpDescription = description || this._helpDescription;

    const helpFlags = splitOptionFlags(this._helpFlags);
    this._helpShortFlag = helpFlags.shortFlag;
    this._helpLongFlag = helpFlags.longFlag;

    return this;
  }

  /**
   * Output help information and exit.
   *
   * Outputs built-in help, and custom text added using `.addHelpText()`.
   *
   * @param {{ error: boolean }} [contextOptions] - pass {error:true} to write to stderr instead of stdout
   */

  help(contextOptions) {
    this.outputHelp(contextOptions);
    let exitCode = process.exitCode || 0;
    if (exitCode === 0 && contextOptions && typeof contextOptions !== 'function' && contextOptions.error) {
      exitCode = 1;
    }
    // message: do not have all displayed text available so only passing placeholder.
    this._exit(exitCode, 'commander.help', '(outputHelp)');
  }

  /**
   * Add additional text to be displayed with the built-in help.
   *
   * Position is 'before' or 'after' to affect just this command,
   * and 'beforeAll' or 'afterAll' to affect this command and all its subcommands.
   *
   * @param {string} position - before or after built-in help
   * @param {string | Function} text - string to add, or a function returning a string
   * @return {Command} `this` command for chaining
   */
  addHelpText(position, text) {
    const allowedValues = ['beforeAll', 'before', 'after', 'afterAll'];
    if (!allowedValues.includes(position)) {
      throw new Error(`Unexpected value for position to addHelpText.
Expecting one of '${allowedValues.join("', '")}'`);
    }
    const helpEvent = `${position}Help`;
    this.on(helpEvent, (context) => {
      let helpStr;
      if (typeof text === 'function') {
        helpStr = text({ error: context.error, command: context.command });
      } else {
        helpStr = text;
      }
      // Ignore falsy value when nothing to output.
      if (helpStr) {
        context.write(`${helpStr}\n`);
      }
    });
    return this;
  }
}

/**
 * Output help information if help flags specified
 *
 * @param {Command} cmd - command to output help for
 * @param {Array} args - array of options to search for help flags
 * @api private
 */

function outputHelpIfRequested(cmd, args) {
  const helpOption = cmd._hasHelpOption && args.find(arg => arg === cmd._helpLongFlag || arg === cmd._helpShortFlag);
  if (helpOption) {
    cmd.outputHelp();
    // (Do not have all displayed text available so only passing placeholder.)
    cmd._exit(0, 'commander.helpDisplayed', '(outputHelp)');
  }
}

/**
 * Scan arguments and increment port number for inspect calls (to avoid conflicts when spawning new command).
 *
 * @param {string[]} args - array of arguments from node.execArgv
 * @returns {string[]}
 * @api private
 */

function incrementNodeInspectorPort(args) {
  // Testing for these options:
  //  --inspect[=[host:]port]
  //  --inspect-brk[=[host:]port]
  //  --inspect-port=[host:]port
  return args.map((arg) => {
    if (!arg.startsWith('--inspect')) {
      return arg;
    }
    let debugOption;
    let debugHost = '127.0.0.1';
    let debugPort = '9229';
    let match;
    if ((match = arg.match(/^(--inspect(-brk)?)$/)) !== null) {
      // e.g. --inspect
      debugOption = match[1];
    } else if ((match = arg.match(/^(--inspect(-brk|-port)?)=([^:]+)$/)) !== null) {
      debugOption = match[1];
      if (/^\d+$/.test(match[3])) {
        // e.g. --inspect=1234
        debugPort = match[3];
      } else {
        // e.g. --inspect=localhost
        debugHost = match[3];
      }
    } else if ((match = arg.match(/^(--inspect(-brk|-port)?)=([^:]+):(\d+)$/)) !== null) {
      // e.g. --inspect=localhost:1234
      debugOption = match[1];
      debugHost = match[3];
      debugPort = match[4];
    }

    if (debugOption && debugPort !== '0') {
      return `${debugOption}=${debugHost}:${parseInt(debugPort) + 1}`;
    }
    return arg;
  });
}

/**
 * @param {Command} startCommand
 * @returns {Command[]}
 * @api private
 */

function getCommandAndParents(startCommand) {
  const result = [];
  for (let command = startCommand; command; command = command.parent) {
    result.push(command);
  }
  return result;
}

exports.Command = Command;


/***/ }),

/***/ "../../node_modules/commander/lib/error.js":
/*!*************************************************!*\
  !*** ../../node_modules/commander/lib/error.js ***!
  \*************************************************/
/***/ ((__unused_webpack_module, exports) => {

// @ts-check

/**
 * CommanderError class
 * @class
 */
class CommanderError extends Error {
  /**
   * Constructs the CommanderError class
   * @param {number} exitCode suggested exit code which could be used with process.exit
   * @param {string} code an id string representing the error
   * @param {string} message human-readable description of the error
   * @constructor
   */
  constructor(exitCode, code, message) {
    super(message);
    // properly capture stack trace in Node.js
    Error.captureStackTrace(this, this.constructor);
    this.name = this.constructor.name;
    this.code = code;
    this.exitCode = exitCode;
    this.nestedError = undefined;
  }
}

/**
 * InvalidArgumentError class
 * @class
 */
class InvalidArgumentError extends CommanderError {
  /**
   * Constructs the InvalidArgumentError class
   * @param {string} [message] explanation of why argument is invalid
   * @constructor
   */
  constructor(message) {
    super(1, 'commander.invalidArgument', message);
    // properly capture stack trace in Node.js
    Error.captureStackTrace(this, this.constructor);
    this.name = this.constructor.name;
  }
}

exports.CommanderError = CommanderError;
exports.InvalidArgumentError = InvalidArgumentError;


/***/ }),

/***/ "../../node_modules/commander/lib/help.js":
/*!************************************************!*\
  !*** ../../node_modules/commander/lib/help.js ***!
  \************************************************/
/***/ ((__unused_webpack_module, exports, __webpack_require__) => {

const { humanReadableArgName } = __webpack_require__(/*! ./argument.js */ "../../node_modules/commander/lib/argument.js");

/**
 * TypeScript import types for JSDoc, used by Visual Studio Code IntelliSense and `npm run typescript-checkJS`
 * https://www.typescriptlang.org/docs/handbook/jsdoc-supported-types.html#import-types
 * @typedef { import("./argument.js").Argument } Argument
 * @typedef { import("./command.js").Command } Command
 * @typedef { import("./option.js").Option } Option
 */

// @ts-check

// Although this is a class, methods are static in style to allow override using subclass or just functions.
class Help {
  constructor() {
    this.helpWidth = undefined;
    this.sortSubcommands = false;
    this.sortOptions = false;
    this.showGlobalOptions = false;
  }

  /**
   * Get an array of the visible subcommands. Includes a placeholder for the implicit help command, if there is one.
   *
   * @param {Command} cmd
   * @returns {Command[]}
   */

  visibleCommands(cmd) {
    const visibleCommands = cmd.commands.filter(cmd => !cmd._hidden);
    if (cmd._hasImplicitHelpCommand()) {
      // Create a command matching the implicit help command.
      const [, helpName, helpArgs] = cmd._helpCommandnameAndArgs.match(/([^ ]+) *(.*)/);
      const helpCommand = cmd.createCommand(helpName)
        .helpOption(false);
      helpCommand.description(cmd._helpCommandDescription);
      if (helpArgs) helpCommand.arguments(helpArgs);
      visibleCommands.push(helpCommand);
    }
    if (this.sortSubcommands) {
      visibleCommands.sort((a, b) => {
        // @ts-ignore: overloaded return type
        return a.name().localeCompare(b.name());
      });
    }
    return visibleCommands;
  }

  /**
   * Compare options for sort.
   *
   * @param {Option} a
   * @param {Option} b
   * @returns number
   */
  compareOptions(a, b) {
    const getSortKey = (option) => {
      // WYSIWYG for order displayed in help. Short used for comparison if present. No special handling for negated.
      return option.short ? option.short.replace(/^-/, '') : option.long.replace(/^--/, '');
    };
    return getSortKey(a).localeCompare(getSortKey(b));
  }

  /**
   * Get an array of the visible options. Includes a placeholder for the implicit help option, if there is one.
   *
   * @param {Command} cmd
   * @returns {Option[]}
   */

  visibleOptions(cmd) {
    const visibleOptions = cmd.options.filter((option) => !option.hidden);
    // Implicit help
    const showShortHelpFlag = cmd._hasHelpOption && cmd._helpShortFlag && !cmd._findOption(cmd._helpShortFlag);
    const showLongHelpFlag = cmd._hasHelpOption && !cmd._findOption(cmd._helpLongFlag);
    if (showShortHelpFlag || showLongHelpFlag) {
      let helpOption;
      if (!showShortHelpFlag) {
        helpOption = cmd.createOption(cmd._helpLongFlag, cmd._helpDescription);
      } else if (!showLongHelpFlag) {
        helpOption = cmd.createOption(cmd._helpShortFlag, cmd._helpDescription);
      } else {
        helpOption = cmd.createOption(cmd._helpFlags, cmd._helpDescription);
      }
      visibleOptions.push(helpOption);
    }
    if (this.sortOptions) {
      visibleOptions.sort(this.compareOptions);
    }
    return visibleOptions;
  }

  /**
   * Get an array of the visible global options. (Not including help.)
   *
   * @param {Command} cmd
   * @returns {Option[]}
   */

  visibleGlobalOptions(cmd) {
    if (!this.showGlobalOptions) return [];

    const globalOptions = [];
    for (let parentCmd = cmd.parent; parentCmd; parentCmd = parentCmd.parent) {
      const visibleOptions = parentCmd.options.filter((option) => !option.hidden);
      globalOptions.push(...visibleOptions);
    }
    if (this.sortOptions) {
      globalOptions.sort(this.compareOptions);
    }
    return globalOptions;
  }

  /**
   * Get an array of the arguments if any have a description.
   *
   * @param {Command} cmd
   * @returns {Argument[]}
   */

  visibleArguments(cmd) {
    // Side effect! Apply the legacy descriptions before the arguments are displayed.
    if (cmd._argsDescription) {
      cmd._args.forEach(argument => {
        argument.description = argument.description || cmd._argsDescription[argument.name()] || '';
      });
    }

    // If there are any arguments with a description then return all the arguments.
    if (cmd._args.find(argument => argument.description)) {
      return cmd._args;
    }
    return [];
  }

  /**
   * Get the command term to show in the list of subcommands.
   *
   * @param {Command} cmd
   * @returns {string}
   */

  subcommandTerm(cmd) {
    // Legacy. Ignores custom usage string, and nested commands.
    const args = cmd._args.map(arg => humanReadableArgName(arg)).join(' ');
    return cmd._name +
      (cmd._aliases[0] ? '|' + cmd._aliases[0] : '') +
      (cmd.options.length ? ' [options]' : '') + // simplistic check for non-help option
      (args ? ' ' + args : '');
  }

  /**
   * Get the option term to show in the list of options.
   *
   * @param {Option} option
   * @returns {string}
   */

  optionTerm(option) {
    return option.flags;
  }

  /**
   * Get the argument term to show in the list of arguments.
   *
   * @param {Argument} argument
   * @returns {string}
   */

  argumentTerm(argument) {
    return argument.name();
  }

  /**
   * Get the longest command term length.
   *
   * @param {Command} cmd
   * @param {Help} helper
   * @returns {number}
   */

  longestSubcommandTermLength(cmd, helper) {
    return helper.visibleCommands(cmd).reduce((max, command) => {
      return Math.max(max, helper.subcommandTerm(command).length);
    }, 0);
  }

  /**
   * Get the longest option term length.
   *
   * @param {Command} cmd
   * @param {Help} helper
   * @returns {number}
   */

  longestOptionTermLength(cmd, helper) {
    return helper.visibleOptions(cmd).reduce((max, option) => {
      return Math.max(max, helper.optionTerm(option).length);
    }, 0);
  }

  /**
   * Get the longest global option term length.
   *
   * @param {Command} cmd
   * @param {Help} helper
   * @returns {number}
   */

  longestGlobalOptionTermLength(cmd, helper) {
    return helper.visibleGlobalOptions(cmd).reduce((max, option) => {
      return Math.max(max, helper.optionTerm(option).length);
    }, 0);
  }

  /**
   * Get the longest argument term length.
   *
   * @param {Command} cmd
   * @param {Help} helper
   * @returns {number}
   */

  longestArgumentTermLength(cmd, helper) {
    return helper.visibleArguments(cmd).reduce((max, argument) => {
      return Math.max(max, helper.argumentTerm(argument).length);
    }, 0);
  }

  /**
   * Get the command usage to be displayed at the top of the built-in help.
   *
   * @param {Command} cmd
   * @returns {string}
   */

  commandUsage(cmd) {
    // Usage
    let cmdName = cmd._name;
    if (cmd._aliases[0]) {
      cmdName = cmdName + '|' + cmd._aliases[0];
    }
    let parentCmdNames = '';
    for (let parentCmd = cmd.parent; parentCmd; parentCmd = parentCmd.parent) {
      parentCmdNames = parentCmd.name() + ' ' + parentCmdNames;
    }
    return parentCmdNames + cmdName + ' ' + cmd.usage();
  }

  /**
   * Get the description for the command.
   *
   * @param {Command} cmd
   * @returns {string}
   */

  commandDescription(cmd) {
    // @ts-ignore: overloaded return type
    return cmd.description();
  }

  /**
   * Get the subcommand summary to show in the list of subcommands.
   * (Fallback to description for backwards compatibility.)
   *
   * @param {Command} cmd
   * @returns {string}
   */

  subcommandDescription(cmd) {
    // @ts-ignore: overloaded return type
    return cmd.summary() || cmd.description();
  }

  /**
   * Get the option description to show in the list of options.
   *
   * @param {Option} option
   * @return {string}
   */

  optionDescription(option) {
    const extraInfo = [];

    if (option.argChoices) {
      extraInfo.push(
        // use stringify to match the display of the default value
        `choices: ${option.argChoices.map((choice) => JSON.stringify(choice)).join(', ')}`);
    }
    if (option.defaultValue !== undefined) {
      // default for boolean and negated more for programmer than end user,
      // but show true/false for boolean option as may be for hand-rolled env or config processing.
      const showDefault = option.required || option.optional ||
        (option.isBoolean() && typeof option.defaultValue === 'boolean');
      if (showDefault) {
        extraInfo.push(`default: ${option.defaultValueDescription || JSON.stringify(option.defaultValue)}`);
      }
    }
    // preset for boolean and negated are more for programmer than end user
    if (option.presetArg !== undefined && option.optional) {
      extraInfo.push(`preset: ${JSON.stringify(option.presetArg)}`);
    }
    if (option.envVar !== undefined) {
      extraInfo.push(`env: ${option.envVar}`);
    }
    if (extraInfo.length > 0) {
      return `${option.description} (${extraInfo.join(', ')})`;
    }

    return option.description;
  }

  /**
   * Get the argument description to show in the list of arguments.
   *
   * @param {Argument} argument
   * @return {string}
   */

  argumentDescription(argument) {
    const extraInfo = [];
    if (argument.argChoices) {
      extraInfo.push(
        // use stringify to match the display of the default value
        `choices: ${argument.argChoices.map((choice) => JSON.stringify(choice)).join(', ')}`);
    }
    if (argument.defaultValue !== undefined) {
      extraInfo.push(`default: ${argument.defaultValueDescription || JSON.stringify(argument.defaultValue)}`);
    }
    if (extraInfo.length > 0) {
      const extraDescripton = `(${extraInfo.join(', ')})`;
      if (argument.description) {
        return `${argument.description} ${extraDescripton}`;
      }
      return extraDescripton;
    }
    return argument.description;
  }

  /**
   * Generate the built-in help text.
   *
   * @param {Command} cmd
   * @param {Help} helper
   * @returns {string}
   */

  formatHelp(cmd, helper) {
    const termWidth = helper.padWidth(cmd, helper);
    const helpWidth = helper.helpWidth || 80;
    const itemIndentWidth = 2;
    const itemSeparatorWidth = 2; // between term and description
    function formatItem(term, description) {
      if (description) {
        const fullText = `${term.padEnd(termWidth + itemSeparatorWidth)}${description}`;
        return helper.wrap(fullText, helpWidth - itemIndentWidth, termWidth + itemSeparatorWidth);
      }
      return term;
    }
    function formatList(textArray) {
      return textArray.join('\n').replace(/^/gm, ' '.repeat(itemIndentWidth));
    }

    // Usage
    let output = [`Usage: ${helper.commandUsage(cmd)}`, ''];

    // Description
    const commandDescription = helper.commandDescription(cmd);
    if (commandDescription.length > 0) {
      output = output.concat([helper.wrap(commandDescription, helpWidth, 0), '']);
    }

    // Arguments
    const argumentList = helper.visibleArguments(cmd).map((argument) => {
      return formatItem(helper.argumentTerm(argument), helper.argumentDescription(argument));
    });
    if (argumentList.length > 0) {
      output = output.concat(['Arguments:', formatList(argumentList), '']);
    }

    // Options
    const optionList = helper.visibleOptions(cmd).map((option) => {
      return formatItem(helper.optionTerm(option), helper.optionDescription(option));
    });
    if (optionList.length > 0) {
      output = output.concat(['Options:', formatList(optionList), '']);
    }

    if (this.showGlobalOptions) {
      const globalOptionList = helper.visibleGlobalOptions(cmd).map((option) => {
        return formatItem(helper.optionTerm(option), helper.optionDescription(option));
      });
      if (globalOptionList.length > 0) {
        output = output.concat(['Global Options:', formatList(globalOptionList), '']);
      }
    }

    // Commands
    const commandList = helper.visibleCommands(cmd).map((cmd) => {
      return formatItem(helper.subcommandTerm(cmd), helper.subcommandDescription(cmd));
    });
    if (commandList.length > 0) {
      output = output.concat(['Commands:', formatList(commandList), '']);
    }

    return output.join('\n');
  }

  /**
   * Calculate the pad width from the maximum term length.
   *
   * @param {Command} cmd
   * @param {Help} helper
   * @returns {number}
   */

  padWidth(cmd, helper) {
    return Math.max(
      helper.longestOptionTermLength(cmd, helper),
      helper.longestGlobalOptionTermLength(cmd, helper),
      helper.longestSubcommandTermLength(cmd, helper),
      helper.longestArgumentTermLength(cmd, helper)
    );
  }

  /**
   * Wrap the given string to width characters per line, with lines after the first indented.
   * Do not wrap if insufficient room for wrapping (minColumnWidth), or string is manually formatted.
   *
   * @param {string} str
   * @param {number} width
   * @param {number} indent
   * @param {number} [minColumnWidth=40]
   * @return {string}
   *
   */

  wrap(str, width, indent, minColumnWidth = 40) {
    // Full \s characters, minus the linefeeds.
    const indents = ' \\f\\t\\v\u00a0\u1680\u2000-\u200a\u202f\u205f\u3000\ufeff';
    // Detect manually wrapped and indented strings by searching for line break followed by spaces.
    const manualIndent = new RegExp(`[\\n][${indents}]+`);
    if (str.match(manualIndent)) return str;
    // Do not wrap if not enough room for a wrapped column of text (as could end up with a word per line).
    const columnWidth = width - indent;
    if (columnWidth < minColumnWidth) return str;

    const leadingStr = str.slice(0, indent);
    const columnText = str.slice(indent).replace('\r\n', '\n');
    const indentString = ' '.repeat(indent);
    const zeroWidthSpace = '\u200B';
    const breaks = `\\s${zeroWidthSpace}`;
    // Match line end (so empty lines don't collapse),
    // or as much text as will fit in column, or excess text up to first break.
    const regex = new RegExp(`\n|.{1,${columnWidth - 1}}([${breaks}]|$)|[^${breaks}]+?([${breaks}]|$)`, 'g');
    const lines = columnText.match(regex) || [];
    return leadingStr + lines.map((line, i) => {
      if (line === '\n') return ''; // preserve empty lines
      return ((i > 0) ? indentString : '') + line.trimEnd();
    }).join('\n');
  }
}

exports.Help = Help;


/***/ }),

/***/ "../../node_modules/commander/lib/option.js":
/*!**************************************************!*\
  !*** ../../node_modules/commander/lib/option.js ***!
  \**************************************************/
/***/ ((__unused_webpack_module, exports, __webpack_require__) => {

const { InvalidArgumentError } = __webpack_require__(/*! ./error.js */ "../../node_modules/commander/lib/error.js");

// @ts-check

class Option {
  /**
   * Initialize a new `Option` with the given `flags` and `description`.
   *
   * @param {string} flags
   * @param {string} [description]
   */

  constructor(flags, description) {
    this.flags = flags;
    this.description = description || '';

    this.required = flags.includes('<'); // A value must be supplied when the option is specified.
    this.optional = flags.includes('['); // A value is optional when the option is specified.
    // variadic test ignores <value,...> et al which might be used to describe custom splitting of single argument
    this.variadic = /\w\.\.\.[>\]]$/.test(flags); // The option can take multiple values.
    this.mandatory = false; // The option must have a value after parsing, which usually means it must be specified on command line.
    const optionFlags = splitOptionFlags(flags);
    this.short = optionFlags.shortFlag;
    this.long = optionFlags.longFlag;
    this.negate = false;
    if (this.long) {
      this.negate = this.long.startsWith('--no-');
    }
    this.defaultValue = undefined;
    this.defaultValueDescription = undefined;
    this.presetArg = undefined;
    this.envVar = undefined;
    this.parseArg = undefined;
    this.hidden = false;
    this.argChoices = undefined;
    this.conflictsWith = [];
    this.implied = undefined;
  }

  /**
   * Set the default value, and optionally supply the description to be displayed in the help.
   *
   * @param {any} value
   * @param {string} [description]
   * @return {Option}
   */

  default(value, description) {
    this.defaultValue = value;
    this.defaultValueDescription = description;
    return this;
  }

  /**
   * Preset to use when option used without option-argument, especially optional but also boolean and negated.
   * The custom processing (parseArg) is called.
   *
   * @example
   * new Option('--color').default('GREYSCALE').preset('RGB');
   * new Option('--donate [amount]').preset('20').argParser(parseFloat);
   *
   * @param {any} arg
   * @return {Option}
   */

  preset(arg) {
    this.presetArg = arg;
    return this;
  }

  /**
   * Add option name(s) that conflict with this option.
   * An error will be displayed if conflicting options are found during parsing.
   *
   * @example
   * new Option('--rgb').conflicts('cmyk');
   * new Option('--js').conflicts(['ts', 'jsx']);
   *
   * @param {string | string[]} names
   * @return {Option}
   */

  conflicts(names) {
    this.conflictsWith = this.conflictsWith.concat(names);
    return this;
  }

  /**
   * Specify implied option values for when this option is set and the implied options are not.
   *
   * The custom processing (parseArg) is not called on the implied values.
   *
   * @example
   * program
   *   .addOption(new Option('--log', 'write logging information to file'))
   *   .addOption(new Option('--trace', 'log extra details').implies({ log: 'trace.txt' }));
   *
   * @param {Object} impliedOptionValues
   * @return {Option}
   */
  implies(impliedOptionValues) {
    let newImplied = impliedOptionValues;
    if (typeof impliedOptionValues === 'string') {
      // string is not documented, but easy mistake and we can do what user probably intended.
      newImplied = { [impliedOptionValues]: true };
    }
    this.implied = Object.assign(this.implied || {}, newImplied);
    return this;
  }

  /**
   * Set environment variable to check for option value.
   *
   * An environment variable is only used if when processed the current option value is
   * undefined, or the source of the current value is 'default' or 'config' or 'env'.
   *
   * @param {string} name
   * @return {Option}
   */

  env(name) {
    this.envVar = name;
    return this;
  }

  /**
   * Set the custom handler for processing CLI option arguments into option values.
   *
   * @param {Function} [fn]
   * @return {Option}
   */

  argParser(fn) {
    this.parseArg = fn;
    return this;
  }

  /**
   * Whether the option is mandatory and must have a value after parsing.
   *
   * @param {boolean} [mandatory=true]
   * @return {Option}
   */

  makeOptionMandatory(mandatory = true) {
    this.mandatory = !!mandatory;
    return this;
  }

  /**
   * Hide option in help.
   *
   * @param {boolean} [hide=true]
   * @return {Option}
   */

  hideHelp(hide = true) {
    this.hidden = !!hide;
    return this;
  }

  /**
   * @api private
   */

  _concatValue(value, previous) {
    if (previous === this.defaultValue || !Array.isArray(previous)) {
      return [value];
    }

    return previous.concat(value);
  }

  /**
   * Only allow option value to be one of choices.
   *
   * @param {string[]} values
   * @return {Option}
   */

  choices(values) {
    this.argChoices = values.slice();
    this.parseArg = (arg, previous) => {
      if (!this.argChoices.includes(arg)) {
        throw new InvalidArgumentError(`Allowed choices are ${this.argChoices.join(', ')}.`);
      }
      if (this.variadic) {
        return this._concatValue(arg, previous);
      }
      return arg;
    };
    return this;
  }

  /**
   * Return option name.
   *
   * @return {string}
   */

  name() {
    if (this.long) {
      return this.long.replace(/^--/, '');
    }
    return this.short.replace(/^-/, '');
  }

  /**
   * Return option name, in a camelcase format that can be used
   * as a object attribute key.
   *
   * @return {string}
   * @api private
   */

  attributeName() {
    return camelcase(this.name().replace(/^no-/, ''));
  }

  /**
   * Check if `arg` matches the short or long flag.
   *
   * @param {string} arg
   * @return {boolean}
   * @api private
   */

  is(arg) {
    return this.short === arg || this.long === arg;
  }

  /**
   * Return whether a boolean option.
   *
   * Options are one of boolean, negated, required argument, or optional argument.
   *
   * @return {boolean}
   * @api private
   */

  isBoolean() {
    return !this.required && !this.optional && !this.negate;
  }
}

/**
 * This class is to make it easier to work with dual options, without changing the existing
 * implementation. We support separate dual options for separate positive and negative options,
 * like `--build` and `--no-build`, which share a single option value. This works nicely for some
 * use cases, but is tricky for others where we want separate behaviours despite
 * the single shared option value.
 */
class DualOptions {
  /**
   * @param {Option[]} options
   */
  constructor(options) {
    this.positiveOptions = new Map();
    this.negativeOptions = new Map();
    this.dualOptions = new Set();
    options.forEach(option => {
      if (option.negate) {
        this.negativeOptions.set(option.attributeName(), option);
      } else {
        this.positiveOptions.set(option.attributeName(), option);
      }
    });
    this.negativeOptions.forEach((value, key) => {
      if (this.positiveOptions.has(key)) {
        this.dualOptions.add(key);
      }
    });
  }

  /**
   * Did the value come from the option, and not from possible matching dual option?
   *
   * @param {any} value
   * @param {Option} option
   * @returns {boolean}
   */
  valueFromOption(value, option) {
    const optionKey = option.attributeName();
    if (!this.dualOptions.has(optionKey)) return true;

    // Use the value to deduce if (probably) came from the option.
    const preset = this.negativeOptions.get(optionKey).presetArg;
    const negativeValue = (preset !== undefined) ? preset : false;
    return option.negate === (negativeValue === value);
  }
}

/**
 * Convert string from kebab-case to camelCase.
 *
 * @param {string} str
 * @return {string}
 * @api private
 */

function camelcase(str) {
  return str.split('-').reduce((str, word) => {
    return str + word[0].toUpperCase() + word.slice(1);
  });
}

/**
 * Split the short and long flag out of something like '-m,--mixed <value>'
 *
 * @api private
 */

function splitOptionFlags(flags) {
  let shortFlag;
  let longFlag;
  // Use original very loose parsing to maintain backwards compatibility for now,
  // which allowed for example unintended `-sw, --short-word` [sic].
  const flagParts = flags.split(/[ |,]+/);
  if (flagParts.length > 1 && !/^[[<]/.test(flagParts[1])) shortFlag = flagParts.shift();
  longFlag = flagParts.shift();
  // Add support for lone short flag without significantly changing parsing!
  if (!shortFlag && /^-[^-]$/.test(longFlag)) {
    shortFlag = longFlag;
    longFlag = undefined;
  }
  return { shortFlag, longFlag };
}

exports.Option = Option;
exports.splitOptionFlags = splitOptionFlags;
exports.DualOptions = DualOptions;


/***/ }),

/***/ "../../node_modules/commander/lib/suggestSimilar.js":
/*!**********************************************************!*\
  !*** ../../node_modules/commander/lib/suggestSimilar.js ***!
  \**********************************************************/
/***/ ((__unused_webpack_module, exports) => {

const maxDistance = 3;

function editDistance(a, b) {
  // https://en.wikipedia.org/wiki/Damerau–Levenshtein_distance
  // Calculating optimal string alignment distance, no substring is edited more than once.
  // (Simple implementation.)

  // Quick early exit, return worst case.
  if (Math.abs(a.length - b.length) > maxDistance) return Math.max(a.length, b.length);

  // distance between prefix substrings of a and b
  const d = [];

  // pure deletions turn a into empty string
  for (let i = 0; i <= a.length; i++) {
    d[i] = [i];
  }
  // pure insertions turn empty string into b
  for (let j = 0; j <= b.length; j++) {
    d[0][j] = j;
  }

  // fill matrix
  for (let j = 1; j <= b.length; j++) {
    for (let i = 1; i <= a.length; i++) {
      let cost = 1;
      if (a[i - 1] === b[j - 1]) {
        cost = 0;
      } else {
        cost = 1;
      }
      d[i][j] = Math.min(
        d[i - 1][j] + 1, // deletion
        d[i][j - 1] + 1, // insertion
        d[i - 1][j - 1] + cost // substitution
      );
      // transposition
      if (i > 1 && j > 1 && a[i - 1] === b[j - 2] && a[i - 2] === b[j - 1]) {
        d[i][j] = Math.min(d[i][j], d[i - 2][j - 2] + 1);
      }
    }
  }

  return d[a.length][b.length];
}

/**
 * Find close matches, restricted to same number of edits.
 *
 * @param {string} word
 * @param {string[]} candidates
 * @returns {string}
 */

function suggestSimilar(word, candidates) {
  if (!candidates || candidates.length === 0) return '';
  // remove possible duplicates
  candidates = Array.from(new Set(candidates));

  const searchingOptions = word.startsWith('--');
  if (searchingOptions) {
    word = word.slice(2);
    candidates = candidates.map(candidate => candidate.slice(2));
  }

  let similar = [];
  let bestDistance = maxDistance;
  const minSimilarity = 0.4;
  candidates.forEach((candidate) => {
    if (candidate.length <= 1) return; // no one character guesses

    const distance = editDistance(word, candidate);
    const length = Math.max(word.length, candidate.length);
    const similarity = (length - distance) / length;
    if (similarity > minSimilarity) {
      if (distance < bestDistance) {
        // better edit distance, throw away previous worse matches
        bestDistance = distance;
        similar = [candidate];
      } else if (distance === bestDistance) {
        similar.push(candidate);
      }
    }
  });

  similar.sort((a, b) => a.localeCompare(b));
  if (searchingOptions) {
    similar = similar.map(candidate => `--${candidate}`);
  }

  if (similar.length > 1) {
    return `\n(Did you mean one of ${similar.join(', ')}?)`;
  }
  if (similar.length === 1) {
    return `\n(Did you mean ${similar[0]}?)`;
  }
  return '';
}

exports.suggestSimilar = suggestSimilar;


/***/ }),

/***/ "../../node_modules/minimatch/dist/commonjs/assert-valid-pattern.js":
/*!**************************************************************************!*\
  !*** ../../node_modules/minimatch/dist/commonjs/assert-valid-pattern.js ***!
  \**************************************************************************/
/***/ ((__unused_webpack_module, exports) => {

"use strict";

Object.defineProperty(exports, "__esModule", ({ value: true }));
exports.assertValidPattern = void 0;
const MAX_PATTERN_LENGTH = 1024 * 64;
const assertValidPattern = (pattern) => {
    if (typeof pattern !== 'string') {
        throw new TypeError('invalid pattern');
    }
    if (pattern.length > MAX_PATTERN_LENGTH) {
        throw new TypeError('pattern is too long');
    }
};
exports.assertValidPattern = assertValidPattern;
//# sourceMappingURL=assert-valid-pattern.js.map

/***/ }),

/***/ "../../node_modules/minimatch/dist/commonjs/ast.js":
/*!*********************************************************!*\
  !*** ../../node_modules/minimatch/dist/commonjs/ast.js ***!
  \*********************************************************/
/***/ ((__unused_webpack_module, exports, __webpack_require__) => {

"use strict";

// parse a single path portion
Object.defineProperty(exports, "__esModule", ({ value: true }));
exports.AST = void 0;
const brace_expressions_js_1 = __webpack_require__(/*! ./brace-expressions.js */ "../../node_modules/minimatch/dist/commonjs/brace-expressions.js");
const unescape_js_1 = __webpack_require__(/*! ./unescape.js */ "../../node_modules/minimatch/dist/commonjs/unescape.js");
const types = new Set(['!', '?', '+', '*', '@']);
const isExtglobType = (c) => types.has(c);
// Patterns that get prepended to bind to the start of either the
// entire string, or just a single path portion, to prevent dots
// and/or traversal patterns, when needed.
// Exts don't need the ^ or / bit, because the root binds that already.
const startNoTraversal = '(?!(?:^|/)\\.\\.?(?:$|/))';
const startNoDot = '(?!\\.)';
// characters that indicate a start of pattern needs the "no dots" bit,
// because a dot *might* be matched. ( is not in the list, because in
// the case of a child extglob, it will handle the prevention itself.
const addPatternStart = new Set(['[', '.']);
// cases where traversal is A-OK, no dot prevention needed
const justDots = new Set(['..', '.']);
const reSpecials = new Set('().*{}+?[]^$\\!');
const regExpEscape = (s) => s.replace(/[-[\]{}()*+?.,\\^$|#\s]/g, '\\$&');
// any single thing other than /
const qmark = '[^/]';
// * => any number of characters
const star = qmark + '*?';
// use + when we need to ensure that *something* matches, because the * is
// the only thing in the path portion.
const starNoEmpty = qmark + '+?';
// remove the \ chars that we added if we end up doing a nonmagic compare
// const deslash = (s: string) => s.replace(/\\(.)/g, '$1')
class AST {
    type;
    #root;
    #hasMagic;
    #uflag = false;
    #parts = [];
    #parent;
    #parentIndex;
    #negs;
    #filledNegs = false;
    #options;
    #toString;
    // set to true if it's an extglob with no children
    // (which really means one child of '')
    #emptyExt = false;
    constructor(type, parent, options = {}) {
        this.type = type;
        // extglobs are inherently magical
        if (type)
            this.#hasMagic = true;
        this.#parent = parent;
        this.#root = this.#parent ? this.#parent.#root : this;
        this.#options = this.#root === this ? options : this.#root.#options;
        this.#negs = this.#root === this ? [] : this.#root.#negs;
        if (type === '!' && !this.#root.#filledNegs)
            this.#negs.push(this);
        this.#parentIndex = this.#parent ? this.#parent.#parts.length : 0;
    }
    get hasMagic() {
        /* c8 ignore start */
        if (this.#hasMagic !== undefined)
            return this.#hasMagic;
        /* c8 ignore stop */
        for (const p of this.#parts) {
            if (typeof p === 'string')
                continue;
            if (p.type || p.hasMagic)
                return (this.#hasMagic = true);
        }
        // note: will be undefined until we generate the regexp src and find out
        return this.#hasMagic;
    }
    // reconstructs the pattern
    toString() {
        if (this.#toString !== undefined)
            return this.#toString;
        if (!this.type) {
            return (this.#toString = this.#parts.map(p => String(p)).join(''));
        }
        else {
            return (this.#toString =
                this.type + '(' + this.#parts.map(p => String(p)).join('|') + ')');
        }
    }
    #fillNegs() {
        /* c8 ignore start */
        if (this !== this.#root)
            throw new Error('should only call on root');
        if (this.#filledNegs)
            return this;
        /* c8 ignore stop */
        // call toString() once to fill this out
        this.toString();
        this.#filledNegs = true;
        let n;
        while ((n = this.#negs.pop())) {
            if (n.type !== '!')
                continue;
            // walk up the tree, appending everthing that comes AFTER parentIndex
            let p = n;
            let pp = p.#parent;
            while (pp) {
                for (let i = p.#parentIndex + 1; !pp.type && i < pp.#parts.length; i++) {
                    for (const part of n.#parts) {
                        /* c8 ignore start */
                        if (typeof part === 'string') {
                            throw new Error('string part in extglob AST??');
                        }
                        /* c8 ignore stop */
                        part.copyIn(pp.#parts[i]);
                    }
                }
                p = pp;
                pp = p.#parent;
            }
        }
        return this;
    }
    push(...parts) {
        for (const p of parts) {
            if (p === '')
                continue;
            /* c8 ignore start */
            if (typeof p !== 'string' && !(p instanceof AST && p.#parent === this)) {
                throw new Error('invalid part: ' + p);
            }
            /* c8 ignore stop */
            this.#parts.push(p);
        }
    }
    toJSON() {
        const ret = this.type === null
            ? this.#parts.slice().map(p => (typeof p === 'string' ? p : p.toJSON()))
            : [this.type, ...this.#parts.map(p => p.toJSON())];
        if (this.isStart() && !this.type)
            ret.unshift([]);
        if (this.isEnd() &&
            (this === this.#root ||
                (this.#root.#filledNegs && this.#parent?.type === '!'))) {
            ret.push({});
        }
        return ret;
    }
    isStart() {
        if (this.#root === this)
            return true;
        // if (this.type) return !!this.#parent?.isStart()
        if (!this.#parent?.isStart())
            return false;
        if (this.#parentIndex === 0)
            return true;
        // if everything AHEAD of this is a negation, then it's still the "start"
        const p = this.#parent;
        for (let i = 0; i < this.#parentIndex; i++) {
            const pp = p.#parts[i];
            if (!(pp instanceof AST && pp.type === '!')) {
                return false;
            }
        }
        return true;
    }
    isEnd() {
        if (this.#root === this)
            return true;
        if (this.#parent?.type === '!')
            return true;
        if (!this.#parent?.isEnd())
            return false;
        if (!this.type)
            return this.#parent?.isEnd();
        // if not root, it'll always have a parent
        /* c8 ignore start */
        const pl = this.#parent ? this.#parent.#parts.length : 0;
        /* c8 ignore stop */
        return this.#parentIndex === pl - 1;
    }
    copyIn(part) {
        if (typeof part === 'string')
            this.push(part);
        else
            this.push(part.clone(this));
    }
    clone(parent) {
        const c = new AST(this.type, parent);
        for (const p of this.#parts) {
            c.copyIn(p);
        }
        return c;
    }
    static #parseAST(str, ast, pos, opt) {
        let escaping = false;
        let inBrace = false;
        let braceStart = -1;
        let braceNeg = false;
        if (ast.type === null) {
            // outside of a extglob, append until we find a start
            let i = pos;
            let acc = '';
            while (i < str.length) {
                const c = str.charAt(i++);
                // still accumulate escapes at this point, but we do ignore
                // starts that are escaped
                if (escaping || c === '\\') {
                    escaping = !escaping;
                    acc += c;
                    continue;
                }
                if (inBrace) {
                    if (i === braceStart + 1) {
                        if (c === '^' || c === '!') {
                            braceNeg = true;
                        }
                    }
                    else if (c === ']' && !(i === braceStart + 2 && braceNeg)) {
                        inBrace = false;
                    }
                    acc += c;
                    continue;
                }
                else if (c === '[') {
                    inBrace = true;
                    braceStart = i;
                    braceNeg = false;
                    acc += c;
                    continue;
                }
                if (!opt.noext && isExtglobType(c) && str.charAt(i) === '(') {
                    ast.push(acc);
                    acc = '';
                    const ext = new AST(c, ast);
                    i = AST.#parseAST(str, ext, i, opt);
                    ast.push(ext);
                    continue;
                }
                acc += c;
            }
            ast.push(acc);
            return i;
        }
        // some kind of extglob, pos is at the (
        // find the next | or )
        let i = pos + 1;
        let part = new AST(null, ast);
        const parts = [];
        let acc = '';
        while (i < str.length) {
            const c = str.charAt(i++);
            // still accumulate escapes at this point, but we do ignore
            // starts that are escaped
            if (escaping || c === '\\') {
                escaping = !escaping;
                acc += c;
                continue;
            }
            if (inBrace) {
                if (i === braceStart + 1) {
                    if (c === '^' || c === '!') {
                        braceNeg = true;
                    }
                }
                else if (c === ']' && !(i === braceStart + 2 && braceNeg)) {
                    inBrace = false;
                }
                acc += c;
                continue;
            }
            else if (c === '[') {
                inBrace = true;
                braceStart = i;
                braceNeg = false;
                acc += c;
                continue;
            }
            if (isExtglobType(c) && str.charAt(i) === '(') {
                part.push(acc);
                acc = '';
                const ext = new AST(c, part);
                part.push(ext);
                i = AST.#parseAST(str, ext, i, opt);
                continue;
            }
            if (c === '|') {
                part.push(acc);
                acc = '';
                parts.push(part);
                part = new AST(null, ast);
                continue;
            }
            if (c === ')') {
                if (acc === '' && ast.#parts.length === 0) {
                    ast.#emptyExt = true;
                }
                part.push(acc);
                acc = '';
                ast.push(...parts, part);
                return i;
            }
            acc += c;
        }
        // unfinished extglob
        // if we got here, it was a malformed extglob! not an extglob, but
        // maybe something else in there.
        ast.type = null;
        ast.#hasMagic = undefined;
        ast.#parts = [str.substring(pos - 1)];
        return i;
    }
    static fromGlob(pattern, options = {}) {
        const ast = new AST(null, undefined, options);
        AST.#parseAST(pattern, ast, 0, options);
        return ast;
    }
    // returns the regular expression if there's magic, or the unescaped
    // string if not.
    toMMPattern() {
        // should only be called on root
        /* c8 ignore start */
        if (this !== this.#root)
            return this.#root.toMMPattern();
        /* c8 ignore stop */
        const glob = this.toString();
        const [re, body, hasMagic, uflag] = this.toRegExpSource();
        // if we're in nocase mode, and not nocaseMagicOnly, then we do
        // still need a regular expression if we have to case-insensitively
        // match capital/lowercase characters.
        const anyMagic = hasMagic ||
            this.#hasMagic ||
            (this.#options.nocase &&
                !this.#options.nocaseMagicOnly &&
                glob.toUpperCase() !== glob.toLowerCase());
        if (!anyMagic) {
            return body;
        }
        const flags = (this.#options.nocase ? 'i' : '') + (uflag ? 'u' : '');
        return Object.assign(new RegExp(`^${re}$`, flags), {
            _src: re,
            _glob: glob,
        });
    }
    get options() {
        return this.#options;
    }
    // returns the string match, the regexp source, whether there's magic
    // in the regexp (so a regular expression is required) and whether or
    // not the uflag is needed for the regular expression (for posix classes)
    // TODO: instead of injecting the start/end at this point, just return
    // the BODY of the regexp, along with the start/end portions suitable
    // for binding the start/end in either a joined full-path makeRe context
    // (where we bind to (^|/), or a standalone matchPart context (where
    // we bind to ^, and not /).  Otherwise slashes get duped!
    //
    // In part-matching mode, the start is:
    // - if not isStart: nothing
    // - if traversal possible, but not allowed: ^(?!\.\.?$)
    // - if dots allowed or not possible: ^
    // - if dots possible and not allowed: ^(?!\.)
    // end is:
    // - if not isEnd(): nothing
    // - else: $
    //
    // In full-path matching mode, we put the slash at the START of the
    // pattern, so start is:
    // - if first pattern: same as part-matching mode
    // - if not isStart(): nothing
    // - if traversal possible, but not allowed: /(?!\.\.?(?:$|/))
    // - if dots allowed or not possible: /
    // - if dots possible and not allowed: /(?!\.)
    // end is:
    // - if last pattern, same as part-matching mode
    // - else nothing
    //
    // Always put the (?:$|/) on negated tails, though, because that has to be
    // there to bind the end of the negated pattern portion, and it's easier to
    // just stick it in now rather than try to inject it later in the middle of
    // the pattern.
    //
    // We can just always return the same end, and leave it up to the caller
    // to know whether it's going to be used joined or in parts.
    // And, if the start is adjusted slightly, can do the same there:
    // - if not isStart: nothing
    // - if traversal possible, but not allowed: (?:/|^)(?!\.\.?$)
    // - if dots allowed or not possible: (?:/|^)
    // - if dots possible and not allowed: (?:/|^)(?!\.)
    //
    // But it's better to have a simpler binding without a conditional, for
    // performance, so probably better to return both start options.
    //
    // Then the caller just ignores the end if it's not the first pattern,
    // and the start always gets applied.
    //
    // But that's always going to be $ if it's the ending pattern, or nothing,
    // so the caller can just attach $ at the end of the pattern when building.
    //
    // So the todo is:
    // - better detect what kind of start is needed
    // - return both flavors of starting pattern
    // - attach $ at the end of the pattern when creating the actual RegExp
    //
    // Ah, but wait, no, that all only applies to the root when the first pattern
    // is not an extglob. If the first pattern IS an extglob, then we need all
    // that dot prevention biz to live in the extglob portions, because eg
    // +(*|.x*) can match .xy but not .yx.
    //
    // So, return the two flavors if it's #root and the first child is not an
    // AST, otherwise leave it to the child AST to handle it, and there,
    // use the (?:^|/) style of start binding.
    //
    // Even simplified further:
    // - Since the start for a join is eg /(?!\.) and the start for a part
    // is ^(?!\.), we can just prepend (?!\.) to the pattern (either root
    // or start or whatever) and prepend ^ or / at the Regexp construction.
    toRegExpSource(allowDot) {
        const dot = allowDot ?? !!this.#options.dot;
        if (this.#root === this)
            this.#fillNegs();
        if (!this.type) {
            const noEmpty = this.isStart() && this.isEnd();
            const src = this.#parts
                .map(p => {
                const [re, _, hasMagic, uflag] = typeof p === 'string'
                    ? AST.#parseGlob(p, this.#hasMagic, noEmpty)
                    : p.toRegExpSource(allowDot);
                this.#hasMagic = this.#hasMagic || hasMagic;
                this.#uflag = this.#uflag || uflag;
                return re;
            })
                .join('');
            let start = '';
            if (this.isStart()) {
                if (typeof this.#parts[0] === 'string') {
                    // this is the string that will match the start of the pattern,
                    // so we need to protect against dots and such.
                    // '.' and '..' cannot match unless the pattern is that exactly,
                    // even if it starts with . or dot:true is set.
                    const dotTravAllowed = this.#parts.length === 1 && justDots.has(this.#parts[0]);
                    if (!dotTravAllowed) {
                        const aps = addPatternStart;
                        // check if we have a possibility of matching . or ..,
                        // and prevent that.
                        const needNoTrav = 
                        // dots are allowed, and the pattern starts with [ or .
                        (dot && aps.has(src.charAt(0))) ||
                            // the pattern starts with \., and then [ or .
                            (src.startsWith('\\.') && aps.has(src.charAt(2))) ||
                            // the pattern starts with \.\., and then [ or .
                            (src.startsWith('\\.\\.') && aps.has(src.charAt(4)));
                        // no need to prevent dots if it can't match a dot, or if a
                        // sub-pattern will be preventing it anyway.
                        const needNoDot = !dot && !allowDot && aps.has(src.charAt(0));
                        start = needNoTrav ? startNoTraversal : needNoDot ? startNoDot : '';
                    }
                }
            }
            // append the "end of path portion" pattern to negation tails
            let end = '';
            if (this.isEnd() &&
                this.#root.#filledNegs &&
                this.#parent?.type === '!') {
                end = '(?:$|\\/)';
            }
            const final = start + src + end;
            return [
                final,
                (0, unescape_js_1.unescape)(src),
                (this.#hasMagic = !!this.#hasMagic),
                this.#uflag,
            ];
        }
        // We need to calculate the body *twice* if it's a repeat pattern
        // at the start, once in nodot mode, then again in dot mode, so a
        // pattern like *(?) can match 'x.y'
        const repeated = this.type === '*' || this.type === '+';
        // some kind of extglob
        const start = this.type === '!' ? '(?:(?!(?:' : '(?:';
        let body = this.#partsToRegExp(dot);
        if (this.isStart() && this.isEnd() && !body && this.type !== '!') {
            // invalid extglob, has to at least be *something* present, if it's
            // the entire path portion.
            const s = this.toString();
            this.#parts = [s];
            this.type = null;
            this.#hasMagic = undefined;
            return [s, (0, unescape_js_1.unescape)(this.toString()), false, false];
        }
        // XXX abstract out this map method
        let bodyDotAllowed = !repeated || allowDot || dot || !startNoDot
            ? ''
            : this.#partsToRegExp(true);
        if (bodyDotAllowed === body) {
            bodyDotAllowed = '';
        }
        if (bodyDotAllowed) {
            body = `(?:${body})(?:${bodyDotAllowed})*?`;
        }
        // an empty !() is exactly equivalent to a starNoEmpty
        let final = '';
        if (this.type === '!' && this.#emptyExt) {
            final = (this.isStart() && !dot ? startNoDot : '') + starNoEmpty;
        }
        else {
            const close = this.type === '!'
                ? // !() must match something,but !(x) can match ''
                    '))' +
                        (this.isStart() && !dot && !allowDot ? startNoDot : '') +
                        star +
                        ')'
                : this.type === '@'
                    ? ')'
                    : this.type === '?'
                        ? ')?'
                        : this.type === '+' && bodyDotAllowed
                            ? ')'
                            : this.type === '*' && bodyDotAllowed
                                ? `)?`
                                : `)${this.type}`;
            final = start + body + close;
        }
        return [
            final,
            (0, unescape_js_1.unescape)(body),
            (this.#hasMagic = !!this.#hasMagic),
            this.#uflag,
        ];
    }
    #partsToRegExp(dot) {
        return this.#parts
            .map(p => {
            // extglob ASTs should only contain parent ASTs
            /* c8 ignore start */
            if (typeof p === 'string') {
                throw new Error('string type in extglob ast??');
            }
            /* c8 ignore stop */
            // can ignore hasMagic, because extglobs are already always magic
            const [re, _, _hasMagic, uflag] = p.toRegExpSource(dot);
            this.#uflag = this.#uflag || uflag;
            return re;
        })
            .filter(p => !(this.isStart() && this.isEnd()) || !!p)
            .join('|');
    }
    static #parseGlob(glob, hasMagic, noEmpty = false) {
        let escaping = false;
        let re = '';
        let uflag = false;
        for (let i = 0; i < glob.length; i++) {
            const c = glob.charAt(i);
            if (escaping) {
                escaping = false;
                re += (reSpecials.has(c) ? '\\' : '') + c;
                continue;
            }
            if (c === '\\') {
                if (i === glob.length - 1) {
                    re += '\\\\';
                }
                else {
                    escaping = true;
                }
                continue;
            }
            if (c === '[') {
                const [src, needUflag, consumed, magic] = (0, brace_expressions_js_1.parseClass)(glob, i);
                if (consumed) {
                    re += src;
                    uflag = uflag || needUflag;
                    i += consumed - 1;
                    hasMagic = hasMagic || magic;
                    continue;
                }
            }
            if (c === '*') {
                if (noEmpty && glob === '*')
                    re += starNoEmpty;
                else
                    re += star;
                hasMagic = true;
                continue;
            }
            if (c === '?') {
                re += qmark;
                hasMagic = true;
                continue;
            }
            re += regExpEscape(c);
        }
        return [re, (0, unescape_js_1.unescape)(glob), !!hasMagic, uflag];
    }
}
exports.AST = AST;
//# sourceMappingURL=ast.js.map

/***/ }),

/***/ "../../node_modules/minimatch/dist/commonjs/brace-expressions.js":
/*!***********************************************************************!*\
  !*** ../../node_modules/minimatch/dist/commonjs/brace-expressions.js ***!
  \***********************************************************************/
/***/ ((__unused_webpack_module, exports) => {

"use strict";

// translate the various posix character classes into unicode properties
// this works across all unicode locales
Object.defineProperty(exports, "__esModule", ({ value: true }));
exports.parseClass = void 0;
// { <posix class>: [<translation>, /u flag required, negated]
const posixClasses = {
    '[:alnum:]': ['\\p{L}\\p{Nl}\\p{Nd}', true],
    '[:alpha:]': ['\\p{L}\\p{Nl}', true],
    '[:ascii:]': ['\\x' + '00-\\x' + '7f', false],
    '[:blank:]': ['\\p{Zs}\\t', true],
    '[:cntrl:]': ['\\p{Cc}', true],
    '[:digit:]': ['\\p{Nd}', true],
    '[:graph:]': ['\\p{Z}\\p{C}', true, true],
    '[:lower:]': ['\\p{Ll}', true],
    '[:print:]': ['\\p{C}', true],
    '[:punct:]': ['\\p{P}', true],
    '[:space:]': ['\\p{Z}\\t\\r\\n\\v\\f', true],
    '[:upper:]': ['\\p{Lu}', true],
    '[:word:]': ['\\p{L}\\p{Nl}\\p{Nd}\\p{Pc}', true],
    '[:xdigit:]': ['A-Fa-f0-9', false],
};
// only need to escape a few things inside of brace expressions
// escapes: [ \ ] -
const braceEscape = (s) => s.replace(/[[\]\\-]/g, '\\$&');
// escape all regexp magic characters
const regexpEscape = (s) => s.replace(/[-[\]{}()*+?.,\\^$|#\s]/g, '\\$&');
// everything has already been escaped, we just have to join
const rangesToString = (ranges) => ranges.join('');
// takes a glob string at a posix brace expression, and returns
// an equivalent regular expression source, and boolean indicating
// whether the /u flag needs to be applied, and the number of chars
// consumed to parse the character class.
// This also removes out of order ranges, and returns ($.) if the
// entire class just no good.
const parseClass = (glob, position) => {
    const pos = position;
    /* c8 ignore start */
    if (glob.charAt(pos) !== '[') {
        throw new Error('not in a brace expression');
    }
    /* c8 ignore stop */
    const ranges = [];
    const negs = [];
    let i = pos + 1;
    let sawStart = false;
    let uflag = false;
    let escaping = false;
    let negate = false;
    let endPos = pos;
    let rangeStart = '';
    WHILE: while (i < glob.length) {
        const c = glob.charAt(i);
        if ((c === '!' || c === '^') && i === pos + 1) {
            negate = true;
            i++;
            continue;
        }
        if (c === ']' && sawStart && !escaping) {
            endPos = i + 1;
            break;
        }
        sawStart = true;
        if (c === '\\') {
            if (!escaping) {
                escaping = true;
                i++;
                continue;
            }
            // escaped \ char, fall through and treat like normal char
        }
        if (c === '[' && !escaping) {
            // either a posix class, a collation equivalent, or just a [
            for (const [cls, [unip, u, neg]] of Object.entries(posixClasses)) {
                if (glob.startsWith(cls, i)) {
                    // invalid, [a-[] is fine, but not [a-[:alpha]]
                    if (rangeStart) {
                        return ['$.', false, glob.length - pos, true];
                    }
                    i += cls.length;
                    if (neg)
                        negs.push(unip);
                    else
                        ranges.push(unip);
                    uflag = uflag || u;
                    continue WHILE;
                }
            }
        }
        // now it's just a normal character, effectively
        escaping = false;
        if (rangeStart) {
            // throw this range away if it's not valid, but others
            // can still match.
            if (c > rangeStart) {
                ranges.push(braceEscape(rangeStart) + '-' + braceEscape(c));
            }
            else if (c === rangeStart) {
                ranges.push(braceEscape(c));
            }
            rangeStart = '';
            i++;
            continue;
        }
        // now might be the start of a range.
        // can be either c-d or c-] or c<more...>] or c] at this point
        if (glob.startsWith('-]', i + 1)) {
            ranges.push(braceEscape(c + '-'));
            i += 2;
            continue;
        }
        if (glob.startsWith('-', i + 1)) {
            rangeStart = c;
            i += 2;
            continue;
        }
        // not the start of a range, just a single character
        ranges.push(braceEscape(c));
        i++;
    }
    if (endPos < i) {
        // didn't see the end of the class, not a valid class,
        // but might still be valid as a literal match.
        return ['', false, 0, false];
    }
    // if we got no ranges and no negates, then we have a range that
    // cannot possibly match anything, and that poisons the whole glob
    if (!ranges.length && !negs.length) {
        return ['$.', false, glob.length - pos, true];
    }
    // if we got one positive range, and it's a single character, then that's
    // not actually a magic pattern, it's just that one literal character.
    // we should not treat that as "magic", we should just return the literal
    // character. [_] is a perfectly valid way to escape glob magic chars.
    if (negs.length === 0 &&
        ranges.length === 1 &&
        /^\\?.$/.test(ranges[0]) &&
        !negate) {
        const r = ranges[0].length === 2 ? ranges[0].slice(-1) : ranges[0];
        return [regexpEscape(r), false, endPos - pos, false];
    }
    const sranges = '[' + (negate ? '^' : '') + rangesToString(ranges) + ']';
    const snegs = '[' + (negate ? '' : '^') + rangesToString(negs) + ']';
    const comb = ranges.length && negs.length
        ? '(' + sranges + '|' + snegs + ')'
        : ranges.length
            ? sranges
            : snegs;
    return [comb, uflag, endPos - pos, true];
};
exports.parseClass = parseClass;
//# sourceMappingURL=brace-expressions.js.map

/***/ }),

/***/ "../../node_modules/minimatch/dist/commonjs/escape.js":
/*!************************************************************!*\
  !*** ../../node_modules/minimatch/dist/commonjs/escape.js ***!
  \************************************************************/
/***/ ((__unused_webpack_module, exports) => {

"use strict";

Object.defineProperty(exports, "__esModule", ({ value: true }));
exports.escape = void 0;
/**
 * Escape all magic characters in a glob pattern.
 *
 * If the {@link windowsPathsNoEscape | GlobOptions.windowsPathsNoEscape}
 * option is used, then characters are escaped by wrapping in `[]`, because
 * a magic character wrapped in a character class can only be satisfied by
 * that exact character.  In this mode, `\` is _not_ escaped, because it is
 * not interpreted as a magic character, but instead as a path separator.
 */
const escape = (s, { windowsPathsNoEscape = false, } = {}) => {
    // don't need to escape +@! because we escape the parens
    // that make those magic, and escaping ! as [!] isn't valid,
    // because [!]] is a valid glob class meaning not ']'.
    return windowsPathsNoEscape
        ? s.replace(/[?*()[\]]/g, '[$&]')
        : s.replace(/[?*()[\]\\]/g, '\\$&');
};
exports.escape = escape;
//# sourceMappingURL=escape.js.map

/***/ }),

/***/ "../../node_modules/minimatch/dist/commonjs/index.js":
/*!***********************************************************!*\
  !*** ../../node_modules/minimatch/dist/commonjs/index.js ***!
  \***********************************************************/
/***/ (function(__unused_webpack_module, exports, __webpack_require__) {

"use strict";

var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", ({ value: true }));
exports.unescape = exports.escape = exports.AST = exports.Minimatch = exports.match = exports.makeRe = exports.braceExpand = exports.defaults = exports.filter = exports.GLOBSTAR = exports.sep = exports.minimatch = void 0;
const brace_expansion_1 = __importDefault(__webpack_require__(/*! brace-expansion */ "../../node_modules/brace-expansion/index.js"));
const assert_valid_pattern_js_1 = __webpack_require__(/*! ./assert-valid-pattern.js */ "../../node_modules/minimatch/dist/commonjs/assert-valid-pattern.js");
const ast_js_1 = __webpack_require__(/*! ./ast.js */ "../../node_modules/minimatch/dist/commonjs/ast.js");
const escape_js_1 = __webpack_require__(/*! ./escape.js */ "../../node_modules/minimatch/dist/commonjs/escape.js");
const unescape_js_1 = __webpack_require__(/*! ./unescape.js */ "../../node_modules/minimatch/dist/commonjs/unescape.js");
const minimatch = (p, pattern, options = {}) => {
    (0, assert_valid_pattern_js_1.assertValidPattern)(pattern);
    // shortcut: comments match nothing.
    if (!options.nocomment && pattern.charAt(0) === '#') {
        return false;
    }
    return new Minimatch(pattern, options).match(p);
};
exports.minimatch = minimatch;
// Optimized checking for the most common glob patterns.
const starDotExtRE = /^\*+([^+@!?\*\[\(]*)$/;
const starDotExtTest = (ext) => (f) => !f.startsWith('.') && f.endsWith(ext);
const starDotExtTestDot = (ext) => (f) => f.endsWith(ext);
const starDotExtTestNocase = (ext) => {
    ext = ext.toLowerCase();
    return (f) => !f.startsWith('.') && f.toLowerCase().endsWith(ext);
};
const starDotExtTestNocaseDot = (ext) => {
    ext = ext.toLowerCase();
    return (f) => f.toLowerCase().endsWith(ext);
};
const starDotStarRE = /^\*+\.\*+$/;
const starDotStarTest = (f) => !f.startsWith('.') && f.includes('.');
const starDotStarTestDot = (f) => f !== '.' && f !== '..' && f.includes('.');
const dotStarRE = /^\.\*+$/;
const dotStarTest = (f) => f !== '.' && f !== '..' && f.startsWith('.');
const starRE = /^\*+$/;
const starTest = (f) => f.length !== 0 && !f.startsWith('.');
const starTestDot = (f) => f.length !== 0 && f !== '.' && f !== '..';
const qmarksRE = /^\?+([^+@!?\*\[\(]*)?$/;
const qmarksTestNocase = ([$0, ext = '']) => {
    const noext = qmarksTestNoExt([$0]);
    if (!ext)
        return noext;
    ext = ext.toLowerCase();
    return (f) => noext(f) && f.toLowerCase().endsWith(ext);
};
const qmarksTestNocaseDot = ([$0, ext = '']) => {
    const noext = qmarksTestNoExtDot([$0]);
    if (!ext)
        return noext;
    ext = ext.toLowerCase();
    return (f) => noext(f) && f.toLowerCase().endsWith(ext);
};
const qmarksTestDot = ([$0, ext = '']) => {
    const noext = qmarksTestNoExtDot([$0]);
    return !ext ? noext : (f) => noext(f) && f.endsWith(ext);
};
const qmarksTest = ([$0, ext = '']) => {
    const noext = qmarksTestNoExt([$0]);
    return !ext ? noext : (f) => noext(f) && f.endsWith(ext);
};
const qmarksTestNoExt = ([$0]) => {
    const len = $0.length;
    return (f) => f.length === len && !f.startsWith('.');
};
const qmarksTestNoExtDot = ([$0]) => {
    const len = $0.length;
    return (f) => f.length === len && f !== '.' && f !== '..';
};
/* c8 ignore start */
const defaultPlatform = (typeof process === 'object' && process
    ? (typeof process.env === 'object' &&
        process.env &&
        process.env.__MINIMATCH_TESTING_PLATFORM__) ||
        process.platform
    : 'posix');
const path = {
    win32: { sep: '\\' },
    posix: { sep: '/' },
};
/* c8 ignore stop */
exports.sep = defaultPlatform === 'win32' ? path.win32.sep : path.posix.sep;
exports.minimatch.sep = exports.sep;
exports.GLOBSTAR = Symbol('globstar **');
exports.minimatch.GLOBSTAR = exports.GLOBSTAR;
// any single thing other than /
// don't need to escape / when using new RegExp()
const qmark = '[^/]';
// * => any number of characters
const star = qmark + '*?';
// ** when dots are allowed.  Anything goes, except .. and .
// not (^ or / followed by one or two dots followed by $ or /),
// followed by anything, any number of times.
const twoStarDot = '(?:(?!(?:\\/|^)(?:\\.{1,2})($|\\/)).)*?';
// not a ^ or / followed by a dot,
// followed by anything, any number of times.
const twoStarNoDot = '(?:(?!(?:\\/|^)\\.).)*?';
const filter = (pattern, options = {}) => (p) => (0, exports.minimatch)(p, pattern, options);
exports.filter = filter;
exports.minimatch.filter = exports.filter;
const ext = (a, b = {}) => Object.assign({}, a, b);
const defaults = (def) => {
    if (!def || typeof def !== 'object' || !Object.keys(def).length) {
        return exports.minimatch;
    }
    const orig = exports.minimatch;
    const m = (p, pattern, options = {}) => orig(p, pattern, ext(def, options));
    return Object.assign(m, {
        Minimatch: class Minimatch extends orig.Minimatch {
            constructor(pattern, options = {}) {
                super(pattern, ext(def, options));
            }
            static defaults(options) {
                return orig.defaults(ext(def, options)).Minimatch;
            }
        },
        AST: class AST extends orig.AST {
            /* c8 ignore start */
            constructor(type, parent, options = {}) {
                super(type, parent, ext(def, options));
            }
            /* c8 ignore stop */
            static fromGlob(pattern, options = {}) {
                return orig.AST.fromGlob(pattern, ext(def, options));
            }
        },
        unescape: (s, options = {}) => orig.unescape(s, ext(def, options)),
        escape: (s, options = {}) => orig.escape(s, ext(def, options)),
        filter: (pattern, options = {}) => orig.filter(pattern, ext(def, options)),
        defaults: (options) => orig.defaults(ext(def, options)),
        makeRe: (pattern, options = {}) => orig.makeRe(pattern, ext(def, options)),
        braceExpand: (pattern, options = {}) => orig.braceExpand(pattern, ext(def, options)),
        match: (list, pattern, options = {}) => orig.match(list, pattern, ext(def, options)),
        sep: orig.sep,
        GLOBSTAR: exports.GLOBSTAR,
    });
};
exports.defaults = defaults;
exports.minimatch.defaults = exports.defaults;
// Brace expansion:
// a{b,c}d -> abd acd
// a{b,}c -> abc ac
// a{0..3}d -> a0d a1d a2d a3d
// a{b,c{d,e}f}g -> abg acdfg acefg
// a{b,c}d{e,f}g -> abdeg acdeg abdeg abdfg
//
// Invalid sets are not expanded.
// a{2..}b -> a{2..}b
// a{b}c -> a{b}c
const braceExpand = (pattern, options = {}) => {
    (0, assert_valid_pattern_js_1.assertValidPattern)(pattern);
    // Thanks to Yeting Li <https://github.com/yetingli> for
    // improving this regexp to avoid a ReDOS vulnerability.
    if (options.nobrace || !/\{(?:(?!\{).)*\}/.test(pattern)) {
        // shortcut. no need to expand.
        return [pattern];
    }
    return (0, brace_expansion_1.default)(pattern);
};
exports.braceExpand = braceExpand;
exports.minimatch.braceExpand = exports.braceExpand;
// parse a component of the expanded set.
// At this point, no pattern may contain "/" in it
// so we're going to return a 2d array, where each entry is the full
// pattern, split on '/', and then turned into a regular expression.
// A regexp is made at the end which joins each array with an
// escaped /, and another full one which joins each regexp with |.
//
// Following the lead of Bash 4.1, note that "**" only has special meaning
// when it is the *only* thing in a path portion.  Otherwise, any series
// of * is equivalent to a single *.  Globstar behavior is enabled by
// default, and can be disabled by setting options.noglobstar.
const makeRe = (pattern, options = {}) => new Minimatch(pattern, options).makeRe();
exports.makeRe = makeRe;
exports.minimatch.makeRe = exports.makeRe;
const match = (list, pattern, options = {}) => {
    const mm = new Minimatch(pattern, options);
    list = list.filter(f => mm.match(f));
    if (mm.options.nonull && !list.length) {
        list.push(pattern);
    }
    return list;
};
exports.match = match;
exports.minimatch.match = exports.match;
// replace stuff like \* with *
const globMagic = /[?*]|[+@!]\(.*?\)|\[|\]/;
const regExpEscape = (s) => s.replace(/[-[\]{}()*+?.,\\^$|#\s]/g, '\\$&');
class Minimatch {
    options;
    set;
    pattern;
    windowsPathsNoEscape;
    nonegate;
    negate;
    comment;
    empty;
    preserveMultipleSlashes;
    partial;
    globSet;
    globParts;
    nocase;
    isWindows;
    platform;
    windowsNoMagicRoot;
    regexp;
    constructor(pattern, options = {}) {
        (0, assert_valid_pattern_js_1.assertValidPattern)(pattern);
        options = options || {};
        this.options = options;
        this.pattern = pattern;
        this.platform = options.platform || defaultPlatform;
        this.isWindows = this.platform === 'win32';
        this.windowsPathsNoEscape =
            !!options.windowsPathsNoEscape || options.allowWindowsEscape === false;
        if (this.windowsPathsNoEscape) {
            this.pattern = this.pattern.replace(/\\/g, '/');
        }
        this.preserveMultipleSlashes = !!options.preserveMultipleSlashes;
        this.regexp = null;
        this.negate = false;
        this.nonegate = !!options.nonegate;
        this.comment = false;
        this.empty = false;
        this.partial = !!options.partial;
        this.nocase = !!this.options.nocase;
        this.windowsNoMagicRoot =
            options.windowsNoMagicRoot !== undefined
                ? options.windowsNoMagicRoot
                : !!(this.isWindows && this.nocase);
        this.globSet = [];
        this.globParts = [];
        this.set = [];
        // make the set of regexps etc.
        this.make();
    }
    hasMagic() {
        if (this.options.magicalBraces && this.set.length > 1) {
            return true;
        }
        for (const pattern of this.set) {
            for (const part of pattern) {
                if (typeof part !== 'string')
                    return true;
            }
        }
        return false;
    }
    debug(..._) { }
    make() {
        const pattern = this.pattern;
        const options = this.options;
        // empty patterns and comments match nothing.
        if (!options.nocomment && pattern.charAt(0) === '#') {
            this.comment = true;
            return;
        }
        if (!pattern) {
            this.empty = true;
            return;
        }
        // step 1: figure out negation, etc.
        this.parseNegate();
        // step 2: expand braces
        this.globSet = [...new Set(this.braceExpand())];
        if (options.debug) {
            this.debug = (...args) => console.error(...args);
        }
        this.debug(this.pattern, this.globSet);
        // step 3: now we have a set, so turn each one into a series of
        // path-portion matching patterns.
        // These will be regexps, except in the case of "**", which is
        // set to the GLOBSTAR object for globstar behavior,
        // and will not contain any / characters
        //
        // First, we preprocess to make the glob pattern sets a bit simpler
        // and deduped.  There are some perf-killing patterns that can cause
        // problems with a glob walk, but we can simplify them down a bit.
        const rawGlobParts = this.globSet.map(s => this.slashSplit(s));
        this.globParts = this.preprocess(rawGlobParts);
        this.debug(this.pattern, this.globParts);
        // glob --> regexps
        let set = this.globParts.map((s, _, __) => {
            if (this.isWindows && this.windowsNoMagicRoot) {
                // check if it's a drive or unc path.
                const isUNC = s[0] === '' &&
                    s[1] === '' &&
                    (s[2] === '?' || !globMagic.test(s[2])) &&
                    !globMagic.test(s[3]);
                const isDrive = /^[a-z]:/i.test(s[0]);
                if (isUNC) {
                    return [...s.slice(0, 4), ...s.slice(4).map(ss => this.parse(ss))];
                }
                else if (isDrive) {
                    return [s[0], ...s.slice(1).map(ss => this.parse(ss))];
                }
            }
            return s.map(ss => this.parse(ss));
        });
        this.debug(this.pattern, set);
        // filter out everything that didn't compile properly.
        this.set = set.filter(s => s.indexOf(false) === -1);
        // do not treat the ? in UNC paths as magic
        if (this.isWindows) {
            for (let i = 0; i < this.set.length; i++) {
                const p = this.set[i];
                if (p[0] === '' &&
                    p[1] === '' &&
                    this.globParts[i][2] === '?' &&
                    typeof p[3] === 'string' &&
                    /^[a-z]:$/i.test(p[3])) {
                    p[2] = '?';
                }
            }
        }
        this.debug(this.pattern, this.set);
    }
    // various transforms to equivalent pattern sets that are
    // faster to process in a filesystem walk.  The goal is to
    // eliminate what we can, and push all ** patterns as far
    // to the right as possible, even if it increases the number
    // of patterns that we have to process.
    preprocess(globParts) {
        // if we're not in globstar mode, then turn all ** into *
        if (this.options.noglobstar) {
            for (let i = 0; i < globParts.length; i++) {
                for (let j = 0; j < globParts[i].length; j++) {
                    if (globParts[i][j] === '**') {
                        globParts[i][j] = '*';
                    }
                }
            }
        }
        const { optimizationLevel = 1 } = this.options;
        if (optimizationLevel >= 2) {
            // aggressive optimization for the purpose of fs walking
            globParts = this.firstPhasePreProcess(globParts);
            globParts = this.secondPhasePreProcess(globParts);
        }
        else if (optimizationLevel >= 1) {
            // just basic optimizations to remove some .. parts
            globParts = this.levelOneOptimize(globParts);
        }
        else {
            // just collapse multiple ** portions into one
            globParts = this.adjascentGlobstarOptimize(globParts);
        }
        return globParts;
    }
    // just get rid of adjascent ** portions
    adjascentGlobstarOptimize(globParts) {
        return globParts.map(parts => {
            let gs = -1;
            while (-1 !== (gs = parts.indexOf('**', gs + 1))) {
                let i = gs;
                while (parts[i + 1] === '**') {
                    i++;
                }
                if (i !== gs) {
                    parts.splice(gs, i - gs);
                }
            }
            return parts;
        });
    }
    // get rid of adjascent ** and resolve .. portions
    levelOneOptimize(globParts) {
        return globParts.map(parts => {
            parts = parts.reduce((set, part) => {
                const prev = set[set.length - 1];
                if (part === '**' && prev === '**') {
                    return set;
                }
                if (part === '..') {
                    if (prev && prev !== '..' && prev !== '.' && prev !== '**') {
                        set.pop();
                        return set;
                    }
                }
                set.push(part);
                return set;
            }, []);
            return parts.length === 0 ? [''] : parts;
        });
    }
    levelTwoFileOptimize(parts) {
        if (!Array.isArray(parts)) {
            parts = this.slashSplit(parts);
        }
        let didSomething = false;
        do {
            didSomething = false;
            // <pre>/<e>/<rest> -> <pre>/<rest>
            if (!this.preserveMultipleSlashes) {
                for (let i = 1; i < parts.length - 1; i++) {
                    const p = parts[i];
                    // don't squeeze out UNC patterns
                    if (i === 1 && p === '' && parts[0] === '')
                        continue;
                    if (p === '.' || p === '') {
                        didSomething = true;
                        parts.splice(i, 1);
                        i--;
                    }
                }
                if (parts[0] === '.' &&
                    parts.length === 2 &&
                    (parts[1] === '.' || parts[1] === '')) {
                    didSomething = true;
                    parts.pop();
                }
            }
            // <pre>/<p>/../<rest> -> <pre>/<rest>
            let dd = 0;
            while (-1 !== (dd = parts.indexOf('..', dd + 1))) {
                const p = parts[dd - 1];
                if (p && p !== '.' && p !== '..' && p !== '**') {
                    didSomething = true;
                    parts.splice(dd - 1, 2);
                    dd -= 2;
                }
            }
        } while (didSomething);
        return parts.length === 0 ? [''] : parts;
    }
    // First phase: single-pattern processing
    // <pre> is 1 or more portions
    // <rest> is 1 or more portions
    // <p> is any portion other than ., .., '', or **
    // <e> is . or ''
    //
    // **/.. is *brutal* for filesystem walking performance, because
    // it effectively resets the recursive walk each time it occurs,
    // and ** cannot be reduced out by a .. pattern part like a regexp
    // or most strings (other than .., ., and '') can be.
    //
    // <pre>/**/../<p>/<p>/<rest> -> {<pre>/../<p>/<p>/<rest>,<pre>/**/<p>/<p>/<rest>}
    // <pre>/<e>/<rest> -> <pre>/<rest>
    // <pre>/<p>/../<rest> -> <pre>/<rest>
    // **/**/<rest> -> **/<rest>
    //
    // **/*/<rest> -> */**/<rest> <== not valid because ** doesn't follow
    // this WOULD be allowed if ** did follow symlinks, or * didn't
    firstPhasePreProcess(globParts) {
        let didSomething = false;
        do {
            didSomething = false;
            // <pre>/**/../<p>/<p>/<rest> -> {<pre>/../<p>/<p>/<rest>,<pre>/**/<p>/<p>/<rest>}
            for (let parts of globParts) {
                let gs = -1;
                while (-1 !== (gs = parts.indexOf('**', gs + 1))) {
                    let gss = gs;
                    while (parts[gss + 1] === '**') {
                        // <pre>/**/**/<rest> -> <pre>/**/<rest>
                        gss++;
                    }
                    // eg, if gs is 2 and gss is 4, that means we have 3 **
                    // parts, and can remove 2 of them.
                    if (gss > gs) {
                        parts.splice(gs + 1, gss - gs);
                    }
                    let next = parts[gs + 1];
                    const p = parts[gs + 2];
                    const p2 = parts[gs + 3];
                    if (next !== '..')
                        continue;
                    if (!p ||
                        p === '.' ||
                        p === '..' ||
                        !p2 ||
                        p2 === '.' ||
                        p2 === '..') {
                        continue;
                    }
                    didSomething = true;
                    // edit parts in place, and push the new one
                    parts.splice(gs, 1);
                    const other = parts.slice(0);
                    other[gs] = '**';
                    globParts.push(other);
                    gs--;
                }
                // <pre>/<e>/<rest> -> <pre>/<rest>
                if (!this.preserveMultipleSlashes) {
                    for (let i = 1; i < parts.length - 1; i++) {
                        const p = parts[i];
                        // don't squeeze out UNC patterns
                        if (i === 1 && p === '' && parts[0] === '')
                            continue;
                        if (p === '.' || p === '') {
                            didSomething = true;
                            parts.splice(i, 1);
                            i--;
                        }
                    }
                    if (parts[0] === '.' &&
                        parts.length === 2 &&
                        (parts[1] === '.' || parts[1] === '')) {
                        didSomething = true;
                        parts.pop();
                    }
                }
                // <pre>/<p>/../<rest> -> <pre>/<rest>
                let dd = 0;
                while (-1 !== (dd = parts.indexOf('..', dd + 1))) {
                    const p = parts[dd - 1];
                    if (p && p !== '.' && p !== '..' && p !== '**') {
                        didSomething = true;
                        const needDot = dd === 1 && parts[dd + 1] === '**';
                        const splin = needDot ? ['.'] : [];
                        parts.splice(dd - 1, 2, ...splin);
                        if (parts.length === 0)
                            parts.push('');
                        dd -= 2;
                    }
                }
            }
        } while (didSomething);
        return globParts;
    }
    // second phase: multi-pattern dedupes
    // {<pre>/*/<rest>,<pre>/<p>/<rest>} -> <pre>/*/<rest>
    // {<pre>/<rest>,<pre>/<rest>} -> <pre>/<rest>
    // {<pre>/**/<rest>,<pre>/<rest>} -> <pre>/**/<rest>
    //
    // {<pre>/**/<rest>,<pre>/**/<p>/<rest>} -> <pre>/**/<rest>
    // ^-- not valid because ** doens't follow symlinks
    secondPhasePreProcess(globParts) {
        for (let i = 0; i < globParts.length - 1; i++) {
            for (let j = i + 1; j < globParts.length; j++) {
                const matched = this.partsMatch(globParts[i], globParts[j], !this.preserveMultipleSlashes);
                if (matched) {
                    globParts[i] = [];
                    globParts[j] = matched;
                    break;
                }
            }
        }
        return globParts.filter(gs => gs.length);
    }
    partsMatch(a, b, emptyGSMatch = false) {
        let ai = 0;
        let bi = 0;
        let result = [];
        let which = '';
        while (ai < a.length && bi < b.length) {
            if (a[ai] === b[bi]) {
                result.push(which === 'b' ? b[bi] : a[ai]);
                ai++;
                bi++;
            }
            else if (emptyGSMatch && a[ai] === '**' && b[bi] === a[ai + 1]) {
                result.push(a[ai]);
                ai++;
            }
            else if (emptyGSMatch && b[bi] === '**' && a[ai] === b[bi + 1]) {
                result.push(b[bi]);
                bi++;
            }
            else if (a[ai] === '*' &&
                b[bi] &&
                (this.options.dot || !b[bi].startsWith('.')) &&
                b[bi] !== '**') {
                if (which === 'b')
                    return false;
                which = 'a';
                result.push(a[ai]);
                ai++;
                bi++;
            }
            else if (b[bi] === '*' &&
                a[ai] &&
                (this.options.dot || !a[ai].startsWith('.')) &&
                a[ai] !== '**') {
                if (which === 'a')
                    return false;
                which = 'b';
                result.push(b[bi]);
                ai++;
                bi++;
            }
            else {
                return false;
            }
        }
        // if we fall out of the loop, it means they two are identical
        // as long as their lengths match
        return a.length === b.length && result;
    }
    parseNegate() {
        if (this.nonegate)
            return;
        const pattern = this.pattern;
        let negate = false;
        let negateOffset = 0;
        for (let i = 0; i < pattern.length && pattern.charAt(i) === '!'; i++) {
            negate = !negate;
            negateOffset++;
        }
        if (negateOffset)
            this.pattern = pattern.slice(negateOffset);
        this.negate = negate;
    }
    // set partial to true to test if, for example,
    // "/a/b" matches the start of "/*/b/*/d"
    // Partial means, if you run out of file before you run
    // out of pattern, then that's fine, as long as all
    // the parts match.
    matchOne(file, pattern, partial = false) {
        const options = this.options;
        // UNC paths like //?/X:/... can match X:/... and vice versa
        // Drive letters in absolute drive or unc paths are always compared
        // case-insensitively.
        if (this.isWindows) {
            const fileDrive = typeof file[0] === 'string' && /^[a-z]:$/i.test(file[0]);
            const fileUNC = !fileDrive &&
                file[0] === '' &&
                file[1] === '' &&
                file[2] === '?' &&
                /^[a-z]:$/i.test(file[3]);
            const patternDrive = typeof pattern[0] === 'string' && /^[a-z]:$/i.test(pattern[0]);
            const patternUNC = !patternDrive &&
                pattern[0] === '' &&
                pattern[1] === '' &&
                pattern[2] === '?' &&
                typeof pattern[3] === 'string' &&
                /^[a-z]:$/i.test(pattern[3]);
            const fdi = fileUNC ? 3 : fileDrive ? 0 : undefined;
            const pdi = patternUNC ? 3 : patternDrive ? 0 : undefined;
            if (typeof fdi === 'number' && typeof pdi === 'number') {
                const [fd, pd] = [file[fdi], pattern[pdi]];
                if (fd.toLowerCase() === pd.toLowerCase()) {
                    pattern[pdi] = fd;
                    if (pdi > fdi) {
                        pattern = pattern.slice(pdi);
                    }
                    else if (fdi > pdi) {
                        file = file.slice(fdi);
                    }
                }
            }
        }
        // resolve and reduce . and .. portions in the file as well.
        // dont' need to do the second phase, because it's only one string[]
        const { optimizationLevel = 1 } = this.options;
        if (optimizationLevel >= 2) {
            file = this.levelTwoFileOptimize(file);
        }
        this.debug('matchOne', this, { file, pattern });
        this.debug('matchOne', file.length, pattern.length);
        for (var fi = 0, pi = 0, fl = file.length, pl = pattern.length; fi < fl && pi < pl; fi++, pi++) {
            this.debug('matchOne loop');
            var p = pattern[pi];
            var f = file[fi];
            this.debug(pattern, p, f);
            // should be impossible.
            // some invalid regexp stuff in the set.
            /* c8 ignore start */
            if (p === false) {
                return false;
            }
            /* c8 ignore stop */
            if (p === exports.GLOBSTAR) {
                this.debug('GLOBSTAR', [pattern, p, f]);
                // "**"
                // a/**/b/**/c would match the following:
                // a/b/x/y/z/c
                // a/x/y/z/b/c
                // a/b/x/b/x/c
                // a/b/c
                // To do this, take the rest of the pattern after
                // the **, and see if it would match the file remainder.
                // If so, return success.
                // If not, the ** "swallows" a segment, and try again.
                // This is recursively awful.
                //
                // a/**/b/**/c matching a/b/x/y/z/c
                // - a matches a
                // - doublestar
                //   - matchOne(b/x/y/z/c, b/**/c)
                //     - b matches b
                //     - doublestar
                //       - matchOne(x/y/z/c, c) -> no
                //       - matchOne(y/z/c, c) -> no
                //       - matchOne(z/c, c) -> no
                //       - matchOne(c, c) yes, hit
                var fr = fi;
                var pr = pi + 1;
                if (pr === pl) {
                    this.debug('** at the end');
                    // a ** at the end will just swallow the rest.
                    // We have found a match.
                    // however, it will not swallow /.x, unless
                    // options.dot is set.
                    // . and .. are *never* matched by **, for explosively
                    // exponential reasons.
                    for (; fi < fl; fi++) {
                        if (file[fi] === '.' ||
                            file[fi] === '..' ||
                            (!options.dot && file[fi].charAt(0) === '.'))
                            return false;
                    }
                    return true;
                }
                // ok, let's see if we can swallow whatever we can.
                while (fr < fl) {
                    var swallowee = file[fr];
                    this.debug('\nglobstar while', file, fr, pattern, pr, swallowee);
                    // XXX remove this slice.  Just pass the start index.
                    if (this.matchOne(file.slice(fr), pattern.slice(pr), partial)) {
                        this.debug('globstar found match!', fr, fl, swallowee);
                        // found a match.
                        return true;
                    }
                    else {
                        // can't swallow "." or ".." ever.
                        // can only swallow ".foo" when explicitly asked.
                        if (swallowee === '.' ||
                            swallowee === '..' ||
                            (!options.dot && swallowee.charAt(0) === '.')) {
                            this.debug('dot detected!', file, fr, pattern, pr);
                            break;
                        }
                        // ** swallows a segment, and continue.
                        this.debug('globstar swallow a segment, and continue');
                        fr++;
                    }
                }
                // no match was found.
                // However, in partial mode, we can't say this is necessarily over.
                /* c8 ignore start */
                if (partial) {
                    // ran out of file
                    this.debug('\n>>> no match, partial?', file, fr, pattern, pr);
                    if (fr === fl) {
                        return true;
                    }
                }
                /* c8 ignore stop */
                return false;
            }
            // something other than **
            // non-magic patterns just have to match exactly
            // patterns with magic have been turned into regexps.
            let hit;
            if (typeof p === 'string') {
                hit = f === p;
                this.debug('string match', p, f, hit);
            }
            else {
                hit = p.test(f);
                this.debug('pattern match', p, f, hit);
            }
            if (!hit)
                return false;
        }
        // Note: ending in / means that we'll get a final ""
        // at the end of the pattern.  This can only match a
        // corresponding "" at the end of the file.
        // If the file ends in /, then it can only match a
        // a pattern that ends in /, unless the pattern just
        // doesn't have any more for it. But, a/b/ should *not*
        // match "a/b/*", even though "" matches against the
        // [^/]*? pattern, except in partial mode, where it might
        // simply not be reached yet.
        // However, a/b/ should still satisfy a/*
        // now either we fell off the end of the pattern, or we're done.
        if (fi === fl && pi === pl) {
            // ran out of pattern and filename at the same time.
            // an exact hit!
            return true;
        }
        else if (fi === fl) {
            // ran out of file, but still had pattern left.
            // this is ok if we're doing the match as part of
            // a glob fs traversal.
            return partial;
        }
        else if (pi === pl) {
            // ran out of pattern, still have file left.
            // this is only acceptable if we're on the very last
            // empty segment of a file with a trailing slash.
            // a/* should match a/b/
            return fi === fl - 1 && file[fi] === '';
            /* c8 ignore start */
        }
        else {
            // should be unreachable.
            throw new Error('wtf?');
        }
        /* c8 ignore stop */
    }
    braceExpand() {
        return (0, exports.braceExpand)(this.pattern, this.options);
    }
    parse(pattern) {
        (0, assert_valid_pattern_js_1.assertValidPattern)(pattern);
        const options = this.options;
        // shortcuts
        if (pattern === '**')
            return exports.GLOBSTAR;
        if (pattern === '')
            return '';
        // far and away, the most common glob pattern parts are
        // *, *.*, and *.<ext>  Add a fast check method for those.
        let m;
        let fastTest = null;
        if ((m = pattern.match(starRE))) {
            fastTest = options.dot ? starTestDot : starTest;
        }
        else if ((m = pattern.match(starDotExtRE))) {
            fastTest = (options.nocase
                ? options.dot
                    ? starDotExtTestNocaseDot
                    : starDotExtTestNocase
                : options.dot
                    ? starDotExtTestDot
                    : starDotExtTest)(m[1]);
        }
        else if ((m = pattern.match(qmarksRE))) {
            fastTest = (options.nocase
                ? options.dot
                    ? qmarksTestNocaseDot
                    : qmarksTestNocase
                : options.dot
                    ? qmarksTestDot
                    : qmarksTest)(m);
        }
        else if ((m = pattern.match(starDotStarRE))) {
            fastTest = options.dot ? starDotStarTestDot : starDotStarTest;
        }
        else if ((m = pattern.match(dotStarRE))) {
            fastTest = dotStarTest;
        }
        const re = ast_js_1.AST.fromGlob(pattern, this.options).toMMPattern();
        if (fastTest && typeof re === 'object') {
            // Avoids overriding in frozen environments
            Reflect.defineProperty(re, 'test', { value: fastTest });
        }
        return re;
    }
    makeRe() {
        if (this.regexp || this.regexp === false)
            return this.regexp;
        // at this point, this.set is a 2d array of partial
        // pattern strings, or "**".
        //
        // It's better to use .match().  This function shouldn't
        // be used, really, but it's pretty convenient sometimes,
        // when you just want to work with a regex.
        const set = this.set;
        if (!set.length) {
            this.regexp = false;
            return this.regexp;
        }
        const options = this.options;
        const twoStar = options.noglobstar
            ? star
            : options.dot
                ? twoStarDot
                : twoStarNoDot;
        const flags = new Set(options.nocase ? ['i'] : []);
        // regexpify non-globstar patterns
        // if ** is only item, then we just do one twoStar
        // if ** is first, and there are more, prepend (\/|twoStar\/)? to next
        // if ** is last, append (\/twoStar|) to previous
        // if ** is in the middle, append (\/|\/twoStar\/) to previous
        // then filter out GLOBSTAR symbols
        let re = set
            .map(pattern => {
            const pp = pattern.map(p => {
                if (p instanceof RegExp) {
                    for (const f of p.flags.split(''))
                        flags.add(f);
                }
                return typeof p === 'string'
                    ? regExpEscape(p)
                    : p === exports.GLOBSTAR
                        ? exports.GLOBSTAR
                        : p._src;
            });
            pp.forEach((p, i) => {
                const next = pp[i + 1];
                const prev = pp[i - 1];
                if (p !== exports.GLOBSTAR || prev === exports.GLOBSTAR) {
                    return;
                }
                if (prev === undefined) {
                    if (next !== undefined && next !== exports.GLOBSTAR) {
                        pp[i + 1] = '(?:\\/|' + twoStar + '\\/)?' + next;
                    }
                    else {
                        pp[i] = twoStar;
                    }
                }
                else if (next === undefined) {
                    pp[i - 1] = prev + '(?:\\/|' + twoStar + ')?';
                }
                else if (next !== exports.GLOBSTAR) {
                    pp[i - 1] = prev + '(?:\\/|\\/' + twoStar + '\\/)' + next;
                    pp[i + 1] = exports.GLOBSTAR;
                }
            });
            return pp.filter(p => p !== exports.GLOBSTAR).join('/');
        })
            .join('|');
        // need to wrap in parens if we had more than one thing with |,
        // otherwise only the first will be anchored to ^ and the last to $
        const [open, close] = set.length > 1 ? ['(?:', ')'] : ['', ''];
        // must match entire pattern
        // ending in a * or ** will make it less strict.
        re = '^' + open + re + close + '$';
        // can match anything, as long as it's not this.
        if (this.negate)
            re = '^(?!' + re + ').+$';
        try {
            this.regexp = new RegExp(re, [...flags].join(''));
            /* c8 ignore start */
        }
        catch (ex) {
            // should be impossible
            this.regexp = false;
        }
        /* c8 ignore stop */
        return this.regexp;
    }
    slashSplit(p) {
        // if p starts with // on windows, we preserve that
        // so that UNC paths aren't broken.  Otherwise, any number of
        // / characters are coalesced into one, unless
        // preserveMultipleSlashes is set to true.
        if (this.preserveMultipleSlashes) {
            return p.split('/');
        }
        else if (this.isWindows && /^\/\/[^\/]+/.test(p)) {
            // add an extra '' for the one we lose
            return ['', ...p.split(/\/+/)];
        }
        else {
            return p.split(/\/+/);
        }
    }
    match(f, partial = this.partial) {
        this.debug('match', f, this.pattern);
        // short-circuit in the case of busted things.
        // comments, etc.
        if (this.comment) {
            return false;
        }
        if (this.empty) {
            return f === '';
        }
        if (f === '/' && partial) {
            return true;
        }
        const options = this.options;
        // windows: need to use /, not \
        if (this.isWindows) {
            f = f.split('\\').join('/');
        }
        // treat the test path as a set of pathparts.
        const ff = this.slashSplit(f);
        this.debug(this.pattern, 'split', ff);
        // just ONE of the pattern sets in this.set needs to match
        // in order for it to be valid.  If negating, then just one
        // match means that we have failed.
        // Either way, return on the first hit.
        const set = this.set;
        this.debug(this.pattern, 'set', set);
        // Find the basename of the path by looking for the last non-empty segment
        let filename = ff[ff.length - 1];
        if (!filename) {
            for (let i = ff.length - 2; !filename && i >= 0; i--) {
                filename = ff[i];
            }
        }
        for (let i = 0; i < set.length; i++) {
            const pattern = set[i];
            let file = ff;
            if (options.matchBase && pattern.length === 1) {
                file = [filename];
            }
            const hit = this.matchOne(file, pattern, partial);
            if (hit) {
                if (options.flipNegate) {
                    return true;
                }
                return !this.negate;
            }
        }
        // didn't get any hits.  this is success if it's a negative
        // pattern, failure otherwise.
        if (options.flipNegate) {
            return false;
        }
        return this.negate;
    }
    static defaults(def) {
        return exports.minimatch.defaults(def).Minimatch;
    }
}
exports.Minimatch = Minimatch;
/* c8 ignore start */
var ast_js_2 = __webpack_require__(/*! ./ast.js */ "../../node_modules/minimatch/dist/commonjs/ast.js");
Object.defineProperty(exports, "AST", ({ enumerable: true, get: function () { return ast_js_2.AST; } }));
var escape_js_2 = __webpack_require__(/*! ./escape.js */ "../../node_modules/minimatch/dist/commonjs/escape.js");
Object.defineProperty(exports, "escape", ({ enumerable: true, get: function () { return escape_js_2.escape; } }));
var unescape_js_2 = __webpack_require__(/*! ./unescape.js */ "../../node_modules/minimatch/dist/commonjs/unescape.js");
Object.defineProperty(exports, "unescape", ({ enumerable: true, get: function () { return unescape_js_2.unescape; } }));
/* c8 ignore stop */
exports.minimatch.AST = ast_js_1.AST;
exports.minimatch.Minimatch = Minimatch;
exports.minimatch.escape = escape_js_1.escape;
exports.minimatch.unescape = unescape_js_1.unescape;
//# sourceMappingURL=index.js.map

/***/ }),

/***/ "../../node_modules/minimatch/dist/commonjs/unescape.js":
/*!**************************************************************!*\
  !*** ../../node_modules/minimatch/dist/commonjs/unescape.js ***!
  \**************************************************************/
/***/ ((__unused_webpack_module, exports) => {

"use strict";

Object.defineProperty(exports, "__esModule", ({ value: true }));
exports.unescape = void 0;
/**
 * Un-escape a string that has been escaped with {@link escape}.
 *
 * If the {@link windowsPathsNoEscape} option is used, then square-brace
 * escapes are removed, but not backslash escapes.  For example, it will turn
 * the string `'[*]'` into `*`, but it will not turn `'\\*'` into `'*'`,
 * becuase `\` is a path separator in `windowsPathsNoEscape` mode.
 *
 * When `windowsPathsNoEscape` is not set, then both brace escapes and
 * backslash escapes are removed.
 *
 * Slashes (and backslashes in `windowsPathsNoEscape` mode) cannot be escaped
 * or unescaped.
 */
const unescape = (s, { windowsPathsNoEscape = false, } = {}) => {
    return windowsPathsNoEscape
        ? s.replace(/\[([^\/\\])\]/g, '$1')
        : s.replace(/((?!\\).|^)\[([^\/\\])\]/g, '$1$2').replace(/\\([^\/])/g, '$1');
};
exports.unescape = unescape;
//# sourceMappingURL=unescape.js.map

/***/ }),

/***/ "child_process":
/*!********************************!*\
  !*** external "child_process" ***!
  \********************************/
/***/ ((module) => {

"use strict";
module.exports = require("child_process");

/***/ }),

/***/ "events":
/*!*************************!*\
  !*** external "events" ***!
  \*************************/
/***/ ((module) => {

"use strict";
module.exports = require("events");

/***/ }),

/***/ "fs":
/*!*********************!*\
  !*** external "fs" ***!
  \*********************/
/***/ ((module) => {

"use strict";
module.exports = require("fs");

/***/ }),

/***/ "path":
/*!***********************!*\
  !*** external "path" ***!
  \***********************/
/***/ ((module) => {

"use strict";
module.exports = require("path");

/***/ }),

/***/ "process":
/*!**************************!*\
  !*** external "process" ***!
  \**************************/
/***/ ((module) => {

"use strict";
module.exports = require("process");

/***/ })

/******/ 	});
/************************************************************************/
/******/ 	// The module cache
/******/ 	var __webpack_module_cache__ = {};
/******/ 	
/******/ 	// The require function
/******/ 	function __webpack_require__(moduleId) {
/******/ 		// Check if module is in cache
/******/ 		var cachedModule = __webpack_module_cache__[moduleId];
/******/ 		if (cachedModule !== undefined) {
/******/ 			return cachedModule.exports;
/******/ 		}
/******/ 		// Create a new module (and put it into the cache)
/******/ 		var module = __webpack_module_cache__[moduleId] = {
/******/ 			// no module.id needed
/******/ 			// no module.loaded needed
/******/ 			exports: {}
/******/ 		};
/******/ 	
/******/ 		// Execute the module function
/******/ 		__webpack_modules__[moduleId].call(module.exports, module, module.exports, __webpack_require__);
/******/ 	
/******/ 		// Return the exports of the module
/******/ 		return module.exports;
/******/ 	}
/******/ 	
/************************************************************************/
var __webpack_exports__ = {};
// This entry needs to be wrapped in an IIFE because it needs to be in strict mode.
(() => {
"use strict";
var exports = __webpack_exports__;
/*!*********************!*\
  !*** ./src/main.ts ***!
  \*********************/
//#!/usr/bin/env node

/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
Object.defineProperty(exports, "__esModule", ({ value: true }));
const commander_1 = __webpack_require__(/*! commander */ "../../node_modules/commander/index.js");
const fs = __webpack_require__(/*! fs */ "fs");
const path = __webpack_require__(/*! path */ "path");
const child_process = __webpack_require__(/*! child_process */ "child_process");
const minimatch_1 = __webpack_require__(/*! minimatch */ "../../node_modules/minimatch/dist/commonjs/index.js");
const readdirSyncRecursive = (dir) => fs.readdirSync(dir).reduce((files, file) => {
    const name = path.join(dir, file);
    return fs.lstatSync(name).isDirectory() ? [...files, ...readdirSyncRecursive(name)] : [...files, name];
}, []);
const options = commander_1.program
    .option('--input-files <path>', 'Path to input file(s), comma separated')
    .option('--output-dir <path>', 'Path to output dir')
    .option('--compiler <path>', 'Path to compiler')
    .option('--link-name <path>', 'Name of combined link-name.abc', "all")
    .option('--target <ninja|make>', 'Target build system', "ninja")
    .option('--file-option', 'When provided pass the source as --file <path> rather than a free option')
    .option('--aot-libs <libs>', 'Comma-separated AOT libraries to include')
    .option('--only-aot <file>', 'AOT an .abc taking --aot-libs into account')
    .option('--aot-target <arm|arm64|x86|x86_64>', 'Compilation target for AOT')
    .parse()
    .opts();
if (options.onlyAot)
    mainAot(path.resolve(options.onlyAot));
else
    main(options.inputFiles, path.resolve(options.outputDir), options.linkName, options.target);
function findMatching(base, include, exclude) {
    return readdirSyncRecursive(base)
        .map(it => path.resolve(it))
        .filter(it => include.some(value => (0, minimatch_1.minimatch)(it, path.join(base, value), { matchBase: true })))
        .filter(it => !exclude.some(value => (0, minimatch_1.minimatch)(it, path.join(base, value), { matchBase: true })));
}
function producePairs(files, baseDir, rootDir, buildDir) {
    return files.map(srcFile => {
        const fileBuildDir = buildDir
            ? path.join(buildDir, path.relative(rootDir !== null && rootDir !== void 0 ? rootDir : baseDir, path.dirname(srcFile)))
            : path.dirname(srcFile);
        fs.mkdirSync(fileBuildDir, { recursive: true });
        return {
            input: srcFile,
            output: `${path.join(fileBuildDir, path.basename(srcFile).replace(path.extname(srcFile), ".abc"))}`
        };
    });
}
function archDir() {
    const arch = process.arch;
    let sdkArch = "";
    switch (arch) {
        case "x64":
            sdkArch = "";
            break;
        case "arm64":
            sdkArch = "arm64";
            break;
        default: throw new Error(`Unexpected arch: ${arch}`);
    }
    const platform = process.platform;
    let sdkPlatform = "";
    switch (platform) {
        case "linux":
            sdkPlatform = "linux";
            break;
        case "win32":
            sdkPlatform = "windows";
            break;
        case "darwin":
            sdkPlatform = "macos";
            break;
        default: throw new Error(`Unsupported platform ${platform}`);
    }
    const suffix = "host_tools";
    return [sdkPlatform, sdkArch, suffix].filter(it => it != "").join("_");
}
function produceMakefile(compiler, files, outputDir, config, linkName) {
    let result = [];
    let all = [];
    result.push("default: all");
    let basename = path.basename(compiler);
    let linker = compiler.replace(basename, 'arklink');
    files.forEach(it => {
        all.push(it.output);
        result.push(`${it.output}: ${it.input}`);
        result.push(`\t${compiler} --ets-module --arktsconfig ${path.resolve(config)} ${options.fileOption ? "--file" : ""} ${it.input} --output ${it.output}`);
    });
    result.push(`compile: ${all.join(' ')}`);
    result.push(`link: compile`);
    result.push(`\t${linker} --output ${outputDir}/${linkName}.abc -- ${all.join(' ')}`);
    result.push(`all: link`);
    return result.join('\n');
}
function produceNinjafile(compiler, files, outputDir, config, linkName) {
    // We have no Panda SDK for macOS.
    const tools_prefix = process.platform == "darwin" ? "echo " : "";
    let result = [];
    let all = [];
    let basename = path.basename(compiler);
    let linker = compiler.replace(basename, 'arklink');
    let prefix = `
rule arkts_compiler
    command = ${tools_prefix}${compiler} --ets-module --arktsconfig ${path.resolve(config)} ${options.fileOption ? "--file" : ""} $in --output $out
    description = "Compiling ARKTS $out"
rule arkts_linker
    command = ${tools_prefix}${linker} --output $out -- $in
    description = "Linking ARKTS $out"`;
    files.forEach(it => {
        all.push(it.output);
        result.push(`build ${it.output}: arkts_compiler ${it.input}\n`);
    });
    result.push(`build compile: phony ${all.join(' ')}`);
    result.push(`build ${outputDir}/${linkName}.abc: arkts_linker ${all.join(' ')}\n`);
    result.push(`build link: phony ${outputDir}/${linkName}.abc`);
    result.push(`build all: phony link`);
    result.push("default all\n");
    return prefix + '\n' + result.join('\n');
}
function main(inputFile, outputDir, linkName, target) {
    let config = JSON.parse(fs.readFileSync(inputFile, 'utf8'));
    let baseDir = path.resolve(path.dirname(inputFile));
    let include = config.include.map(it => it.replace('\\.', '.'));
    let exclude = config.exclude ? config.exclude.map(it => it.replace('\\.', '.')) : [];
    const buildDir = config.compilerOptions.outDir ? (path.resolve(config.compilerOptions.outDir)) : undefined;
    const rootDir = config.compilerOptions.rootDir ? (path.resolve(config.compilerOptions.rootDir)) : undefined;
    const files = producePairs(findMatching(baseDir, include, exclude), baseDir, rootDir, buildDir);
    if (files.length == 0) {
        throw new Error(`No files matching include "${include.join(",")}" exclude "${exclude.join(",")}"`);
    }
    fs.mkdirSync(outputDir, { recursive: true });
    if (target == 'make') {
        let maker = produceMakefile(path.resolve(options.compiler), files, outputDir, inputFile, linkName);
        fs.writeFileSync(`${outputDir}/Makefile`, maker);
    }
    else {
        let ninja = produceNinjafile(path.resolve(options.compiler), files, outputDir, inputFile, linkName);
        fs.writeFileSync(`${outputDir}/build.ninja`, ninja);
    }
}
function mainAot(abc) {
    var _a;
    let sdk = (_a = options.sdk) !== null && _a !== void 0 ? _a : path.resolve(path.join(__dirname, '..', '..', 'panda', 'node_modules', '@panda', 'sdk'));
    let aot = path.join(sdk, archDir(), 'bin', 'ark_aot');
    let stdlib = path.resolve(path.join(sdk, "ets", "etsstdlib.abc"));
    const aotLibs = [stdlib];
    if (options.aotLibs)
        aotLibs.push(...options.aotLibs.split(","));
    let args = [];
    if (process.platform == "darwin") {
        // No tools on macOS, just echo
        args.push(aot);
        aot = "echo";
    }
    let result = abc.replace('.abc', '.an');
    args.push(...options.aotTarget ? [`--compiler-cross-arch=${options.aotTarget}`] : []);
    args.push(...[
        `--load-runtimes=ets`,
        `--boot-panda-files=${aotLibs.join(':')}:${abc}`,
        `--paoc-panda-files=${abc}`,
        `--paoc-output=${result}`
    ]);
    console.log(`AOT compile ${abc}...`);
    const child = child_process.spawn(aot, args);
    child.stdout.on('data', (data) => {
        process.stdout.write(data);
    });
    child.stderr.on('data', (data) => {
        process.stderr.write(data);
    });
    child.on('close', (code) => {
        if (code != 0)
            console.log(`Command ${aot} ${args.join(" ")} failed with return code ${code}`);
        else
            console.log(`Produced AOT file ${result}: ${Math.round(fs.statSync(result).size / 1024 / 1024)}M`);
        process.exit(code);
    });
    child.on('exit', (code, signal) => {
        if (signal) {
            console.log(`Received signal: ${signal} from '${aot} ${args.join(' ')}'`);
            process.exit(1);
        }
    });
}

})();

module.exports = __webpack_exports__;
/******/ })()
;
//# sourceMappingURL=data:application/json;charset=utf-8;base64,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O0FBQ0Esd0JBQXdCLHVCQUF1QjtBQUMvQztBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQSx5Q0FBeUM7QUFDekM7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBLDRDQUE0QyxHQUFHO0FBQy9DO0FBQ0E7QUFDQSxTQUFTO0FBQ1Q7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0EsYUFBYTtBQUNiO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBLHlCQUF5QixLQUFLLE1BQU0sZUFBZTtBQUNuRDtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7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QTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBLGlEQUFpRCxpQkFBaUI7QUFDbEU7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0EsYUFBYTtBQUNiO0FBQ0E7QUFD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QUFLLENBQUMsTUFBTSxDQUFDLEVBQUUsQ0FBQyxNQUFNLEVBQUUsQ0FBQyxJQUFJLEVBQUUsRUFBRTtRQUM3QixPQUFPLENBQUMsTUFBTSxDQUFDLEtBQUssQ0FBQyxJQUFJLENBQUMsQ0FBQztJQUMvQixDQUFDLENBQUM7SUFDRixLQUFLLENBQUMsRUFBRSxDQUFDLE9BQU8sRUFBRSxDQUFDLElBQUksRUFBRSxFQUFFO1FBQ3ZCLElBQUksSUFBSSxJQUFJLENBQUM7WUFDVCxPQUFPLENBQUMsR0FBRyxDQUFDLFdBQVcsR0FBRyxJQUFJLElBQUksQ0FBQyxJQUFJLENBQUMsR0FBRyxDQUFDLDRCQUE0QixJQUFJLEVBQUUsQ0FBQzs7WUFFL0UsT0FBTyxDQUFDLEdBQUcsQ0FBQyxxQkFBcUIsTUFBTSxLQUFLLElBQUksQ0FBQyxLQUFLLENBQUMsRUFBRSxDQUFDLFFBQVEsQ0FBQyxNQUFNLENBQUMsQ0FBQyxJQUFJLEdBQUcsSUFBSSxHQUFHLElBQUksQ0FBQyxHQUFHLENBQUM7UUFDdEcsT0FBTyxDQUFDLElBQUksQ0FBQyxJQUFJLENBQUM7SUFDdEIsQ0FBQyxDQUFDO0lBQ0YsS0FBSyxDQUFDLEVBQUUsQ0FBQyxNQUFNLEVBQUUsQ0FBQyxJQUFJLEVBQUUsTUFBTSxFQUFFLEVBQUU7UUFDOUIsSUFBSSxNQUFNLEVBQUU7WUFDUixPQUFPLENBQUMsR0FBRyxDQUFDLG9CQUFvQixNQUFNLFVBQVUsR0FBRyxJQUFJLElBQUksQ0FBQyxJQUFJLENBQUMsR0FBRyxDQUFDLEdBQUcsQ0FBQztZQUN6RSxPQUFPLENBQUMsSUFBSSxDQUFDLENBQUMsQ0FBQztTQUNsQjtJQUNMLENBQUMsQ0FBQztBQUNOLENBQUMiLCJzb3VyY2VzIjpbIndlYnBhY2s6Ly9Aa29hbGF1aS9mYXN0LWFya3RzYy8uLi8uLi9ub2RlX21vZHVsZXMvYmFsYW5jZWQtbWF0Y2gvaW5kZXguanMiLCJ3ZWJwYWNrOi8vQGtvYWxhdWkvZmFzdC1hcmt0c2MvLi4vLi4vbm9kZV9tb2R1bGVzL2JyYWNlLWV4cGFuc2lvbi9pbmRleC5qcyIsIndlYnBhY2s6Ly9Aa29hbGF1aS9mYXN0LWFya3RzYy8uLi8uLi9ub2RlX21vZHVsZXMvY29tbWFuZGVyL2luZGV4LmpzIiwid2VicGFjazovL0Brb2FsYXVpL2Zhc3QtYXJrdHNjLy4uLy4uL25vZGVfbW9kdWxlcy9jb21tYW5kZXIvbGliL2FyZ3VtZW50LmpzIiwid2VicGFjazovL0Brb2FsYXVpL2Zhc3QtYXJrdHNjLy4uLy4uL25vZGVfbW9kdWxlcy9jb21tYW5kZXIvbGliL2NvbW1hbmQuanMiLCJ3ZWJwYWNrOi8vQGtvYWxhdWkvZmFzdC1hcmt0c2MvLi4vLi4vbm9kZV9tb2R1bGVzL2NvbW1hbmRlci9saWIvZXJyb3IuanMiLCJ3ZWJwYWNrOi8vQGtvYWxhdWkvZmFzdC1hcmt0c2MvLi4vLi4vbm9kZV9tb2R1bGVzL2NvbW1hbmRlci9saWIvaGVscC5qcyIsIndlYnBhY2s6Ly9Aa29hbGF1aS9mYXN0LWFya3RzYy8uLi8uLi9ub2RlX21vZHVsZXMvY29tbWFuZGVyL2xpYi9vcHRpb24uanMiLCJ3ZWJwYWNrOi8vQGtvYWxhdWkvZmFzdC1hcmt0c2MvLi4vLi4vbm9kZV9tb2R1bGVzL2NvbW1hbmRlci9saWIvc3VnZ2VzdFNpbWlsYXIuanMiLCJ3ZWJwYWNrOi8vQGtvYWxhdWkvZmFzdC1hcmt0c2MvLi4vLi4vbm9kZV9tb2R1bGVzL21pbmltYXRjaC9kaXN0L2NvbW1vbmpzL2Fzc2VydC12YWxpZC1wYXR0ZXJuLmpzIiwid2VicGFjazovL0Brb2FsYXVpL2Zhc3QtYXJrdHNjLy4uLy4uL25vZGVfbW9kdWxlcy9taW5pbWF0Y2gvZGlzdC9jb21tb25qcy9hc3QuanMiLCJ3ZWJwYWNrOi8vQGtvYWxhdWkvZmFzdC1hcmt0c2MvLi4vLi4vbm9kZV9tb2R1bGVzL21pbmltYXRjaC9kaXN0L2NvbW1vbmpzL2JyYWNlLWV4cHJlc3Npb25zLmpzIiwid2VicGFjazovL0Brb2FsYXVpL2Zhc3QtYXJrdHNjLy4uLy4uL25vZGVfbW9kdWxlcy9taW5pbWF0Y2gvZGlzdC9jb21tb25qcy9lc2NhcGUuanMiLCJ3ZWJwYWNrOi8vQGtvYWxhdWkvZmFzdC1hcmt0c2MvLi4vLi4vbm9kZV9tb2R1bGVzL21pbmltYXRjaC9kaXN0L2NvbW1vbmpzL2luZGV4LmpzIiwid2VicGFjazovL0Brb2FsYXVpL2Zhc3QtYXJrdHNjLy4uLy4uL25vZGVfbW9kdWxlcy9taW5pbWF0Y2gvZGlzdC9jb21tb25qcy91bmVzY2FwZS5qcyIsIndlYnBhY2s6Ly9Aa29hbGF1aS9mYXN0LWFya3RzYy9leHRlcm5hbCBub2RlLWNvbW1vbmpzIFwiY2hpbGRfcHJvY2Vzc1wiIiwid2VicGFjazovL0Brb2FsYXVpL2Zhc3QtYXJrdHNjL2V4dGVybmFsIG5vZGUtY29tbW9uanMgXCJldmVudHNcIiIsIndlYnBhY2s6Ly9Aa29hbGF1aS9mYXN0LWFya3RzYy9leHRlcm5hbCBub2RlLWNvbW1vbmpzIFwiZnNcIiIsIndlYnBhY2s6Ly9Aa29hbGF1aS9mYXN0LWFya3RzYy9leHRlcm5hbCBub2RlLWNvbW1vbmpzIFwicGF0aFwiIiwid2VicGFjazovL0Brb2FsYXVpL2Zhc3QtYXJrdHNjL2V4dGVybmFsIG5vZGUtY29tbW9uanMgXCJwcm9jZXNzXCIiLCJ3ZWJwYWNrOi8vQGtvYWxhdWkvZmFzdC1hcmt0c2Mvd2VicGFjay9ib290c3RyYXAiLCJ3ZWJwYWNrOi8vQGtvYWxhdWkvZmFzdC1hcmt0c2MvLi9zcmMvbWFpbi50cyJdLCJzb3VyY2VzQ29udGVudCI6WyIndXNlIHN0cmljdCc7XG5tb2R1bGUuZXhwb3J0cyA9IGJhbGFuY2VkO1xuZnVuY3Rpb24gYmFsYW5jZWQoYSwgYiwgc3RyKSB7XG4gIGlmIChhIGluc3RhbmNlb2YgUmVnRXhwKSBhID0gbWF5YmVNYXRjaChhLCBzdHIpO1xuICBpZiAoYiBpbnN0YW5jZW9mIFJlZ0V4cCkgYiA9IG1heWJlTWF0Y2goYiwgc3RyKTtcblxuICB2YXIgciA9IHJhbmdlKGEsIGIsIHN0cik7XG5cbiAgcmV0dXJuIHIgJiYge1xuICAgIHN0YXJ0OiByWzBdLFxuICAgIGVuZDogclsxXSxcbiAgICBwcmU6IHN0ci5zbGljZSgwLCByWzBdKSxcbiAgICBib2R5OiBzdHIuc2xpY2UoclswXSArIGEubGVuZ3RoLCByWzFdKSxcbiAgICBwb3N0OiBzdHIuc2xpY2UoclsxXSArIGIubGVuZ3RoKVxuICB9O1xufVxuXG5mdW5jdGlvbiBtYXliZU1hdGNoKHJlZywgc3RyKSB7XG4gIHZhciBtID0gc3RyLm1hdGNoKHJlZyk7XG4gIHJldHVybiBtID8gbVswXSA6IG51bGw7XG59XG5cbmJhbGFuY2VkLnJhbmdlID0gcmFuZ2U7XG5mdW5jdGlvbiByYW5nZShhLCBiLCBzdHIpIHtcbiAgdmFyIGJlZ3MsIGJlZywgbGVmdCwgcmlnaHQsIHJlc3VsdDtcbiAgdmFyIGFpID0gc3RyLmluZGV4T2YoYSk7XG4gIHZhciBiaSA9IHN0ci5pbmRleE9mKGIsIGFpICsgMSk7XG4gIHZhciBpID0gYWk7XG5cbiAgaWYgKGFpID49IDAgJiYgYmkgPiAwKSB7XG4gICAgaWYoYT09PWIpIHtcbiAgICAgIHJldHVybiBbYWksIGJpXTtcbiAgICB9XG4gICAgYmVncyA9IFtdO1xuICAgIGxlZnQgPSBzdHIubGVuZ3RoO1xuXG4gICAgd2hpbGUgKGkgPj0gMCAmJiAhcmVzdWx0KSB7XG4gICAgICBpZiAoaSA9PSBhaSkge1xuICAgICAgICBiZWdzLnB1c2goaSk7XG4gICAgICAgIGFpID0gc3RyLmluZGV4T2YoYSwgaSArIDEpO1xuICAgICAgfSBlbHNlIGlmIChiZWdzLmxlbmd0aCA9PSAxKSB7XG4gICAgICAgIHJlc3VsdCA9IFsgYmVncy5wb3AoKSwgYmkgXTtcbiAgICAgIH0gZWxzZSB7XG4gICAgICAgIGJlZyA9IGJlZ3MucG9wKCk7XG4gICAgICAgIGlmIChiZWcgPCBsZWZ0KSB7XG4gICAgICAgICAgbGVmdCA9IGJlZztcbiAgICAgICAgICByaWdodCA9IGJpO1xuICAgICAgICB9XG5cbiAgICAgICAgYmkgPSBzdHIuaW5kZXhPZihiLCBpICsgMSk7XG4gICAgICB9XG5cbiAgICAgIGkgPSBhaSA8IGJpICYmIGFpID49IDAgPyBhaSA6IGJpO1xuICAgIH1cblxuICAgIGlmIChiZWdzLmxlbmd0aCkge1xuICAgICAgcmVzdWx0ID0gWyBsZWZ0LCByaWdodCBdO1xuICAgIH1cbiAgfVxuXG4gIHJldHVybiByZXN1bHQ7XG59XG4iLCJ2YXIgYmFsYW5jZWQgPSByZXF1aXJlKCdiYWxhbmNlZC1tYXRjaCcpO1xuXG5tb2R1bGUuZXhwb3J0cyA9IGV4cGFuZFRvcDtcblxudmFyIGVzY1NsYXNoID0gJ1xcMFNMQVNIJytNYXRoLnJhbmRvbSgpKydcXDAnO1xudmFyIGVzY09wZW4gPSAnXFwwT1BFTicrTWF0aC5yYW5kb20oKSsnXFwwJztcbnZhciBlc2NDbG9zZSA9ICdcXDBDTE9TRScrTWF0aC5yYW5kb20oKSsnXFwwJztcbnZhciBlc2NDb21tYSA9ICdcXDBDT01NQScrTWF0aC5yYW5kb20oKSsnXFwwJztcbnZhciBlc2NQZXJpb2QgPSAnXFwwUEVSSU9EJytNYXRoLnJhbmRvbSgpKydcXDAnO1xuXG5mdW5jdGlvbiBudW1lcmljKHN0cikge1xuICByZXR1cm4gcGFyc2VJbnQoc3RyLCAxMCkgPT0gc3RyXG4gICAgPyBwYXJzZUludChzdHIsIDEwKVxuICAgIDogc3RyLmNoYXJDb2RlQXQoMCk7XG59XG5cbmZ1bmN0aW9uIGVzY2FwZUJyYWNlcyhzdHIpIHtcbiAgcmV0dXJuIHN0ci5zcGxpdCgnXFxcXFxcXFwnKS5qb2luKGVzY1NsYXNoKVxuICAgICAgICAgICAgLnNwbGl0KCdcXFxceycpLmpvaW4oZXNjT3BlbilcbiAgICAgICAgICAgIC5zcGxpdCgnXFxcXH0nKS5qb2luKGVzY0Nsb3NlKVxuICAgICAgICAgICAgLnNwbGl0KCdcXFxcLCcpLmpvaW4oZXNjQ29tbWEpXG4gICAgICAgICAgICAuc3BsaXQoJ1xcXFwuJykuam9pbihlc2NQZXJpb2QpO1xufVxuXG5mdW5jdGlvbiB1bmVzY2FwZUJyYWNlcyhzdHIpIHtcbiAgcmV0dXJuIHN0ci5zcGxpdChlc2NTbGFzaCkuam9pbignXFxcXCcpXG4gICAgICAgICAgICAuc3BsaXQoZXNjT3Blbikuam9pbigneycpXG4gICAgICAgICAgICAuc3BsaXQoZXNjQ2xvc2UpLmpvaW4oJ30nKVxuICAgICAgICAgICAgLnNwbGl0KGVzY0NvbW1hKS5qb2luKCcsJylcbiAgICAgICAgICAgIC5zcGxpdChlc2NQZXJpb2QpLmpvaW4oJy4nKTtcbn1cblxuXG4vLyBCYXNpY2FsbHkganVzdCBzdHIuc3BsaXQoXCIsXCIpLCBidXQgaGFuZGxpbmcgY2FzZXNcbi8vIHdoZXJlIHdlIGhhdmUgbmVzdGVkIGJyYWNlZCBzZWN0aW9ucywgd2hpY2ggc2hvdWxkIGJlXG4vLyB0cmVhdGVkIGFzIGluZGl2aWR1YWwgbWVtYmVycywgbGlrZSB7YSx7YixjfSxkfVxuZnVuY3Rpb24gcGFyc2VDb21tYVBhcnRzKHN0cikge1xuICBpZiAoIXN0cilcbiAgICByZXR1cm4gWycnXTtcblxuICB2YXIgcGFydHMgPSBbXTtcbiAgdmFyIG0gPSBiYWxhbmNlZCgneycsICd9Jywgc3RyKTtcblxuICBpZiAoIW0pXG4gICAgcmV0dXJuIHN0ci5zcGxpdCgnLCcpO1xuXG4gIHZhciBwcmUgPSBtLnByZTtcbiAgdmFyIGJvZHkgPSBtLmJvZHk7XG4gIHZhciBwb3N0ID0gbS5wb3N0O1xuICB2YXIgcCA9IHByZS5zcGxpdCgnLCcpO1xuXG4gIHBbcC5sZW5ndGgtMV0gKz0gJ3snICsgYm9keSArICd9JztcbiAgdmFyIHBvc3RQYXJ0cyA9IHBhcnNlQ29tbWFQYXJ0cyhwb3N0KTtcbiAgaWYgKHBvc3QubGVuZ3RoKSB7XG4gICAgcFtwLmxlbmd0aC0xXSArPSBwb3N0UGFydHMuc2hpZnQoKTtcbiAgICBwLnB1c2guYXBwbHkocCwgcG9zdFBhcnRzKTtcbiAgfVxuXG4gIHBhcnRzLnB1c2guYXBwbHkocGFydHMsIHApO1xuXG4gIHJldHVybiBwYXJ0cztcbn1cblxuZnVuY3Rpb24gZXhwYW5kVG9wKHN0cikge1xuICBpZiAoIXN0cilcbiAgICByZXR1cm4gW107XG5cbiAgLy8gSSBkb24ndCBrbm93IHdoeSBCYXNoIDQuMyBkb2VzIHRoaXMsIGJ1dCBpdCBkb2VzLlxuICAvLyBBbnl0aGluZyBzdGFydGluZyB3aXRoIHt9IHdpbGwgaGF2ZSB0aGUgZmlyc3QgdHdvIGJ5dGVzIHByZXNlcnZlZFxuICAvLyBidXQgKm9ubHkqIGF0IHRoZSB0b3AgbGV2ZWwsIHNvIHt9LGF9YiB3aWxsIG5vdCBleHBhbmQgdG8gYW55dGhpbmcsXG4gIC8vIGJ1dCBhe30sYn1jIHdpbGwgYmUgZXhwYW5kZWQgdG8gW2F9YyxhYmNdLlxuICAvLyBPbmUgY291bGQgYXJndWUgdGhhdCB0aGlzIGlzIGEgYnVnIGluIEJhc2gsIGJ1dCBzaW5jZSB0aGUgZ29hbCBvZlxuICAvLyB0aGlzIG1vZHVsZSBpcyB0byBtYXRjaCBCYXNoJ3MgcnVsZXMsIHdlIGVzY2FwZSBhIGxlYWRpbmcge31cbiAgaWYgKHN0ci5zdWJzdHIoMCwgMikgPT09ICd7fScpIHtcbiAgICBzdHIgPSAnXFxcXHtcXFxcfScgKyBzdHIuc3Vic3RyKDIpO1xuICB9XG5cbiAgcmV0dXJuIGV4cGFuZChlc2NhcGVCcmFjZXMoc3RyKSwgdHJ1ZSkubWFwKHVuZXNjYXBlQnJhY2VzKTtcbn1cblxuZnVuY3Rpb24gZW1icmFjZShzdHIpIHtcbiAgcmV0dXJuICd7JyArIHN0ciArICd9Jztcbn1cbmZ1bmN0aW9uIGlzUGFkZGVkKGVsKSB7XG4gIHJldHVybiAvXi0/MFxcZC8udGVzdChlbCk7XG59XG5cbmZ1bmN0aW9uIGx0ZShpLCB5KSB7XG4gIHJldHVybiBpIDw9IHk7XG59XG5mdW5jdGlvbiBndGUoaSwgeSkge1xuICByZXR1cm4gaSA+PSB5O1xufVxuXG5mdW5jdGlvbiBleHBhbmQoc3RyLCBpc1RvcCkge1xuICB2YXIgZXhwYW5zaW9ucyA9IFtdO1xuXG4gIHZhciBtID0gYmFsYW5jZWQoJ3snLCAnfScsIHN0cik7XG4gIGlmICghbSkgcmV0dXJuIFtzdHJdO1xuXG4gIC8vIG5vIG5lZWQgdG8gZXhwYW5kIHByZSwgc2luY2UgaXQgaXMgZ3VhcmFudGVlZCB0byBiZSBmcmVlIG9mIGJyYWNlLXNldHNcbiAgdmFyIHByZSA9IG0ucHJlO1xuICB2YXIgcG9zdCA9IG0ucG9zdC5sZW5ndGhcbiAgICA/IGV4cGFuZChtLnBvc3QsIGZhbHNlKVxuICAgIDogWycnXTtcblxuICBpZiAoL1xcJCQvLnRlc3QobS5wcmUpKSB7ICAgIFxuICAgIGZvciAodmFyIGsgPSAwOyBrIDwgcG9zdC5sZW5ndGg7IGsrKykge1xuICAgICAgdmFyIGV4cGFuc2lvbiA9IHByZSsgJ3snICsgbS5ib2R5ICsgJ30nICsgcG9zdFtrXTtcbiAgICAgIGV4cGFuc2lvbnMucHVzaChleHBhbnNpb24pO1xuICAgIH1cbiAgfSBlbHNlIHtcbiAgICB2YXIgaXNOdW1lcmljU2VxdWVuY2UgPSAvXi0/XFxkK1xcLlxcLi0/XFxkKyg/OlxcLlxcLi0/XFxkKyk/JC8udGVzdChtLmJvZHkpO1xuICAgIHZhciBpc0FscGhhU2VxdWVuY2UgPSAvXlthLXpBLVpdXFwuXFwuW2EtekEtWl0oPzpcXC5cXC4tP1xcZCspPyQvLnRlc3QobS5ib2R5KTtcbiAgICB2YXIgaXNTZXF1ZW5jZSA9IGlzTnVtZXJpY1NlcXVlbmNlIHx8IGlzQWxwaGFTZXF1ZW5jZTtcbiAgICB2YXIgaXNPcHRpb25zID0gbS5ib2R5LmluZGV4T2YoJywnKSA+PSAwO1xuICAgIGlmICghaXNTZXF1ZW5jZSAmJiAhaXNPcHRpb25zKSB7XG4gICAgICAvLyB7YX0sYn1cbiAgICAgIGlmIChtLnBvc3QubWF0Y2goLywuKlxcfS8pKSB7XG4gICAgICAgIHN0ciA9IG0ucHJlICsgJ3snICsgbS5ib2R5ICsgZXNjQ2xvc2UgKyBtLnBvc3Q7XG4gICAgICAgIHJldHVybiBleHBhbmQoc3RyKTtcbiAgICAgIH1cbiAgICAgIHJldHVybiBbc3RyXTtcbiAgICB9XG5cbiAgICB2YXIgbjtcbiAgICBpZiAoaXNTZXF1ZW5jZSkge1xuICAgICAgbiA9IG0uYm9keS5zcGxpdCgvXFwuXFwuLyk7XG4gICAgfSBlbHNlIHtcbiAgICAgIG4gPSBwYXJzZUNvbW1hUGFydHMobS5ib2R5KTtcbiAgICAgIGlmIChuLmxlbmd0aCA9PT0gMSkge1xuICAgICAgICAvLyB4e3thLGJ9fXkgPT0+IHh7YX15IHh7Yn15XG4gICAgICAgIG4gPSBleHBhbmQoblswXSwgZmFsc2UpLm1hcChlbWJyYWNlKTtcbiAgICAgICAgaWYgKG4ubGVuZ3RoID09PSAxKSB7XG4gICAgICAgICAgcmV0dXJuIHBvc3QubWFwKGZ1bmN0aW9uKHApIHtcbiAgICAgICAgICAgIHJldHVybiBtLnByZSArIG5bMF0gKyBwO1xuICAgICAgICAgIH0pO1xuICAgICAgICB9XG4gICAgICB9XG4gICAgfVxuXG4gICAgLy8gYXQgdGhpcyBwb2ludCwgbiBpcyB0aGUgcGFydHMsIGFuZCB3ZSBrbm93IGl0J3Mgbm90IGEgY29tbWEgc2V0XG4gICAgLy8gd2l0aCBhIHNpbmdsZSBlbnRyeS5cbiAgICB2YXIgTjtcblxuICAgIGlmIChpc1NlcXVlbmNlKSB7XG4gICAgICB2YXIgeCA9IG51bWVyaWMoblswXSk7XG4gICAgICB2YXIgeSA9IG51bWVyaWMoblsxXSk7XG4gICAgICB2YXIgd2lkdGggPSBNYXRoLm1heChuWzBdLmxlbmd0aCwgblsxXS5sZW5ndGgpXG4gICAgICB2YXIgaW5jciA9IG4ubGVuZ3RoID09IDNcbiAgICAgICAgPyBNYXRoLmFicyhudW1lcmljKG5bMl0pKVxuICAgICAgICA6IDE7XG4gICAgICB2YXIgdGVzdCA9IGx0ZTtcbiAgICAgIHZhciByZXZlcnNlID0geSA8IHg7XG4gICAgICBpZiAocmV2ZXJzZSkge1xuICAgICAgICBpbmNyICo9IC0xO1xuICAgICAgICB0ZXN0ID0gZ3RlO1xuICAgICAgfVxuICAgICAgdmFyIHBhZCA9IG4uc29tZShpc1BhZGRlZCk7XG5cbiAgICAgIE4gPSBbXTtcblxuICAgICAgZm9yICh2YXIgaSA9IHg7IHRlc3QoaSwgeSk7IGkgKz0gaW5jcikge1xuICAgICAgICB2YXIgYztcbiAgICAgICAgaWYgKGlzQWxwaGFTZXF1ZW5jZSkge1xuICAgICAgICAgIGMgPSBTdHJpbmcuZnJvbUNoYXJDb2RlKGkpO1xuICAgICAgICAgIGlmIChjID09PSAnXFxcXCcpXG4gICAgICAgICAgICBjID0gJyc7XG4gICAgICAgIH0gZWxzZSB7XG4gICAgICAgICAgYyA9IFN0cmluZyhpKTtcbiAgICAgICAgICBpZiAocGFkKSB7XG4gICAgICAgICAgICB2YXIgbmVlZCA9IHdpZHRoIC0gYy5sZW5ndGg7XG4gICAgICAgICAgICBpZiAobmVlZCA+IDApIHtcbiAgICAgICAgICAgICAgdmFyIHogPSBuZXcgQXJyYXkobmVlZCArIDEpLmpvaW4oJzAnKTtcbiAgICAgICAgICAgICAgaWYgKGkgPCAwKVxuICAgICAgICAgICAgICAgIGMgPSAnLScgKyB6ICsgYy5zbGljZSgxKTtcbiAgICAgICAgICAgICAgZWxzZVxuICAgICAgICAgICAgICAgIGMgPSB6ICsgYztcbiAgICAgICAgICAgIH1cbiAgICAgICAgICB9XG4gICAgICAgIH1cbiAgICAgICAgTi5wdXNoKGMpO1xuICAgICAgfVxuICAgIH0gZWxzZSB7XG4gICAgICBOID0gW107XG5cbiAgICAgIGZvciAodmFyIGogPSAwOyBqIDwgbi5sZW5ndGg7IGorKykge1xuICAgICAgICBOLnB1c2guYXBwbHkoTiwgZXhwYW5kKG5bal0sIGZhbHNlKSk7XG4gICAgICB9XG4gICAgfVxuXG4gICAgZm9yICh2YXIgaiA9IDA7IGogPCBOLmxlbmd0aDsgaisrKSB7XG4gICAgICBmb3IgKHZhciBrID0gMDsgayA8IHBvc3QubGVuZ3RoOyBrKyspIHtcbiAgICAgICAgdmFyIGV4cGFuc2lvbiA9IHByZSArIE5bal0gKyBwb3N0W2tdO1xuICAgICAgICBpZiAoIWlzVG9wIHx8IGlzU2VxdWVuY2UgfHwgZXhwYW5zaW9uKVxuICAgICAgICAgIGV4cGFuc2lvbnMucHVzaChleHBhbnNpb24pO1xuICAgICAgfVxuICAgIH1cbiAgfVxuXG4gIHJldHVybiBleHBhbnNpb25zO1xufVxuXG4iLCJjb25zdCB7IEFyZ3VtZW50IH0gPSByZXF1aXJlKCcuL2xpYi9hcmd1bWVudC5qcycpO1xuY29uc3QgeyBDb21tYW5kIH0gPSByZXF1aXJlKCcuL2xpYi9jb21tYW5kLmpzJyk7XG5jb25zdCB7IENvbW1hbmRlckVycm9yLCBJbnZhbGlkQXJndW1lbnRFcnJvciB9ID0gcmVxdWlyZSgnLi9saWIvZXJyb3IuanMnKTtcbmNvbnN0IHsgSGVscCB9ID0gcmVxdWlyZSgnLi9saWIvaGVscC5qcycpO1xuY29uc3QgeyBPcHRpb24gfSA9IHJlcXVpcmUoJy4vbGliL29wdGlvbi5qcycpO1xuXG4vLyBAdHMtY2hlY2tcblxuLyoqXG4gKiBFeHBvc2UgdGhlIHJvb3QgY29tbWFuZC5cbiAqL1xuXG5leHBvcnRzID0gbW9kdWxlLmV4cG9ydHMgPSBuZXcgQ29tbWFuZCgpO1xuZXhwb3J0cy5wcm9ncmFtID0gZXhwb3J0czsgLy8gTW9yZSBleHBsaWNpdCBhY2Nlc3MgdG8gZ2xvYmFsIGNvbW1hbmQuXG4vLyBJbXBsaWNpdCBleHBvcnQgb2YgY3JlYXRlQXJndW1lbnQsIGNyZWF0ZUNvbW1hbmQsIGFuZCBjcmVhdGVPcHRpb24uXG5cbi8qKlxuICogRXhwb3NlIGNsYXNzZXNcbiAqL1xuXG5leHBvcnRzLkFyZ3VtZW50ID0gQXJndW1lbnQ7XG5leHBvcnRzLkNvbW1hbmQgPSBDb21tYW5kO1xuZXhwb3J0cy5Db21tYW5kZXJFcnJvciA9IENvbW1hbmRlckVycm9yO1xuZXhwb3J0cy5IZWxwID0gSGVscDtcbmV4cG9ydHMuSW52YWxpZEFyZ3VtZW50RXJyb3IgPSBJbnZhbGlkQXJndW1lbnRFcnJvcjtcbmV4cG9ydHMuSW52YWxpZE9wdGlvbkFyZ3VtZW50RXJyb3IgPSBJbnZhbGlkQXJndW1lbnRFcnJvcjsgLy8gRGVwcmVjYXRlZFxuZXhwb3J0cy5PcHRpb24gPSBPcHRpb247XG4iLCJjb25zdCB7IEludmFsaWRBcmd1bWVudEVycm9yIH0gPSByZXF1aXJlKCcuL2Vycm9yLmpzJyk7XG5cbi8vIEB0cy1jaGVja1xuXG5jbGFzcyBBcmd1bWVudCB7XG4gIC8qKlxuICAgKiBJbml0aWFsaXplIGEgbmV3IGNvbW1hbmQgYXJndW1lbnQgd2l0aCB0aGUgZ2l2ZW4gbmFtZSBhbmQgZGVzY3JpcHRpb24uXG4gICAqIFRoZSBkZWZhdWx0IGlzIHRoYXQgdGhlIGFyZ3VtZW50IGlzIHJlcXVpcmVkLCBhbmQgeW91IGNhbiBleHBsaWNpdGx5XG4gICAqIGluZGljYXRlIHRoaXMgd2l0aCA8PiBhcm91bmQgdGhlIG5hbWUuIFB1dCBbXSBhcm91bmQgdGhlIG5hbWUgZm9yIGFuIG9wdGlvbmFsIGFyZ3VtZW50LlxuICAgKlxuICAgKiBAcGFyYW0ge3N0cmluZ30gbmFtZVxuICAgKiBAcGFyYW0ge3N0cmluZ30gW2Rlc2NyaXB0aW9uXVxuICAgKi9cblxuICBjb25zdHJ1Y3RvcihuYW1lLCBkZXNjcmlwdGlvbikge1xuICAgIHRoaXMuZGVzY3JpcHRpb24gPSBkZXNjcmlwdGlvbiB8fCAnJztcbiAgICB0aGlzLnZhcmlhZGljID0gZmFsc2U7XG4gICAgdGhpcy5wYXJzZUFyZyA9IHVuZGVmaW5lZDtcbiAgICB0aGlzLmRlZmF1bHRWYWx1ZSA9IHVuZGVmaW5lZDtcbiAgICB0aGlzLmRlZmF1bHRWYWx1ZURlc2NyaXB0aW9uID0gdW5kZWZpbmVkO1xuICAgIHRoaXMuYXJnQ2hvaWNlcyA9IHVuZGVmaW5lZDtcblxuICAgIHN3aXRjaCAobmFtZVswXSkge1xuICAgICAgY2FzZSAnPCc6IC8vIGUuZy4gPHJlcXVpcmVkPlxuICAgICAgICB0aGlzLnJlcXVpcmVkID0gdHJ1ZTtcbiAgICAgICAgdGhpcy5fbmFtZSA9IG5hbWUuc2xpY2UoMSwgLTEpO1xuICAgICAgICBicmVhaztcbiAgICAgIGNhc2UgJ1snOiAvLyBlLmcuIFtvcHRpb25hbF1cbiAgICAgICAgdGhpcy5yZXF1aXJlZCA9IGZhbHNlO1xuICAgICAgICB0aGlzLl9uYW1lID0gbmFtZS5zbGljZSgxLCAtMSk7XG4gICAgICAgIGJyZWFrO1xuICAgICAgZGVmYXVsdDpcbiAgICAgICAgdGhpcy5yZXF1aXJlZCA9IHRydWU7XG4gICAgICAgIHRoaXMuX25hbWUgPSBuYW1lO1xuICAgICAgICBicmVhaztcbiAgICB9XG5cbiAgICBpZiAodGhpcy5fbmFtZS5sZW5ndGggPiAzICYmIHRoaXMuX25hbWUuc2xpY2UoLTMpID09PSAnLi4uJykge1xuICAgICAgdGhpcy52YXJpYWRpYyA9IHRydWU7XG4gICAgICB0aGlzLl9uYW1lID0gdGhpcy5fbmFtZS5zbGljZSgwLCAtMyk7XG4gICAgfVxuICB9XG5cbiAgLyoqXG4gICAqIFJldHVybiBhcmd1bWVudCBuYW1lLlxuICAgKlxuICAgKiBAcmV0dXJuIHtzdHJpbmd9XG4gICAqL1xuXG4gIG5hbWUoKSB7XG4gICAgcmV0dXJuIHRoaXMuX25hbWU7XG4gIH1cblxuICAvKipcbiAgICogQGFwaSBwcml2YXRlXG4gICAqL1xuXG4gIF9jb25jYXRWYWx1ZSh2YWx1ZSwgcHJldmlvdXMpIHtcbiAgICBpZiAocHJldmlvdXMgPT09IHRoaXMuZGVmYXVsdFZhbHVlIHx8ICFBcnJheS5pc0FycmF5KHByZXZpb3VzKSkge1xuICAgICAgcmV0dXJuIFt2YWx1ZV07XG4gICAgfVxuXG4gICAgcmV0dXJuIHByZXZpb3VzLmNvbmNhdCh2YWx1ZSk7XG4gIH1cblxuICAvKipcbiAgICogU2V0IHRoZSBkZWZhdWx0IHZhbHVlLCBhbmQgb3B0aW9uYWxseSBzdXBwbHkgdGhlIGRlc2NyaXB0aW9uIHRvIGJlIGRpc3BsYXllZCBpbiB0aGUgaGVscC5cbiAgICpcbiAgICogQHBhcmFtIHthbnl9IHZhbHVlXG4gICAqIEBwYXJhbSB7c3RyaW5nfSBbZGVzY3JpcHRpb25dXG4gICAqIEByZXR1cm4ge0FyZ3VtZW50fVxuICAgKi9cblxuICBkZWZhdWx0KHZhbHVlLCBkZXNjcmlwdGlvbikge1xuICAgIHRoaXMuZGVmYXVsdFZhbHVlID0gdmFsdWU7XG4gICAgdGhpcy5kZWZhdWx0VmFsdWVEZXNjcmlwdGlvbiA9IGRlc2NyaXB0aW9uO1xuICAgIHJldHVybiB0aGlzO1xuICB9XG5cbiAgLyoqXG4gICAqIFNldCB0aGUgY3VzdG9tIGhhbmRsZXIgZm9yIHByb2Nlc3NpbmcgQ0xJIGNvbW1hbmQgYXJndW1lbnRzIGludG8gYXJndW1lbnQgdmFsdWVzLlxuICAgKlxuICAgKiBAcGFyYW0ge0Z1bmN0aW9ufSBbZm5dXG4gICAqIEByZXR1cm4ge0FyZ3VtZW50fVxuICAgKi9cblxuICBhcmdQYXJzZXIoZm4pIHtcbiAgICB0aGlzLnBhcnNlQXJnID0gZm47XG4gICAgcmV0dXJuIHRoaXM7XG4gIH1cblxuICAvKipcbiAgICogT25seSBhbGxvdyBhcmd1bWVudCB2YWx1ZSB0byBiZSBvbmUgb2YgY2hvaWNlcy5cbiAgICpcbiAgICogQHBhcmFtIHtzdHJpbmdbXX0gdmFsdWVzXG4gICAqIEByZXR1cm4ge0FyZ3VtZW50fVxuICAgKi9cblxuICBjaG9pY2VzKHZhbHVlcykge1xuICAgIHRoaXMuYXJnQ2hvaWNlcyA9IHZhbHVlcy5zbGljZSgpO1xuICAgIHRoaXMucGFyc2VBcmcgPSAoYXJnLCBwcmV2aW91cykgPT4ge1xuICAgICAgaWYgKCF0aGlzLmFyZ0Nob2ljZXMuaW5jbHVkZXMoYXJnKSkge1xuICAgICAgICB0aHJvdyBuZXcgSW52YWxpZEFyZ3VtZW50RXJyb3IoYEFsbG93ZWQgY2hvaWNlcyBhcmUgJHt0aGlzLmFyZ0Nob2ljZXMuam9pbignLCAnKX0uYCk7XG4gICAgICB9XG4gICAgICBpZiAodGhpcy52YXJpYWRpYykge1xuICAgICAgICByZXR1cm4gdGhpcy5fY29uY2F0VmFsdWUoYXJnLCBwcmV2aW91cyk7XG4gICAgICB9XG4gICAgICByZXR1cm4gYXJnO1xuICAgIH07XG4gICAgcmV0dXJuIHRoaXM7XG4gIH1cblxuICAvKipcbiAgICogTWFrZSBhcmd1bWVudCByZXF1aXJlZC5cbiAgICovXG4gIGFyZ1JlcXVpcmVkKCkge1xuICAgIHRoaXMucmVxdWlyZWQgPSB0cnVlO1xuICAgIHJldHVybiB0aGlzO1xuICB9XG5cbiAgLyoqXG4gICAqIE1ha2UgYXJndW1lbnQgb3B0aW9uYWwuXG4gICAqL1xuICBhcmdPcHRpb25hbCgpIHtcbiAgICB0aGlzLnJlcXVpcmVkID0gZmFsc2U7XG4gICAgcmV0dXJuIHRoaXM7XG4gIH1cbn1cblxuLyoqXG4gKiBUYWtlcyBhbiBhcmd1bWVudCBhbmQgcmV0dXJucyBpdHMgaHVtYW4gcmVhZGFibGUgZXF1aXZhbGVudCBmb3IgaGVscCB1c2FnZS5cbiAqXG4gKiBAcGFyYW0ge0FyZ3VtZW50fSBhcmdcbiAqIEByZXR1cm4ge3N0cmluZ31cbiAqIEBhcGkgcHJpdmF0ZVxuICovXG5cbmZ1bmN0aW9uIGh1bWFuUmVhZGFibGVBcmdOYW1lKGFyZykge1xuICBjb25zdCBuYW1lT3V0cHV0ID0gYXJnLm5hbWUoKSArIChhcmcudmFyaWFkaWMgPT09IHRydWUgPyAnLi4uJyA6ICcnKTtcblxuICByZXR1cm4gYXJnLnJlcXVpcmVkXG4gICAgPyAnPCcgKyBuYW1lT3V0cHV0ICsgJz4nXG4gICAgOiAnWycgKyBuYW1lT3V0cHV0ICsgJ10nO1xufVxuXG5leHBvcnRzLkFyZ3VtZW50ID0gQXJndW1lbnQ7XG5leHBvcnRzLmh1bWFuUmVhZGFibGVBcmdOYW1lID0gaHVtYW5SZWFkYWJsZUFyZ05hbWU7XG4iLCJjb25zdCBFdmVudEVtaXR0ZXIgPSByZXF1aXJlKCdldmVudHMnKS5FdmVudEVtaXR0ZXI7XG5jb25zdCBjaGlsZFByb2Nlc3MgPSByZXF1aXJlKCdjaGlsZF9wcm9jZXNzJyk7XG5jb25zdCBwYXRoID0gcmVxdWlyZSgncGF0aCcpO1xuY29uc3QgZnMgPSByZXF1aXJlKCdmcycpO1xuY29uc3QgcHJvY2VzcyA9IHJlcXVpcmUoJ3Byb2Nlc3MnKTtcblxuY29uc3QgeyBBcmd1bWVudCwgaHVtYW5SZWFkYWJsZUFyZ05hbWUgfSA9IHJlcXVpcmUoJy4vYXJndW1lbnQuanMnKTtcbmNvbnN0IHsgQ29tbWFuZGVyRXJyb3IgfSA9IHJlcXVpcmUoJy4vZXJyb3IuanMnKTtcbmNvbnN0IHsgSGVscCB9ID0gcmVxdWlyZSgnLi9oZWxwLmpzJyk7XG5jb25zdCB7IE9wdGlvbiwgc3BsaXRPcHRpb25GbGFncywgRHVhbE9wdGlvbnMgfSA9IHJlcXVpcmUoJy4vb3B0aW9uLmpzJyk7XG5jb25zdCB7IHN1Z2dlc3RTaW1pbGFyIH0gPSByZXF1aXJlKCcuL3N1Z2dlc3RTaW1pbGFyJyk7XG5cbi8vIEB0cy1jaGVja1xuXG5jbGFzcyBDb21tYW5kIGV4dGVuZHMgRXZlbnRFbWl0dGVyIHtcbiAgLyoqXG4gICAqIEluaXRpYWxpemUgYSBuZXcgYENvbW1hbmRgLlxuICAgKlxuICAgKiBAcGFyYW0ge3N0cmluZ30gW25hbWVdXG4gICAqL1xuXG4gIGNvbnN0cnVjdG9yKG5hbWUpIHtcbiAgICBzdXBlcigpO1xuICAgIC8qKiBAdHlwZSB7Q29tbWFuZFtdfSAqL1xuICAgIHRoaXMuY29tbWFuZHMgPSBbXTtcbiAgICAvKiogQHR5cGUge09wdGlvbltdfSAqL1xuICAgIHRoaXMub3B0aW9ucyA9IFtdO1xuICAgIHRoaXMucGFyZW50ID0gbnVsbDtcbiAgICB0aGlzLl9hbGxvd1Vua25vd25PcHRpb24gPSBmYWxzZTtcbiAgICB0aGlzLl9hbGxvd0V4Y2Vzc0FyZ3VtZW50cyA9IHRydWU7XG4gICAgLyoqIEB0eXBlIHtBcmd1bWVudFtdfSAqL1xuICAgIHRoaXMuX2FyZ3MgPSBbXTtcbiAgICAvKiogQHR5cGUge3N0cmluZ1tdfSAqL1xuICAgIHRoaXMuYXJncyA9IFtdOyAvLyBjbGkgYXJncyB3aXRoIG9wdGlvbnMgcmVtb3ZlZFxuICAgIHRoaXMucmF3QXJncyA9IFtdO1xuICAgIHRoaXMucHJvY2Vzc2VkQXJncyA9IFtdOyAvLyBsaWtlIC5hcmdzIGJ1dCBhZnRlciBjdXN0b20gcHJvY2Vzc2luZyBhbmQgY29sbGVjdGluZyB2YXJpYWRpY1xuICAgIHRoaXMuX3NjcmlwdFBhdGggPSBudWxsO1xuICAgIHRoaXMuX25hbWUgPSBuYW1lIHx8ICcnO1xuICAgIHRoaXMuX29wdGlvblZhbHVlcyA9IHt9O1xuICAgIHRoaXMuX29wdGlvblZhbHVlU291cmNlcyA9IHt9OyAvLyBkZWZhdWx0LCBlbnYsIGNsaSBldGNcbiAgICB0aGlzLl9zdG9yZU9wdGlvbnNBc1Byb3BlcnRpZXMgPSBmYWxzZTtcbiAgICB0aGlzLl9hY3Rpb25IYW5kbGVyID0gbnVsbDtcbiAgICB0aGlzLl9leGVjdXRhYmxlSGFuZGxlciA9IGZhbHNlO1xuICAgIHRoaXMuX2V4ZWN1dGFibGVGaWxlID0gbnVsbDsgLy8gY3VzdG9tIG5hbWUgZm9yIGV4ZWN1dGFibGVcbiAgICB0aGlzLl9leGVjdXRhYmxlRGlyID0gbnVsbDsgLy8gY3VzdG9tIHNlYXJjaCBkaXJlY3RvcnkgZm9yIHN1YmNvbW1hbmRzXG4gICAgdGhpcy5fZGVmYXVsdENvbW1hbmROYW1lID0gbnVsbDtcbiAgICB0aGlzLl9leGl0Q2FsbGJhY2sgPSBudWxsO1xuICAgIHRoaXMuX2FsaWFzZXMgPSBbXTtcbiAgICB0aGlzLl9jb21iaW5lRmxhZ0FuZE9wdGlvbmFsVmFsdWUgPSB0cnVlO1xuICAgIHRoaXMuX2Rlc2NyaXB0aW9uID0gJyc7XG4gICAgdGhpcy5fc3VtbWFyeSA9ICcnO1xuICAgIHRoaXMuX2FyZ3NEZXNjcmlwdGlvbiA9IHVuZGVmaW5lZDsgLy8gbGVnYWN5XG4gICAgdGhpcy5fZW5hYmxlUG9zaXRpb25hbE9wdGlvbnMgPSBmYWxzZTtcbiAgICB0aGlzLl9wYXNzVGhyb3VnaE9wdGlvbnMgPSBmYWxzZTtcbiAgICB0aGlzLl9saWZlQ3ljbGVIb29rcyA9IHt9OyAvLyBhIGhhc2ggb2YgYXJyYXlzXG4gICAgLyoqIEB0eXBlIHtib29sZWFuIHwgc3RyaW5nfSAqL1xuICAgIHRoaXMuX3Nob3dIZWxwQWZ0ZXJFcnJvciA9IGZhbHNlO1xuICAgIHRoaXMuX3Nob3dTdWdnZXN0aW9uQWZ0ZXJFcnJvciA9IHRydWU7XG5cbiAgICAvLyBzZWUgLmNvbmZpZ3VyZU91dHB1dCgpIGZvciBkb2NzXG4gICAgdGhpcy5fb3V0cHV0Q29uZmlndXJhdGlvbiA9IHtcbiAgICAgIHdyaXRlT3V0OiAoc3RyKSA9PiBwcm9jZXNzLnN0ZG91dC53cml0ZShzdHIpLFxuICAgICAgd3JpdGVFcnI6IChzdHIpID0+IHByb2Nlc3Muc3RkZXJyLndyaXRlKHN0ciksXG4gICAgICBnZXRPdXRIZWxwV2lkdGg6ICgpID0+IHByb2Nlc3Muc3Rkb3V0LmlzVFRZID8gcHJvY2Vzcy5zdGRvdXQuY29sdW1ucyA6IHVuZGVmaW5lZCxcbiAgICAgIGdldEVyckhlbHBXaWR0aDogKCkgPT4gcHJvY2Vzcy5zdGRlcnIuaXNUVFkgPyBwcm9jZXNzLnN0ZGVyci5jb2x1bW5zIDogdW5kZWZpbmVkLFxuICAgICAgb3V0cHV0RXJyb3I6IChzdHIsIHdyaXRlKSA9PiB3cml0ZShzdHIpXG4gICAgfTtcblxuICAgIHRoaXMuX2hpZGRlbiA9IGZhbHNlO1xuICAgIHRoaXMuX2hhc0hlbHBPcHRpb24gPSB0cnVlO1xuICAgIHRoaXMuX2hlbHBGbGFncyA9ICctaCwgLS1oZWxwJztcbiAgICB0aGlzLl9oZWxwRGVzY3JpcHRpb24gPSAnZGlzcGxheSBoZWxwIGZvciBjb21tYW5kJztcbiAgICB0aGlzLl9oZWxwU2hvcnRGbGFnID0gJy1oJztcbiAgICB0aGlzLl9oZWxwTG9uZ0ZsYWcgPSAnLS1oZWxwJztcbiAgICB0aGlzLl9hZGRJbXBsaWNpdEhlbHBDb21tYW5kID0gdW5kZWZpbmVkOyAvLyBEZWxpYmVyYXRlbHkgdW5kZWZpbmVkLCBub3QgZGVjaWRlZCB3aGV0aGVyIHRydWUgb3IgZmFsc2VcbiAgICB0aGlzLl9oZWxwQ29tbWFuZE5hbWUgPSAnaGVscCc7XG4gICAgdGhpcy5faGVscENvbW1hbmRuYW1lQW5kQXJncyA9ICdoZWxwIFtjb21tYW5kXSc7XG4gICAgdGhpcy5faGVscENvbW1hbmREZXNjcmlwdGlvbiA9ICdkaXNwbGF5IGhlbHAgZm9yIGNvbW1hbmQnO1xuICAgIHRoaXMuX2hlbHBDb25maWd1cmF0aW9uID0ge307XG4gIH1cblxuICAvKipcbiAgICogQ29weSBzZXR0aW5ncyB0aGF0IGFyZSB1c2VmdWwgdG8gaGF2ZSBpbiBjb21tb24gYWNyb3NzIHJvb3QgY29tbWFuZCBhbmQgc3ViY29tbWFuZHMuXG4gICAqXG4gICAqIChVc2VkIGludGVybmFsbHkgd2hlbiBhZGRpbmcgYSBjb21tYW5kIHVzaW5nIGAuY29tbWFuZCgpYCBzbyBzdWJjb21tYW5kcyBpbmhlcml0IHBhcmVudCBzZXR0aW5ncy4pXG4gICAqXG4gICAqIEBwYXJhbSB7Q29tbWFuZH0gc291cmNlQ29tbWFuZFxuICAgKiBAcmV0dXJuIHtDb21tYW5kfSBgdGhpc2AgY29tbWFuZCBmb3IgY2hhaW5pbmdcbiAgICovXG4gIGNvcHlJbmhlcml0ZWRTZXR0aW5ncyhzb3VyY2VDb21tYW5kKSB7XG4gICAgdGhpcy5fb3V0cHV0Q29uZmlndXJhdGlvbiA9IHNvdXJjZUNvbW1hbmQuX291dHB1dENvbmZpZ3VyYXRpb247XG4gICAgdGhpcy5faGFzSGVscE9wdGlvbiA9IHNvdXJjZUNvbW1hbmQuX2hhc0hlbHBPcHRpb247XG4gICAgdGhpcy5faGVscEZsYWdzID0gc291cmNlQ29tbWFuZC5faGVscEZsYWdzO1xuICAgIHRoaXMuX2hlbHBEZXNjcmlwdGlvbiA9IHNvdXJjZUNvbW1hbmQuX2hlbHBEZXNjcmlwdGlvbjtcbiAgICB0aGlzLl9oZWxwU2hvcnRGbGFnID0gc291cmNlQ29tbWFuZC5faGVscFNob3J0RmxhZztcbiAgICB0aGlzLl9oZWxwTG9uZ0ZsYWcgPSBzb3VyY2VDb21tYW5kLl9oZWxwTG9uZ0ZsYWc7XG4gICAgdGhpcy5faGVscENvbW1hbmROYW1lID0gc291cmNlQ29tbWFuZC5faGVscENvbW1hbmROYW1lO1xuICAgIHRoaXMuX2hlbHBDb21tYW5kbmFtZUFuZEFyZ3MgPSBzb3VyY2VDb21tYW5kLl9oZWxwQ29tbWFuZG5hbWVBbmRBcmdzO1xuICAgIHRoaXMuX2hlbHBDb21tYW5kRGVzY3JpcHRpb24gPSBzb3VyY2VDb21tYW5kLl9oZWxwQ29tbWFuZERlc2NyaXB0aW9uO1xuICAgIHRoaXMuX2hlbHBDb25maWd1cmF0aW9uID0gc291cmNlQ29tbWFuZC5faGVscENvbmZpZ3VyYXRpb247XG4gICAgdGhpcy5fZXhpdENhbGxiYWNrID0gc291cmNlQ29tbWFuZC5fZXhpdENhbGxiYWNrO1xuICAgIHRoaXMuX3N0b3JlT3B0aW9uc0FzUHJvcGVydGllcyA9IHNvdXJjZUNvbW1hbmQuX3N0b3JlT3B0aW9uc0FzUHJvcGVydGllcztcbiAgICB0aGlzLl9jb21iaW5lRmxhZ0FuZE9wdGlvbmFsVmFsdWUgPSBzb3VyY2VDb21tYW5kLl9jb21iaW5lRmxhZ0FuZE9wdGlvbmFsVmFsdWU7XG4gICAgdGhpcy5fYWxsb3dFeGNlc3NBcmd1bWVudHMgPSBzb3VyY2VDb21tYW5kLl9hbGxvd0V4Y2Vzc0FyZ3VtZW50cztcbiAgICB0aGlzLl9lbmFibGVQb3NpdGlvbmFsT3B0aW9ucyA9IHNvdXJjZUNvbW1hbmQuX2VuYWJsZVBvc2l0aW9uYWxPcHRpb25zO1xuICAgIHRoaXMuX3Nob3dIZWxwQWZ0ZXJFcnJvciA9IHNvdXJjZUNvbW1hbmQuX3Nob3dIZWxwQWZ0ZXJFcnJvcjtcbiAgICB0aGlzLl9zaG93U3VnZ2VzdGlvbkFmdGVyRXJyb3IgPSBzb3VyY2VDb21tYW5kLl9zaG93U3VnZ2VzdGlvbkFmdGVyRXJyb3I7XG5cbiAgICByZXR1cm4gdGhpcztcbiAgfVxuXG4gIC8qKlxuICAgKiBEZWZpbmUgYSBjb21tYW5kLlxuICAgKlxuICAgKiBUaGVyZSBhcmUgdHdvIHN0eWxlcyBvZiBjb21tYW5kOiBwYXkgYXR0ZW50aW9uIHRvIHdoZXJlIHRvIHB1dCB0aGUgZGVzY3JpcHRpb24uXG4gICAqXG4gICAqIEBleGFtcGxlXG4gICAqIC8vIENvbW1hbmQgaW1wbGVtZW50ZWQgdXNpbmcgYWN0aW9uIGhhbmRsZXIgKGRlc2NyaXB0aW9uIGlzIHN1cHBsaWVkIHNlcGFyYXRlbHkgdG8gYC5jb21tYW5kYClcbiAgICogcHJvZ3JhbVxuICAgKiAgIC5jb21tYW5kKCdjbG9uZSA8c291cmNlPiBbZGVzdGluYXRpb25dJylcbiAgICogICAuZGVzY3JpcHRpb24oJ2Nsb25lIGEgcmVwb3NpdG9yeSBpbnRvIGEgbmV3bHkgY3JlYXRlZCBkaXJlY3RvcnknKVxuICAgKiAgIC5hY3Rpb24oKHNvdXJjZSwgZGVzdGluYXRpb24pID0+IHtcbiAgICogICAgIGNvbnNvbGUubG9nKCdjbG9uZSBjb21tYW5kIGNhbGxlZCcpO1xuICAgKiAgIH0pO1xuICAgKlxuICAgKiAvLyBDb21tYW5kIGltcGxlbWVudGVkIHVzaW5nIHNlcGFyYXRlIGV4ZWN1dGFibGUgZmlsZSAoZGVzY3JpcHRpb24gaXMgc2Vjb25kIHBhcmFtZXRlciB0byBgLmNvbW1hbmRgKVxuICAgKiBwcm9ncmFtXG4gICAqICAgLmNvbW1hbmQoJ3N0YXJ0IDxzZXJ2aWNlPicsICdzdGFydCBuYW1lZCBzZXJ2aWNlJylcbiAgICogICAuY29tbWFuZCgnc3RvcCBbc2VydmljZV0nLCAnc3RvcCBuYW1lZCBzZXJ2aWNlLCBvciBhbGwgaWYgbm8gbmFtZSBzdXBwbGllZCcpO1xuICAgKlxuICAgKiBAcGFyYW0ge3N0cmluZ30gbmFtZUFuZEFyZ3MgLSBjb21tYW5kIG5hbWUgYW5kIGFyZ3VtZW50cywgYXJncyBhcmUgYDxyZXF1aXJlZD5gIG9yIGBbb3B0aW9uYWxdYCBhbmQgbGFzdCBtYXkgYWxzbyBiZSBgdmFyaWFkaWMuLi5gXG4gICAqIEBwYXJhbSB7T2JqZWN0fHN0cmluZ30gW2FjdGlvbk9wdHNPckV4ZWNEZXNjXSAtIGNvbmZpZ3VyYXRpb24gb3B0aW9ucyAoZm9yIGFjdGlvbiksIG9yIGRlc2NyaXB0aW9uIChmb3IgZXhlY3V0YWJsZSlcbiAgICogQHBhcmFtIHtPYmplY3R9IFtleGVjT3B0c10gLSBjb25maWd1cmF0aW9uIG9wdGlvbnMgKGZvciBleGVjdXRhYmxlKVxuICAgKiBAcmV0dXJuIHtDb21tYW5kfSByZXR1cm5zIG5ldyBjb21tYW5kIGZvciBhY3Rpb24gaGFuZGxlciwgb3IgYHRoaXNgIGZvciBleGVjdXRhYmxlIGNvbW1hbmRcbiAgICovXG5cbiAgY29tbWFuZChuYW1lQW5kQXJncywgYWN0aW9uT3B0c09yRXhlY0Rlc2MsIGV4ZWNPcHRzKSB7XG4gICAgbGV0IGRlc2MgPSBhY3Rpb25PcHRzT3JFeGVjRGVzYztcbiAgICBsZXQgb3B0cyA9IGV4ZWNPcHRzO1xuICAgIGlmICh0eXBlb2YgZGVzYyA9PT0gJ29iamVjdCcgJiYgZGVzYyAhPT0gbnVsbCkge1xuICAgICAgb3B0cyA9IGRlc2M7XG4gICAgICBkZXNjID0gbnVsbDtcbiAgICB9XG4gICAgb3B0cyA9IG9wdHMgfHwge307XG4gICAgY29uc3QgWywgbmFtZSwgYXJnc10gPSBuYW1lQW5kQXJncy5tYXRjaCgvKFteIF0rKSAqKC4qKS8pO1xuXG4gICAgY29uc3QgY21kID0gdGhpcy5jcmVhdGVDb21tYW5kKG5hbWUpO1xuICAgIGlmIChkZXNjKSB7XG4gICAgICBjbWQuZGVzY3JpcHRpb24oZGVzYyk7XG4gICAgICBjbWQuX2V4ZWN1dGFibGVIYW5kbGVyID0gdHJ1ZTtcbiAgICB9XG4gICAgaWYgKG9wdHMuaXNEZWZhdWx0KSB0aGlzLl9kZWZhdWx0Q29tbWFuZE5hbWUgPSBjbWQuX25hbWU7XG4gICAgY21kLl9oaWRkZW4gPSAhIShvcHRzLm5vSGVscCB8fCBvcHRzLmhpZGRlbik7IC8vIG5vSGVscCBpcyBkZXByZWNhdGVkIG9sZCBuYW1lIGZvciBoaWRkZW5cbiAgICBjbWQuX2V4ZWN1dGFibGVGaWxlID0gb3B0cy5leGVjdXRhYmxlRmlsZSB8fCBudWxsOyAvLyBDdXN0b20gbmFtZSBmb3IgZXhlY3V0YWJsZSBmaWxlLCBzZXQgbWlzc2luZyB0byBudWxsIHRvIG1hdGNoIGNvbnN0cnVjdG9yXG4gICAgaWYgKGFyZ3MpIGNtZC5hcmd1bWVudHMoYXJncyk7XG4gICAgdGhpcy5jb21tYW5kcy5wdXNoKGNtZCk7XG4gICAgY21kLnBhcmVudCA9IHRoaXM7XG4gICAgY21kLmNvcHlJbmhlcml0ZWRTZXR0aW5ncyh0aGlzKTtcblxuICAgIGlmIChkZXNjKSByZXR1cm4gdGhpcztcbiAgICByZXR1cm4gY21kO1xuICB9XG5cbiAgLyoqXG4gICAqIEZhY3Rvcnkgcm91dGluZSB0byBjcmVhdGUgYSBuZXcgdW5hdHRhY2hlZCBjb21tYW5kLlxuICAgKlxuICAgKiBTZWUgLmNvbW1hbmQoKSBmb3IgY3JlYXRpbmcgYW4gYXR0YWNoZWQgc3ViY29tbWFuZCwgd2hpY2ggdXNlcyB0aGlzIHJvdXRpbmUgdG9cbiAgICogY3JlYXRlIHRoZSBjb21tYW5kLiBZb3UgY2FuIG92ZXJyaWRlIGNyZWF0ZUNvbW1hbmQgdG8gY3VzdG9taXNlIHN1YmNvbW1hbmRzLlxuICAgKlxuICAgKiBAcGFyYW0ge3N0cmluZ30gW25hbWVdXG4gICAqIEByZXR1cm4ge0NvbW1hbmR9IG5ldyBjb21tYW5kXG4gICAqL1xuXG4gIGNyZWF0ZUNvbW1hbmQobmFtZSkge1xuICAgIHJldHVybiBuZXcgQ29tbWFuZChuYW1lKTtcbiAgfVxuXG4gIC8qKlxuICAgKiBZb3UgY2FuIGN1c3RvbWlzZSB0aGUgaGVscCB3aXRoIGEgc3ViY2xhc3Mgb2YgSGVscCBieSBvdmVycmlkaW5nIGNyZWF0ZUhlbHAsXG4gICAqIG9yIGJ5IG92ZXJyaWRpbmcgSGVscCBwcm9wZXJ0aWVzIHVzaW5nIGNvbmZpZ3VyZUhlbHAoKS5cbiAgICpcbiAgICogQHJldHVybiB7SGVscH1cbiAgICovXG5cbiAgY3JlYXRlSGVscCgpIHtcbiAgICByZXR1cm4gT2JqZWN0LmFzc2lnbihuZXcgSGVscCgpLCB0aGlzLmNvbmZpZ3VyZUhlbHAoKSk7XG4gIH1cblxuICAvKipcbiAgICogWW91IGNhbiBjdXN0b21pc2UgdGhlIGhlbHAgYnkgb3ZlcnJpZGluZyBIZWxwIHByb3BlcnRpZXMgdXNpbmcgY29uZmlndXJlSGVscCgpLFxuICAgKiBvciB3aXRoIGEgc3ViY2xhc3Mgb2YgSGVscCBieSBvdmVycmlkaW5nIGNyZWF0ZUhlbHAoKS5cbiAgICpcbiAgICogQHBhcmFtIHtPYmplY3R9IFtjb25maWd1cmF0aW9uXSAtIGNvbmZpZ3VyYXRpb24gb3B0aW9uc1xuICAgKiBAcmV0dXJuIHtDb21tYW5kfE9iamVjdH0gYHRoaXNgIGNvbW1hbmQgZm9yIGNoYWluaW5nLCBvciBzdG9yZWQgY29uZmlndXJhdGlvblxuICAgKi9cblxuICBjb25maWd1cmVIZWxwKGNvbmZpZ3VyYXRpb24pIHtcbiAgICBpZiAoY29uZmlndXJhdGlvbiA9PT0gdW5kZWZpbmVkKSByZXR1cm4gdGhpcy5faGVscENvbmZpZ3VyYXRpb247XG5cbiAgICB0aGlzLl9oZWxwQ29uZmlndXJhdGlvbiA9IGNvbmZpZ3VyYXRpb247XG4gICAgcmV0dXJuIHRoaXM7XG4gIH1cblxuICAvKipcbiAgICogVGhlIGRlZmF1bHQgb3V0cHV0IGdvZXMgdG8gc3Rkb3V0IGFuZCBzdGRlcnIuIFlvdSBjYW4gY3VzdG9taXNlIHRoaXMgZm9yIHNwZWNpYWxcbiAgICogYXBwbGljYXRpb25zLiBZb3UgY2FuIGFsc28gY3VzdG9taXNlIHRoZSBkaXNwbGF5IG9mIGVycm9ycyBieSBvdmVycmlkaW5nIG91dHB1dEVycm9yLlxuICAgKlxuICAgKiBUaGUgY29uZmlndXJhdGlvbiBwcm9wZXJ0aWVzIGFyZSBhbGwgZnVuY3Rpb25zOlxuICAgKlxuICAgKiAgICAgLy8gZnVuY3Rpb25zIHRvIGNoYW5nZSB3aGVyZSBiZWluZyB3cml0dGVuLCBzdGRvdXQgYW5kIHN0ZGVyclxuICAgKiAgICAgd3JpdGVPdXQoc3RyKVxuICAgKiAgICAgd3JpdGVFcnIoc3RyKVxuICAgKiAgICAgLy8gbWF0Y2hpbmcgZnVuY3Rpb25zIHRvIHNwZWNpZnkgd2lkdGggZm9yIHdyYXBwaW5nIGhlbHBcbiAgICogICAgIGdldE91dEhlbHBXaWR0aCgpXG4gICAqICAgICBnZXRFcnJIZWxwV2lkdGgoKVxuICAgKiAgICAgLy8gZnVuY3Rpb25zIGJhc2VkIG9uIHdoYXQgaXMgYmVpbmcgd3JpdHRlbiBvdXRcbiAgICogICAgIG91dHB1dEVycm9yKHN0ciwgd3JpdGUpIC8vIHVzZWQgZm9yIGRpc3BsYXlpbmcgZXJyb3JzLCBhbmQgbm90IHVzZWQgZm9yIGRpc3BsYXlpbmcgaGVscFxuICAgKlxuICAgKiBAcGFyYW0ge09iamVjdH0gW2NvbmZpZ3VyYXRpb25dIC0gY29uZmlndXJhdGlvbiBvcHRpb25zXG4gICAqIEByZXR1cm4ge0NvbW1hbmR8T2JqZWN0fSBgdGhpc2AgY29tbWFuZCBmb3IgY2hhaW5pbmcsIG9yIHN0b3JlZCBjb25maWd1cmF0aW9uXG4gICAqL1xuXG4gIGNvbmZpZ3VyZU91dHB1dChjb25maWd1cmF0aW9uKSB7XG4gICAgaWYgKGNvbmZpZ3VyYXRpb24gPT09IHVuZGVmaW5lZCkgcmV0dXJuIHRoaXMuX291dHB1dENvbmZpZ3VyYXRpb247XG5cbiAgICBPYmplY3QuYXNzaWduKHRoaXMuX291dHB1dENvbmZpZ3VyYXRpb24sIGNvbmZpZ3VyYXRpb24pO1xuICAgIHJldHVybiB0aGlzO1xuICB9XG5cbiAgLyoqXG4gICAqIERpc3BsYXkgdGhlIGhlbHAgb3IgYSBjdXN0b20gbWVzc2FnZSBhZnRlciBhbiBlcnJvciBvY2N1cnMuXG4gICAqXG4gICAqIEBwYXJhbSB7Ym9vbGVhbnxzdHJpbmd9IFtkaXNwbGF5SGVscF1cbiAgICogQHJldHVybiB7Q29tbWFuZH0gYHRoaXNgIGNvbW1hbmQgZm9yIGNoYWluaW5nXG4gICAqL1xuICBzaG93SGVscEFmdGVyRXJyb3IoZGlzcGxheUhlbHAgPSB0cnVlKSB7XG4gICAgaWYgKHR5cGVvZiBkaXNwbGF5SGVscCAhPT0gJ3N0cmluZycpIGRpc3BsYXlIZWxwID0gISFkaXNwbGF5SGVscDtcbiAgICB0aGlzLl9zaG93SGVscEFmdGVyRXJyb3IgPSBkaXNwbGF5SGVscDtcbiAgICByZXR1cm4gdGhpcztcbiAgfVxuXG4gIC8qKlxuICAgKiBEaXNwbGF5IHN1Z2dlc3Rpb24gb2Ygc2ltaWxhciBjb21tYW5kcyBmb3IgdW5rbm93biBjb21tYW5kcywgb3Igb3B0aW9ucyBmb3IgdW5rbm93biBvcHRpb25zLlxuICAgKlxuICAgKiBAcGFyYW0ge2Jvb2xlYW59IFtkaXNwbGF5U3VnZ2VzdGlvbl1cbiAgICogQHJldHVybiB7Q29tbWFuZH0gYHRoaXNgIGNvbW1hbmQgZm9yIGNoYWluaW5nXG4gICAqL1xuICBzaG93U3VnZ2VzdGlvbkFmdGVyRXJyb3IoZGlzcGxheVN1Z2dlc3Rpb24gPSB0cnVlKSB7XG4gICAgdGhpcy5fc2hvd1N1Z2dlc3Rpb25BZnRlckVycm9yID0gISFkaXNwbGF5U3VnZ2VzdGlvbjtcbiAgICByZXR1cm4gdGhpcztcbiAgfVxuXG4gIC8qKlxuICAgKiBBZGQgYSBwcmVwYXJlZCBzdWJjb21tYW5kLlxuICAgKlxuICAgKiBTZWUgLmNvbW1hbmQoKSBmb3IgY3JlYXRpbmcgYW4gYXR0YWNoZWQgc3ViY29tbWFuZCB3aGljaCBpbmhlcml0cyBzZXR0aW5ncyBmcm9tIGl0cyBwYXJlbnQuXG4gICAqXG4gICAqIEBwYXJhbSB7Q29tbWFuZH0gY21kIC0gbmV3IHN1YmNvbW1hbmRcbiAgICogQHBhcmFtIHtPYmplY3R9IFtvcHRzXSAtIGNvbmZpZ3VyYXRpb24gb3B0aW9uc1xuICAgKiBAcmV0dXJuIHtDb21tYW5kfSBgdGhpc2AgY29tbWFuZCBmb3IgY2hhaW5pbmdcbiAgICovXG5cbiAgYWRkQ29tbWFuZChjbWQsIG9wdHMpIHtcbiAgICBpZiAoIWNtZC5fbmFtZSkge1xuICAgICAgdGhyb3cgbmV3IEVycm9yKGBDb21tYW5kIHBhc3NlZCB0byAuYWRkQ29tbWFuZCgpIG11c3QgaGF2ZSBhIG5hbWVcbi0gc3BlY2lmeSB0aGUgbmFtZSBpbiBDb21tYW5kIGNvbnN0cnVjdG9yIG9yIHVzaW5nIC5uYW1lKClgKTtcbiAgICB9XG5cbiAgICBvcHRzID0gb3B0cyB8fCB7fTtcbiAgICBpZiAob3B0cy5pc0RlZmF1bHQpIHRoaXMuX2RlZmF1bHRDb21tYW5kTmFtZSA9IGNtZC5fbmFtZTtcbiAgICBpZiAob3B0cy5ub0hlbHAgfHwgb3B0cy5oaWRkZW4pIGNtZC5faGlkZGVuID0gdHJ1ZTsgLy8gbW9kaWZ5aW5nIHBhc3NlZCBjb21tYW5kIGR1ZSB0byBleGlzdGluZyBpbXBsZW1lbnRhdGlvblxuXG4gICAgdGhpcy5jb21tYW5kcy5wdXNoKGNtZCk7XG4gICAgY21kLnBhcmVudCA9IHRoaXM7XG4gICAgcmV0dXJuIHRoaXM7XG4gIH1cblxuICAvKipcbiAgICogRmFjdG9yeSByb3V0aW5lIHRvIGNyZWF0ZSBhIG5ldyB1bmF0dGFjaGVkIGFyZ3VtZW50LlxuICAgKlxuICAgKiBTZWUgLmFyZ3VtZW50KCkgZm9yIGNyZWF0aW5nIGFuIGF0dGFjaGVkIGFyZ3VtZW50LCB3aGljaCB1c2VzIHRoaXMgcm91dGluZSB0b1xuICAgKiBjcmVhdGUgdGhlIGFyZ3VtZW50LiBZb3UgY2FuIG92ZXJyaWRlIGNyZWF0ZUFyZ3VtZW50IHRvIHJldHVybiBhIGN1c3RvbSBhcmd1bWVudC5cbiAgICpcbiAgICogQHBhcmFtIHtzdHJpbmd9IG5hbWVcbiAgICogQHBhcmFtIHtzdHJpbmd9IFtkZXNjcmlwdGlvbl1cbiAgICogQHJldHVybiB7QXJndW1lbnR9IG5ldyBhcmd1bWVudFxuICAgKi9cblxuICBjcmVhdGVBcmd1bWVudChuYW1lLCBkZXNjcmlwdGlvbikge1xuICAgIHJldHVybiBuZXcgQXJndW1lbnQobmFtZSwgZGVzY3JpcHRpb24pO1xuICB9XG5cbiAgLyoqXG4gICAqIERlZmluZSBhcmd1bWVudCBzeW50YXggZm9yIGNvbW1hbmQuXG4gICAqXG4gICAqIFRoZSBkZWZhdWx0IGlzIHRoYXQgdGhlIGFyZ3VtZW50IGlzIHJlcXVpcmVkLCBhbmQgeW91IGNhbiBleHBsaWNpdGx5XG4gICAqIGluZGljYXRlIHRoaXMgd2l0aCA8PiBhcm91bmQgdGhlIG5hbWUuIFB1dCBbXSBhcm91bmQgdGhlIG5hbWUgZm9yIGFuIG9wdGlvbmFsIGFyZ3VtZW50LlxuICAgKlxuICAgKiBAZXhhbXBsZVxuICAgKiBwcm9ncmFtLmFyZ3VtZW50KCc8aW5wdXQtZmlsZT4nKTtcbiAgICogcHJvZ3JhbS5hcmd1bWVudCgnW291dHB1dC1maWxlXScpO1xuICAgKlxuICAgKiBAcGFyYW0ge3N0cmluZ30gbmFtZVxuICAgKiBAcGFyYW0ge3N0cmluZ30gW2Rlc2NyaXB0aW9uXVxuICAgKiBAcGFyYW0ge0Z1bmN0aW9ufCp9IFtmbl0gLSBjdXN0b20gYXJndW1lbnQgcHJvY2Vzc2luZyBmdW5jdGlvblxuICAgKiBAcGFyYW0geyp9IFtkZWZhdWx0VmFsdWVdXG4gICAqIEByZXR1cm4ge0NvbW1hbmR9IGB0aGlzYCBjb21tYW5kIGZvciBjaGFpbmluZ1xuICAgKi9cbiAgYXJndW1lbnQobmFtZSwgZGVzY3JpcHRpb24sIGZuLCBkZWZhdWx0VmFsdWUpIHtcbiAgICBjb25zdCBhcmd1bWVudCA9IHRoaXMuY3JlYXRlQXJndW1lbnQobmFtZSwgZGVzY3JpcHRpb24pO1xuICAgIGlmICh0eXBlb2YgZm4gPT09ICdmdW5jdGlvbicpIHtcbiAgICAgIGFyZ3VtZW50LmRlZmF1bHQoZGVmYXVsdFZhbHVlKS5hcmdQYXJzZXIoZm4pO1xuICAgIH0gZWxzZSB7XG4gICAgICBhcmd1bWVudC5kZWZhdWx0KGZuKTtcbiAgICB9XG4gICAgdGhpcy5hZGRBcmd1bWVudChhcmd1bWVudCk7XG4gICAgcmV0dXJuIHRoaXM7XG4gIH1cblxuICAvKipcbiAgICogRGVmaW5lIGFyZ3VtZW50IHN5bnRheCBmb3IgY29tbWFuZCwgYWRkaW5nIG11bHRpcGxlIGF0IG9uY2UgKHdpdGhvdXQgZGVzY3JpcHRpb25zKS5cbiAgICpcbiAgICogU2VlIGFsc28gLmFyZ3VtZW50KCkuXG4gICAqXG4gICAqIEBleGFtcGxlXG4gICAqIHByb2dyYW0uYXJndW1lbnRzKCc8Y21kPiBbZW52XScpO1xuICAgKlxuICAgKiBAcGFyYW0ge3N0cmluZ30gbmFtZXNcbiAgICogQHJldHVybiB7Q29tbWFuZH0gYHRoaXNgIGNvbW1hbmQgZm9yIGNoYWluaW5nXG4gICAqL1xuXG4gIGFyZ3VtZW50cyhuYW1lcykge1xuICAgIG5hbWVzLnNwbGl0KC8gKy8pLmZvckVhY2goKGRldGFpbCkgPT4ge1xuICAgICAgdGhpcy5hcmd1bWVudChkZXRhaWwpO1xuICAgIH0pO1xuICAgIHJldHVybiB0aGlzO1xuICB9XG5cbiAgLyoqXG4gICAqIERlZmluZSBhcmd1bWVudCBzeW50YXggZm9yIGNvbW1hbmQsIGFkZGluZyBhIHByZXBhcmVkIGFyZ3VtZW50LlxuICAgKlxuICAgKiBAcGFyYW0ge0FyZ3VtZW50fSBhcmd1bWVudFxuICAgKiBAcmV0dXJuIHtDb21tYW5kfSBgdGhpc2AgY29tbWFuZCBmb3IgY2hhaW5pbmdcbiAgICovXG4gIGFkZEFyZ3VtZW50KGFyZ3VtZW50KSB7XG4gICAgY29uc3QgcHJldmlvdXNBcmd1bWVudCA9IHRoaXMuX2FyZ3Muc2xpY2UoLTEpWzBdO1xuICAgIGlmIChwcmV2aW91c0FyZ3VtZW50ICYmIHByZXZpb3VzQXJndW1lbnQudmFyaWFkaWMpIHtcbiAgICAgIHRocm93IG5ldyBFcnJvcihgb25seSB0aGUgbGFzdCBhcmd1bWVudCBjYW4gYmUgdmFyaWFkaWMgJyR7cHJldmlvdXNBcmd1bWVudC5uYW1lKCl9J2ApO1xuICAgIH1cbiAgICBpZiAoYXJndW1lbnQucmVxdWlyZWQgJiYgYXJndW1lbnQuZGVmYXVsdFZhbHVlICE9PSB1bmRlZmluZWQgJiYgYXJndW1lbnQucGFyc2VBcmcgPT09IHVuZGVmaW5lZCkge1xuICAgICAgdGhyb3cgbmV3IEVycm9yKGBhIGRlZmF1bHQgdmFsdWUgZm9yIGEgcmVxdWlyZWQgYXJndW1lbnQgaXMgbmV2ZXIgdXNlZDogJyR7YXJndW1lbnQubmFtZSgpfSdgKTtcbiAgICB9XG4gICAgdGhpcy5fYXJncy5wdXNoKGFyZ3VtZW50KTtcbiAgICByZXR1cm4gdGhpcztcbiAgfVxuXG4gIC8qKlxuICAgKiBPdmVycmlkZSBkZWZhdWx0IGRlY2lzaW9uIHdoZXRoZXIgdG8gYWRkIGltcGxpY2l0IGhlbHAgY29tbWFuZC5cbiAgICpcbiAgICogICAgYWRkSGVscENvbW1hbmQoKSAvLyBmb3JjZSBvblxuICAgKiAgICBhZGRIZWxwQ29tbWFuZChmYWxzZSk7IC8vIGZvcmNlIG9mZlxuICAgKiAgICBhZGRIZWxwQ29tbWFuZCgnaGVscCBbY21kXScsICdkaXNwbGF5IGhlbHAgZm9yIFtjbWRdJyk7IC8vIGZvcmNlIG9uIHdpdGggY3VzdG9tIGRldGFpbHNcbiAgICpcbiAgICogQHJldHVybiB7Q29tbWFuZH0gYHRoaXNgIGNvbW1hbmQgZm9yIGNoYWluaW5nXG4gICAqL1xuXG4gIGFkZEhlbHBDb21tYW5kKGVuYWJsZU9yTmFtZUFuZEFyZ3MsIGRlc2NyaXB0aW9uKSB7XG4gICAgaWYgKGVuYWJsZU9yTmFtZUFuZEFyZ3MgPT09IGZhbHNlKSB7XG4gICAgICB0aGlzLl9hZGRJbXBsaWNpdEhlbHBDb21tYW5kID0gZmFsc2U7XG4gICAgfSBlbHNlIHtcbiAgICAgIHRoaXMuX2FkZEltcGxpY2l0SGVscENvbW1hbmQgPSB0cnVlO1xuICAgICAgaWYgKHR5cGVvZiBlbmFibGVPck5hbWVBbmRBcmdzID09PSAnc3RyaW5nJykge1xuICAgICAgICB0aGlzLl9oZWxwQ29tbWFuZE5hbWUgPSBlbmFibGVPck5hbWVBbmRBcmdzLnNwbGl0KCcgJylbMF07XG4gICAgICAgIHRoaXMuX2hlbHBDb21tYW5kbmFtZUFuZEFyZ3MgPSBlbmFibGVPck5hbWVBbmRBcmdzO1xuICAgICAgfVxuICAgICAgdGhpcy5faGVscENvbW1hbmREZXNjcmlwdGlvbiA9IGRlc2NyaXB0aW9uIHx8IHRoaXMuX2hlbHBDb21tYW5kRGVzY3JpcHRpb247XG4gICAgfVxuICAgIHJldHVybiB0aGlzO1xuICB9XG5cbiAgLyoqXG4gICAqIEByZXR1cm4ge2Jvb2xlYW59XG4gICAqIEBhcGkgcHJpdmF0ZVxuICAgKi9cblxuICBfaGFzSW1wbGljaXRIZWxwQ29tbWFuZCgpIHtcbiAgICBpZiAodGhpcy5fYWRkSW1wbGljaXRIZWxwQ29tbWFuZCA9PT0gdW5kZWZpbmVkKSB7XG4gICAgICByZXR1cm4gdGhpcy5jb21tYW5kcy5sZW5ndGggJiYgIXRoaXMuX2FjdGlvbkhhbmRsZXIgJiYgIXRoaXMuX2ZpbmRDb21tYW5kKCdoZWxwJyk7XG4gICAgfVxuICAgIHJldHVybiB0aGlzLl9hZGRJbXBsaWNpdEhlbHBDb21tYW5kO1xuICB9XG5cbiAgLyoqXG4gICAqIEFkZCBob29rIGZvciBsaWZlIGN5Y2xlIGV2ZW50LlxuICAgKlxuICAgKiBAcGFyYW0ge3N0cmluZ30gZXZlbnRcbiAgICogQHBhcmFtIHtGdW5jdGlvbn0gbGlzdGVuZXJcbiAgICogQHJldHVybiB7Q29tbWFuZH0gYHRoaXNgIGNvbW1hbmQgZm9yIGNoYWluaW5nXG4gICAqL1xuXG4gIGhvb2soZXZlbnQsIGxpc3RlbmVyKSB7XG4gICAgY29uc3QgYWxsb3dlZFZhbHVlcyA9IFsncHJlU3ViY29tbWFuZCcsICdwcmVBY3Rpb24nLCAncG9zdEFjdGlvbiddO1xuICAgIGlmICghYWxsb3dlZFZhbHVlcy5pbmNsdWRlcyhldmVudCkpIHtcbiAgICAgIHRocm93IG5ldyBFcnJvcihgVW5leHBlY3RlZCB2YWx1ZSBmb3IgZXZlbnQgcGFzc2VkIHRvIGhvb2sgOiAnJHtldmVudH0nLlxuRXhwZWN0aW5nIG9uZSBvZiAnJHthbGxvd2VkVmFsdWVzLmpvaW4oXCInLCAnXCIpfSdgKTtcbiAgICB9XG4gICAgaWYgKHRoaXMuX2xpZmVDeWNsZUhvb2tzW2V2ZW50XSkge1xuICAgICAgdGhpcy5fbGlmZUN5Y2xlSG9va3NbZXZlbnRdLnB1c2gobGlzdGVuZXIpO1xuICAgIH0gZWxzZSB7XG4gICAgICB0aGlzLl9saWZlQ3ljbGVIb29rc1tldmVudF0gPSBbbGlzdGVuZXJdO1xuICAgIH1cbiAgICByZXR1cm4gdGhpcztcbiAgfVxuXG4gIC8qKlxuICAgKiBSZWdpc3RlciBjYWxsYmFjayB0byB1c2UgYXMgcmVwbGFjZW1lbnQgZm9yIGNhbGxpbmcgcHJvY2Vzcy5leGl0LlxuICAgKlxuICAgKiBAcGFyYW0ge0Z1bmN0aW9ufSBbZm5dIG9wdGlvbmFsIGNhbGxiYWNrIHdoaWNoIHdpbGwgYmUgcGFzc2VkIGEgQ29tbWFuZGVyRXJyb3IsIGRlZmF1bHRzIHRvIHRocm93aW5nXG4gICAqIEByZXR1cm4ge0NvbW1hbmR9IGB0aGlzYCBjb21tYW5kIGZvciBjaGFpbmluZ1xuICAgKi9cblxuICBleGl0T3ZlcnJpZGUoZm4pIHtcbiAgICBpZiAoZm4pIHtcbiAgICAgIHRoaXMuX2V4aXRDYWxsYmFjayA9IGZuO1xuICAgIH0gZWxzZSB7XG4gICAgICB0aGlzLl9leGl0Q2FsbGJhY2sgPSAoZXJyKSA9PiB7XG4gICAgICAgIGlmIChlcnIuY29kZSAhPT0gJ2NvbW1hbmRlci5leGVjdXRlU3ViQ29tbWFuZEFzeW5jJykge1xuICAgICAgICAgIHRocm93IGVycjtcbiAgICAgICAgfSBlbHNlIHtcbiAgICAgICAgICAvLyBBc3luYyBjYWxsYmFjayBmcm9tIHNwYXduIGV2ZW50cywgbm90IHVzZWZ1bCB0byB0aHJvdy5cbiAgICAgICAgfVxuICAgICAgfTtcbiAgICB9XG4gICAgcmV0dXJuIHRoaXM7XG4gIH1cblxuICAvKipcbiAgICogQ2FsbCBwcm9jZXNzLmV4aXQsIGFuZCBfZXhpdENhbGxiYWNrIGlmIGRlZmluZWQuXG4gICAqXG4gICAqIEBwYXJhbSB7bnVtYmVyfSBleGl0Q29kZSBleGl0IGNvZGUgZm9yIHVzaW5nIHdpdGggcHJvY2Vzcy5leGl0XG4gICAqIEBwYXJhbSB7c3RyaW5nfSBjb2RlIGFuIGlkIHN0cmluZyByZXByZXNlbnRpbmcgdGhlIGVycm9yXG4gICAqIEBwYXJhbSB7c3RyaW5nfSBtZXNzYWdlIGh1bWFuLXJlYWRhYmxlIGRlc2NyaXB0aW9uIG9mIHRoZSBlcnJvclxuICAgKiBAcmV0dXJuIG5ldmVyXG4gICAqIEBhcGkgcHJpdmF0ZVxuICAgKi9cblxuICBfZXhpdChleGl0Q29kZSwgY29kZSwgbWVzc2FnZSkge1xuICAgIGlmICh0aGlzLl9leGl0Q2FsbGJhY2spIHtcbiAgICAgIHRoaXMuX2V4aXRDYWxsYmFjayhuZXcgQ29tbWFuZGVyRXJyb3IoZXhpdENvZGUsIGNvZGUsIG1lc3NhZ2UpKTtcbiAgICAgIC8vIEV4cGVjdGluZyB0aGlzIGxpbmUgaXMgbm90IHJlYWNoZWQuXG4gICAgfVxuICAgIHByb2Nlc3MuZXhpdChleGl0Q29kZSk7XG4gIH1cblxuICAvKipcbiAgICogUmVnaXN0ZXIgY2FsbGJhY2sgYGZuYCBmb3IgdGhlIGNvbW1hbmQuXG4gICAqXG4gICAqIEBleGFtcGxlXG4gICAqIHByb2dyYW1cbiAgICogICAuY29tbWFuZCgnc2VydmUnKVxuICAgKiAgIC5kZXNjcmlwdGlvbignc3RhcnQgc2VydmljZScpXG4gICAqICAgLmFjdGlvbihmdW5jdGlvbigpIHtcbiAgICogICAgICAvLyBkbyB3b3JrIGhlcmVcbiAgICogICB9KTtcbiAgICpcbiAgICogQHBhcmFtIHtGdW5jdGlvbn0gZm5cbiAgICogQHJldHVybiB7Q29tbWFuZH0gYHRoaXNgIGNvbW1hbmQgZm9yIGNoYWluaW5nXG4gICAqL1xuXG4gIGFjdGlvbihmbikge1xuICAgIGNvbnN0IGxpc3RlbmVyID0gKGFyZ3MpID0+IHtcbiAgICAgIC8vIFRoZSAuYWN0aW9uIGNhbGxiYWNrIHRha2VzIGFuIGV4dHJhIHBhcmFtZXRlciB3aGljaCBpcyB0aGUgY29tbWFuZCBvciBvcHRpb25zLlxuICAgICAgY29uc3QgZXhwZWN0ZWRBcmdzQ291bnQgPSB0aGlzLl9hcmdzLmxlbmd0aDtcbiAgICAgIGNvbnN0IGFjdGlvbkFyZ3MgPSBhcmdzLnNsaWNlKDAsIGV4cGVjdGVkQXJnc0NvdW50KTtcbiAgICAgIGlmICh0aGlzLl9zdG9yZU9wdGlvbnNBc1Byb3BlcnRpZXMpIHtcbiAgICAgICAgYWN0aW9uQXJnc1tleHBlY3RlZEFyZ3NDb3VudF0gPSB0aGlzOyAvLyBiYWNrd2FyZHMgY29tcGF0aWJsZSBcIm9wdGlvbnNcIlxuICAgICAgfSBlbHNlIHtcbiAgICAgICAgYWN0aW9uQXJnc1tleHBlY3RlZEFyZ3NDb3VudF0gPSB0aGlzLm9wdHMoKTtcbiAgICAgIH1cbiAgICAgIGFjdGlvbkFyZ3MucHVzaCh0aGlzKTtcblxuICAgICAgcmV0dXJuIGZuLmFwcGx5KHRoaXMsIGFjdGlvbkFyZ3MpO1xuICAgIH07XG4gICAgdGhpcy5fYWN0aW9uSGFuZGxlciA9IGxpc3RlbmVyO1xuICAgIHJldHVybiB0aGlzO1xuICB9XG5cbiAgLyoqXG4gICAqIEZhY3Rvcnkgcm91dGluZSB0byBjcmVhdGUgYSBuZXcgdW5hdHRhY2hlZCBvcHRpb24uXG4gICAqXG4gICAqIFNlZSAub3B0aW9uKCkgZm9yIGNyZWF0aW5nIGFuIGF0dGFjaGVkIG9wdGlvbiwgd2hpY2ggdXNlcyB0aGlzIHJvdXRpbmUgdG9cbiAgICogY3JlYXRlIHRoZSBvcHRpb24uIFlvdSBjYW4gb3ZlcnJpZGUgY3JlYXRlT3B0aW9uIHRvIHJldHVybiBhIGN1c3RvbSBvcHRpb24uXG4gICAqXG4gICAqIEBwYXJhbSB7c3RyaW5nfSBmbGFnc1xuICAgKiBAcGFyYW0ge3N0cmluZ30gW2Rlc2NyaXB0aW9uXVxuICAgKiBAcmV0dXJuIHtPcHRpb259IG5ldyBvcHRpb25cbiAgICovXG5cbiAgY3JlYXRlT3B0aW9uKGZsYWdzLCBkZXNjcmlwdGlvbikge1xuICAgIHJldHVybiBuZXcgT3B0aW9uKGZsYWdzLCBkZXNjcmlwdGlvbik7XG4gIH1cblxuICAvKipcbiAgICogQWRkIGFuIG9wdGlvbi5cbiAgICpcbiAgICogQHBhcmFtIHtPcHRpb259IG9wdGlvblxuICAgKiBAcmV0dXJuIHtDb21tYW5kfSBgdGhpc2AgY29tbWFuZCBmb3IgY2hhaW5pbmdcbiAgICovXG4gIGFkZE9wdGlvbihvcHRpb24pIHtcbiAgICBjb25zdCBvbmFtZSA9IG9wdGlvbi5uYW1lKCk7XG4gICAgY29uc3QgbmFtZSA9IG9wdGlvbi5hdHRyaWJ1dGVOYW1lKCk7XG5cbiAgICAvLyBzdG9yZSBkZWZhdWx0IHZhbHVlXG4gICAgaWYgKG9wdGlvbi5uZWdhdGUpIHtcbiAgICAgIC8vIC0tbm8tZm9vIGlzIHNwZWNpYWwgYW5kIGRlZmF1bHRzIGZvbyB0byB0cnVlLCB1bmxlc3MgYSAtLWZvbyBvcHRpb24gaXMgYWxyZWFkeSBkZWZpbmVkXG4gICAgICBjb25zdCBwb3NpdGl2ZUxvbmdGbGFnID0gb3B0aW9uLmxvbmcucmVwbGFjZSgvXi0tbm8tLywgJy0tJyk7XG4gICAgICBpZiAoIXRoaXMuX2ZpbmRPcHRpb24ocG9zaXRpdmVMb25nRmxhZykpIHtcbiAgICAgICAgdGhpcy5zZXRPcHRpb25WYWx1ZVdpdGhTb3VyY2UobmFtZSwgb3B0aW9uLmRlZmF1bHRWYWx1ZSA9PT0gdW5kZWZpbmVkID8gdHJ1ZSA6IG9wdGlvbi5kZWZhdWx0VmFsdWUsICdkZWZhdWx0Jyk7XG4gICAgICB9XG4gICAgfSBlbHNlIGlmIChvcHRpb24uZGVmYXVsdFZhbHVlICE9PSB1bmRlZmluZWQpIHtcbiAgICAgIHRoaXMuc2V0T3B0aW9uVmFsdWVXaXRoU291cmNlKG5hbWUsIG9wdGlvbi5kZWZhdWx0VmFsdWUsICdkZWZhdWx0Jyk7XG4gICAgfVxuXG4gICAgLy8gcmVnaXN0ZXIgdGhlIG9wdGlvblxuICAgIHRoaXMub3B0aW9ucy5wdXNoKG9wdGlvbik7XG5cbiAgICAvLyBoYW5kbGVyIGZvciBjbGkgYW5kIGVudiBzdXBwbGllZCB2YWx1ZXNcbiAgICBjb25zdCBoYW5kbGVPcHRpb25WYWx1ZSA9ICh2YWwsIGludmFsaWRWYWx1ZU1lc3NhZ2UsIHZhbHVlU291cmNlKSA9PiB7XG4gICAgICAvLyB2YWwgaXMgbnVsbCBmb3Igb3B0aW9uYWwgb3B0aW9uIHVzZWQgd2l0aG91dCBhbiBvcHRpb25hbC1hcmd1bWVudC5cbiAgICAgIC8vIHZhbCBpcyB1bmRlZmluZWQgZm9yIGJvb2xlYW4gYW5kIG5lZ2F0ZWQgb3B0aW9uLlxuICAgICAgaWYgKHZhbCA9PSBudWxsICYmIG9wdGlvbi5wcmVzZXRBcmcgIT09IHVuZGVmaW5lZCkge1xuICAgICAgICB2YWwgPSBvcHRpb24ucHJlc2V0QXJnO1xuICAgICAgfVxuXG4gICAgICAvLyBjdXN0b20gcHJvY2Vzc2luZ1xuICAgICAgY29uc3Qgb2xkVmFsdWUgPSB0aGlzLmdldE9wdGlvblZhbHVlKG5hbWUpO1xuICAgICAgaWYgKHZhbCAhPT0gbnVsbCAmJiBvcHRpb24ucGFyc2VBcmcpIHtcbiAgICAgICAgdHJ5IHtcbiAgICAgICAgICB2YWwgPSBvcHRpb24ucGFyc2VBcmcodmFsLCBvbGRWYWx1ZSk7XG4gICAgICAgIH0gY2F0Y2ggKGVycikge1xuICAgICAgICAgIGlmIChlcnIuY29kZSA9PT0gJ2NvbW1hbmRlci5pbnZhbGlkQXJndW1lbnQnKSB7XG4gICAgICAgICAgICBjb25zdCBtZXNzYWdlID0gYCR7aW52YWxpZFZhbHVlTWVzc2FnZX0gJHtlcnIubWVzc2FnZX1gO1xuICAgICAgICAgICAgdGhpcy5lcnJvcihtZXNzYWdlLCB7IGV4aXRDb2RlOiBlcnIuZXhpdENvZGUsIGNvZGU6IGVyci5jb2RlIH0pO1xuICAgICAgICAgIH1cbiAgICAgICAgICB0aHJvdyBlcnI7XG4gICAgICAgIH1cbiAgICAgIH0gZWxzZSBpZiAodmFsICE9PSBudWxsICYmIG9wdGlvbi52YXJpYWRpYykge1xuICAgICAgICB2YWwgPSBvcHRpb24uX2NvbmNhdFZhbHVlKHZhbCwgb2xkVmFsdWUpO1xuICAgICAgfVxuXG4gICAgICAvLyBGaWxsLWluIGFwcHJvcHJpYXRlIG1pc3NpbmcgdmFsdWVzLiBMb25nIHdpbmRlZCBidXQgZWFzeSB0byBmb2xsb3cuXG4gICAgICBpZiAodmFsID09IG51bGwpIHtcbiAgICAgICAgaWYgKG9wdGlvbi5uZWdhdGUpIHtcbiAgICAgICAgICB2YWwgPSBmYWxzZTtcbiAgICAgICAgfSBlbHNlIGlmIChvcHRpb24uaXNCb29sZWFuKCkgfHwgb3B0aW9uLm9wdGlvbmFsKSB7XG4gICAgICAgICAgdmFsID0gdHJ1ZTtcbiAgICAgICAgfSBlbHNlIHtcbiAgICAgICAgICB2YWwgPSAnJzsgLy8gbm90IG5vcm1hbCwgcGFyc2VBcmcgbWlnaHQgaGF2ZSBmYWlsZWQgb3IgYmUgYSBtb2NrIGZ1bmN0aW9uIGZvciB0ZXN0aW5nXG4gICAgICAgIH1cbiAgICAgIH1cbiAgICAgIHRoaXMuc2V0T3B0aW9uVmFsdWVXaXRoU291cmNlKG5hbWUsIHZhbCwgdmFsdWVTb3VyY2UpO1xuICAgIH07XG5cbiAgICB0aGlzLm9uKCdvcHRpb246JyArIG9uYW1lLCAodmFsKSA9PiB7XG4gICAgICBjb25zdCBpbnZhbGlkVmFsdWVNZXNzYWdlID0gYGVycm9yOiBvcHRpb24gJyR7b3B0aW9uLmZsYWdzfScgYXJndW1lbnQgJyR7dmFsfScgaXMgaW52YWxpZC5gO1xuICAgICAgaGFuZGxlT3B0aW9uVmFsdWUodmFsLCBpbnZhbGlkVmFsdWVNZXNzYWdlLCAnY2xpJyk7XG4gICAgfSk7XG5cbiAgICBpZiAob3B0aW9uLmVudlZhcikge1xuICAgICAgdGhpcy5vbignb3B0aW9uRW52OicgKyBvbmFtZSwgKHZhbCkgPT4ge1xuICAgICAgICBjb25zdCBpbnZhbGlkVmFsdWVNZXNzYWdlID0gYGVycm9yOiBvcHRpb24gJyR7b3B0aW9uLmZsYWdzfScgdmFsdWUgJyR7dmFsfScgZnJvbSBlbnYgJyR7b3B0aW9uLmVudlZhcn0nIGlzIGludmFsaWQuYDtcbiAgICAgICAgaGFuZGxlT3B0aW9uVmFsdWUodmFsLCBpbnZhbGlkVmFsdWVNZXNzYWdlLCAnZW52Jyk7XG4gICAgICB9KTtcbiAgICB9XG5cbiAgICByZXR1cm4gdGhpcztcbiAgfVxuXG4gIC8qKlxuICAgKiBJbnRlcm5hbCBpbXBsZW1lbnRhdGlvbiBzaGFyZWQgYnkgLm9wdGlvbigpIGFuZCAucmVxdWlyZWRPcHRpb24oKVxuICAgKlxuICAgKiBAYXBpIHByaXZhdGVcbiAgICovXG4gIF9vcHRpb25FeChjb25maWcsIGZsYWdzLCBkZXNjcmlwdGlvbiwgZm4sIGRlZmF1bHRWYWx1ZSkge1xuICAgIGlmICh0eXBlb2YgZmxhZ3MgPT09ICdvYmplY3QnICYmIGZsYWdzIGluc3RhbmNlb2YgT3B0aW9uKSB7XG4gICAgICB0aHJvdyBuZXcgRXJyb3IoJ1RvIGFkZCBhbiBPcHRpb24gb2JqZWN0IHVzZSBhZGRPcHRpb24oKSBpbnN0ZWFkIG9mIG9wdGlvbigpIG9yIHJlcXVpcmVkT3B0aW9uKCknKTtcbiAgICB9XG4gICAgY29uc3Qgb3B0aW9uID0gdGhpcy5jcmVhdGVPcHRpb24oZmxhZ3MsIGRlc2NyaXB0aW9uKTtcbiAgICBvcHRpb24ubWFrZU9wdGlvbk1hbmRhdG9yeSghIWNvbmZpZy5tYW5kYXRvcnkpO1xuICAgIGlmICh0eXBlb2YgZm4gPT09ICdmdW5jdGlvbicpIHtcbiAgICAgIG9wdGlvbi5kZWZhdWx0KGRlZmF1bHRWYWx1ZSkuYXJnUGFyc2VyKGZuKTtcbiAgICB9IGVsc2UgaWYgKGZuIGluc3RhbmNlb2YgUmVnRXhwKSB7XG4gICAgICAvLyBkZXByZWNhdGVkXG4gICAgICBjb25zdCByZWdleCA9IGZuO1xuICAgICAgZm4gPSAodmFsLCBkZWYpID0+IHtcbiAgICAgICAgY29uc3QgbSA9IHJlZ2V4LmV4ZWModmFsKTtcbiAgICAgICAgcmV0dXJuIG0gPyBtWzBdIDogZGVmO1xuICAgICAgfTtcbiAgICAgIG9wdGlvbi5kZWZhdWx0KGRlZmF1bHRWYWx1ZSkuYXJnUGFyc2VyKGZuKTtcbiAgICB9IGVsc2Uge1xuICAgICAgb3B0aW9uLmRlZmF1bHQoZm4pO1xuICAgIH1cblxuICAgIHJldHVybiB0aGlzLmFkZE9wdGlvbihvcHRpb24pO1xuICB9XG5cbiAgLyoqXG4gICAqIERlZmluZSBvcHRpb24gd2l0aCBgZmxhZ3NgLCBgZGVzY3JpcHRpb25gIGFuZCBvcHRpb25hbFxuICAgKiBjb2VyY2lvbiBgZm5gLlxuICAgKlxuICAgKiBUaGUgYGZsYWdzYCBzdHJpbmcgY29udGFpbnMgdGhlIHNob3J0IGFuZC9vciBsb25nIGZsYWdzLFxuICAgKiBzZXBhcmF0ZWQgYnkgY29tbWEsIGEgcGlwZSBvciBzcGFjZS4gVGhlIGZvbGxvd2luZyBhcmUgYWxsIHZhbGlkXG4gICAqIGFsbCB3aWxsIG91dHB1dCB0aGlzIHdheSB3aGVuIGAtLWhlbHBgIGlzIHVzZWQuXG4gICAqXG4gICAqICAgICBcIi1wLCAtLXBlcHBlclwiXG4gICAqICAgICBcIi1wfC0tcGVwcGVyXCJcbiAgICogICAgIFwiLXAgLS1wZXBwZXJcIlxuICAgKlxuICAgKiBAZXhhbXBsZVxuICAgKiAvLyBzaW1wbGUgYm9vbGVhbiBkZWZhdWx0aW5nIHRvIHVuZGVmaW5lZFxuICAgKiBwcm9ncmFtLm9wdGlvbignLXAsIC0tcGVwcGVyJywgJ2FkZCBwZXBwZXInKTtcbiAgICpcbiAgICogcHJvZ3JhbS5wZXBwZXJcbiAgICogLy8gPT4gdW5kZWZpbmVkXG4gICAqXG4gICAqIC0tcGVwcGVyXG4gICAqIHByb2dyYW0ucGVwcGVyXG4gICAqIC8vID0+IHRydWVcbiAgICpcbiAgICogLy8gc2ltcGxlIGJvb2xlYW4gZGVmYXVsdGluZyB0byB0cnVlICh1bmxlc3Mgbm9uLW5lZ2F0ZWQgb3B0aW9uIGlzIGFsc28gZGVmaW5lZClcbiAgICogcHJvZ3JhbS5vcHRpb24oJy1DLCAtLW5vLWNoZWVzZScsICdyZW1vdmUgY2hlZXNlJyk7XG4gICAqXG4gICAqIHByb2dyYW0uY2hlZXNlXG4gICAqIC8vID0+IHRydWVcbiAgICpcbiAgICogLS1uby1jaGVlc2VcbiAgICogcHJvZ3JhbS5jaGVlc2VcbiAgICogLy8gPT4gZmFsc2VcbiAgICpcbiAgICogLy8gcmVxdWlyZWQgYXJndW1lbnRcbiAgICogcHJvZ3JhbS5vcHRpb24oJy1DLCAtLWNoZGlyIDxwYXRoPicsICdjaGFuZ2UgdGhlIHdvcmtpbmcgZGlyZWN0b3J5Jyk7XG4gICAqXG4gICAqIC0tY2hkaXIgL3RtcFxuICAgKiBwcm9ncmFtLmNoZGlyXG4gICAqIC8vID0+IFwiL3RtcFwiXG4gICAqXG4gICAqIC8vIG9wdGlvbmFsIGFyZ3VtZW50XG4gICAqIHByb2dyYW0ub3B0aW9uKCctYywgLS1jaGVlc2UgW3R5cGVdJywgJ2FkZCBjaGVlc2UgW21hcmJsZV0nKTtcbiAgICpcbiAgICogQHBhcmFtIHtzdHJpbmd9IGZsYWdzXG4gICAqIEBwYXJhbSB7c3RyaW5nfSBbZGVzY3JpcHRpb25dXG4gICAqIEBwYXJhbSB7RnVuY3Rpb258Kn0gW2ZuXSAtIGN1c3RvbSBvcHRpb24gcHJvY2Vzc2luZyBmdW5jdGlvbiBvciBkZWZhdWx0IHZhbHVlXG4gICAqIEBwYXJhbSB7Kn0gW2RlZmF1bHRWYWx1ZV1cbiAgICogQHJldHVybiB7Q29tbWFuZH0gYHRoaXNgIGNvbW1hbmQgZm9yIGNoYWluaW5nXG4gICAqL1xuXG4gIG9wdGlvbihmbGFncywgZGVzY3JpcHRpb24sIGZuLCBkZWZhdWx0VmFsdWUpIHtcbiAgICByZXR1cm4gdGhpcy5fb3B0aW9uRXgoe30sIGZsYWdzLCBkZXNjcmlwdGlvbiwgZm4sIGRlZmF1bHRWYWx1ZSk7XG4gIH1cblxuICAvKipcbiAgKiBBZGQgYSByZXF1aXJlZCBvcHRpb24gd2hpY2ggbXVzdCBoYXZlIGEgdmFsdWUgYWZ0ZXIgcGFyc2luZy4gVGhpcyB1c3VhbGx5IG1lYW5zXG4gICogdGhlIG9wdGlvbiBtdXN0IGJlIHNwZWNpZmllZCBvbiB0aGUgY29tbWFuZCBsaW5lLiAoT3RoZXJ3aXNlIHRoZSBzYW1lIGFzIC5vcHRpb24oKS4pXG4gICpcbiAgKiBUaGUgYGZsYWdzYCBzdHJpbmcgY29udGFpbnMgdGhlIHNob3J0IGFuZC9vciBsb25nIGZsYWdzLCBzZXBhcmF0ZWQgYnkgY29tbWEsIGEgcGlwZSBvciBzcGFjZS5cbiAgKlxuICAqIEBwYXJhbSB7c3RyaW5nfSBmbGFnc1xuICAqIEBwYXJhbSB7c3RyaW5nfSBbZGVzY3JpcHRpb25dXG4gICogQHBhcmFtIHtGdW5jdGlvbnwqfSBbZm5dIC0gY3VzdG9tIG9wdGlvbiBwcm9jZXNzaW5nIGZ1bmN0aW9uIG9yIGRlZmF1bHQgdmFsdWVcbiAgKiBAcGFyYW0geyp9IFtkZWZhdWx0VmFsdWVdXG4gICogQHJldHVybiB7Q29tbWFuZH0gYHRoaXNgIGNvbW1hbmQgZm9yIGNoYWluaW5nXG4gICovXG5cbiAgcmVxdWlyZWRPcHRpb24oZmxhZ3MsIGRlc2NyaXB0aW9uLCBmbiwgZGVmYXVsdFZhbHVlKSB7XG4gICAgcmV0dXJuIHRoaXMuX29wdGlvbkV4KHsgbWFuZGF0b3J5OiB0cnVlIH0sIGZsYWdzLCBkZXNjcmlwdGlvbiwgZm4sIGRlZmF1bHRWYWx1ZSk7XG4gIH1cblxuICAvKipcbiAgICogQWx0ZXIgcGFyc2luZyBvZiBzaG9ydCBmbGFncyB3aXRoIG9wdGlvbmFsIHZhbHVlcy5cbiAgICpcbiAgICogQGV4YW1wbGVcbiAgICogLy8gZm9yIGAub3B0aW9uKCctZiwtLWZsYWcgW3ZhbHVlXScpOlxuICAgKiBwcm9ncmFtLmNvbWJpbmVGbGFnQW5kT3B0aW9uYWxWYWx1ZSh0cnVlKTsgIC8vIGAtZjgwYCBpcyB0cmVhdGVkIGxpa2UgYC0tZmxhZz04MGAsIHRoaXMgaXMgdGhlIGRlZmF1bHQgYmVoYXZpb3VyXG4gICAqIHByb2dyYW0uY29tYmluZUZsYWdBbmRPcHRpb25hbFZhbHVlKGZhbHNlKSAvLyBgLWZiYCBpcyB0cmVhdGVkIGxpa2UgYC1mIC1iYFxuICAgKlxuICAgKiBAcGFyYW0ge0Jvb2xlYW59IFtjb21iaW5lPXRydWVdIC0gaWYgYHRydWVgIG9yIG9taXR0ZWQsIGFuIG9wdGlvbmFsIHZhbHVlIGNhbiBiZSBzcGVjaWZpZWQgZGlyZWN0bHkgYWZ0ZXIgdGhlIGZsYWcuXG4gICAqL1xuICBjb21iaW5lRmxhZ0FuZE9wdGlvbmFsVmFsdWUoY29tYmluZSA9IHRydWUpIHtcbiAgICB0aGlzLl9jb21iaW5lRmxhZ0FuZE9wdGlvbmFsVmFsdWUgPSAhIWNvbWJpbmU7XG4gICAgcmV0dXJuIHRoaXM7XG4gIH1cblxuICAvKipcbiAgICogQWxsb3cgdW5rbm93biBvcHRpb25zIG9uIHRoZSBjb21tYW5kIGxpbmUuXG4gICAqXG4gICAqIEBwYXJhbSB7Qm9vbGVhbn0gW2FsbG93VW5rbm93bj10cnVlXSAtIGlmIGB0cnVlYCBvciBvbWl0dGVkLCBubyBlcnJvciB3aWxsIGJlIHRocm93blxuICAgKiBmb3IgdW5rbm93biBvcHRpb25zLlxuICAgKi9cbiAgYWxsb3dVbmtub3duT3B0aW9uKGFsbG93VW5rbm93biA9IHRydWUpIHtcbiAgICB0aGlzLl9hbGxvd1Vua25vd25PcHRpb24gPSAhIWFsbG93VW5rbm93bjtcbiAgICByZXR1cm4gdGhpcztcbiAgfVxuXG4gIC8qKlxuICAgKiBBbGxvdyBleGNlc3MgY29tbWFuZC1hcmd1bWVudHMgb24gdGhlIGNvbW1hbmQgbGluZS4gUGFzcyBmYWxzZSB0byBtYWtlIGV4Y2VzcyBhcmd1bWVudHMgYW4gZXJyb3IuXG4gICAqXG4gICAqIEBwYXJhbSB7Qm9vbGVhbn0gW2FsbG93RXhjZXNzPXRydWVdIC0gaWYgYHRydWVgIG9yIG9taXR0ZWQsIG5vIGVycm9yIHdpbGwgYmUgdGhyb3duXG4gICAqIGZvciBleGNlc3MgYXJndW1lbnRzLlxuICAgKi9cbiAgYWxsb3dFeGNlc3NBcmd1bWVudHMoYWxsb3dFeGNlc3MgPSB0cnVlKSB7XG4gICAgdGhpcy5fYWxsb3dFeGNlc3NBcmd1bWVudHMgPSAhIWFsbG93RXhjZXNzO1xuICAgIHJldHVybiB0aGlzO1xuICB9XG5cbiAgLyoqXG4gICAqIEVuYWJsZSBwb3NpdGlvbmFsIG9wdGlvbnMuIFBvc2l0aW9uYWwgbWVhbnMgZ2xvYmFsIG9wdGlvbnMgYXJlIHNwZWNpZmllZCBiZWZvcmUgc3ViY29tbWFuZHMgd2hpY2ggbGV0c1xuICAgKiBzdWJjb21tYW5kcyByZXVzZSB0aGUgc2FtZSBvcHRpb24gbmFtZXMsIGFuZCBhbHNvIGVuYWJsZXMgc3ViY29tbWFuZHMgdG8gdHVybiBvbiBwYXNzVGhyb3VnaE9wdGlvbnMuXG4gICAqIFRoZSBkZWZhdWx0IGJlaGF2aW91ciBpcyBub24tcG9zaXRpb25hbCBhbmQgZ2xvYmFsIG9wdGlvbnMgbWF5IGFwcGVhciBhbnl3aGVyZSBvbiB0aGUgY29tbWFuZCBsaW5lLlxuICAgKlxuICAgKiBAcGFyYW0ge0Jvb2xlYW59IFtwb3NpdGlvbmFsPXRydWVdXG4gICAqL1xuICBlbmFibGVQb3NpdGlvbmFsT3B0aW9ucyhwb3NpdGlvbmFsID0gdHJ1ZSkge1xuICAgIHRoaXMuX2VuYWJsZVBvc2l0aW9uYWxPcHRpb25zID0gISFwb3NpdGlvbmFsO1xuICAgIHJldHVybiB0aGlzO1xuICB9XG5cbiAgLyoqXG4gICAqIFBhc3MgdGhyb3VnaCBvcHRpb25zIHRoYXQgY29tZSBhZnRlciBjb21tYW5kLWFyZ3VtZW50cyByYXRoZXIgdGhhbiB0cmVhdCB0aGVtIGFzIGNvbW1hbmQtb3B0aW9ucyxcbiAgICogc28gYWN0dWFsIGNvbW1hbmQtb3B0aW9ucyBjb21lIGJlZm9yZSBjb21tYW5kLWFyZ3VtZW50cy4gVHVybmluZyB0aGlzIG9uIGZvciBhIHN1YmNvbW1hbmQgcmVxdWlyZXNcbiAgICogcG9zaXRpb25hbCBvcHRpb25zIHRvIGhhdmUgYmVlbiBlbmFibGVkIG9uIHRoZSBwcm9ncmFtIChwYXJlbnQgY29tbWFuZHMpLlxuICAgKiBUaGUgZGVmYXVsdCBiZWhhdmlvdXIgaXMgbm9uLXBvc2l0aW9uYWwgYW5kIG9wdGlvbnMgbWF5IGFwcGVhciBiZWZvcmUgb3IgYWZ0ZXIgY29tbWFuZC1hcmd1bWVudHMuXG4gICAqXG4gICAqIEBwYXJhbSB7Qm9vbGVhbn0gW3Bhc3NUaHJvdWdoPXRydWVdXG4gICAqIGZvciB1bmtub3duIG9wdGlvbnMuXG4gICAqL1xuICBwYXNzVGhyb3VnaE9wdGlvbnMocGFzc1Rocm91Z2ggPSB0cnVlKSB7XG4gICAgdGhpcy5fcGFzc1Rocm91Z2hPcHRpb25zID0gISFwYXNzVGhyb3VnaDtcbiAgICBpZiAoISF0aGlzLnBhcmVudCAmJiBwYXNzVGhyb3VnaCAmJiAhdGhpcy5wYXJlbnQuX2VuYWJsZVBvc2l0aW9uYWxPcHRpb25zKSB7XG4gICAgICB0aHJvdyBuZXcgRXJyb3IoJ3Bhc3NUaHJvdWdoT3B0aW9ucyBjYW4gbm90IGJlIHVzZWQgd2l0aG91dCB0dXJuaW5nIG9uIGVuYWJsZVBvc2l0aW9uYWxPcHRpb25zIGZvciBwYXJlbnQgY29tbWFuZChzKScpO1xuICAgIH1cbiAgICByZXR1cm4gdGhpcztcbiAgfVxuXG4gIC8qKlxuICAgICogV2hldGhlciB0byBzdG9yZSBvcHRpb24gdmFsdWVzIGFzIHByb3BlcnRpZXMgb24gY29tbWFuZCBvYmplY3QsXG4gICAgKiBvciBzdG9yZSBzZXBhcmF0ZWx5IChzcGVjaWZ5IGZhbHNlKS4gSW4gYm90aCBjYXNlcyB0aGUgb3B0aW9uIHZhbHVlcyBjYW4gYmUgYWNjZXNzZWQgdXNpbmcgLm9wdHMoKS5cbiAgICAqXG4gICAgKiBAcGFyYW0ge2Jvb2xlYW59IFtzdG9yZUFzUHJvcGVydGllcz10cnVlXVxuICAgICogQHJldHVybiB7Q29tbWFuZH0gYHRoaXNgIGNvbW1hbmQgZm9yIGNoYWluaW5nXG4gICAgKi9cblxuICBzdG9yZU9wdGlvbnNBc1Byb3BlcnRpZXMoc3RvcmVBc1Byb3BlcnRpZXMgPSB0cnVlKSB7XG4gICAgdGhpcy5fc3RvcmVPcHRpb25zQXNQcm9wZXJ0aWVzID0gISFzdG9yZUFzUHJvcGVydGllcztcbiAgICBpZiAodGhpcy5vcHRpb25zLmxlbmd0aCkge1xuICAgICAgdGhyb3cgbmV3IEVycm9yKCdjYWxsIC5zdG9yZU9wdGlvbnNBc1Byb3BlcnRpZXMoKSBiZWZvcmUgYWRkaW5nIG9wdGlvbnMnKTtcbiAgICB9XG4gICAgcmV0dXJuIHRoaXM7XG4gIH1cblxuICAvKipcbiAgICogUmV0cmlldmUgb3B0aW9uIHZhbHVlLlxuICAgKlxuICAgKiBAcGFyYW0ge3N0cmluZ30ga2V5XG4gICAqIEByZXR1cm4ge09iamVjdH0gdmFsdWVcbiAgICovXG5cbiAgZ2V0T3B0aW9uVmFsdWUoa2V5KSB7XG4gICAgaWYgKHRoaXMuX3N0b3JlT3B0aW9uc0FzUHJvcGVydGllcykge1xuICAgICAgcmV0dXJuIHRoaXNba2V5XTtcbiAgICB9XG4gICAgcmV0dXJuIHRoaXMuX29wdGlvblZhbHVlc1trZXldO1xuICB9XG5cbiAgLyoqXG4gICAqIFN0b3JlIG9wdGlvbiB2YWx1ZS5cbiAgICpcbiAgICogQHBhcmFtIHtzdHJpbmd9IGtleVxuICAgKiBAcGFyYW0ge09iamVjdH0gdmFsdWVcbiAgICogQHJldHVybiB7Q29tbWFuZH0gYHRoaXNgIGNvbW1hbmQgZm9yIGNoYWluaW5nXG4gICAqL1xuXG4gIHNldE9wdGlvblZhbHVlKGtleSwgdmFsdWUpIHtcbiAgICByZXR1cm4gdGhpcy5zZXRPcHRpb25WYWx1ZVdpdGhTb3VyY2Uoa2V5LCB2YWx1ZSwgdW5kZWZpbmVkKTtcbiAgfVxuXG4gIC8qKlxuICAgICogU3RvcmUgb3B0aW9uIHZhbHVlIGFuZCB3aGVyZSB0aGUgdmFsdWUgY2FtZSBmcm9tLlxuICAgICpcbiAgICAqIEBwYXJhbSB7c3RyaW5nfSBrZXlcbiAgICAqIEBwYXJhbSB7T2JqZWN0fSB2YWx1ZVxuICAgICogQHBhcmFtIHtzdHJpbmd9IHNvdXJjZSAtIGV4cGVjdGVkIHZhbHVlcyBhcmUgZGVmYXVsdC9jb25maWcvZW52L2NsaS9pbXBsaWVkXG4gICAgKiBAcmV0dXJuIHtDb21tYW5kfSBgdGhpc2AgY29tbWFuZCBmb3IgY2hhaW5pbmdcbiAgICAqL1xuXG4gIHNldE9wdGlvblZhbHVlV2l0aFNvdXJjZShrZXksIHZhbHVlLCBzb3VyY2UpIHtcbiAgICBpZiAodGhpcy5fc3RvcmVPcHRpb25zQXNQcm9wZXJ0aWVzKSB7XG4gICAgICB0aGlzW2tleV0gPSB2YWx1ZTtcbiAgICB9IGVsc2Uge1xuICAgICAgdGhpcy5fb3B0aW9uVmFsdWVzW2tleV0gPSB2YWx1ZTtcbiAgICB9XG4gICAgdGhpcy5fb3B0aW9uVmFsdWVTb3VyY2VzW2tleV0gPSBzb3VyY2U7XG4gICAgcmV0dXJuIHRoaXM7XG4gIH1cblxuICAvKipcbiAgICAqIEdldCBzb3VyY2Ugb2Ygb3B0aW9uIHZhbHVlLlxuICAgICogRXhwZWN0ZWQgdmFsdWVzIGFyZSBkZWZhdWx0IHwgY29uZmlnIHwgZW52IHwgY2xpIHwgaW1wbGllZFxuICAgICpcbiAgICAqIEBwYXJhbSB7c3RyaW5nfSBrZXlcbiAgICAqIEByZXR1cm4ge3N0cmluZ31cbiAgICAqL1xuXG4gIGdldE9wdGlvblZhbHVlU291cmNlKGtleSkge1xuICAgIHJldHVybiB0aGlzLl9vcHRpb25WYWx1ZVNvdXJjZXNba2V5XTtcbiAgfVxuXG4gIC8qKlxuICAgICogR2V0IHNvdXJjZSBvZiBvcHRpb24gdmFsdWUuIFNlZSBhbHNvIC5vcHRzV2l0aEdsb2JhbHMoKS5cbiAgICAqIEV4cGVjdGVkIHZhbHVlcyBhcmUgZGVmYXVsdCB8IGNvbmZpZyB8IGVudiB8IGNsaSB8IGltcGxpZWRcbiAgICAqXG4gICAgKiBAcGFyYW0ge3N0cmluZ30ga2V5XG4gICAgKiBAcmV0dXJuIHtzdHJpbmd9XG4gICAgKi9cblxuICBnZXRPcHRpb25WYWx1ZVNvdXJjZVdpdGhHbG9iYWxzKGtleSkge1xuICAgIC8vIGdsb2JhbCBvdmVyd3JpdGVzIGxvY2FsLCBsaWtlIG9wdHNXaXRoR2xvYmFsc1xuICAgIGxldCBzb3VyY2U7XG4gICAgZ2V0Q29tbWFuZEFuZFBhcmVudHModGhpcykuZm9yRWFjaCgoY21kKSA9PiB7XG4gICAgICBpZiAoY21kLmdldE9wdGlvblZhbHVlU291cmNlKGtleSkgIT09IHVuZGVmaW5lZCkge1xuICAgICAgICBzb3VyY2UgPSBjbWQuZ2V0T3B0aW9uVmFsdWVTb3VyY2Uoa2V5KTtcbiAgICAgIH1cbiAgICB9KTtcbiAgICByZXR1cm4gc291cmNlO1xuICB9XG5cbiAgLyoqXG4gICAqIEdldCB1c2VyIGFyZ3VtZW50cyBmcm9tIGltcGxpZWQgb3IgZXhwbGljaXQgYXJndW1lbnRzLlxuICAgKiBTaWRlLWVmZmVjdHM6IHNldCBfc2NyaXB0UGF0aCBpZiBhcmdzIGluY2x1ZGVkIHNjcmlwdC4gVXNlZCBmb3IgZGVmYXVsdCBwcm9ncmFtIG5hbWUsIGFuZCBzdWJjb21tYW5kIHNlYXJjaGVzLlxuICAgKlxuICAgKiBAYXBpIHByaXZhdGVcbiAgICovXG5cbiAgX3ByZXBhcmVVc2VyQXJncyhhcmd2LCBwYXJzZU9wdGlvbnMpIHtcbiAgICBpZiAoYXJndiAhPT0gdW5kZWZpbmVkICYmICFBcnJheS5pc0FycmF5KGFyZ3YpKSB7XG4gICAgICB0aHJvdyBuZXcgRXJyb3IoJ2ZpcnN0IHBhcmFtZXRlciB0byBwYXJzZSBtdXN0IGJlIGFycmF5IG9yIHVuZGVmaW5lZCcpO1xuICAgIH1cbiAgICBwYXJzZU9wdGlvbnMgPSBwYXJzZU9wdGlvbnMgfHwge307XG5cbiAgICAvLyBEZWZhdWx0IHRvIHVzaW5nIHByb2Nlc3MuYXJndlxuICAgIGlmIChhcmd2ID09PSB1bmRlZmluZWQpIHtcbiAgICAgIGFyZ3YgPSBwcm9jZXNzLmFyZ3Y7XG4gICAgICAvLyBAdHMtaWdub3JlOiB1bmtub3duIHByb3BlcnR5XG4gICAgICBpZiAocHJvY2Vzcy52ZXJzaW9ucyAmJiBwcm9jZXNzLnZlcnNpb25zLmVsZWN0cm9uKSB7XG4gICAgICAgIHBhcnNlT3B0aW9ucy5mcm9tID0gJ2VsZWN0cm9uJztcbiAgICAgIH1cbiAgICB9XG4gICAgdGhpcy5yYXdBcmdzID0gYXJndi5zbGljZSgpO1xuXG4gICAgLy8gbWFrZSBpdCBhIGxpdHRsZSBlYXNpZXIgZm9yIGNhbGxlcnMgYnkgc3VwcG9ydGluZyB2YXJpb3VzIGFyZ3YgY29udmVudGlvbnNcbiAgICBsZXQgdXNlckFyZ3M7XG4gICAgc3dpdGNoIChwYXJzZU9wdGlvbnMuZnJvbSkge1xuICAgICAgY2FzZSB1bmRlZmluZWQ6XG4gICAgICBjYXNlICdub2RlJzpcbiAgICAgICAgdGhpcy5fc2NyaXB0UGF0aCA9IGFyZ3ZbMV07XG4gICAgICAgIHVzZXJBcmdzID0gYXJndi5zbGljZSgyKTtcbiAgICAgICAgYnJlYWs7XG4gICAgICBjYXNlICdlbGVjdHJvbic6XG4gICAgICAgIC8vIEB0cy1pZ25vcmU6IHVua25vd24gcHJvcGVydHlcbiAgICAgICAgaWYgKHByb2Nlc3MuZGVmYXVsdEFwcCkge1xuICAgICAgICAgIHRoaXMuX3NjcmlwdFBhdGggPSBhcmd2WzFdO1xuICAgICAgICAgIHVzZXJBcmdzID0gYXJndi5zbGljZSgyKTtcbiAgICAgICAgfSBlbHNlIHtcbiAgICAgICAgICB1c2VyQXJncyA9IGFyZ3Yuc2xpY2UoMSk7XG4gICAgICAgIH1cbiAgICAgICAgYnJlYWs7XG4gICAgICBjYXNlICd1c2VyJzpcbiAgICAgICAgdXNlckFyZ3MgPSBhcmd2LnNsaWNlKDApO1xuICAgICAgICBicmVhaztcbiAgICAgIGRlZmF1bHQ6XG4gICAgICAgIHRocm93IG5ldyBFcnJvcihgdW5leHBlY3RlZCBwYXJzZSBvcHRpb24geyBmcm9tOiAnJHtwYXJzZU9wdGlvbnMuZnJvbX0nIH1gKTtcbiAgICB9XG5cbiAgICAvLyBGaW5kIGRlZmF1bHQgbmFtZSBmb3IgcHJvZ3JhbSBmcm9tIGFyZ3VtZW50cy5cbiAgICBpZiAoIXRoaXMuX25hbWUgJiYgdGhpcy5fc2NyaXB0UGF0aCkgdGhpcy5uYW1lRnJvbUZpbGVuYW1lKHRoaXMuX3NjcmlwdFBhdGgpO1xuICAgIHRoaXMuX25hbWUgPSB0aGlzLl9uYW1lIHx8ICdwcm9ncmFtJztcblxuICAgIHJldHVybiB1c2VyQXJncztcbiAgfVxuXG4gIC8qKlxuICAgKiBQYXJzZSBgYXJndmAsIHNldHRpbmcgb3B0aW9ucyBhbmQgaW52b2tpbmcgY29tbWFuZHMgd2hlbiBkZWZpbmVkLlxuICAgKlxuICAgKiBUaGUgZGVmYXVsdCBleHBlY3RhdGlvbiBpcyB0aGF0IHRoZSBhcmd1bWVudHMgYXJlIGZyb20gbm9kZSBhbmQgaGF2ZSB0aGUgYXBwbGljYXRpb24gYXMgYXJndlswXVxuICAgKiBhbmQgdGhlIHNjcmlwdCBiZWluZyBydW4gaW4gYXJndlsxXSwgd2l0aCB1c2VyIHBhcmFtZXRlcnMgYWZ0ZXIgdGhhdC5cbiAgICpcbiAgICogQGV4YW1wbGVcbiAgICogcHJvZ3JhbS5wYXJzZShwcm9jZXNzLmFyZ3YpO1xuICAgKiBwcm9ncmFtLnBhcnNlKCk7IC8vIGltcGxpY2l0bHkgdXNlIHByb2Nlc3MuYXJndiBhbmQgYXV0by1kZXRlY3Qgbm9kZSB2cyBlbGVjdHJvbiBjb252ZW50aW9uc1xuICAgKiBwcm9ncmFtLnBhcnNlKG15LWFyZ3MsIHsgZnJvbTogJ3VzZXInIH0pOyAvLyBqdXN0IHVzZXIgc3VwcGxpZWQgYXJndW1lbnRzLCBub3RoaW5nIHNwZWNpYWwgYWJvdXQgYXJndlswXVxuICAgKlxuICAgKiBAcGFyYW0ge3N0cmluZ1tdfSBbYXJndl0gLSBvcHRpb25hbCwgZGVmYXVsdHMgdG8gcHJvY2Vzcy5hcmd2XG4gICAqIEBwYXJhbSB7T2JqZWN0fSBbcGFyc2VPcHRpb25zXSAtIG9wdGlvbmFsbHkgc3BlY2lmeSBzdHlsZSBvZiBvcHRpb25zIHdpdGggZnJvbTogbm9kZS91c2VyL2VsZWN0cm9uXG4gICAqIEBwYXJhbSB7c3RyaW5nfSBbcGFyc2VPcHRpb25zLmZyb21dIC0gd2hlcmUgdGhlIGFyZ3MgYXJlIGZyb206ICdub2RlJywgJ3VzZXInLCAnZWxlY3Ryb24nXG4gICAqIEByZXR1cm4ge0NvbW1hbmR9IGB0aGlzYCBjb21tYW5kIGZvciBjaGFpbmluZ1xuICAgKi9cblxuICBwYXJzZShhcmd2LCBwYXJzZU9wdGlvbnMpIHtcbiAgICBjb25zdCB1c2VyQXJncyA9IHRoaXMuX3ByZXBhcmVVc2VyQXJncyhhcmd2LCBwYXJzZU9wdGlvbnMpO1xuICAgIHRoaXMuX3BhcnNlQ29tbWFuZChbXSwgdXNlckFyZ3MpO1xuXG4gICAgcmV0dXJuIHRoaXM7XG4gIH1cblxuICAvKipcbiAgICogUGFyc2UgYGFyZ3ZgLCBzZXR0aW5nIG9wdGlvbnMgYW5kIGludm9raW5nIGNvbW1hbmRzIHdoZW4gZGVmaW5lZC5cbiAgICpcbiAgICogVXNlIHBhcnNlQXN5bmMgaW5zdGVhZCBvZiBwYXJzZSBpZiBhbnkgb2YgeW91ciBhY3Rpb24gaGFuZGxlcnMgYXJlIGFzeW5jLiBSZXR1cm5zIGEgUHJvbWlzZS5cbiAgICpcbiAgICogVGhlIGRlZmF1bHQgZXhwZWN0YXRpb24gaXMgdGhhdCB0aGUgYXJndW1lbnRzIGFyZSBmcm9tIG5vZGUgYW5kIGhhdmUgdGhlIGFwcGxpY2F0aW9uIGFzIGFyZ3ZbMF1cbiAgICogYW5kIHRoZSBzY3JpcHQgYmVpbmcgcnVuIGluIGFyZ3ZbMV0sIHdpdGggdXNlciBwYXJhbWV0ZXJzIGFmdGVyIHRoYXQuXG4gICAqXG4gICAqIEBleGFtcGxlXG4gICAqIGF3YWl0IHByb2dyYW0ucGFyc2VBc3luYyhwcm9jZXNzLmFyZ3YpO1xuICAgKiBhd2FpdCBwcm9ncmFtLnBhcnNlQXN5bmMoKTsgLy8gaW1wbGljaXRseSB1c2UgcHJvY2Vzcy5hcmd2IGFuZCBhdXRvLWRldGVjdCBub2RlIHZzIGVsZWN0cm9uIGNvbnZlbnRpb25zXG4gICAqIGF3YWl0IHByb2dyYW0ucGFyc2VBc3luYyhteS1hcmdzLCB7IGZyb206ICd1c2VyJyB9KTsgLy8ganVzdCB1c2VyIHN1cHBsaWVkIGFyZ3VtZW50cywgbm90aGluZyBzcGVjaWFsIGFib3V0IGFyZ3ZbMF1cbiAgICpcbiAgICogQHBhcmFtIHtzdHJpbmdbXX0gW2FyZ3ZdXG4gICAqIEBwYXJhbSB7T2JqZWN0fSBbcGFyc2VPcHRpb25zXVxuICAgKiBAcGFyYW0ge3N0cmluZ30gcGFyc2VPcHRpb25zLmZyb20gLSB3aGVyZSB0aGUgYXJncyBhcmUgZnJvbTogJ25vZGUnLCAndXNlcicsICdlbGVjdHJvbidcbiAgICogQHJldHVybiB7UHJvbWlzZX1cbiAgICovXG5cbiAgYXN5bmMgcGFyc2VBc3luYyhhcmd2LCBwYXJzZU9wdGlvbnMpIHtcbiAgICBjb25zdCB1c2VyQXJncyA9IHRoaXMuX3ByZXBhcmVVc2VyQXJncyhhcmd2LCBwYXJzZU9wdGlvbnMpO1xuICAgIGF3YWl0IHRoaXMuX3BhcnNlQ29tbWFuZChbXSwgdXNlckFyZ3MpO1xuXG4gICAgcmV0dXJuIHRoaXM7XG4gIH1cblxuICAvKipcbiAgICogRXhlY3V0ZSBhIHN1Yi1jb21tYW5kIGV4ZWN1dGFibGUuXG4gICAqXG4gICAqIEBhcGkgcHJpdmF0ZVxuICAgKi9cblxuICBfZXhlY3V0ZVN1YkNvbW1hbmQoc3ViY29tbWFuZCwgYXJncykge1xuICAgIGFyZ3MgPSBhcmdzLnNsaWNlKCk7XG4gICAgbGV0IGxhdW5jaFdpdGhOb2RlID0gZmFsc2U7IC8vIFVzZSBub2RlIGZvciBzb3VyY2UgdGFyZ2V0cyBzbyBkbyBub3QgbmVlZCB0byBnZXQgcGVybWlzc2lvbnMgY29ycmVjdCwgYW5kIG9uIFdpbmRvd3MuXG4gICAgY29uc3Qgc291cmNlRXh0ID0gWycuanMnLCAnLnRzJywgJy50c3gnLCAnLm1qcycsICcuY2pzJ107XG5cbiAgICBmdW5jdGlvbiBmaW5kRmlsZShiYXNlRGlyLCBiYXNlTmFtZSkge1xuICAgICAgLy8gTG9vayBmb3Igc3BlY2lmaWVkIGZpbGVcbiAgICAgIGNvbnN0IGxvY2FsQmluID0gcGF0aC5yZXNvbHZlKGJhc2VEaXIsIGJhc2VOYW1lKTtcbiAgICAgIGlmIChmcy5leGlzdHNTeW5jKGxvY2FsQmluKSkgcmV0dXJuIGxvY2FsQmluO1xuXG4gICAgICAvLyBTdG9wIGxvb2tpbmcgaWYgY2FuZGlkYXRlIGFscmVhZHkgaGFzIGFuIGV4cGVjdGVkIGV4dGVuc2lvbi5cbiAgICAgIGlmIChzb3VyY2VFeHQuaW5jbHVkZXMocGF0aC5leHRuYW1lKGJhc2VOYW1lKSkpIHJldHVybiB1bmRlZmluZWQ7XG5cbiAgICAgIC8vIFRyeSBhbGwgdGhlIGV4dGVuc2lvbnMuXG4gICAgICBjb25zdCBmb3VuZEV4dCA9IHNvdXJjZUV4dC5maW5kKGV4dCA9PiBmcy5leGlzdHNTeW5jKGAke2xvY2FsQmlufSR7ZXh0fWApKTtcbiAgICAgIGlmIChmb3VuZEV4dCkgcmV0dXJuIGAke2xvY2FsQmlufSR7Zm91bmRFeHR9YDtcblxuICAgICAgcmV0dXJuIHVuZGVmaW5lZDtcbiAgICB9XG5cbiAgICAvLyBOb3QgY2hlY2tpbmcgZm9yIGhlbHAgZmlyc3QuIFVubGlrZWx5IHRvIGhhdmUgbWFuZGF0b3J5IGFuZCBleGVjdXRhYmxlLCBhbmQgY2FuJ3Qgcm9idXN0bHkgdGVzdCBmb3IgaGVscCBmbGFncyBpbiBleHRlcm5hbCBjb21tYW5kLlxuICAgIHRoaXMuX2NoZWNrRm9yTWlzc2luZ01hbmRhdG9yeU9wdGlvbnMoKTtcbiAgICB0aGlzLl9jaGVja0ZvckNvbmZsaWN0aW5nT3B0aW9ucygpO1xuXG4gICAgLy8gZXhlY3V0YWJsZUZpbGUgYW5kIGV4ZWN1dGFibGVEaXIgbWlnaHQgYmUgZnVsbCBwYXRoLCBvciBqdXN0IGEgbmFtZVxuICAgIGxldCBleGVjdXRhYmxlRmlsZSA9IHN1YmNvbW1hbmQuX2V4ZWN1dGFibGVGaWxlIHx8IGAke3RoaXMuX25hbWV9LSR7c3ViY29tbWFuZC5fbmFtZX1gO1xuICAgIGxldCBleGVjdXRhYmxlRGlyID0gdGhpcy5fZXhlY3V0YWJsZURpciB8fCAnJztcbiAgICBpZiAodGhpcy5fc2NyaXB0UGF0aCkge1xuICAgICAgbGV0IHJlc29sdmVkU2NyaXB0UGF0aDsgLy8gcmVzb2x2ZSBwb3NzaWJsZSBzeW1saW5rIGZvciBpbnN0YWxsZWQgbnBtIGJpbmFyeVxuICAgICAgdHJ5IHtcbiAgICAgICAgcmVzb2x2ZWRTY3JpcHRQYXRoID0gZnMucmVhbHBhdGhTeW5jKHRoaXMuX3NjcmlwdFBhdGgpO1xuICAgICAgfSBjYXRjaCAoZXJyKSB7XG4gICAgICAgIHJlc29sdmVkU2NyaXB0UGF0aCA9IHRoaXMuX3NjcmlwdFBhdGg7XG4gICAgICB9XG4gICAgICBleGVjdXRhYmxlRGlyID0gcGF0aC5yZXNvbHZlKHBhdGguZGlybmFtZShyZXNvbHZlZFNjcmlwdFBhdGgpLCBleGVjdXRhYmxlRGlyKTtcbiAgICB9XG5cbiAgICAvLyBMb29rIGZvciBhIGxvY2FsIGZpbGUgaW4gcHJlZmVyZW5jZSB0byBhIGNvbW1hbmQgaW4gUEFUSC5cbiAgICBpZiAoZXhlY3V0YWJsZURpcikge1xuICAgICAgbGV0IGxvY2FsRmlsZSA9IGZpbmRGaWxlKGV4ZWN1dGFibGVEaXIsIGV4ZWN1dGFibGVGaWxlKTtcblxuICAgICAgLy8gTGVnYWN5IHNlYXJjaCB1c2luZyBwcmVmaXggb2Ygc2NyaXB0IG5hbWUgaW5zdGVhZCBvZiBjb21tYW5kIG5hbWVcbiAgICAgIGlmICghbG9jYWxGaWxlICYmICFzdWJjb21tYW5kLl9leGVjdXRhYmxlRmlsZSAmJiB0aGlzLl9zY3JpcHRQYXRoKSB7XG4gICAgICAgIGNvbnN0IGxlZ2FjeU5hbWUgPSBwYXRoLmJhc2VuYW1lKHRoaXMuX3NjcmlwdFBhdGgsIHBhdGguZXh0bmFtZSh0aGlzLl9zY3JpcHRQYXRoKSk7XG4gICAgICAgIGlmIChsZWdhY3lOYW1lICE9PSB0aGlzLl9uYW1lKSB7XG4gICAgICAgICAgbG9jYWxGaWxlID0gZmluZEZpbGUoZXhlY3V0YWJsZURpciwgYCR7bGVnYWN5TmFtZX0tJHtzdWJjb21tYW5kLl9uYW1lfWApO1xuICAgICAgICB9XG4gICAgICB9XG4gICAgICBleGVjdXRhYmxlRmlsZSA9IGxvY2FsRmlsZSB8fCBleGVjdXRhYmxlRmlsZTtcbiAgICB9XG5cbiAgICBsYXVuY2hXaXRoTm9kZSA9IHNvdXJjZUV4dC5pbmNsdWRlcyhwYXRoLmV4dG5hbWUoZXhlY3V0YWJsZUZpbGUpKTtcblxuICAgIGxldCBwcm9jO1xuICAgIGlmIChwcm9jZXNzLnBsYXRmb3JtICE9PSAnd2luMzInKSB7XG4gICAgICBpZiAobGF1bmNoV2l0aE5vZGUpIHtcbiAgICAgICAgYXJncy51bnNoaWZ0KGV4ZWN1dGFibGVGaWxlKTtcbiAgICAgICAgLy8gYWRkIGV4ZWN1dGFibGUgYXJndW1lbnRzIHRvIHNwYXduXG4gICAgICAgIGFyZ3MgPSBpbmNyZW1lbnROb2RlSW5zcGVjdG9yUG9ydChwcm9jZXNzLmV4ZWNBcmd2KS5jb25jYXQoYXJncyk7XG5cbiAgICAgICAgcHJvYyA9IGNoaWxkUHJvY2Vzcy5zcGF3bihwcm9jZXNzLmFyZ3ZbMF0sIGFyZ3MsIHsgc3RkaW86ICdpbmhlcml0JyB9KTtcbiAgICAgIH0gZWxzZSB7XG4gICAgICAgIHByb2MgPSBjaGlsZFByb2Nlc3Muc3Bhd24oZXhlY3V0YWJsZUZpbGUsIGFyZ3MsIHsgc3RkaW86ICdpbmhlcml0JyB9KTtcbiAgICAgIH1cbiAgICB9IGVsc2Uge1xuICAgICAgYXJncy51bnNoaWZ0KGV4ZWN1dGFibGVGaWxlKTtcbiAgICAgIC8vIGFkZCBleGVjdXRhYmxlIGFyZ3VtZW50cyB0byBzcGF3blxuICAgICAgYXJncyA9IGluY3JlbWVudE5vZGVJbnNwZWN0b3JQb3J0KHByb2Nlc3MuZXhlY0FyZ3YpLmNvbmNhdChhcmdzKTtcbiAgICAgIHByb2MgPSBjaGlsZFByb2Nlc3Muc3Bhd24ocHJvY2Vzcy5leGVjUGF0aCwgYXJncywgeyBzdGRpbzogJ2luaGVyaXQnIH0pO1xuICAgIH1cblxuICAgIGlmICghcHJvYy5raWxsZWQpIHsgLy8gdGVzdGluZyBtYWlubHkgdG8gYXZvaWQgbGVhayB3YXJuaW5ncyBkdXJpbmcgdW5pdCB0ZXN0cyB3aXRoIG1vY2tlZCBzcGF3blxuICAgICAgY29uc3Qgc2lnbmFscyA9IFsnU0lHVVNSMScsICdTSUdVU1IyJywgJ1NJR1RFUk0nLCAnU0lHSU5UJywgJ1NJR0hVUCddO1xuICAgICAgc2lnbmFscy5mb3JFYWNoKChzaWduYWwpID0+IHtcbiAgICAgICAgLy8gQHRzLWlnbm9yZVxuICAgICAgICBwcm9jZXNzLm9uKHNpZ25hbCwgKCkgPT4ge1xuICAgICAgICAgIGlmIChwcm9jLmtpbGxlZCA9PT0gZmFsc2UgJiYgcHJvYy5leGl0Q29kZSA9PT0gbnVsbCkge1xuICAgICAgICAgICAgcHJvYy5raWxsKHNpZ25hbCk7XG4gICAgICAgICAgfVxuICAgICAgICB9KTtcbiAgICAgIH0pO1xuICAgIH1cblxuICAgIC8vIEJ5IGRlZmF1bHQgdGVybWluYXRlIHByb2Nlc3Mgd2hlbiBzcGF3bmVkIHByb2Nlc3MgdGVybWluYXRlcy5cbiAgICAvLyBTdXBwcmVzc2luZyB0aGUgZXhpdCBpZiBleGl0Q2FsbGJhY2sgZGVmaW5lZCBpcyBhIGJpdCBtZXNzeSBhbmQgb2YgbGltaXRlZCB1c2UsIGJ1dCBkb2VzIGFsbG93IHByb2Nlc3MgdG8gc3RheSBydW5uaW5nIVxuICAgIGNvbnN0IGV4aXRDYWxsYmFjayA9IHRoaXMuX2V4aXRDYWxsYmFjaztcbiAgICBpZiAoIWV4aXRDYWxsYmFjaykge1xuICAgICAgcHJvYy5vbignY2xvc2UnLCBwcm9jZXNzLmV4aXQuYmluZChwcm9jZXNzKSk7XG4gICAgfSBlbHNlIHtcbiAgICAgIHByb2Mub24oJ2Nsb3NlJywgKCkgPT4ge1xuICAgICAgICBleGl0Q2FsbGJhY2sobmV3IENvbW1hbmRlckVycm9yKHByb2Nlc3MuZXhpdENvZGUgfHwgMCwgJ2NvbW1hbmRlci5leGVjdXRlU3ViQ29tbWFuZEFzeW5jJywgJyhjbG9zZSknKSk7XG4gICAgICB9KTtcbiAgICB9XG4gICAgcHJvYy5vbignZXJyb3InLCAoZXJyKSA9PiB7XG4gICAgICAvLyBAdHMtaWdub3JlXG4gICAgICBpZiAoZXJyLmNvZGUgPT09ICdFTk9FTlQnKSB7XG4gICAgICAgIGNvbnN0IGV4ZWN1dGFibGVEaXJNZXNzYWdlID0gZXhlY3V0YWJsZURpclxuICAgICAgICAgID8gYHNlYXJjaGVkIGZvciBsb2NhbCBzdWJjb21tYW5kIHJlbGF0aXZlIHRvIGRpcmVjdG9yeSAnJHtleGVjdXRhYmxlRGlyfSdgXG4gICAgICAgICAgOiAnbm8gZGlyZWN0b3J5IGZvciBzZWFyY2ggZm9yIGxvY2FsIHN1YmNvbW1hbmQsIHVzZSAuZXhlY3V0YWJsZURpcigpIHRvIHN1cHBseSBhIGN1c3RvbSBkaXJlY3RvcnknO1xuICAgICAgICBjb25zdCBleGVjdXRhYmxlTWlzc2luZyA9IGAnJHtleGVjdXRhYmxlRmlsZX0nIGRvZXMgbm90IGV4aXN0XG4gLSBpZiAnJHtzdWJjb21tYW5kLl9uYW1lfScgaXMgbm90IG1lYW50IHRvIGJlIGFuIGV4ZWN1dGFibGUgY29tbWFuZCwgcmVtb3ZlIGRlc2NyaXB0aW9uIHBhcmFtZXRlciBmcm9tICcuY29tbWFuZCgpJyBhbmQgdXNlICcuZGVzY3JpcHRpb24oKScgaW5zdGVhZFxuIC0gaWYgdGhlIGRlZmF1bHQgZXhlY3V0YWJsZSBuYW1lIGlzIG5vdCBzdWl0YWJsZSwgdXNlIHRoZSBleGVjdXRhYmxlRmlsZSBvcHRpb24gdG8gc3VwcGx5IGEgY3VzdG9tIG5hbWUgb3IgcGF0aFxuIC0gJHtleGVjdXRhYmxlRGlyTWVzc2FnZX1gO1xuICAgICAgICB0aHJvdyBuZXcgRXJyb3IoZXhlY3V0YWJsZU1pc3NpbmcpO1xuICAgICAgLy8gQHRzLWlnbm9yZVxuICAgICAgfSBlbHNlIGlmIChlcnIuY29kZSA9PT0gJ0VBQ0NFUycpIHtcbiAgICAgICAgdGhyb3cgbmV3IEVycm9yKGAnJHtleGVjdXRhYmxlRmlsZX0nIG5vdCBleGVjdXRhYmxlYCk7XG4gICAgICB9XG4gICAgICBpZiAoIWV4aXRDYWxsYmFjaykge1xuICAgICAgICBwcm9jZXNzLmV4aXQoMSk7XG4gICAgICB9IGVsc2Uge1xuICAgICAgICBjb25zdCB3cmFwcGVkRXJyb3IgPSBuZXcgQ29tbWFuZGVyRXJyb3IoMSwgJ2NvbW1hbmRlci5leGVjdXRlU3ViQ29tbWFuZEFzeW5jJywgJyhlcnJvciknKTtcbiAgICAgICAgd3JhcHBlZEVycm9yLm5lc3RlZEVycm9yID0gZXJyO1xuICAgICAgICBleGl0Q2FsbGJhY2sod3JhcHBlZEVycm9yKTtcbiAgICAgIH1cbiAgICB9KTtcblxuICAgIC8vIFN0b3JlIHRoZSByZWZlcmVuY2UgdG8gdGhlIGNoaWxkIHByb2Nlc3NcbiAgICB0aGlzLnJ1bm5pbmdDb21tYW5kID0gcHJvYztcbiAgfVxuXG4gIC8qKlxuICAgKiBAYXBpIHByaXZhdGVcbiAgICovXG5cbiAgX2Rpc3BhdGNoU3ViY29tbWFuZChjb21tYW5kTmFtZSwgb3BlcmFuZHMsIHVua25vd24pIHtcbiAgICBjb25zdCBzdWJDb21tYW5kID0gdGhpcy5fZmluZENvbW1hbmQoY29tbWFuZE5hbWUpO1xuICAgIGlmICghc3ViQ29tbWFuZCkgdGhpcy5oZWxwKHsgZXJyb3I6IHRydWUgfSk7XG5cbiAgICBsZXQgaG9va1Jlc3VsdDtcbiAgICBob29rUmVzdWx0ID0gdGhpcy5fY2hhaW5PckNhbGxTdWJDb21tYW5kSG9vayhob29rUmVzdWx0LCBzdWJDb21tYW5kLCAncHJlU3ViY29tbWFuZCcpO1xuICAgIGhvb2tSZXN1bHQgPSB0aGlzLl9jaGFpbk9yQ2FsbChob29rUmVzdWx0LCAoKSA9PiB7XG4gICAgICBpZiAoc3ViQ29tbWFuZC5fZXhlY3V0YWJsZUhhbmRsZXIpIHtcbiAgICAgICAgdGhpcy5fZXhlY3V0ZVN1YkNvbW1hbmQoc3ViQ29tbWFuZCwgb3BlcmFuZHMuY29uY2F0KHVua25vd24pKTtcbiAgICAgIH0gZWxzZSB7XG4gICAgICAgIHJldHVybiBzdWJDb21tYW5kLl9wYXJzZUNvbW1hbmQob3BlcmFuZHMsIHVua25vd24pO1xuICAgICAgfVxuICAgIH0pO1xuICAgIHJldHVybiBob29rUmVzdWx0O1xuICB9XG5cbiAgLyoqXG4gICAqIENoZWNrIHRoaXMuYXJncyBhZ2FpbnN0IGV4cGVjdGVkIHRoaXMuX2FyZ3MuXG4gICAqXG4gICAqIEBhcGkgcHJpdmF0ZVxuICAgKi9cblxuICBfY2hlY2tOdW1iZXJPZkFyZ3VtZW50cygpIHtcbiAgICAvLyB0b28gZmV3XG4gICAgdGhpcy5fYXJncy5mb3JFYWNoKChhcmcsIGkpID0+IHtcbiAgICAgIGlmIChhcmcucmVxdWlyZWQgJiYgdGhpcy5hcmdzW2ldID09IG51bGwpIHtcbiAgICAgICAgdGhpcy5taXNzaW5nQXJndW1lbnQoYXJnLm5hbWUoKSk7XG4gICAgICB9XG4gICAgfSk7XG4gICAgLy8gdG9vIG1hbnlcbiAgICBpZiAodGhpcy5fYXJncy5sZW5ndGggPiAwICYmIHRoaXMuX2FyZ3NbdGhpcy5fYXJncy5sZW5ndGggLSAxXS52YXJpYWRpYykge1xuICAgICAgcmV0dXJuO1xuICAgIH1cbiAgICBpZiAodGhpcy5hcmdzLmxlbmd0aCA+IHRoaXMuX2FyZ3MubGVuZ3RoKSB7XG4gICAgICB0aGlzLl9leGNlc3NBcmd1bWVudHModGhpcy5hcmdzKTtcbiAgICB9XG4gIH1cblxuICAvKipcbiAgICogUHJvY2VzcyB0aGlzLmFyZ3MgdXNpbmcgdGhpcy5fYXJncyBhbmQgc2F2ZSBhcyB0aGlzLnByb2Nlc3NlZEFyZ3MhXG4gICAqXG4gICAqIEBhcGkgcHJpdmF0ZVxuICAgKi9cblxuICBfcHJvY2Vzc0FyZ3VtZW50cygpIHtcbiAgICBjb25zdCBteVBhcnNlQXJnID0gKGFyZ3VtZW50LCB2YWx1ZSwgcHJldmlvdXMpID0+IHtcbiAgICAgIC8vIEV4dHJhIHByb2Nlc3NpbmcgZm9yIG5pY2UgZXJyb3IgbWVzc2FnZSBvbiBwYXJzaW5nIGZhaWx1cmUuXG4gICAgICBsZXQgcGFyc2VkVmFsdWUgPSB2YWx1ZTtcbiAgICAgIGlmICh2YWx1ZSAhPT0gbnVsbCAmJiBhcmd1bWVudC5wYXJzZUFyZykge1xuICAgICAgICB0cnkge1xuICAgICAgICAgIHBhcnNlZFZhbHVlID0gYXJndW1lbnQucGFyc2VBcmcodmFsdWUsIHByZXZpb3VzKTtcbiAgICAgICAgfSBjYXRjaCAoZXJyKSB7XG4gICAgICAgICAgaWYgKGVyci5jb2RlID09PSAnY29tbWFuZGVyLmludmFsaWRBcmd1bWVudCcpIHtcbiAgICAgICAgICAgIGNvbnN0IG1lc3NhZ2UgPSBgZXJyb3I6IGNvbW1hbmQtYXJndW1lbnQgdmFsdWUgJyR7dmFsdWV9JyBpcyBpbnZhbGlkIGZvciBhcmd1bWVudCAnJHthcmd1bWVudC5uYW1lKCl9Jy4gJHtlcnIubWVzc2FnZX1gO1xuICAgICAgICAgICAgdGhpcy5lcnJvcihtZXNzYWdlLCB7IGV4aXRDb2RlOiBlcnIuZXhpdENvZGUsIGNvZGU6IGVyci5jb2RlIH0pO1xuICAgICAgICAgIH1cbiAgICAgICAgICB0aHJvdyBlcnI7XG4gICAgICAgIH1cbiAgICAgIH1cbiAgICAgIHJldHVybiBwYXJzZWRWYWx1ZTtcbiAgICB9O1xuXG4gICAgdGhpcy5fY2hlY2tOdW1iZXJPZkFyZ3VtZW50cygpO1xuXG4gICAgY29uc3QgcHJvY2Vzc2VkQXJncyA9IFtdO1xuICAgIHRoaXMuX2FyZ3MuZm9yRWFjaCgoZGVjbGFyZWRBcmcsIGluZGV4KSA9PiB7XG4gICAgICBsZXQgdmFsdWUgPSBkZWNsYXJlZEFyZy5kZWZhdWx0VmFsdWU7XG4gICAgICBpZiAoZGVjbGFyZWRBcmcudmFyaWFkaWMpIHtcbiAgICAgICAgLy8gQ29sbGVjdCB0b2dldGhlciByZW1haW5pbmcgYXJndW1lbnRzIGZvciBwYXNzaW5nIHRvZ2V0aGVyIGFzIGFuIGFycmF5LlxuICAgICAgICBpZiAoaW5kZXggPCB0aGlzLmFyZ3MubGVuZ3RoKSB7XG4gICAgICAgICAgdmFsdWUgPSB0aGlzLmFyZ3Muc2xpY2UoaW5kZXgpO1xuICAgICAgICAgIGlmIChkZWNsYXJlZEFyZy5wYXJzZUFyZykge1xuICAgICAgICAgICAgdmFsdWUgPSB2YWx1ZS5yZWR1Y2UoKHByb2Nlc3NlZCwgdikgPT4ge1xuICAgICAgICAgICAgICByZXR1cm4gbXlQYXJzZUFyZyhkZWNsYXJlZEFyZywgdiwgcHJvY2Vzc2VkKTtcbiAgICAgICAgICAgIH0sIGRlY2xhcmVkQXJnLmRlZmF1bHRWYWx1ZSk7XG4gICAgICAgICAgfVxuICAgICAgICB9IGVsc2UgaWYgKHZhbHVlID09PSB1bmRlZmluZWQpIHtcbiAgICAgICAgICB2YWx1ZSA9IFtdO1xuICAgICAgICB9XG4gICAgICB9IGVsc2UgaWYgKGluZGV4IDwgdGhpcy5hcmdzLmxlbmd0aCkge1xuICAgICAgICB2YWx1ZSA9IHRoaXMuYXJnc1tpbmRleF07XG4gICAgICAgIGlmIChkZWNsYXJlZEFyZy5wYXJzZUFyZykge1xuICAgICAgICAgIHZhbHVlID0gbXlQYXJzZUFyZyhkZWNsYXJlZEFyZywgdmFsdWUsIGRlY2xhcmVkQXJnLmRlZmF1bHRWYWx1ZSk7XG4gICAgICAgIH1cbiAgICAgIH1cbiAgICAgIHByb2Nlc3NlZEFyZ3NbaW5kZXhdID0gdmFsdWU7XG4gICAgfSk7XG4gICAgdGhpcy5wcm9jZXNzZWRBcmdzID0gcHJvY2Vzc2VkQXJncztcbiAgfVxuXG4gIC8qKlxuICAgKiBPbmNlIHdlIGhhdmUgYSBwcm9taXNlIHdlIGNoYWluLCBidXQgY2FsbCBzeW5jaHJvbm91c2x5IHVudGlsIHRoZW4uXG4gICAqXG4gICAqIEBwYXJhbSB7UHJvbWlzZXx1bmRlZmluZWR9IHByb21pc2VcbiAgICogQHBhcmFtIHtGdW5jdGlvbn0gZm5cbiAgICogQHJldHVybiB7UHJvbWlzZXx1bmRlZmluZWR9XG4gICAqIEBhcGkgcHJpdmF0ZVxuICAgKi9cblxuICBfY2hhaW5PckNhbGwocHJvbWlzZSwgZm4pIHtcbiAgICAvLyB0aGVuYWJsZVxuICAgIGlmIChwcm9taXNlICYmIHByb21pc2UudGhlbiAmJiB0eXBlb2YgcHJvbWlzZS50aGVuID09PSAnZnVuY3Rpb24nKSB7XG4gICAgICAvLyBhbHJlYWR5IGhhdmUgYSBwcm9taXNlLCBjaGFpbiBjYWxsYmFja1xuICAgICAgcmV0dXJuIHByb21pc2UudGhlbigoKSA9PiBmbigpKTtcbiAgICB9XG4gICAgLy8gY2FsbGJhY2sgbWlnaHQgcmV0dXJuIGEgcHJvbWlzZVxuICAgIHJldHVybiBmbigpO1xuICB9XG5cbiAgLyoqXG4gICAqXG4gICAqIEBwYXJhbSB7UHJvbWlzZXx1bmRlZmluZWR9IHByb21pc2VcbiAgICogQHBhcmFtIHtzdHJpbmd9IGV2ZW50XG4gICAqIEByZXR1cm4ge1Byb21pc2V8dW5kZWZpbmVkfVxuICAgKiBAYXBpIHByaXZhdGVcbiAgICovXG5cbiAgX2NoYWluT3JDYWxsSG9va3MocHJvbWlzZSwgZXZlbnQpIHtcbiAgICBsZXQgcmVzdWx0ID0gcHJvbWlzZTtcbiAgICBjb25zdCBob29rcyA9IFtdO1xuICAgIGdldENvbW1hbmRBbmRQYXJlbnRzKHRoaXMpXG4gICAgICAucmV2ZXJzZSgpXG4gICAgICAuZmlsdGVyKGNtZCA9PiBjbWQuX2xpZmVDeWNsZUhvb2tzW2V2ZW50XSAhPT0gdW5kZWZpbmVkKVxuICAgICAgLmZvckVhY2goaG9va2VkQ29tbWFuZCA9PiB7XG4gICAgICAgIGhvb2tlZENvbW1hbmQuX2xpZmVDeWNsZUhvb2tzW2V2ZW50XS5mb3JFYWNoKChjYWxsYmFjaykgPT4ge1xuICAgICAgICAgIGhvb2tzLnB1c2goeyBob29rZWRDb21tYW5kLCBjYWxsYmFjayB9KTtcbiAgICAgICAgfSk7XG4gICAgICB9KTtcbiAgICBpZiAoZXZlbnQgPT09ICdwb3N0QWN0aW9uJykge1xuICAgICAgaG9va3MucmV2ZXJzZSgpO1xuICAgIH1cblxuICAgIGhvb2tzLmZvckVhY2goKGhvb2tEZXRhaWwpID0+IHtcbiAgICAgIHJlc3VsdCA9IHRoaXMuX2NoYWluT3JDYWxsKHJlc3VsdCwgKCkgPT4ge1xuICAgICAgICByZXR1cm4gaG9va0RldGFpbC5jYWxsYmFjayhob29rRGV0YWlsLmhvb2tlZENvbW1hbmQsIHRoaXMpO1xuICAgICAgfSk7XG4gICAgfSk7XG4gICAgcmV0dXJuIHJlc3VsdDtcbiAgfVxuXG4gIC8qKlxuICAgKlxuICAgKiBAcGFyYW0ge1Byb21pc2V8dW5kZWZpbmVkfSBwcm9taXNlXG4gICAqIEBwYXJhbSB7Q29tbWFuZH0gc3ViQ29tbWFuZFxuICAgKiBAcGFyYW0ge3N0cmluZ30gZXZlbnRcbiAgICogQHJldHVybiB7UHJvbWlzZXx1bmRlZmluZWR9XG4gICAqIEBhcGkgcHJpdmF0ZVxuICAgKi9cblxuICBfY2hhaW5PckNhbGxTdWJDb21tYW5kSG9vayhwcm9taXNlLCBzdWJDb21tYW5kLCBldmVudCkge1xuICAgIGxldCByZXN1bHQgPSBwcm9taXNlO1xuICAgIGlmICh0aGlzLl9saWZlQ3ljbGVIb29rc1tldmVudF0gIT09IHVuZGVmaW5lZCkge1xuICAgICAgdGhpcy5fbGlmZUN5Y2xlSG9va3NbZXZlbnRdLmZvckVhY2goKGhvb2spID0+IHtcbiAgICAgICAgcmVzdWx0ID0gdGhpcy5fY2hhaW5PckNhbGwocmVzdWx0LCAoKSA9PiB7XG4gICAgICAgICAgcmV0dXJuIGhvb2sodGhpcywgc3ViQ29tbWFuZCk7XG4gICAgICAgIH0pO1xuICAgICAgfSk7XG4gICAgfVxuICAgIHJldHVybiByZXN1bHQ7XG4gIH1cblxuICAvKipcbiAgICogUHJvY2VzcyBhcmd1bWVudHMgaW4gY29udGV4dCBvZiB0aGlzIGNvbW1hbmQuXG4gICAqIFJldHVybnMgYWN0aW9uIHJlc3VsdCwgaW4gY2FzZSBpdCBpcyBhIHByb21pc2UuXG4gICAqXG4gICAqIEBhcGkgcHJpdmF0ZVxuICAgKi9cblxuICBfcGFyc2VDb21tYW5kKG9wZXJhbmRzLCB1bmtub3duKSB7XG4gICAgY29uc3QgcGFyc2VkID0gdGhpcy5wYXJzZU9wdGlvbnModW5rbm93bik7XG4gICAgdGhpcy5fcGFyc2VPcHRpb25zRW52KCk7IC8vIGFmdGVyIGNsaSwgc28gcGFyc2VBcmcgbm90IGNhbGxlZCBvbiBib3RoIGNsaSBhbmQgZW52XG4gICAgdGhpcy5fcGFyc2VPcHRpb25zSW1wbGllZCgpO1xuICAgIG9wZXJhbmRzID0gb3BlcmFuZHMuY29uY2F0KHBhcnNlZC5vcGVyYW5kcyk7XG4gICAgdW5rbm93biA9IHBhcnNlZC51bmtub3duO1xuICAgIHRoaXMuYXJncyA9IG9wZXJhbmRzLmNvbmNhdCh1bmtub3duKTtcblxuICAgIGlmIChvcGVyYW5kcyAmJiB0aGlzLl9maW5kQ29tbWFuZChvcGVyYW5kc1swXSkpIHtcbiAgICAgIHJldHVybiB0aGlzLl9kaXNwYXRjaFN1YmNvbW1hbmQob3BlcmFuZHNbMF0sIG9wZXJhbmRzLnNsaWNlKDEpLCB1bmtub3duKTtcbiAgICB9XG4gICAgaWYgKHRoaXMuX2hhc0ltcGxpY2l0SGVscENvbW1hbmQoKSAmJiBvcGVyYW5kc1swXSA9PT0gdGhpcy5faGVscENvbW1hbmROYW1lKSB7XG4gICAgICBpZiAob3BlcmFuZHMubGVuZ3RoID09PSAxKSB7XG4gICAgICAgIHRoaXMuaGVscCgpO1xuICAgICAgfVxuICAgICAgcmV0dXJuIHRoaXMuX2Rpc3BhdGNoU3ViY29tbWFuZChvcGVyYW5kc1sxXSwgW10sIFt0aGlzLl9oZWxwTG9uZ0ZsYWddKTtcbiAgICB9XG4gICAgaWYgKHRoaXMuX2RlZmF1bHRDb21tYW5kTmFtZSkge1xuICAgICAgb3V0cHV0SGVscElmUmVxdWVzdGVkKHRoaXMsIHVua25vd24pOyAvLyBSdW4gdGhlIGhlbHAgZm9yIGRlZmF1bHQgY29tbWFuZCBmcm9tIHBhcmVudCByYXRoZXIgdGhhbiBwYXNzaW5nIHRvIGRlZmF1bHQgY29tbWFuZFxuICAgICAgcmV0dXJuIHRoaXMuX2Rpc3BhdGNoU3ViY29tbWFuZCh0aGlzLl9kZWZhdWx0Q29tbWFuZE5hbWUsIG9wZXJhbmRzLCB1bmtub3duKTtcbiAgICB9XG4gICAgaWYgKHRoaXMuY29tbWFuZHMubGVuZ3RoICYmIHRoaXMuYXJncy5sZW5ndGggPT09IDAgJiYgIXRoaXMuX2FjdGlvbkhhbmRsZXIgJiYgIXRoaXMuX2RlZmF1bHRDb21tYW5kTmFtZSkge1xuICAgICAgLy8gcHJvYmFibHkgbWlzc2luZyBzdWJjb21tYW5kIGFuZCBubyBoYW5kbGVyLCB1c2VyIG5lZWRzIGhlbHAgKGFuZCBleGl0KVxuICAgICAgdGhpcy5oZWxwKHsgZXJyb3I6IHRydWUgfSk7XG4gICAgfVxuXG4gICAgb3V0cHV0SGVscElmUmVxdWVzdGVkKHRoaXMsIHBhcnNlZC51bmtub3duKTtcbiAgICB0aGlzLl9jaGVja0Zvck1pc3NpbmdNYW5kYXRvcnlPcHRpb25zKCk7XG4gICAgdGhpcy5fY2hlY2tGb3JDb25mbGljdGluZ09wdGlvbnMoKTtcblxuICAgIC8vIFdlIGRvIG5vdCBhbHdheXMgY2FsbCB0aGlzIGNoZWNrIHRvIGF2b2lkIG1hc2tpbmcgYSBcImJldHRlclwiIGVycm9yLCBsaWtlIHVua25vd24gY29tbWFuZC5cbiAgICBjb25zdCBjaGVja0ZvclVua25vd25PcHRpb25zID0gKCkgPT4ge1xuICAgICAgaWYgKHBhcnNlZC51bmtub3duLmxlbmd0aCA+IDApIHtcbiAgICAgICAgdGhpcy51bmtub3duT3B0aW9uKHBhcnNlZC51bmtub3duWzBdKTtcbiAgICAgIH1cbiAgICB9O1xuXG4gICAgY29uc3QgY29tbWFuZEV2ZW50ID0gYGNvbW1hbmQ6JHt0aGlzLm5hbWUoKX1gO1xuICAgIGlmICh0aGlzLl9hY3Rpb25IYW5kbGVyKSB7XG4gICAgICBjaGVja0ZvclVua25vd25PcHRpb25zKCk7XG4gICAgICB0aGlzLl9wcm9jZXNzQXJndW1lbnRzKCk7XG5cbiAgICAgIGxldCBhY3Rpb25SZXN1bHQ7XG4gICAgICBhY3Rpb25SZXN1bHQgPSB0aGlzLl9jaGFpbk9yQ2FsbEhvb2tzKGFjdGlvblJlc3VsdCwgJ3ByZUFjdGlvbicpO1xuICAgICAgYWN0aW9uUmVzdWx0ID0gdGhpcy5fY2hhaW5PckNhbGwoYWN0aW9uUmVzdWx0LCAoKSA9PiB0aGlzLl9hY3Rpb25IYW5kbGVyKHRoaXMucHJvY2Vzc2VkQXJncykpO1xuICAgICAgaWYgKHRoaXMucGFyZW50KSB7XG4gICAgICAgIGFjdGlvblJlc3VsdCA9IHRoaXMuX2NoYWluT3JDYWxsKGFjdGlvblJlc3VsdCwgKCkgPT4ge1xuICAgICAgICAgIHRoaXMucGFyZW50LmVtaXQoY29tbWFuZEV2ZW50LCBvcGVyYW5kcywgdW5rbm93bik7IC8vIGxlZ2FjeVxuICAgICAgICB9KTtcbiAgICAgIH1cbiAgICAgIGFjdGlvblJlc3VsdCA9IHRoaXMuX2NoYWluT3JDYWxsSG9va3MoYWN0aW9uUmVzdWx0LCAncG9zdEFjdGlvbicpO1xuICAgICAgcmV0dXJuIGFjdGlvblJlc3VsdDtcbiAgICB9XG4gICAgaWYgKHRoaXMucGFyZW50ICYmIHRoaXMucGFyZW50Lmxpc3RlbmVyQ291bnQoY29tbWFuZEV2ZW50KSkge1xuICAgICAgY2hlY2tGb3JVbmtub3duT3B0aW9ucygpO1xuICAgICAgdGhpcy5fcHJvY2Vzc0FyZ3VtZW50cygpO1xuICAgICAgdGhpcy5wYXJlbnQuZW1pdChjb21tYW5kRXZlbnQsIG9wZXJhbmRzLCB1bmtub3duKTsgLy8gbGVnYWN5XG4gICAgfSBlbHNlIGlmIChvcGVyYW5kcy5sZW5ndGgpIHtcbiAgICAgIGlmICh0aGlzLl9maW5kQ29tbWFuZCgnKicpKSB7IC8vIGxlZ2FjeSBkZWZhdWx0IGNvbW1hbmRcbiAgICAgICAgcmV0dXJuIHRoaXMuX2Rpc3BhdGNoU3ViY29tbWFuZCgnKicsIG9wZXJhbmRzLCB1bmtub3duKTtcbiAgICAgIH1cbiAgICAgIGlmICh0aGlzLmxpc3RlbmVyQ291bnQoJ2NvbW1hbmQ6KicpKSB7XG4gICAgICAgIC8vIHNraXAgb3B0aW9uIGNoZWNrLCBlbWl0IGV2ZW50IGZvciBwb3NzaWJsZSBtaXNzcGVsbGluZyBzdWdnZXN0aW9uXG4gICAgICAgIHRoaXMuZW1pdCgnY29tbWFuZDoqJywgb3BlcmFuZHMsIHVua25vd24pO1xuICAgICAgfSBlbHNlIGlmICh0aGlzLmNvbW1hbmRzLmxlbmd0aCkge1xuICAgICAgICB0aGlzLnVua25vd25Db21tYW5kKCk7XG4gICAgICB9IGVsc2Uge1xuICAgICAgICBjaGVja0ZvclVua25vd25PcHRpb25zKCk7XG4gICAgICAgIHRoaXMuX3Byb2Nlc3NBcmd1bWVudHMoKTtcbiAgICAgIH1cbiAgICB9IGVsc2UgaWYgKHRoaXMuY29tbWFuZHMubGVuZ3RoKSB7XG4gICAgICBjaGVja0ZvclVua25vd25PcHRpb25zKCk7XG4gICAgICAvLyBUaGlzIGNvbW1hbmQgaGFzIHN1YmNvbW1hbmRzIGFuZCBub3RoaW5nIGhvb2tlZCB1cCBhdCB0aGlzIGxldmVsLCBzbyBkaXNwbGF5IGhlbHAgKGFuZCBleGl0KS5cbiAgICAgIHRoaXMuaGVscCh7IGVycm9yOiB0cnVlIH0pO1xuICAgIH0gZWxzZSB7XG4gICAgICBjaGVja0ZvclVua25vd25PcHRpb25zKCk7XG4gICAgICB0aGlzLl9wcm9jZXNzQXJndW1lbnRzKCk7XG4gICAgICAvLyBmYWxsIHRocm91Z2ggZm9yIGNhbGxlciB0byBoYW5kbGUgYWZ0ZXIgY2FsbGluZyAucGFyc2UoKVxuICAgIH1cbiAgfVxuXG4gIC8qKlxuICAgKiBGaW5kIG1hdGNoaW5nIGNvbW1hbmQuXG4gICAqXG4gICAqIEBhcGkgcHJpdmF0ZVxuICAgKi9cbiAgX2ZpbmRDb21tYW5kKG5hbWUpIHtcbiAgICBpZiAoIW5hbWUpIHJldHVybiB1bmRlZmluZWQ7XG4gICAgcmV0dXJuIHRoaXMuY29tbWFuZHMuZmluZChjbWQgPT4gY21kLl9uYW1lID09PSBuYW1lIHx8IGNtZC5fYWxpYXNlcy5pbmNsdWRlcyhuYW1lKSk7XG4gIH1cblxuICAvKipcbiAgICogUmV0dXJuIGFuIG9wdGlvbiBtYXRjaGluZyBgYXJnYCBpZiBhbnkuXG4gICAqXG4gICAqIEBwYXJhbSB7c3RyaW5nfSBhcmdcbiAgICogQHJldHVybiB7T3B0aW9ufVxuICAgKiBAYXBpIHByaXZhdGVcbiAgICovXG5cbiAgX2ZpbmRPcHRpb24oYXJnKSB7XG4gICAgcmV0dXJuIHRoaXMub3B0aW9ucy5maW5kKG9wdGlvbiA9PiBvcHRpb24uaXMoYXJnKSk7XG4gIH1cblxuICAvKipcbiAgICogRGlzcGxheSBhbiBlcnJvciBtZXNzYWdlIGlmIGEgbWFuZGF0b3J5IG9wdGlvbiBkb2VzIG5vdCBoYXZlIGEgdmFsdWUuXG4gICAqIENhbGxlZCBhZnRlciBjaGVja2luZyBmb3IgaGVscCBmbGFncyBpbiBsZWFmIHN1YmNvbW1hbmQuXG4gICAqXG4gICAqIEBhcGkgcHJpdmF0ZVxuICAgKi9cblxuICBfY2hlY2tGb3JNaXNzaW5nTWFuZGF0b3J5T3B0aW9ucygpIHtcbiAgICAvLyBXYWxrIHVwIGhpZXJhcmNoeSBzbyBjYW4gY2FsbCBpbiBzdWJjb21tYW5kIGFmdGVyIGNoZWNraW5nIGZvciBkaXNwbGF5aW5nIGhlbHAuXG4gICAgZm9yIChsZXQgY21kID0gdGhpczsgY21kOyBjbWQgPSBjbWQucGFyZW50KSB7XG4gICAgICBjbWQub3B0aW9ucy5mb3JFYWNoKChhbk9wdGlvbikgPT4ge1xuICAgICAgICBpZiAoYW5PcHRpb24ubWFuZGF0b3J5ICYmIChjbWQuZ2V0T3B0aW9uVmFsdWUoYW5PcHRpb24uYXR0cmlidXRlTmFtZSgpKSA9PT0gdW5kZWZpbmVkKSkge1xuICAgICAgICAgIGNtZC5taXNzaW5nTWFuZGF0b3J5T3B0aW9uVmFsdWUoYW5PcHRpb24pO1xuICAgICAgICB9XG4gICAgICB9KTtcbiAgICB9XG4gIH1cblxuICAvKipcbiAgICogRGlzcGxheSBhbiBlcnJvciBtZXNzYWdlIGlmIGNvbmZsaWN0aW5nIG9wdGlvbnMgYXJlIHVzZWQgdG9nZXRoZXIgaW4gdGhpcy5cbiAgICpcbiAgICogQGFwaSBwcml2YXRlXG4gICAqL1xuICBfY2hlY2tGb3JDb25mbGljdGluZ0xvY2FsT3B0aW9ucygpIHtcbiAgICBjb25zdCBkZWZpbmVkTm9uRGVmYXVsdE9wdGlvbnMgPSB0aGlzLm9wdGlvbnMuZmlsdGVyKFxuICAgICAgKG9wdGlvbikgPT4ge1xuICAgICAgICBjb25zdCBvcHRpb25LZXkgPSBvcHRpb24uYXR0cmlidXRlTmFtZSgpO1xuICAgICAgICBpZiAodGhpcy5nZXRPcHRpb25WYWx1ZShvcHRpb25LZXkpID09PSB1bmRlZmluZWQpIHtcbiAgICAgICAgICByZXR1cm4gZmFsc2U7XG4gICAgICAgIH1cbiAgICAgICAgcmV0dXJuIHRoaXMuZ2V0T3B0aW9uVmFsdWVTb3VyY2Uob3B0aW9uS2V5KSAhPT0gJ2RlZmF1bHQnO1xuICAgICAgfVxuICAgICk7XG5cbiAgICBjb25zdCBvcHRpb25zV2l0aENvbmZsaWN0aW5nID0gZGVmaW5lZE5vbkRlZmF1bHRPcHRpb25zLmZpbHRlcihcbiAgICAgIChvcHRpb24pID0+IG9wdGlvbi5jb25mbGljdHNXaXRoLmxlbmd0aCA+IDBcbiAgICApO1xuXG4gICAgb3B0aW9uc1dpdGhDb25mbGljdGluZy5mb3JFYWNoKChvcHRpb24pID0+IHtcbiAgICAgIGNvbnN0IGNvbmZsaWN0aW5nQW5kRGVmaW5lZCA9IGRlZmluZWROb25EZWZhdWx0T3B0aW9ucy5maW5kKChkZWZpbmVkKSA9PlxuICAgICAgICBvcHRpb24uY29uZmxpY3RzV2l0aC5pbmNsdWRlcyhkZWZpbmVkLmF0dHJpYnV0ZU5hbWUoKSlcbiAgICAgICk7XG4gICAgICBpZiAoY29uZmxpY3RpbmdBbmREZWZpbmVkKSB7XG4gICAgICAgIHRoaXMuX2NvbmZsaWN0aW5nT3B0aW9uKG9wdGlvbiwgY29uZmxpY3RpbmdBbmREZWZpbmVkKTtcbiAgICAgIH1cbiAgICB9KTtcbiAgfVxuXG4gIC8qKlxuICAgKiBEaXNwbGF5IGFuIGVycm9yIG1lc3NhZ2UgaWYgY29uZmxpY3Rpbmcgb3B0aW9ucyBhcmUgdXNlZCB0b2dldGhlci5cbiAgICogQ2FsbGVkIGFmdGVyIGNoZWNraW5nIGZvciBoZWxwIGZsYWdzIGluIGxlYWYgc3ViY29tbWFuZC5cbiAgICpcbiAgICogQGFwaSBwcml2YXRlXG4gICAqL1xuICBfY2hlY2tGb3JDb25mbGljdGluZ09wdGlvbnMoKSB7XG4gICAgLy8gV2FsayB1cCBoaWVyYXJjaHkgc28gY2FuIGNhbGwgaW4gc3ViY29tbWFuZCBhZnRlciBjaGVja2luZyBmb3IgZGlzcGxheWluZyBoZWxwLlxuICAgIGZvciAobGV0IGNtZCA9IHRoaXM7IGNtZDsgY21kID0gY21kLnBhcmVudCkge1xuICAgICAgY21kLl9jaGVja0ZvckNvbmZsaWN0aW5nTG9jYWxPcHRpb25zKCk7XG4gICAgfVxuICB9XG5cbiAgLyoqXG4gICAqIFBhcnNlIG9wdGlvbnMgZnJvbSBgYXJndmAgcmVtb3Zpbmcga25vd24gb3B0aW9ucyxcbiAgICogYW5kIHJldHVybiBhcmd2IHNwbGl0IGludG8gb3BlcmFuZHMgYW5kIHVua25vd24gYXJndW1lbnRzLlxuICAgKlxuICAgKiBFeGFtcGxlczpcbiAgICpcbiAgICogICAgIGFyZ3YgPT4gb3BlcmFuZHMsIHVua25vd25cbiAgICogICAgIC0ta25vd24ga2trIG9wID0+IFtvcF0sIFtdXG4gICAqICAgICBvcCAtLWtub3duIGtrayA9PiBbb3BdLCBbXVxuICAgKiAgICAgc3ViIC0tdW5rbm93biB1dXUgb3AgPT4gW3N1Yl0sIFstLXVua25vd24gdXV1IG9wXVxuICAgKiAgICAgc3ViIC0tIC0tdW5rbm93biB1dXUgb3AgPT4gW3N1YiAtLXVua25vd24gdXV1IG9wXSwgW11cbiAgICpcbiAgICogQHBhcmFtIHtTdHJpbmdbXX0gYXJndlxuICAgKiBAcmV0dXJuIHt7b3BlcmFuZHM6IFN0cmluZ1tdLCB1bmtub3duOiBTdHJpbmdbXX19XG4gICAqL1xuXG4gIHBhcnNlT3B0aW9ucyhhcmd2KSB7XG4gICAgY29uc3Qgb3BlcmFuZHMgPSBbXTsgLy8gb3BlcmFuZHMsIG5vdCBvcHRpb25zIG9yIHZhbHVlc1xuICAgIGNvbnN0IHVua25vd24gPSBbXTsgLy8gZmlyc3QgdW5rbm93biBvcHRpb24gYW5kIHJlbWFpbmluZyB1bmtub3duIGFyZ3NcbiAgICBsZXQgZGVzdCA9IG9wZXJhbmRzO1xuICAgIGNvbnN0IGFyZ3MgPSBhcmd2LnNsaWNlKCk7XG5cbiAgICBmdW5jdGlvbiBtYXliZU9wdGlvbihhcmcpIHtcbiAgICAgIHJldHVybiBhcmcubGVuZ3RoID4gMSAmJiBhcmdbMF0gPT09ICctJztcbiAgICB9XG5cbiAgICAvLyBwYXJzZSBvcHRpb25zXG4gICAgbGV0IGFjdGl2ZVZhcmlhZGljT3B0aW9uID0gbnVsbDtcbiAgICB3aGlsZSAoYXJncy5sZW5ndGgpIHtcbiAgICAgIGNvbnN0IGFyZyA9IGFyZ3Muc2hpZnQoKTtcblxuICAgICAgLy8gbGl0ZXJhbFxuICAgICAgaWYgKGFyZyA9PT0gJy0tJykge1xuICAgICAgICBpZiAoZGVzdCA9PT0gdW5rbm93bikgZGVzdC5wdXNoKGFyZyk7XG4gICAgICAgIGRlc3QucHVzaCguLi5hcmdzKTtcbiAgICAgICAgYnJlYWs7XG4gICAgICB9XG5cbiAgICAgIGlmIChhY3RpdmVWYXJpYWRpY09wdGlvbiAmJiAhbWF5YmVPcHRpb24oYXJnKSkge1xuICAgICAgICB0aGlzLmVtaXQoYG9wdGlvbjoke2FjdGl2ZVZhcmlhZGljT3B0aW9uLm5hbWUoKX1gLCBhcmcpO1xuICAgICAgICBjb250aW51ZTtcbiAgICAgIH1cbiAgICAgIGFjdGl2ZVZhcmlhZGljT3B0aW9uID0gbnVsbDtcblxuICAgICAgaWYgKG1heWJlT3B0aW9uKGFyZykpIHtcbiAgICAgICAgY29uc3Qgb3B0aW9uID0gdGhpcy5fZmluZE9wdGlvbihhcmcpO1xuICAgICAgICAvLyByZWNvZ25pc2VkIG9wdGlvbiwgY2FsbCBsaXN0ZW5lciB0byBhc3NpZ24gdmFsdWUgd2l0aCBwb3NzaWJsZSBjdXN0b20gcHJvY2Vzc2luZ1xuICAgICAgICBpZiAob3B0aW9uKSB7XG4gICAgICAgICAgaWYgKG9wdGlvbi5yZXF1aXJlZCkge1xuICAgICAgICAgICAgY29uc3QgdmFsdWUgPSBhcmdzLnNoaWZ0KCk7XG4gICAgICAgICAgICBpZiAodmFsdWUgPT09IHVuZGVmaW5lZCkgdGhpcy5vcHRpb25NaXNzaW5nQXJndW1lbnQob3B0aW9uKTtcbiAgICAgICAgICAgIHRoaXMuZW1pdChgb3B0aW9uOiR7b3B0aW9uLm5hbWUoKX1gLCB2YWx1ZSk7XG4gICAgICAgICAgfSBlbHNlIGlmIChvcHRpb24ub3B0aW9uYWwpIHtcbiAgICAgICAgICAgIGxldCB2YWx1ZSA9IG51bGw7XG4gICAgICAgICAgICAvLyBoaXN0b3JpY2FsIGJlaGF2aW91ciBpcyBvcHRpb25hbCB2YWx1ZSBpcyBmb2xsb3dpbmcgYXJnIHVubGVzcyBhbiBvcHRpb25cbiAgICAgICAgICAgIGlmIChhcmdzLmxlbmd0aCA+IDAgJiYgIW1heWJlT3B0aW9uKGFyZ3NbMF0pKSB7XG4gICAgICAgICAgICAgIHZhbHVlID0gYXJncy5zaGlmdCgpO1xuICAgICAgICAgICAgfVxuICAgICAgICAgICAgdGhpcy5lbWl0KGBvcHRpb246JHtvcHRpb24ubmFtZSgpfWAsIHZhbHVlKTtcbiAgICAgICAgICB9IGVsc2UgeyAvLyBib29sZWFuIGZsYWdcbiAgICAgICAgICAgIHRoaXMuZW1pdChgb3B0aW9uOiR7b3B0aW9uLm5hbWUoKX1gKTtcbiAgICAgICAgICB9XG4gICAgICAgICAgYWN0aXZlVmFyaWFkaWNPcHRpb24gPSBvcHRpb24udmFyaWFkaWMgPyBvcHRpb24gOiBudWxsO1xuICAgICAgICAgIGNvbnRpbnVlO1xuICAgICAgICB9XG4gICAgICB9XG5cbiAgICAgIC8vIExvb2sgZm9yIGNvbWJvIG9wdGlvbnMgZm9sbG93aW5nIHNpbmdsZSBkYXNoLCBlYXQgZmlyc3Qgb25lIGlmIGtub3duLlxuICAgICAgaWYgKGFyZy5sZW5ndGggPiAyICYmIGFyZ1swXSA9PT0gJy0nICYmIGFyZ1sxXSAhPT0gJy0nKSB7XG4gICAgICAgIGNvbnN0IG9wdGlvbiA9IHRoaXMuX2ZpbmRPcHRpb24oYC0ke2FyZ1sxXX1gKTtcbiAgICAgICAgaWYgKG9wdGlvbikge1xuICAgICAgICAgIGlmIChvcHRpb24ucmVxdWlyZWQgfHwgKG9wdGlvbi5vcHRpb25hbCAmJiB0aGlzLl9jb21iaW5lRmxhZ0FuZE9wdGlvbmFsVmFsdWUpKSB7XG4gICAgICAgICAgICAvLyBvcHRpb24gd2l0aCB2YWx1ZSBmb2xsb3dpbmcgaW4gc2FtZSBhcmd1bWVudFxuICAgICAgICAgICAgdGhpcy5lbWl0KGBvcHRpb246JHtvcHRpb24ubmFtZSgpfWAsIGFyZy5zbGljZSgyKSk7XG4gICAgICAgICAgfSBlbHNlIHtcbiAgICAgICAgICAgIC8vIGJvb2xlYW4gb3B0aW9uLCBlbWl0IGFuZCBwdXQgYmFjayByZW1haW5kZXIgb2YgYXJnIGZvciBmdXJ0aGVyIHByb2Nlc3NpbmdcbiAgICAgICAgICAgIHRoaXMuZW1pdChgb3B0aW9uOiR7b3B0aW9uLm5hbWUoKX1gKTtcbiAgICAgICAgICAgIGFyZ3MudW5zaGlmdChgLSR7YXJnLnNsaWNlKDIpfWApO1xuICAgICAgICAgIH1cbiAgICAgICAgICBjb250aW51ZTtcbiAgICAgICAgfVxuICAgICAgfVxuXG4gICAgICAvLyBMb29rIGZvciBrbm93biBsb25nIGZsYWcgd2l0aCB2YWx1ZSwgbGlrZSAtLWZvbz1iYXJcbiAgICAgIGlmICgvXi0tW149XSs9Ly50ZXN0KGFyZykpIHtcbiAgICAgICAgY29uc3QgaW5kZXggPSBhcmcuaW5kZXhPZignPScpO1xuICAgICAgICBjb25zdCBvcHRpb24gPSB0aGlzLl9maW5kT3B0aW9uKGFyZy5zbGljZSgwLCBpbmRleCkpO1xuICAgICAgICBpZiAob3B0aW9uICYmIChvcHRpb24ucmVxdWlyZWQgfHwgb3B0aW9uLm9wdGlvbmFsKSkge1xuICAgICAgICAgIHRoaXMuZW1pdChgb3B0aW9uOiR7b3B0aW9uLm5hbWUoKX1gLCBhcmcuc2xpY2UoaW5kZXggKyAxKSk7XG4gICAgICAgICAgY29udGludWU7XG4gICAgICAgIH1cbiAgICAgIH1cblxuICAgICAgLy8gTm90IGEgcmVjb2duaXNlZCBvcHRpb24gYnkgdGhpcyBjb21tYW5kLlxuICAgICAgLy8gTWlnaHQgYmUgYSBjb21tYW5kLWFyZ3VtZW50LCBvciBzdWJjb21tYW5kIG9wdGlvbiwgb3IgdW5rbm93biBvcHRpb24sIG9yIGhlbHAgY29tbWFuZCBvciBvcHRpb24uXG5cbiAgICAgIC8vIEFuIHVua25vd24gb3B0aW9uIG1lYW5zIGZ1cnRoZXIgYXJndW1lbnRzIGFsc28gY2xhc3NpZmllZCBhcyB1bmtub3duIHNvIGNhbiBiZSByZXByb2Nlc3NlZCBieSBzdWJjb21tYW5kcy5cbiAgICAgIGlmIChtYXliZU9wdGlvbihhcmcpKSB7XG4gICAgICAgIGRlc3QgPSB1bmtub3duO1xuICAgICAgfVxuXG4gICAgICAvLyBJZiB1c2luZyBwb3NpdGlvbmFsT3B0aW9ucywgc3RvcCBwcm9jZXNzaW5nIG91ciBvcHRpb25zIGF0IHN1YmNvbW1hbmQuXG4gICAgICBpZiAoKHRoaXMuX2VuYWJsZVBvc2l0aW9uYWxPcHRpb25zIHx8IHRoaXMuX3Bhc3NUaHJvdWdoT3B0aW9ucykgJiYgb3BlcmFuZHMubGVuZ3RoID09PSAwICYmIHVua25vd24ubGVuZ3RoID09PSAwKSB7XG4gICAgICAgIGlmICh0aGlzLl9maW5kQ29tbWFuZChhcmcpKSB7XG4gICAgICAgICAgb3BlcmFuZHMucHVzaChhcmcpO1xuICAgICAgICAgIGlmIChhcmdzLmxlbmd0aCA+IDApIHVua25vd24ucHVzaCguLi5hcmdzKTtcbiAgICAgICAgICBicmVhaztcbiAgICAgICAgfSBlbHNlIGlmIChhcmcgPT09IHRoaXMuX2hlbHBDb21tYW5kTmFtZSAmJiB0aGlzLl9oYXNJbXBsaWNpdEhlbHBDb21tYW5kKCkpIHtcbiAgICAgICAgICBvcGVyYW5kcy5wdXNoKGFyZyk7XG4gICAgICAgICAgaWYgKGFyZ3MubGVuZ3RoID4gMCkgb3BlcmFuZHMucHVzaCguLi5hcmdzKTtcbiAgICAgICAgICBicmVhaztcbiAgICAgICAgfSBlbHNlIGlmICh0aGlzLl9kZWZhdWx0Q29tbWFuZE5hbWUpIHtcbiAgICAgICAgICB1bmtub3duLnB1c2goYXJnKTtcbiAgICAgICAgICBpZiAoYXJncy5sZW5ndGggPiAwKSB1bmtub3duLnB1c2goLi4uYXJncyk7XG4gICAgICAgICAgYnJlYWs7XG4gICAgICAgIH1cbiAgICAgIH1cblxuICAgICAgLy8gSWYgdXNpbmcgcGFzc1Rocm91Z2hPcHRpb25zLCBzdG9wIHByb2Nlc3Npbmcgb3B0aW9ucyBhdCBmaXJzdCBjb21tYW5kLWFyZ3VtZW50LlxuICAgICAgaWYgKHRoaXMuX3Bhc3NUaHJvdWdoT3B0aW9ucykge1xuICAgICAgICBkZXN0LnB1c2goYXJnKTtcbiAgICAgICAgaWYgKGFyZ3MubGVuZ3RoID4gMCkgZGVzdC5wdXNoKC4uLmFyZ3MpO1xuICAgICAgICBicmVhaztcbiAgICAgIH1cblxuICAgICAgLy8gYWRkIGFyZ1xuICAgICAgZGVzdC5wdXNoKGFyZyk7XG4gICAgfVxuXG4gICAgcmV0dXJuIHsgb3BlcmFuZHMsIHVua25vd24gfTtcbiAgfVxuXG4gIC8qKlxuICAgKiBSZXR1cm4gYW4gb2JqZWN0IGNvbnRhaW5pbmcgbG9jYWwgb3B0aW9uIHZhbHVlcyBhcyBrZXktdmFsdWUgcGFpcnMuXG4gICAqXG4gICAqIEByZXR1cm4ge09iamVjdH1cbiAgICovXG4gIG9wdHMoKSB7XG4gICAgaWYgKHRoaXMuX3N0b3JlT3B0aW9uc0FzUHJvcGVydGllcykge1xuICAgICAgLy8gUHJlc2VydmUgb3JpZ2luYWwgYmVoYXZpb3VyIHNvIGJhY2t3YXJkcyBjb21wYXRpYmxlIHdoZW4gc3RpbGwgdXNpbmcgcHJvcGVydGllc1xuICAgICAgY29uc3QgcmVzdWx0ID0ge307XG4gICAgICBjb25zdCBsZW4gPSB0aGlzLm9wdGlvbnMubGVuZ3RoO1xuXG4gICAgICBmb3IgKGxldCBpID0gMDsgaSA8IGxlbjsgaSsrKSB7XG4gICAgICAgIGNvbnN0IGtleSA9IHRoaXMub3B0aW9uc1tpXS5hdHRyaWJ1dGVOYW1lKCk7XG4gICAgICAgIHJlc3VsdFtrZXldID0ga2V5ID09PSB0aGlzLl92ZXJzaW9uT3B0aW9uTmFtZSA/IHRoaXMuX3ZlcnNpb24gOiB0aGlzW2tleV07XG4gICAgICB9XG4gICAgICByZXR1cm4gcmVzdWx0O1xuICAgIH1cblxuICAgIHJldHVybiB0aGlzLl9vcHRpb25WYWx1ZXM7XG4gIH1cblxuICAvKipcbiAgICogUmV0dXJuIGFuIG9iamVjdCBjb250YWluaW5nIG1lcmdlZCBsb2NhbCBhbmQgZ2xvYmFsIG9wdGlvbiB2YWx1ZXMgYXMga2V5LXZhbHVlIHBhaXJzLlxuICAgKlxuICAgKiBAcmV0dXJuIHtPYmplY3R9XG4gICAqL1xuICBvcHRzV2l0aEdsb2JhbHMoKSB7XG4gICAgLy8gZ2xvYmFscyBvdmVyd3JpdGUgbG9jYWxzXG4gICAgcmV0dXJuIGdldENvbW1hbmRBbmRQYXJlbnRzKHRoaXMpLnJlZHVjZShcbiAgICAgIChjb21iaW5lZE9wdGlvbnMsIGNtZCkgPT4gT2JqZWN0LmFzc2lnbihjb21iaW5lZE9wdGlvbnMsIGNtZC5vcHRzKCkpLFxuICAgICAge31cbiAgICApO1xuICB9XG5cbiAgLyoqXG4gICAqIERpc3BsYXkgZXJyb3IgbWVzc2FnZSBhbmQgZXhpdCAob3IgY2FsbCBleGl0T3ZlcnJpZGUpLlxuICAgKlxuICAgKiBAcGFyYW0ge3N0cmluZ30gbWVzc2FnZVxuICAgKiBAcGFyYW0ge09iamVjdH0gW2Vycm9yT3B0aW9uc11cbiAgICogQHBhcmFtIHtzdHJpbmd9IFtlcnJvck9wdGlvbnMuY29kZV0gLSBhbiBpZCBzdHJpbmcgcmVwcmVzZW50aW5nIHRoZSBlcnJvclxuICAgKiBAcGFyYW0ge251bWJlcn0gW2Vycm9yT3B0aW9ucy5leGl0Q29kZV0gLSB1c2VkIHdpdGggcHJvY2Vzcy5leGl0XG4gICAqL1xuICBlcnJvcihtZXNzYWdlLCBlcnJvck9wdGlvbnMpIHtcbiAgICAvLyBvdXRwdXQgaGFuZGxpbmdcbiAgICB0aGlzLl9vdXRwdXRDb25maWd1cmF0aW9uLm91dHB1dEVycm9yKGAke21lc3NhZ2V9XFxuYCwgdGhpcy5fb3V0cHV0Q29uZmlndXJhdGlvbi53cml0ZUVycik7XG4gICAgaWYgKHR5cGVvZiB0aGlzLl9zaG93SGVscEFmdGVyRXJyb3IgPT09ICdzdHJpbmcnKSB7XG4gICAgICB0aGlzLl9vdXRwdXRDb25maWd1cmF0aW9uLndyaXRlRXJyKGAke3RoaXMuX3Nob3dIZWxwQWZ0ZXJFcnJvcn1cXG5gKTtcbiAgICB9IGVsc2UgaWYgKHRoaXMuX3Nob3dIZWxwQWZ0ZXJFcnJvcikge1xuICAgICAgdGhpcy5fb3V0cHV0Q29uZmlndXJhdGlvbi53cml0ZUVycignXFxuJyk7XG4gICAgICB0aGlzLm91dHB1dEhlbHAoeyBlcnJvcjogdHJ1ZSB9KTtcbiAgICB9XG5cbiAgICAvLyBleGl0IGhhbmRsaW5nXG4gICAgY29uc3QgY29uZmlnID0gZXJyb3JPcHRpb25zIHx8IHt9O1xuICAgIGNvbnN0IGV4aXRDb2RlID0gY29uZmlnLmV4aXRDb2RlIHx8IDE7XG4gICAgY29uc3QgY29kZSA9IGNvbmZpZy5jb2RlIHx8ICdjb21tYW5kZXIuZXJyb3InO1xuICAgIHRoaXMuX2V4aXQoZXhpdENvZGUsIGNvZGUsIG1lc3NhZ2UpO1xuICB9XG5cbiAgLyoqXG4gICAqIEFwcGx5IGFueSBvcHRpb24gcmVsYXRlZCBlbnZpcm9ubWVudCB2YXJpYWJsZXMsIGlmIG9wdGlvbiBkb2VzXG4gICAqIG5vdCBoYXZlIGEgdmFsdWUgZnJvbSBjbGkgb3IgY2xpZW50IGNvZGUuXG4gICAqXG4gICAqIEBhcGkgcHJpdmF0ZVxuICAgKi9cbiAgX3BhcnNlT3B0aW9uc0VudigpIHtcbiAgICB0aGlzLm9wdGlvbnMuZm9yRWFjaCgob3B0aW9uKSA9PiB7XG4gICAgICBpZiAob3B0aW9uLmVudlZhciAmJiBvcHRpb24uZW52VmFyIGluIHByb2Nlc3MuZW52KSB7XG4gICAgICAgIGNvbnN0IG9wdGlvbktleSA9IG9wdGlvbi5hdHRyaWJ1dGVOYW1lKCk7XG4gICAgICAgIC8vIFByaW9yaXR5IGNoZWNrLiBEbyBub3Qgb3ZlcndyaXRlIGNsaSBvciBvcHRpb25zIGZyb20gdW5rbm93biBzb3VyY2UgKGNsaWVudC1jb2RlKS5cbiAgICAgICAgaWYgKHRoaXMuZ2V0T3B0aW9uVmFsdWUob3B0aW9uS2V5KSA9PT0gdW5kZWZpbmVkIHx8IFsnZGVmYXVsdCcsICdjb25maWcnLCAnZW52J10uaW5jbHVkZXModGhpcy5nZXRPcHRpb25WYWx1ZVNvdXJjZShvcHRpb25LZXkpKSkge1xuICAgICAgICAgIGlmIChvcHRpb24ucmVxdWlyZWQgfHwgb3B0aW9uLm9wdGlvbmFsKSB7IC8vIG9wdGlvbiBjYW4gdGFrZSBhIHZhbHVlXG4gICAgICAgICAgICAvLyBrZWVwIHZlcnkgc2ltcGxlLCBvcHRpb25hbCBhbHdheXMgdGFrZXMgdmFsdWVcbiAgICAgICAgICAgIHRoaXMuZW1pdChgb3B0aW9uRW52OiR7b3B0aW9uLm5hbWUoKX1gLCBwcm9jZXNzLmVudltvcHRpb24uZW52VmFyXSk7XG4gICAgICAgICAgfSBlbHNlIHsgLy8gYm9vbGVhblxuICAgICAgICAgICAgLy8ga2VlcCB2ZXJ5IHNpbXBsZSwgb25seSBjYXJlIHRoYXQgZW52VmFyIGRlZmluZWQgYW5kIG5vdCB0aGUgdmFsdWVcbiAgICAgICAgICAgIHRoaXMuZW1pdChgb3B0aW9uRW52OiR7b3B0aW9uLm5hbWUoKX1gKTtcbiAgICAgICAgICB9XG4gICAgICAgIH1cbiAgICAgIH1cbiAgICB9KTtcbiAgfVxuXG4gIC8qKlxuICAgKiBBcHBseSBhbnkgaW1wbGllZCBvcHRpb24gdmFsdWVzLCBpZiBvcHRpb24gaXMgdW5kZWZpbmVkIG9yIGRlZmF1bHQgdmFsdWUuXG4gICAqXG4gICAqIEBhcGkgcHJpdmF0ZVxuICAgKi9cbiAgX3BhcnNlT3B0aW9uc0ltcGxpZWQoKSB7XG4gICAgY29uc3QgZHVhbEhlbHBlciA9IG5ldyBEdWFsT3B0aW9ucyh0aGlzLm9wdGlvbnMpO1xuICAgIGNvbnN0IGhhc0N1c3RvbU9wdGlvblZhbHVlID0gKG9wdGlvbktleSkgPT4ge1xuICAgICAgcmV0dXJuIHRoaXMuZ2V0T3B0aW9uVmFsdWUob3B0aW9uS2V5KSAhPT0gdW5kZWZpbmVkICYmICFbJ2RlZmF1bHQnLCAnaW1wbGllZCddLmluY2x1ZGVzKHRoaXMuZ2V0T3B0aW9uVmFsdWVTb3VyY2Uob3B0aW9uS2V5KSk7XG4gICAgfTtcbiAgICB0aGlzLm9wdGlvbnNcbiAgICAgIC5maWx0ZXIob3B0aW9uID0+IChvcHRpb24uaW1wbGllZCAhPT0gdW5kZWZpbmVkKSAmJlxuICAgICAgICBoYXNDdXN0b21PcHRpb25WYWx1ZShvcHRpb24uYXR0cmlidXRlTmFtZSgpKSAmJlxuICAgICAgICBkdWFsSGVscGVyLnZhbHVlRnJvbU9wdGlvbih0aGlzLmdldE9wdGlvblZhbHVlKG9wdGlvbi5hdHRyaWJ1dGVOYW1lKCkpLCBvcHRpb24pKVxuICAgICAgLmZvckVhY2goKG9wdGlvbikgPT4ge1xuICAgICAgICBPYmplY3Qua2V5cyhvcHRpb24uaW1wbGllZClcbiAgICAgICAgICAuZmlsdGVyKGltcGxpZWRLZXkgPT4gIWhhc0N1c3RvbU9wdGlvblZhbHVlKGltcGxpZWRLZXkpKVxuICAgICAgICAgIC5mb3JFYWNoKGltcGxpZWRLZXkgPT4ge1xuICAgICAgICAgICAgdGhpcy5zZXRPcHRpb25WYWx1ZVdpdGhTb3VyY2UoaW1wbGllZEtleSwgb3B0aW9uLmltcGxpZWRbaW1wbGllZEtleV0sICdpbXBsaWVkJyk7XG4gICAgICAgICAgfSk7XG4gICAgICB9KTtcbiAgfVxuXG4gIC8qKlxuICAgKiBBcmd1bWVudCBgbmFtZWAgaXMgbWlzc2luZy5cbiAgICpcbiAgICogQHBhcmFtIHtzdHJpbmd9IG5hbWVcbiAgICogQGFwaSBwcml2YXRlXG4gICAqL1xuXG4gIG1pc3NpbmdBcmd1bWVudChuYW1lKSB7XG4gICAgY29uc3QgbWVzc2FnZSA9IGBlcnJvcjogbWlzc2luZyByZXF1aXJlZCBhcmd1bWVudCAnJHtuYW1lfSdgO1xuICAgIHRoaXMuZXJyb3IobWVzc2FnZSwgeyBjb2RlOiAnY29tbWFuZGVyLm1pc3NpbmdBcmd1bWVudCcgfSk7XG4gIH1cblxuICAvKipcbiAgICogYE9wdGlvbmAgaXMgbWlzc2luZyBhbiBhcmd1bWVudC5cbiAgICpcbiAgICogQHBhcmFtIHtPcHRpb259IG9wdGlvblxuICAgKiBAYXBpIHByaXZhdGVcbiAgICovXG5cbiAgb3B0aW9uTWlzc2luZ0FyZ3VtZW50KG9wdGlvbikge1xuICAgIGNvbnN0IG1lc3NhZ2UgPSBgZXJyb3I6IG9wdGlvbiAnJHtvcHRpb24uZmxhZ3N9JyBhcmd1bWVudCBtaXNzaW5nYDtcbiAgICB0aGlzLmVycm9yKG1lc3NhZ2UsIHsgY29kZTogJ2NvbW1hbmRlci5vcHRpb25NaXNzaW5nQXJndW1lbnQnIH0pO1xuICB9XG5cbiAgLyoqXG4gICAqIGBPcHRpb25gIGRvZXMgbm90IGhhdmUgYSB2YWx1ZSwgYW5kIGlzIGEgbWFuZGF0b3J5IG9wdGlvbi5cbiAgICpcbiAgICogQHBhcmFtIHtPcHRpb259IG9wdGlvblxuICAgKiBAYXBpIHByaXZhdGVcbiAgICovXG5cbiAgbWlzc2luZ01hbmRhdG9yeU9wdGlvblZhbHVlKG9wdGlvbikge1xuICAgIGNvbnN0IG1lc3NhZ2UgPSBgZXJyb3I6IHJlcXVpcmVkIG9wdGlvbiAnJHtvcHRpb24uZmxhZ3N9JyBub3Qgc3BlY2lmaWVkYDtcbiAgICB0aGlzLmVycm9yKG1lc3NhZ2UsIHsgY29kZTogJ2NvbW1hbmRlci5taXNzaW5nTWFuZGF0b3J5T3B0aW9uVmFsdWUnIH0pO1xuICB9XG5cbiAgLyoqXG4gICAqIGBPcHRpb25gIGNvbmZsaWN0cyB3aXRoIGFub3RoZXIgb3B0aW9uLlxuICAgKlxuICAgKiBAcGFyYW0ge09wdGlvbn0gb3B0aW9uXG4gICAqIEBwYXJhbSB7T3B0aW9ufSBjb25mbGljdGluZ09wdGlvblxuICAgKiBAYXBpIHByaXZhdGVcbiAgICovXG4gIF9jb25mbGljdGluZ09wdGlvbihvcHRpb24sIGNvbmZsaWN0aW5nT3B0aW9uKSB7XG4gICAgLy8gVGhlIGNhbGxpbmcgY29kZSBkb2VzIG5vdCBrbm93IHdoZXRoZXIgYSBuZWdhdGVkIG9wdGlvbiBpcyB0aGUgc291cmNlIG9mIHRoZVxuICAgIC8vIHZhbHVlLCBzbyBkbyBzb21lIHdvcmsgdG8gdGFrZSBhbiBlZHVjYXRlZCBndWVzcy5cbiAgICBjb25zdCBmaW5kQmVzdE9wdGlvbkZyb21WYWx1ZSA9IChvcHRpb24pID0+IHtcbiAgICAgIGNvbnN0IG9wdGlvbktleSA9IG9wdGlvbi5hdHRyaWJ1dGVOYW1lKCk7XG4gICAgICBjb25zdCBvcHRpb25WYWx1ZSA9IHRoaXMuZ2V0T3B0aW9uVmFsdWUob3B0aW9uS2V5KTtcbiAgICAgIGNvbnN0IG5lZ2F0aXZlT3B0aW9uID0gdGhpcy5vcHRpb25zLmZpbmQodGFyZ2V0ID0+IHRhcmdldC5uZWdhdGUgJiYgb3B0aW9uS2V5ID09PSB0YXJnZXQuYXR0cmlidXRlTmFtZSgpKTtcbiAgICAgIGNvbnN0IHBvc2l0aXZlT3B0aW9uID0gdGhpcy5vcHRpb25zLmZpbmQodGFyZ2V0ID0+ICF0YXJnZXQubmVnYXRlICYmIG9wdGlvbktleSA9PT0gdGFyZ2V0LmF0dHJpYnV0ZU5hbWUoKSk7XG4gICAgICBpZiAobmVnYXRpdmVPcHRpb24gJiYgKFxuICAgICAgICAobmVnYXRpdmVPcHRpb24ucHJlc2V0QXJnID09PSB1bmRlZmluZWQgJiYgb3B0aW9uVmFsdWUgPT09IGZhbHNlKSB8fFxuICAgICAgICAobmVnYXRpdmVPcHRpb24ucHJlc2V0QXJnICE9PSB1bmRlZmluZWQgJiYgb3B0aW9uVmFsdWUgPT09IG5lZ2F0aXZlT3B0aW9uLnByZXNldEFyZylcbiAgICAgICkpIHtcbiAgICAgICAgcmV0dXJuIG5lZ2F0aXZlT3B0aW9uO1xuICAgICAgfVxuICAgICAgcmV0dXJuIHBvc2l0aXZlT3B0aW9uIHx8IG9wdGlvbjtcbiAgICB9O1xuXG4gICAgY29uc3QgZ2V0RXJyb3JNZXNzYWdlID0gKG9wdGlvbikgPT4ge1xuICAgICAgY29uc3QgYmVzdE9wdGlvbiA9IGZpbmRCZXN0T3B0aW9uRnJvbVZhbHVlKG9wdGlvbik7XG4gICAgICBjb25zdCBvcHRpb25LZXkgPSBiZXN0T3B0aW9uLmF0dHJpYnV0ZU5hbWUoKTtcbiAgICAgIGNvbnN0IHNvdXJjZSA9IHRoaXMuZ2V0T3B0aW9uVmFsdWVTb3VyY2Uob3B0aW9uS2V5KTtcbiAgICAgIGlmIChzb3VyY2UgPT09ICdlbnYnKSB7XG4gICAgICAgIHJldHVybiBgZW52aXJvbm1lbnQgdmFyaWFibGUgJyR7YmVzdE9wdGlvbi5lbnZWYXJ9J2A7XG4gICAgICB9XG4gICAgICByZXR1cm4gYG9wdGlvbiAnJHtiZXN0T3B0aW9uLmZsYWdzfSdgO1xuICAgIH07XG5cbiAgICBjb25zdCBtZXNzYWdlID0gYGVycm9yOiAke2dldEVycm9yTWVzc2FnZShvcHRpb24pfSBjYW5ub3QgYmUgdXNlZCB3aXRoICR7Z2V0RXJyb3JNZXNzYWdlKGNvbmZsaWN0aW5nT3B0aW9uKX1gO1xuICAgIHRoaXMuZXJyb3IobWVzc2FnZSwgeyBjb2RlOiAnY29tbWFuZGVyLmNvbmZsaWN0aW5nT3B0aW9uJyB9KTtcbiAgfVxuXG4gIC8qKlxuICAgKiBVbmtub3duIG9wdGlvbiBgZmxhZ2AuXG4gICAqXG4gICAqIEBwYXJhbSB7c3RyaW5nfSBmbGFnXG4gICAqIEBhcGkgcHJpdmF0ZVxuICAgKi9cblxuICB1bmtub3duT3B0aW9uKGZsYWcpIHtcbiAgICBpZiAodGhpcy5fYWxsb3dVbmtub3duT3B0aW9uKSByZXR1cm47XG4gICAgbGV0IHN1Z2dlc3Rpb24gPSAnJztcblxuICAgIGlmIChmbGFnLnN0YXJ0c1dpdGgoJy0tJykgJiYgdGhpcy5fc2hvd1N1Z2dlc3Rpb25BZnRlckVycm9yKSB7XG4gICAgICAvLyBMb29waW5nIHRvIHBpY2sgdXAgdGhlIGdsb2JhbCBvcHRpb25zIHRvb1xuICAgICAgbGV0IGNhbmRpZGF0ZUZsYWdzID0gW107XG4gICAgICBsZXQgY29tbWFuZCA9IHRoaXM7XG4gICAgICBkbyB7XG4gICAgICAgIGNvbnN0IG1vcmVGbGFncyA9IGNvbW1hbmQuY3JlYXRlSGVscCgpLnZpc2libGVPcHRpb25zKGNvbW1hbmQpXG4gICAgICAgICAgLmZpbHRlcihvcHRpb24gPT4gb3B0aW9uLmxvbmcpXG4gICAgICAgICAgLm1hcChvcHRpb24gPT4gb3B0aW9uLmxvbmcpO1xuICAgICAgICBjYW5kaWRhdGVGbGFncyA9IGNhbmRpZGF0ZUZsYWdzLmNvbmNhdChtb3JlRmxhZ3MpO1xuICAgICAgICBjb21tYW5kID0gY29tbWFuZC5wYXJlbnQ7XG4gICAgICB9IHdoaWxlIChjb21tYW5kICYmICFjb21tYW5kLl9lbmFibGVQb3NpdGlvbmFsT3B0aW9ucyk7XG4gICAgICBzdWdnZXN0aW9uID0gc3VnZ2VzdFNpbWlsYXIoZmxhZywgY2FuZGlkYXRlRmxhZ3MpO1xuICAgIH1cblxuICAgIGNvbnN0IG1lc3NhZ2UgPSBgZXJyb3I6IHVua25vd24gb3B0aW9uICcke2ZsYWd9JyR7c3VnZ2VzdGlvbn1gO1xuICAgIHRoaXMuZXJyb3IobWVzc2FnZSwgeyBjb2RlOiAnY29tbWFuZGVyLnVua25vd25PcHRpb24nIH0pO1xuICB9XG5cbiAgLyoqXG4gICAqIEV4Y2VzcyBhcmd1bWVudHMsIG1vcmUgdGhhbiBleHBlY3RlZC5cbiAgICpcbiAgICogQHBhcmFtIHtzdHJpbmdbXX0gcmVjZWl2ZWRBcmdzXG4gICAqIEBhcGkgcHJpdmF0ZVxuICAgKi9cblxuICBfZXhjZXNzQXJndW1lbnRzKHJlY2VpdmVkQXJncykge1xuICAgIGlmICh0aGlzLl9hbGxvd0V4Y2Vzc0FyZ3VtZW50cykgcmV0dXJuO1xuXG4gICAgY29uc3QgZXhwZWN0ZWQgPSB0aGlzLl9hcmdzLmxlbmd0aDtcbiAgICBjb25zdCBzID0gKGV4cGVjdGVkID09PSAxKSA/ICcnIDogJ3MnO1xuICAgIGNvbnN0IGZvclN1YmNvbW1hbmQgPSB0aGlzLnBhcmVudCA/IGAgZm9yICcke3RoaXMubmFtZSgpfSdgIDogJyc7XG4gICAgY29uc3QgbWVzc2FnZSA9IGBlcnJvcjogdG9vIG1hbnkgYXJndW1lbnRzJHtmb3JTdWJjb21tYW5kfS4gRXhwZWN0ZWQgJHtleHBlY3RlZH0gYXJndW1lbnQke3N9IGJ1dCBnb3QgJHtyZWNlaXZlZEFyZ3MubGVuZ3RofS5gO1xuICAgIHRoaXMuZXJyb3IobWVzc2FnZSwgeyBjb2RlOiAnY29tbWFuZGVyLmV4Y2Vzc0FyZ3VtZW50cycgfSk7XG4gIH1cblxuICAvKipcbiAgICogVW5rbm93biBjb21tYW5kLlxuICAgKlxuICAgKiBAYXBpIHByaXZhdGVcbiAgICovXG5cbiAgdW5rbm93bkNvbW1hbmQoKSB7XG4gICAgY29uc3QgdW5rbm93bk5hbWUgPSB0aGlzLmFyZ3NbMF07XG4gICAgbGV0IHN1Z2dlc3Rpb24gPSAnJztcblxuICAgIGlmICh0aGlzLl9zaG93U3VnZ2VzdGlvbkFmdGVyRXJyb3IpIHtcbiAgICAgIGNvbnN0IGNhbmRpZGF0ZU5hbWVzID0gW107XG4gICAgICB0aGlzLmNyZWF0ZUhlbHAoKS52aXNpYmxlQ29tbWFuZHModGhpcykuZm9yRWFjaCgoY29tbWFuZCkgPT4ge1xuICAgICAgICBjYW5kaWRhdGVOYW1lcy5wdXNoKGNvbW1hbmQubmFtZSgpKTtcbiAgICAgICAgLy8ganVzdCB2aXNpYmxlIGFsaWFzXG4gICAgICAgIGlmIChjb21tYW5kLmFsaWFzKCkpIGNhbmRpZGF0ZU5hbWVzLnB1c2goY29tbWFuZC5hbGlhcygpKTtcbiAgICAgIH0pO1xuICAgICAgc3VnZ2VzdGlvbiA9IHN1Z2dlc3RTaW1pbGFyKHVua25vd25OYW1lLCBjYW5kaWRhdGVOYW1lcyk7XG4gICAgfVxuXG4gICAgY29uc3QgbWVzc2FnZSA9IGBlcnJvcjogdW5rbm93biBjb21tYW5kICcke3Vua25vd25OYW1lfScke3N1Z2dlc3Rpb259YDtcbiAgICB0aGlzLmVycm9yKG1lc3NhZ2UsIHsgY29kZTogJ2NvbW1hbmRlci51bmtub3duQ29tbWFuZCcgfSk7XG4gIH1cblxuICAvKipcbiAgICogU2V0IHRoZSBwcm9ncmFtIHZlcnNpb24gdG8gYHN0cmAuXG4gICAqXG4gICAqIFRoaXMgbWV0aG9kIGF1dG8tcmVnaXN0ZXJzIHRoZSBcIi1WLCAtLXZlcnNpb25cIiBmbGFnXG4gICAqIHdoaWNoIHdpbGwgcHJpbnQgdGhlIHZlcnNpb24gbnVtYmVyIHdoZW4gcGFzc2VkLlxuICAgKlxuICAgKiBZb3UgY2FuIG9wdGlvbmFsbHkgc3VwcGx5IHRoZSAgZmxhZ3MgYW5kIGRlc2NyaXB0aW9uIHRvIG92ZXJyaWRlIHRoZSBkZWZhdWx0cy5cbiAgICpcbiAgICogQHBhcmFtIHtzdHJpbmd9IHN0clxuICAgKiBAcGFyYW0ge3N0cmluZ30gW2ZsYWdzXVxuICAgKiBAcGFyYW0ge3N0cmluZ30gW2Rlc2NyaXB0aW9uXVxuICAgKiBAcmV0dXJuIHt0aGlzIHwgc3RyaW5nfSBgdGhpc2AgY29tbWFuZCBmb3IgY2hhaW5pbmcsIG9yIHZlcnNpb24gc3RyaW5nIGlmIG5vIGFyZ3VtZW50c1xuICAgKi9cblxuICB2ZXJzaW9uKHN0ciwgZmxhZ3MsIGRlc2NyaXB0aW9uKSB7XG4gICAgaWYgKHN0ciA9PT0gdW5kZWZpbmVkKSByZXR1cm4gdGhpcy5fdmVyc2lvbjtcbiAgICB0aGlzLl92ZXJzaW9uID0gc3RyO1xuICAgIGZsYWdzID0gZmxhZ3MgfHwgJy1WLCAtLXZlcnNpb24nO1xuICAgIGRlc2NyaXB0aW9uID0gZGVzY3JpcHRpb24gfHwgJ291dHB1dCB0aGUgdmVyc2lvbiBudW1iZXInO1xuICAgIGNvbnN0IHZlcnNpb25PcHRpb24gPSB0aGlzLmNyZWF0ZU9wdGlvbihmbGFncywgZGVzY3JpcHRpb24pO1xuICAgIHRoaXMuX3ZlcnNpb25PcHRpb25OYW1lID0gdmVyc2lvbk9wdGlvbi5hdHRyaWJ1dGVOYW1lKCk7XG4gICAgdGhpcy5vcHRpb25zLnB1c2godmVyc2lvbk9wdGlvbik7XG4gICAgdGhpcy5vbignb3B0aW9uOicgKyB2ZXJzaW9uT3B0aW9uLm5hbWUoKSwgKCkgPT4ge1xuICAgICAgdGhpcy5fb3V0cHV0Q29uZmlndXJhdGlvbi53cml0ZU91dChgJHtzdHJ9XFxuYCk7XG4gICAgICB0aGlzLl9leGl0KDAsICdjb21tYW5kZXIudmVyc2lvbicsIHN0cik7XG4gICAgfSk7XG4gICAgcmV0dXJuIHRoaXM7XG4gIH1cblxuICAvKipcbiAgICogU2V0IHRoZSBkZXNjcmlwdGlvbi5cbiAgICpcbiAgICogQHBhcmFtIHtzdHJpbmd9IFtzdHJdXG4gICAqIEBwYXJhbSB7T2JqZWN0fSBbYXJnc0Rlc2NyaXB0aW9uXVxuICAgKiBAcmV0dXJuIHtzdHJpbmd8Q29tbWFuZH1cbiAgICovXG4gIGRlc2NyaXB0aW9uKHN0ciwgYXJnc0Rlc2NyaXB0aW9uKSB7XG4gICAgaWYgKHN0ciA9PT0gdW5kZWZpbmVkICYmIGFyZ3NEZXNjcmlwdGlvbiA9PT0gdW5kZWZpbmVkKSByZXR1cm4gdGhpcy5fZGVzY3JpcHRpb247XG4gICAgdGhpcy5fZGVzY3JpcHRpb24gPSBzdHI7XG4gICAgaWYgKGFyZ3NEZXNjcmlwdGlvbikge1xuICAgICAgdGhpcy5fYXJnc0Rlc2NyaXB0aW9uID0gYXJnc0Rlc2NyaXB0aW9uO1xuICAgIH1cbiAgICByZXR1cm4gdGhpcztcbiAgfVxuXG4gIC8qKlxuICAgKiBTZXQgdGhlIHN1bW1hcnkuIFVzZWQgd2hlbiBsaXN0ZWQgYXMgc3ViY29tbWFuZCBvZiBwYXJlbnQuXG4gICAqXG4gICAqIEBwYXJhbSB7c3RyaW5nfSBbc3RyXVxuICAgKiBAcmV0dXJuIHtzdHJpbmd8Q29tbWFuZH1cbiAgICovXG4gIHN1bW1hcnkoc3RyKSB7XG4gICAgaWYgKHN0ciA9PT0gdW5kZWZpbmVkKSByZXR1cm4gdGhpcy5fc3VtbWFyeTtcbiAgICB0aGlzLl9zdW1tYXJ5ID0gc3RyO1xuICAgIHJldHVybiB0aGlzO1xuICB9XG5cbiAgLyoqXG4gICAqIFNldCBhbiBhbGlhcyBmb3IgdGhlIGNvbW1hbmQuXG4gICAqXG4gICAqIFlvdSBtYXkgY2FsbCBtb3JlIHRoYW4gb25jZSB0byBhZGQgbXVsdGlwbGUgYWxpYXNlcy4gT25seSB0aGUgZmlyc3QgYWxpYXMgaXMgc2hvd24gaW4gdGhlIGF1dG8tZ2VuZXJhdGVkIGhlbHAuXG4gICAqXG4gICAqIEBwYXJhbSB7c3RyaW5nfSBbYWxpYXNdXG4gICAqIEByZXR1cm4ge3N0cmluZ3xDb21tYW5kfVxuICAgKi9cblxuICBhbGlhcyhhbGlhcykge1xuICAgIGlmIChhbGlhcyA9PT0gdW5kZWZpbmVkKSByZXR1cm4gdGhpcy5fYWxpYXNlc1swXTsgLy8ganVzdCByZXR1cm4gZmlyc3QsIGZvciBiYWNrd2FyZHMgY29tcGF0aWJpbGl0eVxuXG4gICAgLyoqIEB0eXBlIHtDb21tYW5kfSAqL1xuICAgIGxldCBjb21tYW5kID0gdGhpcztcbiAgICBpZiAodGhpcy5jb21tYW5kcy5sZW5ndGggIT09IDAgJiYgdGhpcy5jb21tYW5kc1t0aGlzLmNvbW1hbmRzLmxlbmd0aCAtIDFdLl9leGVjdXRhYmxlSGFuZGxlcikge1xuICAgICAgLy8gYXNzdW1lIGFkZGluZyBhbGlhcyBmb3IgbGFzdCBhZGRlZCBleGVjdXRhYmxlIHN1YmNvbW1hbmQsIHJhdGhlciB0aGFuIHRoaXNcbiAgICAgIGNvbW1hbmQgPSB0aGlzLmNvbW1hbmRzW3RoaXMuY29tbWFuZHMubGVuZ3RoIC0gMV07XG4gICAgfVxuXG4gICAgaWYgKGFsaWFzID09PSBjb21tYW5kLl9uYW1lKSB0aHJvdyBuZXcgRXJyb3IoJ0NvbW1hbmQgYWxpYXMgY2FuXFwndCBiZSB0aGUgc2FtZSBhcyBpdHMgbmFtZScpO1xuXG4gICAgY29tbWFuZC5fYWxpYXNlcy5wdXNoKGFsaWFzKTtcbiAgICByZXR1cm4gdGhpcztcbiAgfVxuXG4gIC8qKlxuICAgKiBTZXQgYWxpYXNlcyBmb3IgdGhlIGNvbW1hbmQuXG4gICAqXG4gICAqIE9ubHkgdGhlIGZpcnN0IGFsaWFzIGlzIHNob3duIGluIHRoZSBhdXRvLWdlbmVyYXRlZCBoZWxwLlxuICAgKlxuICAgKiBAcGFyYW0ge3N0cmluZ1tdfSBbYWxpYXNlc11cbiAgICogQHJldHVybiB7c3RyaW5nW118Q29tbWFuZH1cbiAgICovXG5cbiAgYWxpYXNlcyhhbGlhc2VzKSB7XG4gICAgLy8gR2V0dGVyIGZvciB0aGUgYXJyYXkgb2YgYWxpYXNlcyBpcyB0aGUgbWFpbiByZWFzb24gZm9yIGhhdmluZyBhbGlhc2VzKCkgaW4gYWRkaXRpb24gdG8gYWxpYXMoKS5cbiAgICBpZiAoYWxpYXNlcyA9PT0gdW5kZWZpbmVkKSByZXR1cm4gdGhpcy5fYWxpYXNlcztcblxuICAgIGFsaWFzZXMuZm9yRWFjaCgoYWxpYXMpID0+IHRoaXMuYWxpYXMoYWxpYXMpKTtcbiAgICByZXR1cm4gdGhpcztcbiAgfVxuXG4gIC8qKlxuICAgKiBTZXQgLyBnZXQgdGhlIGNvbW1hbmQgdXNhZ2UgYHN0cmAuXG4gICAqXG4gICAqIEBwYXJhbSB7c3RyaW5nfSBbc3RyXVxuICAgKiBAcmV0dXJuIHtTdHJpbmd8Q29tbWFuZH1cbiAgICovXG5cbiAgdXNhZ2Uoc3RyKSB7XG4gICAgaWYgKHN0ciA9PT0gdW5kZWZpbmVkKSB7XG4gICAgICBpZiAodGhpcy5fdXNhZ2UpIHJldHVybiB0aGlzLl91c2FnZTtcblxuICAgICAgY29uc3QgYXJncyA9IHRoaXMuX2FyZ3MubWFwKChhcmcpID0+IHtcbiAgICAgICAgcmV0dXJuIGh1bWFuUmVhZGFibGVBcmdOYW1lKGFyZyk7XG4gICAgICB9KTtcbiAgICAgIHJldHVybiBbXS5jb25jYXQoXG4gICAgICAgICh0aGlzLm9wdGlvbnMubGVuZ3RoIHx8IHRoaXMuX2hhc0hlbHBPcHRpb24gPyAnW29wdGlvbnNdJyA6IFtdKSxcbiAgICAgICAgKHRoaXMuY29tbWFuZHMubGVuZ3RoID8gJ1tjb21tYW5kXScgOiBbXSksXG4gICAgICAgICh0aGlzLl9hcmdzLmxlbmd0aCA/IGFyZ3MgOiBbXSlcbiAgICAgICkuam9pbignICcpO1xuICAgIH1cblxuICAgIHRoaXMuX3VzYWdlID0gc3RyO1xuICAgIHJldHVybiB0aGlzO1xuICB9XG5cbiAgLyoqXG4gICAqIEdldCBvciBzZXQgdGhlIG5hbWUgb2YgdGhlIGNvbW1hbmQuXG4gICAqXG4gICAqIEBwYXJhbSB7c3RyaW5nfSBbc3RyXVxuICAgKiBAcmV0dXJuIHtzdHJpbmd8Q29tbWFuZH1cbiAgICovXG5cbiAgbmFtZShzdHIpIHtcbiAgICBpZiAoc3RyID09PSB1bmRlZmluZWQpIHJldHVybiB0aGlzLl9uYW1lO1xuICAgIHRoaXMuX25hbWUgPSBzdHI7XG4gICAgcmV0dXJuIHRoaXM7XG4gIH1cblxuICAvKipcbiAgICogU2V0IHRoZSBuYW1lIG9mIHRoZSBjb21tYW5kIGZyb20gc2NyaXB0IGZpbGVuYW1lLCBzdWNoIGFzIHByb2Nlc3MuYXJndlsxXSxcbiAgICogb3IgcmVxdWlyZS5tYWluLmZpbGVuYW1lLCBvciBfX2ZpbGVuYW1lLlxuICAgKlxuICAgKiAoVXNlZCBpbnRlcm5hbGx5IGFuZCBwdWJsaWMgYWx0aG91Z2ggbm90IGRvY3VtZW50ZWQgaW4gUkVBRE1FLilcbiAgICpcbiAgICogQGV4YW1wbGVcbiAgICogcHJvZ3JhbS5uYW1lRnJvbUZpbGVuYW1lKHJlcXVpcmUubWFpbi5maWxlbmFtZSk7XG4gICAqXG4gICAqIEBwYXJhbSB7c3RyaW5nfSBmaWxlbmFtZVxuICAgKiBAcmV0dXJuIHtDb21tYW5kfVxuICAgKi9cblxuICBuYW1lRnJvbUZpbGVuYW1lKGZpbGVuYW1lKSB7XG4gICAgdGhpcy5fbmFtZSA9IHBhdGguYmFzZW5hbWUoZmlsZW5hbWUsIHBhdGguZXh0bmFtZShmaWxlbmFtZSkpO1xuXG4gICAgcmV0dXJuIHRoaXM7XG4gIH1cblxuICAvKipcbiAgICogR2V0IG9yIHNldCB0aGUgZGlyZWN0b3J5IGZvciBzZWFyY2hpbmcgZm9yIGV4ZWN1dGFibGUgc3ViY29tbWFuZHMgb2YgdGhpcyBjb21tYW5kLlxuICAgKlxuICAgKiBAZXhhbXBsZVxuICAgKiBwcm9ncmFtLmV4ZWN1dGFibGVEaXIoX19kaXJuYW1lKTtcbiAgICogLy8gb3JcbiAgICogcHJvZ3JhbS5leGVjdXRhYmxlRGlyKCdzdWJjb21tYW5kcycpO1xuICAgKlxuICAgKiBAcGFyYW0ge3N0cmluZ30gW3BhdGhdXG4gICAqIEByZXR1cm4ge3N0cmluZ3xDb21tYW5kfVxuICAgKi9cblxuICBleGVjdXRhYmxlRGlyKHBhdGgpIHtcbiAgICBpZiAocGF0aCA9PT0gdW5kZWZpbmVkKSByZXR1cm4gdGhpcy5fZXhlY3V0YWJsZURpcjtcbiAgICB0aGlzLl9leGVjdXRhYmxlRGlyID0gcGF0aDtcbiAgICByZXR1cm4gdGhpcztcbiAgfVxuXG4gIC8qKlxuICAgKiBSZXR1cm4gcHJvZ3JhbSBoZWxwIGRvY3VtZW50YXRpb24uXG4gICAqXG4gICAqIEBwYXJhbSB7eyBlcnJvcjogYm9vbGVhbiB9fSBbY29udGV4dE9wdGlvbnNdIC0gcGFzcyB7ZXJyb3I6dHJ1ZX0gdG8gd3JhcCBmb3Igc3RkZXJyIGluc3RlYWQgb2Ygc3Rkb3V0XG4gICAqIEByZXR1cm4ge3N0cmluZ31cbiAgICovXG5cbiAgaGVscEluZm9ybWF0aW9uKGNvbnRleHRPcHRpb25zKSB7XG4gICAgY29uc3QgaGVscGVyID0gdGhpcy5jcmVhdGVIZWxwKCk7XG4gICAgaWYgKGhlbHBlci5oZWxwV2lkdGggPT09IHVuZGVmaW5lZCkge1xuICAgICAgaGVscGVyLmhlbHBXaWR0aCA9IChjb250ZXh0T3B0aW9ucyAmJiBjb250ZXh0T3B0aW9ucy5lcnJvcikgPyB0aGlzLl9vdXRwdXRDb25maWd1cmF0aW9uLmdldEVyckhlbHBXaWR0aCgpIDogdGhpcy5fb3V0cHV0Q29uZmlndXJhdGlvbi5nZXRPdXRIZWxwV2lkdGgoKTtcbiAgICB9XG4gICAgcmV0dXJuIGhlbHBlci5mb3JtYXRIZWxwKHRoaXMsIGhlbHBlcik7XG4gIH1cblxuICAvKipcbiAgICogQGFwaSBwcml2YXRlXG4gICAqL1xuXG4gIF9nZXRIZWxwQ29udGV4dChjb250ZXh0T3B0aW9ucykge1xuICAgIGNvbnRleHRPcHRpb25zID0gY29udGV4dE9wdGlvbnMgfHwge307XG4gICAgY29uc3QgY29udGV4dCA9IHsgZXJyb3I6ICEhY29udGV4dE9wdGlvbnMuZXJyb3IgfTtcbiAgICBsZXQgd3JpdGU7XG4gICAgaWYgKGNvbnRleHQuZXJyb3IpIHtcbiAgICAgIHdyaXRlID0gKGFyZykgPT4gdGhpcy5fb3V0cHV0Q29uZmlndXJhdGlvbi53cml0ZUVycihhcmcpO1xuICAgIH0gZWxzZSB7XG4gICAgICB3cml0ZSA9IChhcmcpID0+IHRoaXMuX291dHB1dENvbmZpZ3VyYXRpb24ud3JpdGVPdXQoYXJnKTtcbiAgICB9XG4gICAgY29udGV4dC53cml0ZSA9IGNvbnRleHRPcHRpb25zLndyaXRlIHx8IHdyaXRlO1xuICAgIGNvbnRleHQuY29tbWFuZCA9IHRoaXM7XG4gICAgcmV0dXJuIGNvbnRleHQ7XG4gIH1cblxuICAvKipcbiAgICogT3V0cHV0IGhlbHAgaW5mb3JtYXRpb24gZm9yIHRoaXMgY29tbWFuZC5cbiAgICpcbiAgICogT3V0cHV0cyBidWlsdC1pbiBoZWxwLCBhbmQgY3VzdG9tIHRleHQgYWRkZWQgdXNpbmcgYC5hZGRIZWxwVGV4dCgpYC5cbiAgICpcbiAgICogQHBhcmFtIHt7IGVycm9yOiBib29sZWFuIH0gfCBGdW5jdGlvbn0gW2NvbnRleHRPcHRpb25zXSAtIHBhc3Mge2Vycm9yOnRydWV9IHRvIHdyaXRlIHRvIHN0ZGVyciBpbnN0ZWFkIG9mIHN0ZG91dFxuICAgKi9cblxuICBvdXRwdXRIZWxwKGNvbnRleHRPcHRpb25zKSB7XG4gICAgbGV0IGRlcHJlY2F0ZWRDYWxsYmFjaztcbiAgICBpZiAodHlwZW9mIGNvbnRleHRPcHRpb25zID09PSAnZnVuY3Rpb24nKSB7XG4gICAgICBkZXByZWNhdGVkQ2FsbGJhY2sgPSBjb250ZXh0T3B0aW9ucztcbiAgICAgIGNvbnRleHRPcHRpb25zID0gdW5kZWZpbmVkO1xuICAgIH1cbiAgICBjb25zdCBjb250ZXh0ID0gdGhpcy5fZ2V0SGVscENvbnRleHQoY29udGV4dE9wdGlvbnMpO1xuXG4gICAgZ2V0Q29tbWFuZEFuZFBhcmVudHModGhpcykucmV2ZXJzZSgpLmZvckVhY2goY29tbWFuZCA9PiBjb21tYW5kLmVtaXQoJ2JlZm9yZUFsbEhlbHAnLCBjb250ZXh0KSk7XG4gICAgdGhpcy5lbWl0KCdiZWZvcmVIZWxwJywgY29udGV4dCk7XG5cbiAgICBsZXQgaGVscEluZm9ybWF0aW9uID0gdGhpcy5oZWxwSW5mb3JtYXRpb24oY29udGV4dCk7XG4gICAgaWYgKGRlcHJlY2F0ZWRDYWxsYmFjaykge1xuICAgICAgaGVscEluZm9ybWF0aW9uID0gZGVwcmVjYXRlZENhbGxiYWNrKGhlbHBJbmZvcm1hdGlvbik7XG4gICAgICBpZiAodHlwZW9mIGhlbHBJbmZvcm1hdGlvbiAhPT0gJ3N0cmluZycgJiYgIUJ1ZmZlci5pc0J1ZmZlcihoZWxwSW5mb3JtYXRpb24pKSB7XG4gICAgICAgIHRocm93IG5ldyBFcnJvcignb3V0cHV0SGVscCBjYWxsYmFjayBtdXN0IHJldHVybiBhIHN0cmluZyBvciBhIEJ1ZmZlcicpO1xuICAgICAgfVxuICAgIH1cbiAgICBjb250ZXh0LndyaXRlKGhlbHBJbmZvcm1hdGlvbik7XG5cbiAgICB0aGlzLmVtaXQodGhpcy5faGVscExvbmdGbGFnKTsgLy8gZGVwcmVjYXRlZFxuICAgIHRoaXMuZW1pdCgnYWZ0ZXJIZWxwJywgY29udGV4dCk7XG4gICAgZ2V0Q29tbWFuZEFuZFBhcmVudHModGhpcykuZm9yRWFjaChjb21tYW5kID0+IGNvbW1hbmQuZW1pdCgnYWZ0ZXJBbGxIZWxwJywgY29udGV4dCkpO1xuICB9XG5cbiAgLyoqXG4gICAqIFlvdSBjYW4gcGFzcyBpbiBmbGFncyBhbmQgYSBkZXNjcmlwdGlvbiB0byBvdmVycmlkZSB0aGUgaGVscFxuICAgKiBmbGFncyBhbmQgaGVscCBkZXNjcmlwdGlvbiBmb3IgeW91ciBjb21tYW5kLiBQYXNzIGluIGZhbHNlIHRvXG4gICAqIGRpc2FibGUgdGhlIGJ1aWx0LWluIGhlbHAgb3B0aW9uLlxuICAgKlxuICAgKiBAcGFyYW0ge3N0cmluZyB8IGJvb2xlYW59IFtmbGFnc11cbiAgICogQHBhcmFtIHtzdHJpbmd9IFtkZXNjcmlwdGlvbl1cbiAgICogQHJldHVybiB7Q29tbWFuZH0gYHRoaXNgIGNvbW1hbmQgZm9yIGNoYWluaW5nXG4gICAqL1xuXG4gIGhlbHBPcHRpb24oZmxhZ3MsIGRlc2NyaXB0aW9uKSB7XG4gICAgaWYgKHR5cGVvZiBmbGFncyA9PT0gJ2Jvb2xlYW4nKSB7XG4gICAgICB0aGlzLl9oYXNIZWxwT3B0aW9uID0gZmxhZ3M7XG4gICAgICByZXR1cm4gdGhpcztcbiAgICB9XG4gICAgdGhpcy5faGVscEZsYWdzID0gZmxhZ3MgfHwgdGhpcy5faGVscEZsYWdzO1xuICAgIHRoaXMuX2hlbHBEZXNjcmlwdGlvbiA9IGRlc2NyaXB0aW9uIHx8IHRoaXMuX2hlbHBEZXNjcmlwdGlvbjtcblxuICAgIGNvbnN0IGhlbHBGbGFncyA9IHNwbGl0T3B0aW9uRmxhZ3ModGhpcy5faGVscEZsYWdzKTtcbiAgICB0aGlzLl9oZWxwU2hvcnRGbGFnID0gaGVscEZsYWdzLnNob3J0RmxhZztcbiAgICB0aGlzLl9oZWxwTG9uZ0ZsYWcgPSBoZWxwRmxhZ3MubG9uZ0ZsYWc7XG5cbiAgICByZXR1cm4gdGhpcztcbiAgfVxuXG4gIC8qKlxuICAgKiBPdXRwdXQgaGVscCBpbmZvcm1hdGlvbiBhbmQgZXhpdC5cbiAgICpcbiAgICogT3V0cHV0cyBidWlsdC1pbiBoZWxwLCBhbmQgY3VzdG9tIHRleHQgYWRkZWQgdXNpbmcgYC5hZGRIZWxwVGV4dCgpYC5cbiAgICpcbiAgICogQHBhcmFtIHt7IGVycm9yOiBib29sZWFuIH19IFtjb250ZXh0T3B0aW9uc10gLSBwYXNzIHtlcnJvcjp0cnVlfSB0byB3cml0ZSB0byBzdGRlcnIgaW5zdGVhZCBvZiBzdGRvdXRcbiAgICovXG5cbiAgaGVscChjb250ZXh0T3B0aW9ucykge1xuICAgIHRoaXMub3V0cHV0SGVscChjb250ZXh0T3B0aW9ucyk7XG4gICAgbGV0IGV4aXRDb2RlID0gcHJvY2Vzcy5leGl0Q29kZSB8fCAwO1xuICAgIGlmIChleGl0Q29kZSA9PT0gMCAmJiBjb250ZXh0T3B0aW9ucyAmJiB0eXBlb2YgY29udGV4dE9wdGlvbnMgIT09ICdmdW5jdGlvbicgJiYgY29udGV4dE9wdGlvbnMuZXJyb3IpIHtcbiAgICAgIGV4aXRDb2RlID0gMTtcbiAgICB9XG4gICAgLy8gbWVzc2FnZTogZG8gbm90IGhhdmUgYWxsIGRpc3BsYXllZCB0ZXh0IGF2YWlsYWJsZSBzbyBvbmx5IHBhc3NpbmcgcGxhY2Vob2xkZXIuXG4gICAgdGhpcy5fZXhpdChleGl0Q29kZSwgJ2NvbW1hbmRlci5oZWxwJywgJyhvdXRwdXRIZWxwKScpO1xuICB9XG5cbiAgLyoqXG4gICAqIEFkZCBhZGRpdGlvbmFsIHRleHQgdG8gYmUgZGlzcGxheWVkIHdpdGggdGhlIGJ1aWx0LWluIGhlbHAuXG4gICAqXG4gICAqIFBvc2l0aW9uIGlzICdiZWZvcmUnIG9yICdhZnRlcicgdG8gYWZmZWN0IGp1c3QgdGhpcyBjb21tYW5kLFxuICAgKiBhbmQgJ2JlZm9yZUFsbCcgb3IgJ2FmdGVyQWxsJyB0byBhZmZlY3QgdGhpcyBjb21tYW5kIGFuZCBhbGwgaXRzIHN1YmNvbW1hbmRzLlxuICAgKlxuICAgKiBAcGFyYW0ge3N0cmluZ30gcG9zaXRpb24gLSBiZWZvcmUgb3IgYWZ0ZXIgYnVpbHQtaW4gaGVscFxuICAgKiBAcGFyYW0ge3N0cmluZyB8IEZ1bmN0aW9ufSB0ZXh0IC0gc3RyaW5nIHRvIGFkZCwgb3IgYSBmdW5jdGlvbiByZXR1cm5pbmcgYSBzdHJpbmdcbiAgICogQHJldHVybiB7Q29tbWFuZH0gYHRoaXNgIGNvbW1hbmQgZm9yIGNoYWluaW5nXG4gICAqL1xuICBhZGRIZWxwVGV4dChwb3NpdGlvbiwgdGV4dCkge1xuICAgIGNvbnN0IGFsbG93ZWRWYWx1ZXMgPSBbJ2JlZm9yZUFsbCcsICdiZWZvcmUnLCAnYWZ0ZXInLCAnYWZ0ZXJBbGwnXTtcbiAgICBpZiAoIWFsbG93ZWRWYWx1ZXMuaW5jbHVkZXMocG9zaXRpb24pKSB7XG4gICAgICB0aHJvdyBuZXcgRXJyb3IoYFVuZXhwZWN0ZWQgdmFsdWUgZm9yIHBvc2l0aW9uIHRvIGFkZEhlbHBUZXh0LlxuRXhwZWN0aW5nIG9uZSBvZiAnJHthbGxvd2VkVmFsdWVzLmpvaW4oXCInLCAnXCIpfSdgKTtcbiAgICB9XG4gICAgY29uc3QgaGVscEV2ZW50ID0gYCR7cG9zaXRpb259SGVscGA7XG4gICAgdGhpcy5vbihoZWxwRXZlbnQsIChjb250ZXh0KSA9PiB7XG4gICAgICBsZXQgaGVscFN0cjtcbiAgICAgIGlmICh0eXBlb2YgdGV4dCA9PT0gJ2Z1bmN0aW9uJykge1xuICAgICAgICBoZWxwU3RyID0gdGV4dCh7IGVycm9yOiBjb250ZXh0LmVycm9yLCBjb21tYW5kOiBjb250ZXh0LmNvbW1hbmQgfSk7XG4gICAgICB9IGVsc2Uge1xuICAgICAgICBoZWxwU3RyID0gdGV4dDtcbiAgICAgIH1cbiAgICAgIC8vIElnbm9yZSBmYWxzeSB2YWx1ZSB3aGVuIG5vdGhpbmcgdG8gb3V0cHV0LlxuICAgICAgaWYgKGhlbHBTdHIpIHtcbiAgICAgICAgY29udGV4dC53cml0ZShgJHtoZWxwU3RyfVxcbmApO1xuICAgICAgfVxuICAgIH0pO1xuICAgIHJldHVybiB0aGlzO1xuICB9XG59XG5cbi8qKlxuICogT3V0cHV0IGhlbHAgaW5mb3JtYXRpb24gaWYgaGVscCBmbGFncyBzcGVjaWZpZWRcbiAqXG4gKiBAcGFyYW0ge0NvbW1hbmR9IGNtZCAtIGNvbW1hbmQgdG8gb3V0cHV0IGhlbHAgZm9yXG4gKiBAcGFyYW0ge0FycmF5fSBhcmdzIC0gYXJyYXkgb2Ygb3B0aW9ucyB0byBzZWFyY2ggZm9yIGhlbHAgZmxhZ3NcbiAqIEBhcGkgcHJpdmF0ZVxuICovXG5cbmZ1bmN0aW9uIG91dHB1dEhlbHBJZlJlcXVlc3RlZChjbWQsIGFyZ3MpIHtcbiAgY29uc3QgaGVscE9wdGlvbiA9IGNtZC5faGFzSGVscE9wdGlvbiAmJiBhcmdzLmZpbmQoYXJnID0+IGFyZyA9PT0gY21kLl9oZWxwTG9uZ0ZsYWcgfHwgYXJnID09PSBjbWQuX2hlbHBTaG9ydEZsYWcpO1xuICBpZiAoaGVscE9wdGlvbikge1xuICAgIGNtZC5vdXRwdXRIZWxwKCk7XG4gICAgLy8gKERvIG5vdCBoYXZlIGFsbCBkaXNwbGF5ZWQgdGV4dCBhdmFpbGFibGUgc28gb25seSBwYXNzaW5nIHBsYWNlaG9sZGVyLilcbiAgICBjbWQuX2V4aXQoMCwgJ2NvbW1hbmRlci5oZWxwRGlzcGxheWVkJywgJyhvdXRwdXRIZWxwKScpO1xuICB9XG59XG5cbi8qKlxuICogU2NhbiBhcmd1bWVudHMgYW5kIGluY3JlbWVudCBwb3J0IG51bWJlciBmb3IgaW5zcGVjdCBjYWxscyAodG8gYXZvaWQgY29uZmxpY3RzIHdoZW4gc3Bhd25pbmcgbmV3IGNvbW1hbmQpLlxuICpcbiAqIEBwYXJhbSB7c3RyaW5nW119IGFyZ3MgLSBhcnJheSBvZiBhcmd1bWVudHMgZnJvbSBub2RlLmV4ZWNBcmd2XG4gKiBAcmV0dXJucyB7c3RyaW5nW119XG4gKiBAYXBpIHByaXZhdGVcbiAqL1xuXG5mdW5jdGlvbiBpbmNyZW1lbnROb2RlSW5zcGVjdG9yUG9ydChhcmdzKSB7XG4gIC8vIFRlc3RpbmcgZm9yIHRoZXNlIG9wdGlvbnM6XG4gIC8vICAtLWluc3BlY3RbPVtob3N0Ol1wb3J0XVxuICAvLyAgLS1pbnNwZWN0LWJya1s9W2hvc3Q6XXBvcnRdXG4gIC8vICAtLWluc3BlY3QtcG9ydD1baG9zdDpdcG9ydFxuICByZXR1cm4gYXJncy5tYXAoKGFyZykgPT4ge1xuICAgIGlmICghYXJnLnN0YXJ0c1dpdGgoJy0taW5zcGVjdCcpKSB7XG4gICAgICByZXR1cm4gYXJnO1xuICAgIH1cbiAgICBsZXQgZGVidWdPcHRpb247XG4gICAgbGV0IGRlYnVnSG9zdCA9ICcxMjcuMC4wLjEnO1xuICAgIGxldCBkZWJ1Z1BvcnQgPSAnOTIyOSc7XG4gICAgbGV0IG1hdGNoO1xuICAgIGlmICgobWF0Y2ggPSBhcmcubWF0Y2goL14oLS1pbnNwZWN0KC1icmspPykkLykpICE9PSBudWxsKSB7XG4gICAgICAvLyBlLmcuIC0taW5zcGVjdFxuICAgICAgZGVidWdPcHRpb24gPSBtYXRjaFsxXTtcbiAgICB9IGVsc2UgaWYgKChtYXRjaCA9IGFyZy5tYXRjaCgvXigtLWluc3BlY3QoLWJya3wtcG9ydCk/KT0oW146XSspJC8pKSAhPT0gbnVsbCkge1xuICAgICAgZGVidWdPcHRpb24gPSBtYXRjaFsxXTtcbiAgICAgIGlmICgvXlxcZCskLy50ZXN0KG1hdGNoWzNdKSkge1xuICAgICAgICAvLyBlLmcuIC0taW5zcGVjdD0xMjM0XG4gICAgICAgIGRlYnVnUG9ydCA9IG1hdGNoWzNdO1xuICAgICAgfSBlbHNlIHtcbiAgICAgICAgLy8gZS5nLiAtLWluc3BlY3Q9bG9jYWxob3N0XG4gICAgICAgIGRlYnVnSG9zdCA9IG1hdGNoWzNdO1xuICAgICAgfVxuICAgIH0gZWxzZSBpZiAoKG1hdGNoID0gYXJnLm1hdGNoKC9eKC0taW5zcGVjdCgtYnJrfC1wb3J0KT8pPShbXjpdKyk6KFxcZCspJC8pKSAhPT0gbnVsbCkge1xuICAgICAgLy8gZS5nLiAtLWluc3BlY3Q9bG9jYWxob3N0OjEyMzRcbiAgICAgIGRlYnVnT3B0aW9uID0gbWF0Y2hbMV07XG4gICAgICBkZWJ1Z0hvc3QgPSBtYXRjaFszXTtcbiAgICAgIGRlYnVnUG9ydCA9IG1hdGNoWzRdO1xuICAgIH1cblxuICAgIGlmIChkZWJ1Z09wdGlvbiAmJiBkZWJ1Z1BvcnQgIT09ICcwJykge1xuICAgICAgcmV0dXJuIGAke2RlYnVnT3B0aW9ufT0ke2RlYnVnSG9zdH06JHtwYXJzZUludChkZWJ1Z1BvcnQpICsgMX1gO1xuICAgIH1cbiAgICByZXR1cm4gYXJnO1xuICB9KTtcbn1cblxuLyoqXG4gKiBAcGFyYW0ge0NvbW1hbmR9IHN0YXJ0Q29tbWFuZFxuICogQHJldHVybnMge0NvbW1hbmRbXX1cbiAqIEBhcGkgcHJpdmF0ZVxuICovXG5cbmZ1bmN0aW9uIGdldENvbW1hbmRBbmRQYXJlbnRzKHN0YXJ0Q29tbWFuZCkge1xuICBjb25zdCByZXN1bHQgPSBbXTtcbiAgZm9yIChsZXQgY29tbWFuZCA9IHN0YXJ0Q29tbWFuZDsgY29tbWFuZDsgY29tbWFuZCA9IGNvbW1hbmQucGFyZW50KSB7XG4gICAgcmVzdWx0LnB1c2goY29tbWFuZCk7XG4gIH1cbiAgcmV0dXJuIHJlc3VsdDtcbn1cblxuZXhwb3J0cy5Db21tYW5kID0gQ29tbWFuZDtcbiIsIi8vIEB0cy1jaGVja1xuXG4vKipcbiAqIENvbW1hbmRlckVycm9yIGNsYXNzXG4gKiBAY2xhc3NcbiAqL1xuY2xhc3MgQ29tbWFuZGVyRXJyb3IgZXh0ZW5kcyBFcnJvciB7XG4gIC8qKlxuICAgKiBDb25zdHJ1Y3RzIHRoZSBDb21tYW5kZXJFcnJvciBjbGFzc1xuICAgKiBAcGFyYW0ge251bWJlcn0gZXhpdENvZGUgc3VnZ2VzdGVkIGV4aXQgY29kZSB3aGljaCBjb3VsZCBiZSB1c2VkIHdpdGggcHJvY2Vzcy5leGl0XG4gICAqIEBwYXJhbSB7c3RyaW5nfSBjb2RlIGFuIGlkIHN0cmluZyByZXByZXNlbnRpbmcgdGhlIGVycm9yXG4gICAqIEBwYXJhbSB7c3RyaW5nfSBtZXNzYWdlIGh1bWFuLXJlYWRhYmxlIGRlc2NyaXB0aW9uIG9mIHRoZSBlcnJvclxuICAgKiBAY29uc3RydWN0b3JcbiAgICovXG4gIGNvbnN0cnVjdG9yKGV4aXRDb2RlLCBjb2RlLCBtZXNzYWdlKSB7XG4gICAgc3VwZXIobWVzc2FnZSk7XG4gICAgLy8gcHJvcGVybHkgY2FwdHVyZSBzdGFjayB0cmFjZSBpbiBOb2RlLmpzXG4gICAgRXJyb3IuY2FwdHVyZVN0YWNrVHJhY2UodGhpcywgdGhpcy5jb25zdHJ1Y3Rvcik7XG4gICAgdGhpcy5uYW1lID0gdGhpcy5jb25zdHJ1Y3Rvci5uYW1lO1xuICAgIHRoaXMuY29kZSA9IGNvZGU7XG4gICAgdGhpcy5leGl0Q29kZSA9IGV4aXRDb2RlO1xuICAgIHRoaXMubmVzdGVkRXJyb3IgPSB1bmRlZmluZWQ7XG4gIH1cbn1cblxuLyoqXG4gKiBJbnZhbGlkQXJndW1lbnRFcnJvciBjbGFzc1xuICogQGNsYXNzXG4gKi9cbmNsYXNzIEludmFsaWRBcmd1bWVudEVycm9yIGV4dGVuZHMgQ29tbWFuZGVyRXJyb3Ige1xuICAvKipcbiAgICogQ29uc3RydWN0cyB0aGUgSW52YWxpZEFyZ3VtZW50RXJyb3IgY2xhc3NcbiAgICogQHBhcmFtIHtzdHJpbmd9IFttZXNzYWdlXSBleHBsYW5hdGlvbiBvZiB3aHkgYXJndW1lbnQgaXMgaW52YWxpZFxuICAgKiBAY29uc3RydWN0b3JcbiAgICovXG4gIGNvbnN0cnVjdG9yKG1lc3NhZ2UpIHtcbiAgICBzdXBlcigxLCAnY29tbWFuZGVyLmludmFsaWRBcmd1bWVudCcsIG1lc3NhZ2UpO1xuICAgIC8vIHByb3Blcmx5IGNhcHR1cmUgc3RhY2sgdHJhY2UgaW4gTm9kZS5qc1xuICAgIEVycm9yLmNhcHR1cmVTdGFja1RyYWNlKHRoaXMsIHRoaXMuY29uc3RydWN0b3IpO1xuICAgIHRoaXMubmFtZSA9IHRoaXMuY29uc3RydWN0b3IubmFtZTtcbiAgfVxufVxuXG5leHBvcnRzLkNvbW1hbmRlckVycm9yID0gQ29tbWFuZGVyRXJyb3I7XG5leHBvcnRzLkludmFsaWRBcmd1bWVudEVycm9yID0gSW52YWxpZEFyZ3VtZW50RXJyb3I7XG4iLCJjb25zdCB7IGh1bWFuUmVhZGFibGVBcmdOYW1lIH0gPSByZXF1aXJlKCcuL2FyZ3VtZW50LmpzJyk7XG5cbi8qKlxuICogVHlwZVNjcmlwdCBpbXBvcnQgdHlwZXMgZm9yIEpTRG9jLCB1c2VkIGJ5IFZpc3VhbCBTdHVkaW8gQ29kZSBJbnRlbGxpU2Vuc2UgYW5kIGBucG0gcnVuIHR5cGVzY3JpcHQtY2hlY2tKU2BcbiAqIGh0dHBzOi8vd3d3LnR5cGVzY3JpcHRsYW5nLm9yZy9kb2NzL2hhbmRib29rL2pzZG9jLXN1cHBvcnRlZC10eXBlcy5odG1sI2ltcG9ydC10eXBlc1xuICogQHR5cGVkZWYgeyBpbXBvcnQoXCIuL2FyZ3VtZW50LmpzXCIpLkFyZ3VtZW50IH0gQXJndW1lbnRcbiAqIEB0eXBlZGVmIHsgaW1wb3J0KFwiLi9jb21tYW5kLmpzXCIpLkNvbW1hbmQgfSBDb21tYW5kXG4gKiBAdHlwZWRlZiB7IGltcG9ydChcIi4vb3B0aW9uLmpzXCIpLk9wdGlvbiB9IE9wdGlvblxuICovXG5cbi8vIEB0cy1jaGVja1xuXG4vLyBBbHRob3VnaCB0aGlzIGlzIGEgY2xhc3MsIG1ldGhvZHMgYXJlIHN0YXRpYyBpbiBzdHlsZSB0byBhbGxvdyBvdmVycmlkZSB1c2luZyBzdWJjbGFzcyBvciBqdXN0IGZ1bmN0aW9ucy5cbmNsYXNzIEhlbHAge1xuICBjb25zdHJ1Y3RvcigpIHtcbiAgICB0aGlzLmhlbHBXaWR0aCA9IHVuZGVmaW5lZDtcbiAgICB0aGlzLnNvcnRTdWJjb21tYW5kcyA9IGZhbHNlO1xuICAgIHRoaXMuc29ydE9wdGlvbnMgPSBmYWxzZTtcbiAgICB0aGlzLnNob3dHbG9iYWxPcHRpb25zID0gZmFsc2U7XG4gIH1cblxuICAvKipcbiAgICogR2V0IGFuIGFycmF5IG9mIHRoZSB2aXNpYmxlIHN1YmNvbW1hbmRzLiBJbmNsdWRlcyBhIHBsYWNlaG9sZGVyIGZvciB0aGUgaW1wbGljaXQgaGVscCBjb21tYW5kLCBpZiB0aGVyZSBpcyBvbmUuXG4gICAqXG4gICAqIEBwYXJhbSB7Q29tbWFuZH0gY21kXG4gICAqIEByZXR1cm5zIHtDb21tYW5kW119XG4gICAqL1xuXG4gIHZpc2libGVDb21tYW5kcyhjbWQpIHtcbiAgICBjb25zdCB2aXNpYmxlQ29tbWFuZHMgPSBjbWQuY29tbWFuZHMuZmlsdGVyKGNtZCA9PiAhY21kLl9oaWRkZW4pO1xuICAgIGlmIChjbWQuX2hhc0ltcGxpY2l0SGVscENvbW1hbmQoKSkge1xuICAgICAgLy8gQ3JlYXRlIGEgY29tbWFuZCBtYXRjaGluZyB0aGUgaW1wbGljaXQgaGVscCBjb21tYW5kLlxuICAgICAgY29uc3QgWywgaGVscE5hbWUsIGhlbHBBcmdzXSA9IGNtZC5faGVscENvbW1hbmRuYW1lQW5kQXJncy5tYXRjaCgvKFteIF0rKSAqKC4qKS8pO1xuICAgICAgY29uc3QgaGVscENvbW1hbmQgPSBjbWQuY3JlYXRlQ29tbWFuZChoZWxwTmFtZSlcbiAgICAgICAgLmhlbHBPcHRpb24oZmFsc2UpO1xuICAgICAgaGVscENvbW1hbmQuZGVzY3JpcHRpb24oY21kLl9oZWxwQ29tbWFuZERlc2NyaXB0aW9uKTtcbiAgICAgIGlmIChoZWxwQXJncykgaGVscENvbW1hbmQuYXJndW1lbnRzKGhlbHBBcmdzKTtcbiAgICAgIHZpc2libGVDb21tYW5kcy5wdXNoKGhlbHBDb21tYW5kKTtcbiAgICB9XG4gICAgaWYgKHRoaXMuc29ydFN1YmNvbW1hbmRzKSB7XG4gICAgICB2aXNpYmxlQ29tbWFuZHMuc29ydCgoYSwgYikgPT4ge1xuICAgICAgICAvLyBAdHMtaWdub3JlOiBvdmVybG9hZGVkIHJldHVybiB0eXBlXG4gICAgICAgIHJldHVybiBhLm5hbWUoKS5sb2NhbGVDb21wYXJlKGIubmFtZSgpKTtcbiAgICAgIH0pO1xuICAgIH1cbiAgICByZXR1cm4gdmlzaWJsZUNvbW1hbmRzO1xuICB9XG5cbiAgLyoqXG4gICAqIENvbXBhcmUgb3B0aW9ucyBmb3Igc29ydC5cbiAgICpcbiAgICogQHBhcmFtIHtPcHRpb259IGFcbiAgICogQHBhcmFtIHtPcHRpb259IGJcbiAgICogQHJldHVybnMgbnVtYmVyXG4gICAqL1xuICBjb21wYXJlT3B0aW9ucyhhLCBiKSB7XG4gICAgY29uc3QgZ2V0U29ydEtleSA9IChvcHRpb24pID0+IHtcbiAgICAgIC8vIFdZU0lXWUcgZm9yIG9yZGVyIGRpc3BsYXllZCBpbiBoZWxwLiBTaG9ydCB1c2VkIGZvciBjb21wYXJpc29uIGlmIHByZXNlbnQuIE5vIHNwZWNpYWwgaGFuZGxpbmcgZm9yIG5lZ2F0ZWQuXG4gICAgICByZXR1cm4gb3B0aW9uLnNob3J0ID8gb3B0aW9uLnNob3J0LnJlcGxhY2UoL14tLywgJycpIDogb3B0aW9uLmxvbmcucmVwbGFjZSgvXi0tLywgJycpO1xuICAgIH07XG4gICAgcmV0dXJuIGdldFNvcnRLZXkoYSkubG9jYWxlQ29tcGFyZShnZXRTb3J0S2V5KGIpKTtcbiAgfVxuXG4gIC8qKlxuICAgKiBHZXQgYW4gYXJyYXkgb2YgdGhlIHZpc2libGUgb3B0aW9ucy4gSW5jbHVkZXMgYSBwbGFjZWhvbGRlciBmb3IgdGhlIGltcGxpY2l0IGhlbHAgb3B0aW9uLCBpZiB0aGVyZSBpcyBvbmUuXG4gICAqXG4gICAqIEBwYXJhbSB7Q29tbWFuZH0gY21kXG4gICAqIEByZXR1cm5zIHtPcHRpb25bXX1cbiAgICovXG5cbiAgdmlzaWJsZU9wdGlvbnMoY21kKSB7XG4gICAgY29uc3QgdmlzaWJsZU9wdGlvbnMgPSBjbWQub3B0aW9ucy5maWx0ZXIoKG9wdGlvbikgPT4gIW9wdGlvbi5oaWRkZW4pO1xuICAgIC8vIEltcGxpY2l0IGhlbHBcbiAgICBjb25zdCBzaG93U2hvcnRIZWxwRmxhZyA9IGNtZC5faGFzSGVscE9wdGlvbiAmJiBjbWQuX2hlbHBTaG9ydEZsYWcgJiYgIWNtZC5fZmluZE9wdGlvbihjbWQuX2hlbHBTaG9ydEZsYWcpO1xuICAgIGNvbnN0IHNob3dMb25nSGVscEZsYWcgPSBjbWQuX2hhc0hlbHBPcHRpb24gJiYgIWNtZC5fZmluZE9wdGlvbihjbWQuX2hlbHBMb25nRmxhZyk7XG4gICAgaWYgKHNob3dTaG9ydEhlbHBGbGFnIHx8IHNob3dMb25nSGVscEZsYWcpIHtcbiAgICAgIGxldCBoZWxwT3B0aW9uO1xuICAgICAgaWYgKCFzaG93U2hvcnRIZWxwRmxhZykge1xuICAgICAgICBoZWxwT3B0aW9uID0gY21kLmNyZWF0ZU9wdGlvbihjbWQuX2hlbHBMb25nRmxhZywgY21kLl9oZWxwRGVzY3JpcHRpb24pO1xuICAgICAgfSBlbHNlIGlmICghc2hvd0xvbmdIZWxwRmxhZykge1xuICAgICAgICBoZWxwT3B0aW9uID0gY21kLmNyZWF0ZU9wdGlvbihjbWQuX2hlbHBTaG9ydEZsYWcsIGNtZC5faGVscERlc2NyaXB0aW9uKTtcbiAgICAgIH0gZWxzZSB7XG4gICAgICAgIGhlbHBPcHRpb24gPSBjbWQuY3JlYXRlT3B0aW9uKGNtZC5faGVscEZsYWdzLCBjbWQuX2hlbHBEZXNjcmlwdGlvbik7XG4gICAgICB9XG4gICAgICB2aXNpYmxlT3B0aW9ucy5wdXNoKGhlbHBPcHRpb24pO1xuICAgIH1cbiAgICBpZiAodGhpcy5zb3J0T3B0aW9ucykge1xuICAgICAgdmlzaWJsZU9wdGlvbnMuc29ydCh0aGlzLmNvbXBhcmVPcHRpb25zKTtcbiAgICB9XG4gICAgcmV0dXJuIHZpc2libGVPcHRpb25zO1xuICB9XG5cbiAgLyoqXG4gICAqIEdldCBhbiBhcnJheSBvZiB0aGUgdmlzaWJsZSBnbG9iYWwgb3B0aW9ucy4gKE5vdCBpbmNsdWRpbmcgaGVscC4pXG4gICAqXG4gICAqIEBwYXJhbSB7Q29tbWFuZH0gY21kXG4gICAqIEByZXR1cm5zIHtPcHRpb25bXX1cbiAgICovXG5cbiAgdmlzaWJsZUdsb2JhbE9wdGlvbnMoY21kKSB7XG4gICAgaWYgKCF0aGlzLnNob3dHbG9iYWxPcHRpb25zKSByZXR1cm4gW107XG5cbiAgICBjb25zdCBnbG9iYWxPcHRpb25zID0gW107XG4gICAgZm9yIChsZXQgcGFyZW50Q21kID0gY21kLnBhcmVudDsgcGFyZW50Q21kOyBwYXJlbnRDbWQgPSBwYXJlbnRDbWQucGFyZW50KSB7XG4gICAgICBjb25zdCB2aXNpYmxlT3B0aW9ucyA9IHBhcmVudENtZC5vcHRpb25zLmZpbHRlcigob3B0aW9uKSA9PiAhb3B0aW9uLmhpZGRlbik7XG4gICAgICBnbG9iYWxPcHRpb25zLnB1c2goLi4udmlzaWJsZU9wdGlvbnMpO1xuICAgIH1cbiAgICBpZiAodGhpcy5zb3J0T3B0aW9ucykge1xuICAgICAgZ2xvYmFsT3B0aW9ucy5zb3J0KHRoaXMuY29tcGFyZU9wdGlvbnMpO1xuICAgIH1cbiAgICByZXR1cm4gZ2xvYmFsT3B0aW9ucztcbiAgfVxuXG4gIC8qKlxuICAgKiBHZXQgYW4gYXJyYXkgb2YgdGhlIGFyZ3VtZW50cyBpZiBhbnkgaGF2ZSBhIGRlc2NyaXB0aW9uLlxuICAgKlxuICAgKiBAcGFyYW0ge0NvbW1hbmR9IGNtZFxuICAgKiBAcmV0dXJucyB7QXJndW1lbnRbXX1cbiAgICovXG5cbiAgdmlzaWJsZUFyZ3VtZW50cyhjbWQpIHtcbiAgICAvLyBTaWRlIGVmZmVjdCEgQXBwbHkgdGhlIGxlZ2FjeSBkZXNjcmlwdGlvbnMgYmVmb3JlIHRoZSBhcmd1bWVudHMgYXJlIGRpc3BsYXllZC5cbiAgICBpZiAoY21kLl9hcmdzRGVzY3JpcHRpb24pIHtcbiAgICAgIGNtZC5fYXJncy5mb3JFYWNoKGFyZ3VtZW50ID0+IHtcbiAgICAgICAgYXJndW1lbnQuZGVzY3JpcHRpb24gPSBhcmd1bWVudC5kZXNjcmlwdGlvbiB8fCBjbWQuX2FyZ3NEZXNjcmlwdGlvblthcmd1bWVudC5uYW1lKCldIHx8ICcnO1xuICAgICAgfSk7XG4gICAgfVxuXG4gICAgLy8gSWYgdGhlcmUgYXJlIGFueSBhcmd1bWVudHMgd2l0aCBhIGRlc2NyaXB0aW9uIHRoZW4gcmV0dXJuIGFsbCB0aGUgYXJndW1lbnRzLlxuICAgIGlmIChjbWQuX2FyZ3MuZmluZChhcmd1bWVudCA9PiBhcmd1bWVudC5kZXNjcmlwdGlvbikpIHtcbiAgICAgIHJldHVybiBjbWQuX2FyZ3M7XG4gICAgfVxuICAgIHJldHVybiBbXTtcbiAgfVxuXG4gIC8qKlxuICAgKiBHZXQgdGhlIGNvbW1hbmQgdGVybSB0byBzaG93IGluIHRoZSBsaXN0IG9mIHN1YmNvbW1hbmRzLlxuICAgKlxuICAgKiBAcGFyYW0ge0NvbW1hbmR9IGNtZFxuICAgKiBAcmV0dXJucyB7c3RyaW5nfVxuICAgKi9cblxuICBzdWJjb21tYW5kVGVybShjbWQpIHtcbiAgICAvLyBMZWdhY3kuIElnbm9yZXMgY3VzdG9tIHVzYWdlIHN0cmluZywgYW5kIG5lc3RlZCBjb21tYW5kcy5cbiAgICBjb25zdCBhcmdzID0gY21kLl9hcmdzLm1hcChhcmcgPT4gaHVtYW5SZWFkYWJsZUFyZ05hbWUoYXJnKSkuam9pbignICcpO1xuICAgIHJldHVybiBjbWQuX25hbWUgK1xuICAgICAgKGNtZC5fYWxpYXNlc1swXSA/ICd8JyArIGNtZC5fYWxpYXNlc1swXSA6ICcnKSArXG4gICAgICAoY21kLm9wdGlvbnMubGVuZ3RoID8gJyBbb3B0aW9uc10nIDogJycpICsgLy8gc2ltcGxpc3RpYyBjaGVjayBmb3Igbm9uLWhlbHAgb3B0aW9uXG4gICAgICAoYXJncyA/ICcgJyArIGFyZ3MgOiAnJyk7XG4gIH1cblxuICAvKipcbiAgICogR2V0IHRoZSBvcHRpb24gdGVybSB0byBzaG93IGluIHRoZSBsaXN0IG9mIG9wdGlvbnMuXG4gICAqXG4gICAqIEBwYXJhbSB7T3B0aW9ufSBvcHRpb25cbiAgICogQHJldHVybnMge3N0cmluZ31cbiAgICovXG5cbiAgb3B0aW9uVGVybShvcHRpb24pIHtcbiAgICByZXR1cm4gb3B0aW9uLmZsYWdzO1xuICB9XG5cbiAgLyoqXG4gICAqIEdldCB0aGUgYXJndW1lbnQgdGVybSB0byBzaG93IGluIHRoZSBsaXN0IG9mIGFyZ3VtZW50cy5cbiAgICpcbiAgICogQHBhcmFtIHtBcmd1bWVudH0gYXJndW1lbnRcbiAgICogQHJldHVybnMge3N0cmluZ31cbiAgICovXG5cbiAgYXJndW1lbnRUZXJtKGFyZ3VtZW50KSB7XG4gICAgcmV0dXJuIGFyZ3VtZW50Lm5hbWUoKTtcbiAgfVxuXG4gIC8qKlxuICAgKiBHZXQgdGhlIGxvbmdlc3QgY29tbWFuZCB0ZXJtIGxlbmd0aC5cbiAgICpcbiAgICogQHBhcmFtIHtDb21tYW5kfSBjbWRcbiAgICogQHBhcmFtIHtIZWxwfSBoZWxwZXJcbiAgICogQHJldHVybnMge251bWJlcn1cbiAgICovXG5cbiAgbG9uZ2VzdFN1YmNvbW1hbmRUZXJtTGVuZ3RoKGNtZCwgaGVscGVyKSB7XG4gICAgcmV0dXJuIGhlbHBlci52aXNpYmxlQ29tbWFuZHMoY21kKS5yZWR1Y2UoKG1heCwgY29tbWFuZCkgPT4ge1xuICAgICAgcmV0dXJuIE1hdGgubWF4KG1heCwgaGVscGVyLnN1YmNvbW1hbmRUZXJtKGNvbW1hbmQpLmxlbmd0aCk7XG4gICAgfSwgMCk7XG4gIH1cblxuICAvKipcbiAgICogR2V0IHRoZSBsb25nZXN0IG9wdGlvbiB0ZXJtIGxlbmd0aC5cbiAgICpcbiAgICogQHBhcmFtIHtDb21tYW5kfSBjbWRcbiAgICogQHBhcmFtIHtIZWxwfSBoZWxwZXJcbiAgICogQHJldHVybnMge251bWJlcn1cbiAgICovXG5cbiAgbG9uZ2VzdE9wdGlvblRlcm1MZW5ndGgoY21kLCBoZWxwZXIpIHtcbiAgICByZXR1cm4gaGVscGVyLnZpc2libGVPcHRpb25zKGNtZCkucmVkdWNlKChtYXgsIG9wdGlvbikgPT4ge1xuICAgICAgcmV0dXJuIE1hdGgubWF4KG1heCwgaGVscGVyLm9wdGlvblRlcm0ob3B0aW9uKS5sZW5ndGgpO1xuICAgIH0sIDApO1xuICB9XG5cbiAgLyoqXG4gICAqIEdldCB0aGUgbG9uZ2VzdCBnbG9iYWwgb3B0aW9uIHRlcm0gbGVuZ3RoLlxuICAgKlxuICAgKiBAcGFyYW0ge0NvbW1hbmR9IGNtZFxuICAgKiBAcGFyYW0ge0hlbHB9IGhlbHBlclxuICAgKiBAcmV0dXJucyB7bnVtYmVyfVxuICAgKi9cblxuICBsb25nZXN0R2xvYmFsT3B0aW9uVGVybUxlbmd0aChjbWQsIGhlbHBlcikge1xuICAgIHJldHVybiBoZWxwZXIudmlzaWJsZUdsb2JhbE9wdGlvbnMoY21kKS5yZWR1Y2UoKG1heCwgb3B0aW9uKSA9PiB7XG4gICAgICByZXR1cm4gTWF0aC5tYXgobWF4LCBoZWxwZXIub3B0aW9uVGVybShvcHRpb24pLmxlbmd0aCk7XG4gICAgfSwgMCk7XG4gIH1cblxuICAvKipcbiAgICogR2V0IHRoZSBsb25nZXN0IGFyZ3VtZW50IHRlcm0gbGVuZ3RoLlxuICAgKlxuICAgKiBAcGFyYW0ge0NvbW1hbmR9IGNtZFxuICAgKiBAcGFyYW0ge0hlbHB9IGhlbHBlclxuICAgKiBAcmV0dXJucyB7bnVtYmVyfVxuICAgKi9cblxuICBsb25nZXN0QXJndW1lbnRUZXJtTGVuZ3RoKGNtZCwgaGVscGVyKSB7XG4gICAgcmV0dXJuIGhlbHBlci52aXNpYmxlQXJndW1lbnRzKGNtZCkucmVkdWNlKChtYXgsIGFyZ3VtZW50KSA9PiB7XG4gICAgICByZXR1cm4gTWF0aC5tYXgobWF4LCBoZWxwZXIuYXJndW1lbnRUZXJtKGFyZ3VtZW50KS5sZW5ndGgpO1xuICAgIH0sIDApO1xuICB9XG5cbiAgLyoqXG4gICAqIEdldCB0aGUgY29tbWFuZCB1c2FnZSB0byBiZSBkaXNwbGF5ZWQgYXQgdGhlIHRvcCBvZiB0aGUgYnVpbHQtaW4gaGVscC5cbiAgICpcbiAgICogQHBhcmFtIHtDb21tYW5kfSBjbWRcbiAgICogQHJldHVybnMge3N0cmluZ31cbiAgICovXG5cbiAgY29tbWFuZFVzYWdlKGNtZCkge1xuICAgIC8vIFVzYWdlXG4gICAgbGV0IGNtZE5hbWUgPSBjbWQuX25hbWU7XG4gICAgaWYgKGNtZC5fYWxpYXNlc1swXSkge1xuICAgICAgY21kTmFtZSA9IGNtZE5hbWUgKyAnfCcgKyBjbWQuX2FsaWFzZXNbMF07XG4gICAgfVxuICAgIGxldCBwYXJlbnRDbWROYW1lcyA9ICcnO1xuICAgIGZvciAobGV0IHBhcmVudENtZCA9IGNtZC5wYXJlbnQ7IHBhcmVudENtZDsgcGFyZW50Q21kID0gcGFyZW50Q21kLnBhcmVudCkge1xuICAgICAgcGFyZW50Q21kTmFtZXMgPSBwYXJlbnRDbWQubmFtZSgpICsgJyAnICsgcGFyZW50Q21kTmFtZXM7XG4gICAgfVxuICAgIHJldHVybiBwYXJlbnRDbWROYW1lcyArIGNtZE5hbWUgKyAnICcgKyBjbWQudXNhZ2UoKTtcbiAgfVxuXG4gIC8qKlxuICAgKiBHZXQgdGhlIGRlc2NyaXB0aW9uIGZvciB0aGUgY29tbWFuZC5cbiAgICpcbiAgICogQHBhcmFtIHtDb21tYW5kfSBjbWRcbiAgICogQHJldHVybnMge3N0cmluZ31cbiAgICovXG5cbiAgY29tbWFuZERlc2NyaXB0aW9uKGNtZCkge1xuICAgIC8vIEB0cy1pZ25vcmU6IG92ZXJsb2FkZWQgcmV0dXJuIHR5cGVcbiAgICByZXR1cm4gY21kLmRlc2NyaXB0aW9uKCk7XG4gIH1cblxuICAvKipcbiAgICogR2V0IHRoZSBzdWJjb21tYW5kIHN1bW1hcnkgdG8gc2hvdyBpbiB0aGUgbGlzdCBvZiBzdWJjb21tYW5kcy5cbiAgICogKEZhbGxiYWNrIHRvIGRlc2NyaXB0aW9uIGZvciBiYWNrd2FyZHMgY29tcGF0aWJpbGl0eS4pXG4gICAqXG4gICAqIEBwYXJhbSB7Q29tbWFuZH0gY21kXG4gICAqIEByZXR1cm5zIHtzdHJpbmd9XG4gICAqL1xuXG4gIHN1YmNvbW1hbmREZXNjcmlwdGlvbihjbWQpIHtcbiAgICAvLyBAdHMtaWdub3JlOiBvdmVybG9hZGVkIHJldHVybiB0eXBlXG4gICAgcmV0dXJuIGNtZC5zdW1tYXJ5KCkgfHwgY21kLmRlc2NyaXB0aW9uKCk7XG4gIH1cblxuICAvKipcbiAgICogR2V0IHRoZSBvcHRpb24gZGVzY3JpcHRpb24gdG8gc2hvdyBpbiB0aGUgbGlzdCBvZiBvcHRpb25zLlxuICAgKlxuICAgKiBAcGFyYW0ge09wdGlvbn0gb3B0aW9uXG4gICAqIEByZXR1cm4ge3N0cmluZ31cbiAgICovXG5cbiAgb3B0aW9uRGVzY3JpcHRpb24ob3B0aW9uKSB7XG4gICAgY29uc3QgZXh0cmFJbmZvID0gW107XG5cbiAgICBpZiAob3B0aW9uLmFyZ0Nob2ljZXMpIHtcbiAgICAgIGV4dHJhSW5mby5wdXNoKFxuICAgICAgICAvLyB1c2Ugc3RyaW5naWZ5IHRvIG1hdGNoIHRoZSBkaXNwbGF5IG9mIHRoZSBkZWZhdWx0IHZhbHVlXG4gICAgICAgIGBjaG9pY2VzOiAke29wdGlvbi5hcmdDaG9pY2VzLm1hcCgoY2hvaWNlKSA9PiBKU09OLnN0cmluZ2lmeShjaG9pY2UpKS5qb2luKCcsICcpfWApO1xuICAgIH1cbiAgICBpZiAob3B0aW9uLmRlZmF1bHRWYWx1ZSAhPT0gdW5kZWZpbmVkKSB7XG4gICAgICAvLyBkZWZhdWx0IGZvciBib29sZWFuIGFuZCBuZWdhdGVkIG1vcmUgZm9yIHByb2dyYW1tZXIgdGhhbiBlbmQgdXNlcixcbiAgICAgIC8vIGJ1dCBzaG93IHRydWUvZmFsc2UgZm9yIGJvb2xlYW4gb3B0aW9uIGFzIG1heSBiZSBmb3IgaGFuZC1yb2xsZWQgZW52IG9yIGNvbmZpZyBwcm9jZXNzaW5nLlxuICAgICAgY29uc3Qgc2hvd0RlZmF1bHQgPSBvcHRpb24ucmVxdWlyZWQgfHwgb3B0aW9uLm9wdGlvbmFsIHx8XG4gICAgICAgIChvcHRpb24uaXNCb29sZWFuKCkgJiYgdHlwZW9mIG9wdGlvbi5kZWZhdWx0VmFsdWUgPT09ICdib29sZWFuJyk7XG4gICAgICBpZiAoc2hvd0RlZmF1bHQpIHtcbiAgICAgICAgZXh0cmFJbmZvLnB1c2goYGRlZmF1bHQ6ICR7b3B0aW9uLmRlZmF1bHRWYWx1ZURlc2NyaXB0aW9uIHx8IEpTT04uc3RyaW5naWZ5KG9wdGlvbi5kZWZhdWx0VmFsdWUpfWApO1xuICAgICAgfVxuICAgIH1cbiAgICAvLyBwcmVzZXQgZm9yIGJvb2xlYW4gYW5kIG5lZ2F0ZWQgYXJlIG1vcmUgZm9yIHByb2dyYW1tZXIgdGhhbiBlbmQgdXNlclxuICAgIGlmIChvcHRpb24ucHJlc2V0QXJnICE9PSB1bmRlZmluZWQgJiYgb3B0aW9uLm9wdGlvbmFsKSB7XG4gICAgICBleHRyYUluZm8ucHVzaChgcHJlc2V0OiAke0pTT04uc3RyaW5naWZ5KG9wdGlvbi5wcmVzZXRBcmcpfWApO1xuICAgIH1cbiAgICBpZiAob3B0aW9uLmVudlZhciAhPT0gdW5kZWZpbmVkKSB7XG4gICAgICBleHRyYUluZm8ucHVzaChgZW52OiAke29wdGlvbi5lbnZWYXJ9YCk7XG4gICAgfVxuICAgIGlmIChleHRyYUluZm8ubGVuZ3RoID4gMCkge1xuICAgICAgcmV0dXJuIGAke29wdGlvbi5kZXNjcmlwdGlvbn0gKCR7ZXh0cmFJbmZvLmpvaW4oJywgJyl9KWA7XG4gICAgfVxuXG4gICAgcmV0dXJuIG9wdGlvbi5kZXNjcmlwdGlvbjtcbiAgfVxuXG4gIC8qKlxuICAgKiBHZXQgdGhlIGFyZ3VtZW50IGRlc2NyaXB0aW9uIHRvIHNob3cgaW4gdGhlIGxpc3Qgb2YgYXJndW1lbnRzLlxuICAgKlxuICAgKiBAcGFyYW0ge0FyZ3VtZW50fSBhcmd1bWVudFxuICAgKiBAcmV0dXJuIHtzdHJpbmd9XG4gICAqL1xuXG4gIGFyZ3VtZW50RGVzY3JpcHRpb24oYXJndW1lbnQpIHtcbiAgICBjb25zdCBleHRyYUluZm8gPSBbXTtcbiAgICBpZiAoYXJndW1lbnQuYXJnQ2hvaWNlcykge1xuICAgICAgZXh0cmFJbmZvLnB1c2goXG4gICAgICAgIC8vIHVzZSBzdHJpbmdpZnkgdG8gbWF0Y2ggdGhlIGRpc3BsYXkgb2YgdGhlIGRlZmF1bHQgdmFsdWVcbiAgICAgICAgYGNob2ljZXM6ICR7YXJndW1lbnQuYXJnQ2hvaWNlcy5tYXAoKGNob2ljZSkgPT4gSlNPTi5zdHJpbmdpZnkoY2hvaWNlKSkuam9pbignLCAnKX1gKTtcbiAgICB9XG4gICAgaWYgKGFyZ3VtZW50LmRlZmF1bHRWYWx1ZSAhPT0gdW5kZWZpbmVkKSB7XG4gICAgICBleHRyYUluZm8ucHVzaChgZGVmYXVsdDogJHthcmd1bWVudC5kZWZhdWx0VmFsdWVEZXNjcmlwdGlvbiB8fCBKU09OLnN0cmluZ2lmeShhcmd1bWVudC5kZWZhdWx0VmFsdWUpfWApO1xuICAgIH1cbiAgICBpZiAoZXh0cmFJbmZvLmxlbmd0aCA+IDApIHtcbiAgICAgIGNvbnN0IGV4dHJhRGVzY3JpcHRvbiA9IGAoJHtleHRyYUluZm8uam9pbignLCAnKX0pYDtcbiAgICAgIGlmIChhcmd1bWVudC5kZXNjcmlwdGlvbikge1xuICAgICAgICByZXR1cm4gYCR7YXJndW1lbnQuZGVzY3JpcHRpb259ICR7ZXh0cmFEZXNjcmlwdG9ufWA7XG4gICAgICB9XG4gICAgICByZXR1cm4gZXh0cmFEZXNjcmlwdG9uO1xuICAgIH1cbiAgICByZXR1cm4gYXJndW1lbnQuZGVzY3JpcHRpb247XG4gIH1cblxuICAvKipcbiAgICogR2VuZXJhdGUgdGhlIGJ1aWx0LWluIGhlbHAgdGV4dC5cbiAgICpcbiAgICogQHBhcmFtIHtDb21tYW5kfSBjbWRcbiAgICogQHBhcmFtIHtIZWxwfSBoZWxwZXJcbiAgICogQHJldHVybnMge3N0cmluZ31cbiAgICovXG5cbiAgZm9ybWF0SGVscChjbWQsIGhlbHBlcikge1xuICAgIGNvbnN0IHRlcm1XaWR0aCA9IGhlbHBlci5wYWRXaWR0aChjbWQsIGhlbHBlcik7XG4gICAgY29uc3QgaGVscFdpZHRoID0gaGVscGVyLmhlbHBXaWR0aCB8fCA4MDtcbiAgICBjb25zdCBpdGVtSW5kZW50V2lkdGggPSAyO1xuICAgIGNvbnN0IGl0ZW1TZXBhcmF0b3JXaWR0aCA9IDI7IC8vIGJldHdlZW4gdGVybSBhbmQgZGVzY3JpcHRpb25cbiAgICBmdW5jdGlvbiBmb3JtYXRJdGVtKHRlcm0sIGRlc2NyaXB0aW9uKSB7XG4gICAgICBpZiAoZGVzY3JpcHRpb24pIHtcbiAgICAgICAgY29uc3QgZnVsbFRleHQgPSBgJHt0ZXJtLnBhZEVuZCh0ZXJtV2lkdGggKyBpdGVtU2VwYXJhdG9yV2lkdGgpfSR7ZGVzY3JpcHRpb259YDtcbiAgICAgICAgcmV0dXJuIGhlbHBlci53cmFwKGZ1bGxUZXh0LCBoZWxwV2lkdGggLSBpdGVtSW5kZW50V2lkdGgsIHRlcm1XaWR0aCArIGl0ZW1TZXBhcmF0b3JXaWR0aCk7XG4gICAgICB9XG4gICAgICByZXR1cm4gdGVybTtcbiAgICB9XG4gICAgZnVuY3Rpb24gZm9ybWF0TGlzdCh0ZXh0QXJyYXkpIHtcbiAgICAgIHJldHVybiB0ZXh0QXJyYXkuam9pbignXFxuJykucmVwbGFjZSgvXi9nbSwgJyAnLnJlcGVhdChpdGVtSW5kZW50V2lkdGgpKTtcbiAgICB9XG5cbiAgICAvLyBVc2FnZVxuICAgIGxldCBvdXRwdXQgPSBbYFVzYWdlOiAke2hlbHBlci5jb21tYW5kVXNhZ2UoY21kKX1gLCAnJ107XG5cbiAgICAvLyBEZXNjcmlwdGlvblxuICAgIGNvbnN0IGNvbW1hbmREZXNjcmlwdGlvbiA9IGhlbHBlci5jb21tYW5kRGVzY3JpcHRpb24oY21kKTtcbiAgICBpZiAoY29tbWFuZERlc2NyaXB0aW9uLmxlbmd0aCA+IDApIHtcbiAgICAgIG91dHB1dCA9IG91dHB1dC5jb25jYXQoW2hlbHBlci53cmFwKGNvbW1hbmREZXNjcmlwdGlvbiwgaGVscFdpZHRoLCAwKSwgJyddKTtcbiAgICB9XG5cbiAgICAvLyBBcmd1bWVudHNcbiAgICBjb25zdCBhcmd1bWVudExpc3QgPSBoZWxwZXIudmlzaWJsZUFyZ3VtZW50cyhjbWQpLm1hcCgoYXJndW1lbnQpID0+IHtcbiAgICAgIHJldHVybiBmb3JtYXRJdGVtKGhlbHBlci5hcmd1bWVudFRlcm0oYXJndW1lbnQpLCBoZWxwZXIuYXJndW1lbnREZXNjcmlwdGlvbihhcmd1bWVudCkpO1xuICAgIH0pO1xuICAgIGlmIChhcmd1bWVudExpc3QubGVuZ3RoID4gMCkge1xuICAgICAgb3V0cHV0ID0gb3V0cHV0LmNvbmNhdChbJ0FyZ3VtZW50czonLCBmb3JtYXRMaXN0KGFyZ3VtZW50TGlzdCksICcnXSk7XG4gICAgfVxuXG4gICAgLy8gT3B0aW9uc1xuICAgIGNvbnN0IG9wdGlvbkxpc3QgPSBoZWxwZXIudmlzaWJsZU9wdGlvbnMoY21kKS5tYXAoKG9wdGlvbikgPT4ge1xuICAgICAgcmV0dXJuIGZvcm1hdEl0ZW0oaGVscGVyLm9wdGlvblRlcm0ob3B0aW9uKSwgaGVscGVyLm9wdGlvbkRlc2NyaXB0aW9uKG9wdGlvbikpO1xuICAgIH0pO1xuICAgIGlmIChvcHRpb25MaXN0Lmxlbmd0aCA+IDApIHtcbiAgICAgIG91dHB1dCA9IG91dHB1dC5jb25jYXQoWydPcHRpb25zOicsIGZvcm1hdExpc3Qob3B0aW9uTGlzdCksICcnXSk7XG4gICAgfVxuXG4gICAgaWYgKHRoaXMuc2hvd0dsb2JhbE9wdGlvbnMpIHtcbiAgICAgIGNvbnN0IGdsb2JhbE9wdGlvbkxpc3QgPSBoZWxwZXIudmlzaWJsZUdsb2JhbE9wdGlvbnMoY21kKS5tYXAoKG9wdGlvbikgPT4ge1xuICAgICAgICByZXR1cm4gZm9ybWF0SXRlbShoZWxwZXIub3B0aW9uVGVybShvcHRpb24pLCBoZWxwZXIub3B0aW9uRGVzY3JpcHRpb24ob3B0aW9uKSk7XG4gICAgICB9KTtcbiAgICAgIGlmIChnbG9iYWxPcHRpb25MaXN0Lmxlbmd0aCA+IDApIHtcbiAgICAgICAgb3V0cHV0ID0gb3V0cHV0LmNvbmNhdChbJ0dsb2JhbCBPcHRpb25zOicsIGZvcm1hdExpc3QoZ2xvYmFsT3B0aW9uTGlzdCksICcnXSk7XG4gICAgICB9XG4gICAgfVxuXG4gICAgLy8gQ29tbWFuZHNcbiAgICBjb25zdCBjb21tYW5kTGlzdCA9IGhlbHBlci52aXNpYmxlQ29tbWFuZHMoY21kKS5tYXAoKGNtZCkgPT4ge1xuICAgICAgcmV0dXJuIGZvcm1hdEl0ZW0oaGVscGVyLnN1YmNvbW1hbmRUZXJtKGNtZCksIGhlbHBlci5zdWJjb21tYW5kRGVzY3JpcHRpb24oY21kKSk7XG4gICAgfSk7XG4gICAgaWYgKGNvbW1hbmRMaXN0Lmxlbmd0aCA+IDApIHtcbiAgICAgIG91dHB1dCA9IG91dHB1dC5jb25jYXQoWydDb21tYW5kczonLCBmb3JtYXRMaXN0KGNvbW1hbmRMaXN0KSwgJyddKTtcbiAgICB9XG5cbiAgICByZXR1cm4gb3V0cHV0LmpvaW4oJ1xcbicpO1xuICB9XG5cbiAgLyoqXG4gICAqIENhbGN1bGF0ZSB0aGUgcGFkIHdpZHRoIGZyb20gdGhlIG1heGltdW0gdGVybSBsZW5ndGguXG4gICAqXG4gICAqIEBwYXJhbSB7Q29tbWFuZH0gY21kXG4gICAqIEBwYXJhbSB7SGVscH0gaGVscGVyXG4gICAqIEByZXR1cm5zIHtudW1iZXJ9XG4gICAqL1xuXG4gIHBhZFdpZHRoKGNtZCwgaGVscGVyKSB7XG4gICAgcmV0dXJuIE1hdGgubWF4KFxuICAgICAgaGVscGVyLmxvbmdlc3RPcHRpb25UZXJtTGVuZ3RoKGNtZCwgaGVscGVyKSxcbiAgICAgIGhlbHBlci5sb25nZXN0R2xvYmFsT3B0aW9uVGVybUxlbmd0aChjbWQsIGhlbHBlciksXG4gICAgICBoZWxwZXIubG9uZ2VzdFN1YmNvbW1hbmRUZXJtTGVuZ3RoKGNtZCwgaGVscGVyKSxcbiAgICAgIGhlbHBlci5sb25nZXN0QXJndW1lbnRUZXJtTGVuZ3RoKGNtZCwgaGVscGVyKVxuICAgICk7XG4gIH1cblxuICAvKipcbiAgICogV3JhcCB0aGUgZ2l2ZW4gc3RyaW5nIHRvIHdpZHRoIGNoYXJhY3RlcnMgcGVyIGxpbmUsIHdpdGggbGluZXMgYWZ0ZXIgdGhlIGZpcnN0IGluZGVudGVkLlxuICAgKiBEbyBub3Qgd3JhcCBpZiBpbnN1ZmZpY2llbnQgcm9vbSBmb3Igd3JhcHBpbmcgKG1pbkNvbHVtbldpZHRoKSwgb3Igc3RyaW5nIGlzIG1hbnVhbGx5IGZvcm1hdHRlZC5cbiAgICpcbiAgICogQHBhcmFtIHtzdHJpbmd9IHN0clxuICAgKiBAcGFyYW0ge251bWJlcn0gd2lkdGhcbiAgICogQHBhcmFtIHtudW1iZXJ9IGluZGVudFxuICAgKiBAcGFyYW0ge251bWJlcn0gW21pbkNvbHVtbldpZHRoPTQwXVxuICAgKiBAcmV0dXJuIHtzdHJpbmd9XG4gICAqXG4gICAqL1xuXG4gIHdyYXAoc3RyLCB3aWR0aCwgaW5kZW50LCBtaW5Db2x1bW5XaWR0aCA9IDQwKSB7XG4gICAgLy8gRnVsbCBcXHMgY2hhcmFjdGVycywgbWludXMgdGhlIGxpbmVmZWVkcy5cbiAgICBjb25zdCBpbmRlbnRzID0gJyBcXFxcZlxcXFx0XFxcXHZcXHUwMGEwXFx1MTY4MFxcdTIwMDAtXFx1MjAwYVxcdTIwMmZcXHUyMDVmXFx1MzAwMFxcdWZlZmYnO1xuICAgIC8vIERldGVjdCBtYW51YWxseSB3cmFwcGVkIGFuZCBpbmRlbnRlZCBzdHJpbmdzIGJ5IHNlYXJjaGluZyBmb3IgbGluZSBicmVhayBmb2xsb3dlZCBieSBzcGFjZXMuXG4gICAgY29uc3QgbWFudWFsSW5kZW50ID0gbmV3IFJlZ0V4cChgW1xcXFxuXVske2luZGVudHN9XStgKTtcbiAgICBpZiAoc3RyLm1hdGNoKG1hbnVhbEluZGVudCkpIHJldHVybiBzdHI7XG4gICAgLy8gRG8gbm90IHdyYXAgaWYgbm90IGVub3VnaCByb29tIGZvciBhIHdyYXBwZWQgY29sdW1uIG9mIHRleHQgKGFzIGNvdWxkIGVuZCB1cCB3aXRoIGEgd29yZCBwZXIgbGluZSkuXG4gICAgY29uc3QgY29sdW1uV2lkdGggPSB3aWR0aCAtIGluZGVudDtcbiAgICBpZiAoY29sdW1uV2lkdGggPCBtaW5Db2x1bW5XaWR0aCkgcmV0dXJuIHN0cjtcblxuICAgIGNvbnN0IGxlYWRpbmdTdHIgPSBzdHIuc2xpY2UoMCwgaW5kZW50KTtcbiAgICBjb25zdCBjb2x1bW5UZXh0ID0gc3RyLnNsaWNlKGluZGVudCkucmVwbGFjZSgnXFxyXFxuJywgJ1xcbicpO1xuICAgIGNvbnN0IGluZGVudFN0cmluZyA9ICcgJy5yZXBlYXQoaW5kZW50KTtcbiAgICBjb25zdCB6ZXJvV2lkdGhTcGFjZSA9ICdcXHUyMDBCJztcbiAgICBjb25zdCBicmVha3MgPSBgXFxcXHMke3plcm9XaWR0aFNwYWNlfWA7XG4gICAgLy8gTWF0Y2ggbGluZSBlbmQgKHNvIGVtcHR5IGxpbmVzIGRvbid0IGNvbGxhcHNlKSxcbiAgICAvLyBvciBhcyBtdWNoIHRleHQgYXMgd2lsbCBmaXQgaW4gY29sdW1uLCBvciBleGNlc3MgdGV4dCB1cCB0byBmaXJzdCBicmVhay5cbiAgICBjb25zdCByZWdleCA9IG5ldyBSZWdFeHAoYFxcbnwuezEsJHtjb2x1bW5XaWR0aCAtIDF9fShbJHticmVha3N9XXwkKXxbXiR7YnJlYWtzfV0rPyhbJHticmVha3N9XXwkKWAsICdnJyk7XG4gICAgY29uc3QgbGluZXMgPSBjb2x1bW5UZXh0Lm1hdGNoKHJlZ2V4KSB8fCBbXTtcbiAgICByZXR1cm4gbGVhZGluZ1N0ciArIGxpbmVzLm1hcCgobGluZSwgaSkgPT4ge1xuICAgICAgaWYgKGxpbmUgPT09ICdcXG4nKSByZXR1cm4gJyc7IC8vIHByZXNlcnZlIGVtcHR5IGxpbmVzXG4gICAgICByZXR1cm4gKChpID4gMCkgPyBpbmRlbnRTdHJpbmcgOiAnJykgKyBsaW5lLnRyaW1FbmQoKTtcbiAgICB9KS5qb2luKCdcXG4nKTtcbiAgfVxufVxuXG5leHBvcnRzLkhlbHAgPSBIZWxwO1xuIiwiY29uc3QgeyBJbnZhbGlkQXJndW1lbnRFcnJvciB9ID0gcmVxdWlyZSgnLi9lcnJvci5qcycpO1xuXG4vLyBAdHMtY2hlY2tcblxuY2xhc3MgT3B0aW9uIHtcbiAgLyoqXG4gICAqIEluaXRpYWxpemUgYSBuZXcgYE9wdGlvbmAgd2l0aCB0aGUgZ2l2ZW4gYGZsYWdzYCBhbmQgYGRlc2NyaXB0aW9uYC5cbiAgICpcbiAgICogQHBhcmFtIHtzdHJpbmd9IGZsYWdzXG4gICAqIEBwYXJhbSB7c3RyaW5nfSBbZGVzY3JpcHRpb25dXG4gICAqL1xuXG4gIGNvbnN0cnVjdG9yKGZsYWdzLCBkZXNjcmlwdGlvbikge1xuICAgIHRoaXMuZmxhZ3MgPSBmbGFncztcbiAgICB0aGlzLmRlc2NyaXB0aW9uID0gZGVzY3JpcHRpb24gfHwgJyc7XG5cbiAgICB0aGlzLnJlcXVpcmVkID0gZmxhZ3MuaW5jbHVkZXMoJzwnKTsgLy8gQSB2YWx1ZSBtdXN0IGJlIHN1cHBsaWVkIHdoZW4gdGhlIG9wdGlvbiBpcyBzcGVjaWZpZWQuXG4gICAgdGhpcy5vcHRpb25hbCA9IGZsYWdzLmluY2x1ZGVzKCdbJyk7IC8vIEEgdmFsdWUgaXMgb3B0aW9uYWwgd2hlbiB0aGUgb3B0aW9uIGlzIHNwZWNpZmllZC5cbiAgICAvLyB2YXJpYWRpYyB0ZXN0IGlnbm9yZXMgPHZhbHVlLC4uLj4gZXQgYWwgd2hpY2ggbWlnaHQgYmUgdXNlZCB0byBkZXNjcmliZSBjdXN0b20gc3BsaXR0aW5nIG9mIHNpbmdsZSBhcmd1bWVudFxuICAgIHRoaXMudmFyaWFkaWMgPSAvXFx3XFwuXFwuXFwuWz5cXF1dJC8udGVzdChmbGFncyk7IC8vIFRoZSBvcHRpb24gY2FuIHRha2UgbXVsdGlwbGUgdmFsdWVzLlxuICAgIHRoaXMubWFuZGF0b3J5ID0gZmFsc2U7IC8vIFRoZSBvcHRpb24gbXVzdCBoYXZlIGEgdmFsdWUgYWZ0ZXIgcGFyc2luZywgd2hpY2ggdXN1YWxseSBtZWFucyBpdCBtdXN0IGJlIHNwZWNpZmllZCBvbiBjb21tYW5kIGxpbmUuXG4gICAgY29uc3Qgb3B0aW9uRmxhZ3MgPSBzcGxpdE9wdGlvbkZsYWdzKGZsYWdzKTtcbiAgICB0aGlzLnNob3J0ID0gb3B0aW9uRmxhZ3Muc2hvcnRGbGFnO1xuICAgIHRoaXMubG9uZyA9IG9wdGlvbkZsYWdzLmxvbmdGbGFnO1xuICAgIHRoaXMubmVnYXRlID0gZmFsc2U7XG4gICAgaWYgKHRoaXMubG9uZykge1xuICAgICAgdGhpcy5uZWdhdGUgPSB0aGlzLmxvbmcuc3RhcnRzV2l0aCgnLS1uby0nKTtcbiAgICB9XG4gICAgdGhpcy5kZWZhdWx0VmFsdWUgPSB1bmRlZmluZWQ7XG4gICAgdGhpcy5kZWZhdWx0VmFsdWVEZXNjcmlwdGlvbiA9IHVuZGVmaW5lZDtcbiAgICB0aGlzLnByZXNldEFyZyA9IHVuZGVmaW5lZDtcbiAgICB0aGlzLmVudlZhciA9IHVuZGVmaW5lZDtcbiAgICB0aGlzLnBhcnNlQXJnID0gdW5kZWZpbmVkO1xuICAgIHRoaXMuaGlkZGVuID0gZmFsc2U7XG4gICAgdGhpcy5hcmdDaG9pY2VzID0gdW5kZWZpbmVkO1xuICAgIHRoaXMuY29uZmxpY3RzV2l0aCA9IFtdO1xuICAgIHRoaXMuaW1wbGllZCA9IHVuZGVmaW5lZDtcbiAgfVxuXG4gIC8qKlxuICAgKiBTZXQgdGhlIGRlZmF1bHQgdmFsdWUsIGFuZCBvcHRpb25hbGx5IHN1cHBseSB0aGUgZGVzY3JpcHRpb24gdG8gYmUgZGlzcGxheWVkIGluIHRoZSBoZWxwLlxuICAgKlxuICAgKiBAcGFyYW0ge2FueX0gdmFsdWVcbiAgICogQHBhcmFtIHtzdHJpbmd9IFtkZXNjcmlwdGlvbl1cbiAgICogQHJldHVybiB7T3B0aW9ufVxuICAgKi9cblxuICBkZWZhdWx0KHZhbHVlLCBkZXNjcmlwdGlvbikge1xuICAgIHRoaXMuZGVmYXVsdFZhbHVlID0gdmFsdWU7XG4gICAgdGhpcy5kZWZhdWx0VmFsdWVEZXNjcmlwdGlvbiA9IGRlc2NyaXB0aW9uO1xuICAgIHJldHVybiB0aGlzO1xuICB9XG5cbiAgLyoqXG4gICAqIFByZXNldCB0byB1c2Ugd2hlbiBvcHRpb24gdXNlZCB3aXRob3V0IG9wdGlvbi1hcmd1bWVudCwgZXNwZWNpYWxseSBvcHRpb25hbCBidXQgYWxzbyBib29sZWFuIGFuZCBuZWdhdGVkLlxuICAgKiBUaGUgY3VzdG9tIHByb2Nlc3NpbmcgKHBhcnNlQXJnKSBpcyBjYWxsZWQuXG4gICAqXG4gICAqIEBleGFtcGxlXG4gICAqIG5ldyBPcHRpb24oJy0tY29sb3InKS5kZWZhdWx0KCdHUkVZU0NBTEUnKS5wcmVzZXQoJ1JHQicpO1xuICAgKiBuZXcgT3B0aW9uKCctLWRvbmF0ZSBbYW1vdW50XScpLnByZXNldCgnMjAnKS5hcmdQYXJzZXIocGFyc2VGbG9hdCk7XG4gICAqXG4gICAqIEBwYXJhbSB7YW55fSBhcmdcbiAgICogQHJldHVybiB7T3B0aW9ufVxuICAgKi9cblxuICBwcmVzZXQoYXJnKSB7XG4gICAgdGhpcy5wcmVzZXRBcmcgPSBhcmc7XG4gICAgcmV0dXJuIHRoaXM7XG4gIH1cblxuICAvKipcbiAgICogQWRkIG9wdGlvbiBuYW1lKHMpIHRoYXQgY29uZmxpY3Qgd2l0aCB0aGlzIG9wdGlvbi5cbiAgICogQW4gZXJyb3Igd2lsbCBiZSBkaXNwbGF5ZWQgaWYgY29uZmxpY3Rpbmcgb3B0aW9ucyBhcmUgZm91bmQgZHVyaW5nIHBhcnNpbmcuXG4gICAqXG4gICAqIEBleGFtcGxlXG4gICAqIG5ldyBPcHRpb24oJy0tcmdiJykuY29uZmxpY3RzKCdjbXlrJyk7XG4gICAqIG5ldyBPcHRpb24oJy0tanMnKS5jb25mbGljdHMoWyd0cycsICdqc3gnXSk7XG4gICAqXG4gICAqIEBwYXJhbSB7c3RyaW5nIHwgc3RyaW5nW119IG5hbWVzXG4gICAqIEByZXR1cm4ge09wdGlvbn1cbiAgICovXG5cbiAgY29uZmxpY3RzKG5hbWVzKSB7XG4gICAgdGhpcy5jb25mbGljdHNXaXRoID0gdGhpcy5jb25mbGljdHNXaXRoLmNvbmNhdChuYW1lcyk7XG4gICAgcmV0dXJuIHRoaXM7XG4gIH1cblxuICAvKipcbiAgICogU3BlY2lmeSBpbXBsaWVkIG9wdGlvbiB2YWx1ZXMgZm9yIHdoZW4gdGhpcyBvcHRpb24gaXMgc2V0IGFuZCB0aGUgaW1wbGllZCBvcHRpb25zIGFyZSBub3QuXG4gICAqXG4gICAqIFRoZSBjdXN0b20gcHJvY2Vzc2luZyAocGFyc2VBcmcpIGlzIG5vdCBjYWxsZWQgb24gdGhlIGltcGxpZWQgdmFsdWVzLlxuICAgKlxuICAgKiBAZXhhbXBsZVxuICAgKiBwcm9ncmFtXG4gICAqICAgLmFkZE9wdGlvbihuZXcgT3B0aW9uKCctLWxvZycsICd3cml0ZSBsb2dnaW5nIGluZm9ybWF0aW9uIHRvIGZpbGUnKSlcbiAgICogICAuYWRkT3B0aW9uKG5ldyBPcHRpb24oJy0tdHJhY2UnLCAnbG9nIGV4dHJhIGRldGFpbHMnKS5pbXBsaWVzKHsgbG9nOiAndHJhY2UudHh0JyB9KSk7XG4gICAqXG4gICAqIEBwYXJhbSB7T2JqZWN0fSBpbXBsaWVkT3B0aW9uVmFsdWVzXG4gICAqIEByZXR1cm4ge09wdGlvbn1cbiAgICovXG4gIGltcGxpZXMoaW1wbGllZE9wdGlvblZhbHVlcykge1xuICAgIGxldCBuZXdJbXBsaWVkID0gaW1wbGllZE9wdGlvblZhbHVlcztcbiAgICBpZiAodHlwZW9mIGltcGxpZWRPcHRpb25WYWx1ZXMgPT09ICdzdHJpbmcnKSB7XG4gICAgICAvLyBzdHJpbmcgaXMgbm90IGRvY3VtZW50ZWQsIGJ1dCBlYXN5IG1pc3Rha2UgYW5kIHdlIGNhbiBkbyB3aGF0IHVzZXIgcHJvYmFibHkgaW50ZW5kZWQuXG4gICAgICBuZXdJbXBsaWVkID0geyBbaW1wbGllZE9wdGlvblZhbHVlc106IHRydWUgfTtcbiAgICB9XG4gICAgdGhpcy5pbXBsaWVkID0gT2JqZWN0LmFzc2lnbih0aGlzLmltcGxpZWQgfHwge30sIG5ld0ltcGxpZWQpO1xuICAgIHJldHVybiB0aGlzO1xuICB9XG5cbiAgLyoqXG4gICAqIFNldCBlbnZpcm9ubWVudCB2YXJpYWJsZSB0byBjaGVjayBmb3Igb3B0aW9uIHZhbHVlLlxuICAgKlxuICAgKiBBbiBlbnZpcm9ubWVudCB2YXJpYWJsZSBpcyBvbmx5IHVzZWQgaWYgd2hlbiBwcm9jZXNzZWQgdGhlIGN1cnJlbnQgb3B0aW9uIHZhbHVlIGlzXG4gICAqIHVuZGVmaW5lZCwgb3IgdGhlIHNvdXJjZSBvZiB0aGUgY3VycmVudCB2YWx1ZSBpcyAnZGVmYXVsdCcgb3IgJ2NvbmZpZycgb3IgJ2VudicuXG4gICAqXG4gICAqIEBwYXJhbSB7c3RyaW5nfSBuYW1lXG4gICAqIEByZXR1cm4ge09wdGlvbn1cbiAgICovXG5cbiAgZW52KG5hbWUpIHtcbiAgICB0aGlzLmVudlZhciA9IG5hbWU7XG4gICAgcmV0dXJuIHRoaXM7XG4gIH1cblxuICAvKipcbiAgICogU2V0IHRoZSBjdXN0b20gaGFuZGxlciBmb3IgcHJvY2Vzc2luZyBDTEkgb3B0aW9uIGFyZ3VtZW50cyBpbnRvIG9wdGlvbiB2YWx1ZXMuXG4gICAqXG4gICAqIEBwYXJhbSB7RnVuY3Rpb259IFtmbl1cbiAgICogQHJldHVybiB7T3B0aW9ufVxuICAgKi9cblxuICBhcmdQYXJzZXIoZm4pIHtcbiAgICB0aGlzLnBhcnNlQXJnID0gZm47XG4gICAgcmV0dXJuIHRoaXM7XG4gIH1cblxuICAvKipcbiAgICogV2hldGhlciB0aGUgb3B0aW9uIGlzIG1hbmRhdG9yeSBhbmQgbXVzdCBoYXZlIGEgdmFsdWUgYWZ0ZXIgcGFyc2luZy5cbiAgICpcbiAgICogQHBhcmFtIHtib29sZWFufSBbbWFuZGF0b3J5PXRydWVdXG4gICAqIEByZXR1cm4ge09wdGlvbn1cbiAgICovXG5cbiAgbWFrZU9wdGlvbk1hbmRhdG9yeShtYW5kYXRvcnkgPSB0cnVlKSB7XG4gICAgdGhpcy5tYW5kYXRvcnkgPSAhIW1hbmRhdG9yeTtcbiAgICByZXR1cm4gdGhpcztcbiAgfVxuXG4gIC8qKlxuICAgKiBIaWRlIG9wdGlvbiBpbiBoZWxwLlxuICAgKlxuICAgKiBAcGFyYW0ge2Jvb2xlYW59IFtoaWRlPXRydWVdXG4gICAqIEByZXR1cm4ge09wdGlvbn1cbiAgICovXG5cbiAgaGlkZUhlbHAoaGlkZSA9IHRydWUpIHtcbiAgICB0aGlzLmhpZGRlbiA9ICEhaGlkZTtcbiAgICByZXR1cm4gdGhpcztcbiAgfVxuXG4gIC8qKlxuICAgKiBAYXBpIHByaXZhdGVcbiAgICovXG5cbiAgX2NvbmNhdFZhbHVlKHZhbHVlLCBwcmV2aW91cykge1xuICAgIGlmIChwcmV2aW91cyA9PT0gdGhpcy5kZWZhdWx0VmFsdWUgfHwgIUFycmF5LmlzQXJyYXkocHJldmlvdXMpKSB7XG4gICAgICByZXR1cm4gW3ZhbHVlXTtcbiAgICB9XG5cbiAgICByZXR1cm4gcHJldmlvdXMuY29uY2F0KHZhbHVlKTtcbiAgfVxuXG4gIC8qKlxuICAgKiBPbmx5IGFsbG93IG9wdGlvbiB2YWx1ZSB0byBiZSBvbmUgb2YgY2hvaWNlcy5cbiAgICpcbiAgICogQHBhcmFtIHtzdHJpbmdbXX0gdmFsdWVzXG4gICAqIEByZXR1cm4ge09wdGlvbn1cbiAgICovXG5cbiAgY2hvaWNlcyh2YWx1ZXMpIHtcbiAgICB0aGlzLmFyZ0Nob2ljZXMgPSB2YWx1ZXMuc2xpY2UoKTtcbiAgICB0aGlzLnBhcnNlQXJnID0gKGFyZywgcHJldmlvdXMpID0+IHtcbiAgICAgIGlmICghdGhpcy5hcmdDaG9pY2VzLmluY2x1ZGVzKGFyZykpIHtcbiAgICAgICAgdGhyb3cgbmV3IEludmFsaWRBcmd1bWVudEVycm9yKGBBbGxvd2VkIGNob2ljZXMgYXJlICR7dGhpcy5hcmdDaG9pY2VzLmpvaW4oJywgJyl9LmApO1xuICAgICAgfVxuICAgICAgaWYgKHRoaXMudmFyaWFkaWMpIHtcbiAgICAgICAgcmV0dXJuIHRoaXMuX2NvbmNhdFZhbHVlKGFyZywgcHJldmlvdXMpO1xuICAgICAgfVxuICAgICAgcmV0dXJuIGFyZztcbiAgICB9O1xuICAgIHJldHVybiB0aGlzO1xuICB9XG5cbiAgLyoqXG4gICAqIFJldHVybiBvcHRpb24gbmFtZS5cbiAgICpcbiAgICogQHJldHVybiB7c3RyaW5nfVxuICAgKi9cblxuICBuYW1lKCkge1xuICAgIGlmICh0aGlzLmxvbmcpIHtcbiAgICAgIHJldHVybiB0aGlzLmxvbmcucmVwbGFjZSgvXi0tLywgJycpO1xuICAgIH1cbiAgICByZXR1cm4gdGhpcy5zaG9ydC5yZXBsYWNlKC9eLS8sICcnKTtcbiAgfVxuXG4gIC8qKlxuICAgKiBSZXR1cm4gb3B0aW9uIG5hbWUsIGluIGEgY2FtZWxjYXNlIGZvcm1hdCB0aGF0IGNhbiBiZSB1c2VkXG4gICAqIGFzIGEgb2JqZWN0IGF0dHJpYnV0ZSBrZXkuXG4gICAqXG4gICAqIEByZXR1cm4ge3N0cmluZ31cbiAgICogQGFwaSBwcml2YXRlXG4gICAqL1xuXG4gIGF0dHJpYnV0ZU5hbWUoKSB7XG4gICAgcmV0dXJuIGNhbWVsY2FzZSh0aGlzLm5hbWUoKS5yZXBsYWNlKC9ebm8tLywgJycpKTtcbiAgfVxuXG4gIC8qKlxuICAgKiBDaGVjayBpZiBgYXJnYCBtYXRjaGVzIHRoZSBzaG9ydCBvciBsb25nIGZsYWcuXG4gICAqXG4gICAqIEBwYXJhbSB7c3RyaW5nfSBhcmdcbiAgICogQHJldHVybiB7Ym9vbGVhbn1cbiAgICogQGFwaSBwcml2YXRlXG4gICAqL1xuXG4gIGlzKGFyZykge1xuICAgIHJldHVybiB0aGlzLnNob3J0ID09PSBhcmcgfHwgdGhpcy5sb25nID09PSBhcmc7XG4gIH1cblxuICAvKipcbiAgICogUmV0dXJuIHdoZXRoZXIgYSBib29sZWFuIG9wdGlvbi5cbiAgICpcbiAgICogT3B0aW9ucyBhcmUgb25lIG9mIGJvb2xlYW4sIG5lZ2F0ZWQsIHJlcXVpcmVkIGFyZ3VtZW50LCBvciBvcHRpb25hbCBhcmd1bWVudC5cbiAgICpcbiAgICogQHJldHVybiB7Ym9vbGVhbn1cbiAgICogQGFwaSBwcml2YXRlXG4gICAqL1xuXG4gIGlzQm9vbGVhbigpIHtcbiAgICByZXR1cm4gIXRoaXMucmVxdWlyZWQgJiYgIXRoaXMub3B0aW9uYWwgJiYgIXRoaXMubmVnYXRlO1xuICB9XG59XG5cbi8qKlxuICogVGhpcyBjbGFzcyBpcyB0byBtYWtlIGl0IGVhc2llciB0byB3b3JrIHdpdGggZHVhbCBvcHRpb25zLCB3aXRob3V0IGNoYW5naW5nIHRoZSBleGlzdGluZ1xuICogaW1wbGVtZW50YXRpb24uIFdlIHN1cHBvcnQgc2VwYXJhdGUgZHVhbCBvcHRpb25zIGZvciBzZXBhcmF0ZSBwb3NpdGl2ZSBhbmQgbmVnYXRpdmUgb3B0aW9ucyxcbiAqIGxpa2UgYC0tYnVpbGRgIGFuZCBgLS1uby1idWlsZGAsIHdoaWNoIHNoYXJlIGEgc2luZ2xlIG9wdGlvbiB2YWx1ZS4gVGhpcyB3b3JrcyBuaWNlbHkgZm9yIHNvbWVcbiAqIHVzZSBjYXNlcywgYnV0IGlzIHRyaWNreSBmb3Igb3RoZXJzIHdoZXJlIHdlIHdhbnQgc2VwYXJhdGUgYmVoYXZpb3VycyBkZXNwaXRlXG4gKiB0aGUgc2luZ2xlIHNoYXJlZCBvcHRpb24gdmFsdWUuXG4gKi9cbmNsYXNzIER1YWxPcHRpb25zIHtcbiAgLyoqXG4gICAqIEBwYXJhbSB7T3B0aW9uW119IG9wdGlvbnNcbiAgICovXG4gIGNvbnN0cnVjdG9yKG9wdGlvbnMpIHtcbiAgICB0aGlzLnBvc2l0aXZlT3B0aW9ucyA9IG5ldyBNYXAoKTtcbiAgICB0aGlzLm5lZ2F0aXZlT3B0aW9ucyA9IG5ldyBNYXAoKTtcbiAgICB0aGlzLmR1YWxPcHRpb25zID0gbmV3IFNldCgpO1xuICAgIG9wdGlvbnMuZm9yRWFjaChvcHRpb24gPT4ge1xuICAgICAgaWYgKG9wdGlvbi5uZWdhdGUpIHtcbiAgICAgICAgdGhpcy5uZWdhdGl2ZU9wdGlvbnMuc2V0KG9wdGlvbi5hdHRyaWJ1dGVOYW1lKCksIG9wdGlvbik7XG4gICAgICB9IGVsc2Uge1xuICAgICAgICB0aGlzLnBvc2l0aXZlT3B0aW9ucy5zZXQob3B0aW9uLmF0dHJpYnV0ZU5hbWUoKSwgb3B0aW9uKTtcbiAgICAgIH1cbiAgICB9KTtcbiAgICB0aGlzLm5lZ2F0aXZlT3B0aW9ucy5mb3JFYWNoKCh2YWx1ZSwga2V5KSA9PiB7XG4gICAgICBpZiAodGhpcy5wb3NpdGl2ZU9wdGlvbnMuaGFzKGtleSkpIHtcbiAgICAgICAgdGhpcy5kdWFsT3B0aW9ucy5hZGQoa2V5KTtcbiAgICAgIH1cbiAgICB9KTtcbiAgfVxuXG4gIC8qKlxuICAgKiBEaWQgdGhlIHZhbHVlIGNvbWUgZnJvbSB0aGUgb3B0aW9uLCBhbmQgbm90IGZyb20gcG9zc2libGUgbWF0Y2hpbmcgZHVhbCBvcHRpb24/XG4gICAqXG4gICAqIEBwYXJhbSB7YW55fSB2YWx1ZVxuICAgKiBAcGFyYW0ge09wdGlvbn0gb3B0aW9uXG4gICAqIEByZXR1cm5zIHtib29sZWFufVxuICAgKi9cbiAgdmFsdWVGcm9tT3B0aW9uKHZhbHVlLCBvcHRpb24pIHtcbiAgICBjb25zdCBvcHRpb25LZXkgPSBvcHRpb24uYXR0cmlidXRlTmFtZSgpO1xuICAgIGlmICghdGhpcy5kdWFsT3B0aW9ucy5oYXMob3B0aW9uS2V5KSkgcmV0dXJuIHRydWU7XG5cbiAgICAvLyBVc2UgdGhlIHZhbHVlIHRvIGRlZHVjZSBpZiAocHJvYmFibHkpIGNhbWUgZnJvbSB0aGUgb3B0aW9uLlxuICAgIGNvbnN0IHByZXNldCA9IHRoaXMubmVnYXRpdmVPcHRpb25zLmdldChvcHRpb25LZXkpLnByZXNldEFyZztcbiAgICBjb25zdCBuZWdhdGl2ZVZhbHVlID0gKHByZXNldCAhPT0gdW5kZWZpbmVkKSA/IHByZXNldCA6IGZhbHNlO1xuICAgIHJldHVybiBvcHRpb24ubmVnYXRlID09PSAobmVnYXRpdmVWYWx1ZSA9PT0gdmFsdWUpO1xuICB9XG59XG5cbi8qKlxuICogQ29udmVydCBzdHJpbmcgZnJvbSBrZWJhYi1jYXNlIHRvIGNhbWVsQ2FzZS5cbiAqXG4gKiBAcGFyYW0ge3N0cmluZ30gc3RyXG4gKiBAcmV0dXJuIHtzdHJpbmd9XG4gKiBAYXBpIHByaXZhdGVcbiAqL1xuXG5mdW5jdGlvbiBjYW1lbGNhc2Uoc3RyKSB7XG4gIHJldHVybiBzdHIuc3BsaXQoJy0nKS5yZWR1Y2UoKHN0ciwgd29yZCkgPT4ge1xuICAgIHJldHVybiBzdHIgKyB3b3JkWzBdLnRvVXBwZXJDYXNlKCkgKyB3b3JkLnNsaWNlKDEpO1xuICB9KTtcbn1cblxuLyoqXG4gKiBTcGxpdCB0aGUgc2hvcnQgYW5kIGxvbmcgZmxhZyBvdXQgb2Ygc29tZXRoaW5nIGxpa2UgJy1tLC0tbWl4ZWQgPHZhbHVlPidcbiAqXG4gKiBAYXBpIHByaXZhdGVcbiAqL1xuXG5mdW5jdGlvbiBzcGxpdE9wdGlvbkZsYWdzKGZsYWdzKSB7XG4gIGxldCBzaG9ydEZsYWc7XG4gIGxldCBsb25nRmxhZztcbiAgLy8gVXNlIG9yaWdpbmFsIHZlcnkgbG9vc2UgcGFyc2luZyB0byBtYWludGFpbiBiYWNrd2FyZHMgY29tcGF0aWJpbGl0eSBmb3Igbm93LFxuICAvLyB3aGljaCBhbGxvd2VkIGZvciBleGFtcGxlIHVuaW50ZW5kZWQgYC1zdywgLS1zaG9ydC13b3JkYCBbc2ljXS5cbiAgY29uc3QgZmxhZ1BhcnRzID0gZmxhZ3Muc3BsaXQoL1sgfCxdKy8pO1xuICBpZiAoZmxhZ1BhcnRzLmxlbmd0aCA+IDEgJiYgIS9eW1s8XS8udGVzdChmbGFnUGFydHNbMV0pKSBzaG9ydEZsYWcgPSBmbGFnUGFydHMuc2hpZnQoKTtcbiAgbG9uZ0ZsYWcgPSBmbGFnUGFydHMuc2hpZnQoKTtcbiAgLy8gQWRkIHN1cHBvcnQgZm9yIGxvbmUgc2hvcnQgZmxhZyB3aXRob3V0IHNpZ25pZmljYW50bHkgY2hhbmdpbmcgcGFyc2luZyFcbiAgaWYgKCFzaG9ydEZsYWcgJiYgL14tW14tXSQvLnRlc3QobG9uZ0ZsYWcpKSB7XG4gICAgc2hvcnRGbGFnID0gbG9uZ0ZsYWc7XG4gICAgbG9uZ0ZsYWcgPSB1bmRlZmluZWQ7XG4gIH1cbiAgcmV0dXJuIHsgc2hvcnRGbGFnLCBsb25nRmxhZyB9O1xufVxuXG5leHBvcnRzLk9wdGlvbiA9IE9wdGlvbjtcbmV4cG9ydHMuc3BsaXRPcHRpb25GbGFncyA9IHNwbGl0T3B0aW9uRmxhZ3M7XG5leHBvcnRzLkR1YWxPcHRpb25zID0gRHVhbE9wdGlvbnM7XG4iLCJjb25zdCBtYXhEaXN0YW5jZSA9IDM7XG5cbmZ1bmN0aW9uIGVkaXREaXN0YW5jZShhLCBiKSB7XG4gIC8vIGh0dHBzOi8vZW4ud2lraXBlZGlhLm9yZy93aWtpL0RhbWVyYXXigJNMZXZlbnNodGVpbl9kaXN0YW5jZVxuICAvLyBDYWxjdWxhdGluZyBvcHRpbWFsIHN0cmluZyBhbGlnbm1lbnQgZGlzdGFuY2UsIG5vIHN1YnN0cmluZyBpcyBlZGl0ZWQgbW9yZSB0aGFuIG9uY2UuXG4gIC8vIChTaW1wbGUgaW1wbGVtZW50YXRpb24uKVxuXG4gIC8vIFF1aWNrIGVhcmx5IGV4aXQsIHJldHVybiB3b3JzdCBjYXNlLlxuICBpZiAoTWF0aC5hYnMoYS5sZW5ndGggLSBiLmxlbmd0aCkgPiBtYXhEaXN0YW5jZSkgcmV0dXJuIE1hdGgubWF4KGEubGVuZ3RoLCBiLmxlbmd0aCk7XG5cbiAgLy8gZGlzdGFuY2UgYmV0d2VlbiBwcmVmaXggc3Vic3RyaW5ncyBvZiBhIGFuZCBiXG4gIGNvbnN0IGQgPSBbXTtcblxuICAvLyBwdXJlIGRlbGV0aW9ucyB0dXJuIGEgaW50byBlbXB0eSBzdHJpbmdcbiAgZm9yIChsZXQgaSA9IDA7IGkgPD0gYS5sZW5ndGg7IGkrKykge1xuICAgIGRbaV0gPSBbaV07XG4gIH1cbiAgLy8gcHVyZSBpbnNlcnRpb25zIHR1cm4gZW1wdHkgc3RyaW5nIGludG8gYlxuICBmb3IgKGxldCBqID0gMDsgaiA8PSBiLmxlbmd0aDsgaisrKSB7XG4gICAgZFswXVtqXSA9IGo7XG4gIH1cblxuICAvLyBmaWxsIG1hdHJpeFxuICBmb3IgKGxldCBqID0gMTsgaiA8PSBiLmxlbmd0aDsgaisrKSB7XG4gICAgZm9yIChsZXQgaSA9IDE7IGkgPD0gYS5sZW5ndGg7IGkrKykge1xuICAgICAgbGV0IGNvc3QgPSAxO1xuICAgICAgaWYgKGFbaSAtIDFdID09PSBiW2ogLSAxXSkge1xuICAgICAgICBjb3N0ID0gMDtcbiAgICAgIH0gZWxzZSB7XG4gICAgICAgIGNvc3QgPSAxO1xuICAgICAgfVxuICAgICAgZFtpXVtqXSA9IE1hdGgubWluKFxuICAgICAgICBkW2kgLSAxXVtqXSArIDEsIC8vIGRlbGV0aW9uXG4gICAgICAgIGRbaV1baiAtIDFdICsgMSwgLy8gaW5zZXJ0aW9uXG4gICAgICAgIGRbaSAtIDFdW2ogLSAxXSArIGNvc3QgLy8gc3Vic3RpdHV0aW9uXG4gICAgICApO1xuICAgICAgLy8gdHJhbnNwb3NpdGlvblxuICAgICAgaWYgKGkgPiAxICYmIGogPiAxICYmIGFbaSAtIDFdID09PSBiW2ogLSAyXSAmJiBhW2kgLSAyXSA9PT0gYltqIC0gMV0pIHtcbiAgICAgICAgZFtpXVtqXSA9IE1hdGgubWluKGRbaV1bal0sIGRbaSAtIDJdW2ogLSAyXSArIDEpO1xuICAgICAgfVxuICAgIH1cbiAgfVxuXG4gIHJldHVybiBkW2EubGVuZ3RoXVtiLmxlbmd0aF07XG59XG5cbi8qKlxuICogRmluZCBjbG9zZSBtYXRjaGVzLCByZXN0cmljdGVkIHRvIHNhbWUgbnVtYmVyIG9mIGVkaXRzLlxuICpcbiAqIEBwYXJhbSB7c3RyaW5nfSB3b3JkXG4gKiBAcGFyYW0ge3N0cmluZ1tdfSBjYW5kaWRhdGVzXG4gKiBAcmV0dXJucyB7c3RyaW5nfVxuICovXG5cbmZ1bmN0aW9uIHN1Z2dlc3RTaW1pbGFyKHdvcmQsIGNhbmRpZGF0ZXMpIHtcbiAgaWYgKCFjYW5kaWRhdGVzIHx8IGNhbmRpZGF0ZXMubGVuZ3RoID09PSAwKSByZXR1cm4gJyc7XG4gIC8vIHJlbW92ZSBwb3NzaWJsZSBkdXBsaWNhdGVzXG4gIGNhbmRpZGF0ZXMgPSBBcnJheS5mcm9tKG5ldyBTZXQoY2FuZGlkYXRlcykpO1xuXG4gIGNvbnN0IHNlYXJjaGluZ09wdGlvbnMgPSB3b3JkLnN0YXJ0c1dpdGgoJy0tJyk7XG4gIGlmIChzZWFyY2hpbmdPcHRpb25zKSB7XG4gICAgd29yZCA9IHdvcmQuc2xpY2UoMik7XG4gICAgY2FuZGlkYXRlcyA9IGNhbmRpZGF0ZXMubWFwKGNhbmRpZGF0ZSA9PiBjYW5kaWRhdGUuc2xpY2UoMikpO1xuICB9XG5cbiAgbGV0IHNpbWlsYXIgPSBbXTtcbiAgbGV0IGJlc3REaXN0YW5jZSA9IG1heERpc3RhbmNlO1xuICBjb25zdCBtaW5TaW1pbGFyaXR5ID0gMC40O1xuICBjYW5kaWRhdGVzLmZvckVhY2goKGNhbmRpZGF0ZSkgPT4ge1xuICAgIGlmIChjYW5kaWRhdGUubGVuZ3RoIDw9IDEpIHJldHVybjsgLy8gbm8gb25lIGNoYXJhY3RlciBndWVzc2VzXG5cbiAgICBjb25zdCBkaXN0YW5jZSA9IGVkaXREaXN0YW5jZSh3b3JkLCBjYW5kaWRhdGUpO1xuICAgIGNvbnN0IGxlbmd0aCA9IE1hdGgubWF4KHdvcmQubGVuZ3RoLCBjYW5kaWRhdGUubGVuZ3RoKTtcbiAgICBjb25zdCBzaW1pbGFyaXR5ID0gKGxlbmd0aCAtIGRpc3RhbmNlKSAvIGxlbmd0aDtcbiAgICBpZiAoc2ltaWxhcml0eSA+IG1pblNpbWlsYXJpdHkpIHtcbiAgICAgIGlmIChkaXN0YW5jZSA8IGJlc3REaXN0YW5jZSkge1xuICAgICAgICAvLyBiZXR0ZXIgZWRpdCBkaXN0YW5jZSwgdGhyb3cgYXdheSBwcmV2aW91cyB3b3JzZSBtYXRjaGVzXG4gICAgICAgIGJlc3REaXN0YW5jZSA9IGRpc3RhbmNlO1xuICAgICAgICBzaW1pbGFyID0gW2NhbmRpZGF0ZV07XG4gICAgICB9IGVsc2UgaWYgKGRpc3RhbmNlID09PSBiZXN0RGlzdGFuY2UpIHtcbiAgICAgICAgc2ltaWxhci5wdXNoKGNhbmRpZGF0ZSk7XG4gICAgICB9XG4gICAgfVxuICB9KTtcblxuICBzaW1pbGFyLnNvcnQoKGEsIGIpID0+IGEubG9jYWxlQ29tcGFyZShiKSk7XG4gIGlmIChzZWFyY2hpbmdPcHRpb25zKSB7XG4gICAgc2ltaWxhciA9IHNpbWlsYXIubWFwKGNhbmRpZGF0ZSA9PiBgLS0ke2NhbmRpZGF0ZX1gKTtcbiAgfVxuXG4gIGlmIChzaW1pbGFyLmxlbmd0aCA+IDEpIHtcbiAgICByZXR1cm4gYFxcbihEaWQgeW91IG1lYW4gb25lIG9mICR7c2ltaWxhci5qb2luKCcsICcpfT8pYDtcbiAgfVxuICBpZiAoc2ltaWxhci5sZW5ndGggPT09IDEpIHtcbiAgICByZXR1cm4gYFxcbihEaWQgeW91IG1lYW4gJHtzaW1pbGFyWzBdfT8pYDtcbiAgfVxuICByZXR1cm4gJyc7XG59XG5cbmV4cG9ydHMuc3VnZ2VzdFNpbWlsYXIgPSBzdWdnZXN0U2ltaWxhcjtcbiIsIlwidXNlIHN0cmljdFwiO1xuT2JqZWN0LmRlZmluZVByb3BlcnR5KGV4cG9ydHMsIFwiX19lc01vZHVsZVwiLCB7IHZhbHVlOiB0cnVlIH0pO1xuZXhwb3J0cy5hc3NlcnRWYWxpZFBhdHRlcm4gPSB2b2lkIDA7XG5jb25zdCBNQVhfUEFUVEVSTl9MRU5HVEggPSAxMDI0ICogNjQ7XG5jb25zdCBhc3NlcnRWYWxpZFBhdHRlcm4gPSAocGF0dGVybikgPT4ge1xuICAgIGlmICh0eXBlb2YgcGF0dGVybiAhPT0gJ3N0cmluZycpIHtcbiAgICAgICAgdGhyb3cgbmV3IFR5cGVFcnJvcignaW52YWxpZCBwYXR0ZXJuJyk7XG4gICAgfVxuICAgIGlmIChwYXR0ZXJuLmxlbmd0aCA+IE1BWF9QQVRURVJOX0xFTkdUSCkge1xuICAgICAgICB0aHJvdyBuZXcgVHlwZUVycm9yKCdwYXR0ZXJuIGlzIHRvbyBsb25nJyk7XG4gICAgfVxufTtcbmV4cG9ydHMuYXNzZXJ0VmFsaWRQYXR0ZXJuID0gYXNzZXJ0VmFsaWRQYXR0ZXJuO1xuLy8jIHNvdXJjZU1hcHBpbmdVUkw9YXNzZXJ0LXZhbGlkLXBhdHRlcm4uanMubWFwIiwiXCJ1c2Ugc3RyaWN0XCI7XG4vLyBwYXJzZSBhIHNpbmdsZSBwYXRoIHBvcnRpb25cbk9iamVjdC5kZWZpbmVQcm9wZXJ0eShleHBvcnRzLCBcIl9fZXNNb2R1bGVcIiwgeyB2YWx1ZTogdHJ1ZSB9KTtcbmV4cG9ydHMuQVNUID0gdm9pZCAwO1xuY29uc3QgYnJhY2VfZXhwcmVzc2lvbnNfanNfMSA9IHJlcXVpcmUoXCIuL2JyYWNlLWV4cHJlc3Npb25zLmpzXCIpO1xuY29uc3QgdW5lc2NhcGVfanNfMSA9IHJlcXVpcmUoXCIuL3VuZXNjYXBlLmpzXCIpO1xuY29uc3QgdHlwZXMgPSBuZXcgU2V0KFsnIScsICc/JywgJysnLCAnKicsICdAJ10pO1xuY29uc3QgaXNFeHRnbG9iVHlwZSA9IChjKSA9PiB0eXBlcy5oYXMoYyk7XG4vLyBQYXR0ZXJucyB0aGF0IGdldCBwcmVwZW5kZWQgdG8gYmluZCB0byB0aGUgc3RhcnQgb2YgZWl0aGVyIHRoZVxuLy8gZW50aXJlIHN0cmluZywgb3IganVzdCBhIHNpbmdsZSBwYXRoIHBvcnRpb24sIHRvIHByZXZlbnQgZG90c1xuLy8gYW5kL29yIHRyYXZlcnNhbCBwYXR0ZXJucywgd2hlbiBuZWVkZWQuXG4vLyBFeHRzIGRvbid0IG5lZWQgdGhlIF4gb3IgLyBiaXQsIGJlY2F1c2UgdGhlIHJvb3QgYmluZHMgdGhhdCBhbHJlYWR5LlxuY29uc3Qgc3RhcnROb1RyYXZlcnNhbCA9ICcoPyEoPzpefC8pXFxcXC5cXFxcLj8oPzokfC8pKSc7XG5jb25zdCBzdGFydE5vRG90ID0gJyg/IVxcXFwuKSc7XG4vLyBjaGFyYWN0ZXJzIHRoYXQgaW5kaWNhdGUgYSBzdGFydCBvZiBwYXR0ZXJuIG5lZWRzIHRoZSBcIm5vIGRvdHNcIiBiaXQsXG4vLyBiZWNhdXNlIGEgZG90ICptaWdodCogYmUgbWF0Y2hlZC4gKCBpcyBub3QgaW4gdGhlIGxpc3QsIGJlY2F1c2UgaW5cbi8vIHRoZSBjYXNlIG9mIGEgY2hpbGQgZXh0Z2xvYiwgaXQgd2lsbCBoYW5kbGUgdGhlIHByZXZlbnRpb24gaXRzZWxmLlxuY29uc3QgYWRkUGF0dGVyblN0YXJ0ID0gbmV3IFNldChbJ1snLCAnLiddKTtcbi8vIGNhc2VzIHdoZXJlIHRyYXZlcnNhbCBpcyBBLU9LLCBubyBkb3QgcHJldmVudGlvbiBuZWVkZWRcbmNvbnN0IGp1c3REb3RzID0gbmV3IFNldChbJy4uJywgJy4nXSk7XG5jb25zdCByZVNwZWNpYWxzID0gbmV3IFNldCgnKCkuKnt9Kz9bXV4kXFxcXCEnKTtcbmNvbnN0IHJlZ0V4cEVzY2FwZSA9IChzKSA9PiBzLnJlcGxhY2UoL1stW1xcXXt9KCkqKz8uLFxcXFxeJHwjXFxzXS9nLCAnXFxcXCQmJyk7XG4vLyBhbnkgc2luZ2xlIHRoaW5nIG90aGVyIHRoYW4gL1xuY29uc3QgcW1hcmsgPSAnW14vXSc7XG4vLyAqID0+IGFueSBudW1iZXIgb2YgY2hhcmFjdGVyc1xuY29uc3Qgc3RhciA9IHFtYXJrICsgJyo/Jztcbi8vIHVzZSArIHdoZW4gd2UgbmVlZCB0byBlbnN1cmUgdGhhdCAqc29tZXRoaW5nKiBtYXRjaGVzLCBiZWNhdXNlIHRoZSAqIGlzXG4vLyB0aGUgb25seSB0aGluZyBpbiB0aGUgcGF0aCBwb3J0aW9uLlxuY29uc3Qgc3Rhck5vRW1wdHkgPSBxbWFyayArICcrPyc7XG4vLyByZW1vdmUgdGhlIFxcIGNoYXJzIHRoYXQgd2UgYWRkZWQgaWYgd2UgZW5kIHVwIGRvaW5nIGEgbm9ubWFnaWMgY29tcGFyZVxuLy8gY29uc3QgZGVzbGFzaCA9IChzOiBzdHJpbmcpID0+IHMucmVwbGFjZSgvXFxcXCguKS9nLCAnJDEnKVxuY2xhc3MgQVNUIHtcbiAgICB0eXBlO1xuICAgICNyb290O1xuICAgICNoYXNNYWdpYztcbiAgICAjdWZsYWcgPSBmYWxzZTtcbiAgICAjcGFydHMgPSBbXTtcbiAgICAjcGFyZW50O1xuICAgICNwYXJlbnRJbmRleDtcbiAgICAjbmVncztcbiAgICAjZmlsbGVkTmVncyA9IGZhbHNlO1xuICAgICNvcHRpb25zO1xuICAgICN0b1N0cmluZztcbiAgICAvLyBzZXQgdG8gdHJ1ZSBpZiBpdCdzIGFuIGV4dGdsb2Igd2l0aCBubyBjaGlsZHJlblxuICAgIC8vICh3aGljaCByZWFsbHkgbWVhbnMgb25lIGNoaWxkIG9mICcnKVxuICAgICNlbXB0eUV4dCA9IGZhbHNlO1xuICAgIGNvbnN0cnVjdG9yKHR5cGUsIHBhcmVudCwgb3B0aW9ucyA9IHt9KSB7XG4gICAgICAgIHRoaXMudHlwZSA9IHR5cGU7XG4gICAgICAgIC8vIGV4dGdsb2JzIGFyZSBpbmhlcmVudGx5IG1hZ2ljYWxcbiAgICAgICAgaWYgKHR5cGUpXG4gICAgICAgICAgICB0aGlzLiNoYXNNYWdpYyA9IHRydWU7XG4gICAgICAgIHRoaXMuI3BhcmVudCA9IHBhcmVudDtcbiAgICAgICAgdGhpcy4jcm9vdCA9IHRoaXMuI3BhcmVudCA/IHRoaXMuI3BhcmVudC4jcm9vdCA6IHRoaXM7XG4gICAgICAgIHRoaXMuI29wdGlvbnMgPSB0aGlzLiNyb290ID09PSB0aGlzID8gb3B0aW9ucyA6IHRoaXMuI3Jvb3QuI29wdGlvbnM7XG4gICAgICAgIHRoaXMuI25lZ3MgPSB0aGlzLiNyb290ID09PSB0aGlzID8gW10gOiB0aGlzLiNyb290LiNuZWdzO1xuICAgICAgICBpZiAodHlwZSA9PT0gJyEnICYmICF0aGlzLiNyb290LiNmaWxsZWROZWdzKVxuICAgICAgICAgICAgdGhpcy4jbmVncy5wdXNoKHRoaXMpO1xuICAgICAgICB0aGlzLiNwYXJlbnRJbmRleCA9IHRoaXMuI3BhcmVudCA/IHRoaXMuI3BhcmVudC4jcGFydHMubGVuZ3RoIDogMDtcbiAgICB9XG4gICAgZ2V0IGhhc01hZ2ljKCkge1xuICAgICAgICAvKiBjOCBpZ25vcmUgc3RhcnQgKi9cbiAgICAgICAgaWYgKHRoaXMuI2hhc01hZ2ljICE9PSB1bmRlZmluZWQpXG4gICAgICAgICAgICByZXR1cm4gdGhpcy4jaGFzTWFnaWM7XG4gICAgICAgIC8qIGM4IGlnbm9yZSBzdG9wICovXG4gICAgICAgIGZvciAoY29uc3QgcCBvZiB0aGlzLiNwYXJ0cykge1xuICAgICAgICAgICAgaWYgKHR5cGVvZiBwID09PSAnc3RyaW5nJylcbiAgICAgICAgICAgICAgICBjb250aW51ZTtcbiAgICAgICAgICAgIGlmIChwLnR5cGUgfHwgcC5oYXNNYWdpYylcbiAgICAgICAgICAgICAgICByZXR1cm4gKHRoaXMuI2hhc01hZ2ljID0gdHJ1ZSk7XG4gICAgICAgIH1cbiAgICAgICAgLy8gbm90ZTogd2lsbCBiZSB1bmRlZmluZWQgdW50aWwgd2UgZ2VuZXJhdGUgdGhlIHJlZ2V4cCBzcmMgYW5kIGZpbmQgb3V0XG4gICAgICAgIHJldHVybiB0aGlzLiNoYXNNYWdpYztcbiAgICB9XG4gICAgLy8gcmVjb25zdHJ1Y3RzIHRoZSBwYXR0ZXJuXG4gICAgdG9TdHJpbmcoKSB7XG4gICAgICAgIGlmICh0aGlzLiN0b1N0cmluZyAhPT0gdW5kZWZpbmVkKVxuICAgICAgICAgICAgcmV0dXJuIHRoaXMuI3RvU3RyaW5nO1xuICAgICAgICBpZiAoIXRoaXMudHlwZSkge1xuICAgICAgICAgICAgcmV0dXJuICh0aGlzLiN0b1N0cmluZyA9IHRoaXMuI3BhcnRzLm1hcChwID0+IFN0cmluZyhwKSkuam9pbignJykpO1xuICAgICAgICB9XG4gICAgICAgIGVsc2Uge1xuICAgICAgICAgICAgcmV0dXJuICh0aGlzLiN0b1N0cmluZyA9XG4gICAgICAgICAgICAgICAgdGhpcy50eXBlICsgJygnICsgdGhpcy4jcGFydHMubWFwKHAgPT4gU3RyaW5nKHApKS5qb2luKCd8JykgKyAnKScpO1xuICAgICAgICB9XG4gICAgfVxuICAgICNmaWxsTmVncygpIHtcbiAgICAgICAgLyogYzggaWdub3JlIHN0YXJ0ICovXG4gICAgICAgIGlmICh0aGlzICE9PSB0aGlzLiNyb290KVxuICAgICAgICAgICAgdGhyb3cgbmV3IEVycm9yKCdzaG91bGQgb25seSBjYWxsIG9uIHJvb3QnKTtcbiAgICAgICAgaWYgKHRoaXMuI2ZpbGxlZE5lZ3MpXG4gICAgICAgICAgICByZXR1cm4gdGhpcztcbiAgICAgICAgLyogYzggaWdub3JlIHN0b3AgKi9cbiAgICAgICAgLy8gY2FsbCB0b1N0cmluZygpIG9uY2UgdG8gZmlsbCB0aGlzIG91dFxuICAgICAgICB0aGlzLnRvU3RyaW5nKCk7XG4gICAgICAgIHRoaXMuI2ZpbGxlZE5lZ3MgPSB0cnVlO1xuICAgICAgICBsZXQgbjtcbiAgICAgICAgd2hpbGUgKChuID0gdGhpcy4jbmVncy5wb3AoKSkpIHtcbiAgICAgICAgICAgIGlmIChuLnR5cGUgIT09ICchJylcbiAgICAgICAgICAgICAgICBjb250aW51ZTtcbiAgICAgICAgICAgIC8vIHdhbGsgdXAgdGhlIHRyZWUsIGFwcGVuZGluZyBldmVydGhpbmcgdGhhdCBjb21lcyBBRlRFUiBwYXJlbnRJbmRleFxuICAgICAgICAgICAgbGV0IHAgPSBuO1xuICAgICAgICAgICAgbGV0IHBwID0gcC4jcGFyZW50O1xuICAgICAgICAgICAgd2hpbGUgKHBwKSB7XG4gICAgICAgICAgICAgICAgZm9yIChsZXQgaSA9IHAuI3BhcmVudEluZGV4ICsgMTsgIXBwLnR5cGUgJiYgaSA8IHBwLiNwYXJ0cy5sZW5ndGg7IGkrKykge1xuICAgICAgICAgICAgICAgICAgICBmb3IgKGNvbnN0IHBhcnQgb2Ygbi4jcGFydHMpIHtcbiAgICAgICAgICAgICAgICAgICAgICAgIC8qIGM4IGlnbm9yZSBzdGFydCAqL1xuICAgICAgICAgICAgICAgICAgICAgICAgaWYgKHR5cGVvZiBwYXJ0ID09PSAnc3RyaW5nJykge1xuICAgICAgICAgICAgICAgICAgICAgICAgICAgIHRocm93IG5ldyBFcnJvcignc3RyaW5nIHBhcnQgaW4gZXh0Z2xvYiBBU1Q/PycpO1xuICAgICAgICAgICAgICAgICAgICAgICAgfVxuICAgICAgICAgICAgICAgICAgICAgICAgLyogYzggaWdub3JlIHN0b3AgKi9cbiAgICAgICAgICAgICAgICAgICAgICAgIHBhcnQuY29weUluKHBwLiNwYXJ0c1tpXSk7XG4gICAgICAgICAgICAgICAgICAgIH1cbiAgICAgICAgICAgICAgICB9XG4gICAgICAgICAgICAgICAgcCA9IHBwO1xuICAgICAgICAgICAgICAgIHBwID0gcC4jcGFyZW50O1xuICAgICAgICAgICAgfVxuICAgICAgICB9XG4gICAgICAgIHJldHVybiB0aGlzO1xuICAgIH1cbiAgICBwdXNoKC4uLnBhcnRzKSB7XG4gICAgICAgIGZvciAoY29uc3QgcCBvZiBwYXJ0cykge1xuICAgICAgICAgICAgaWYgKHAgPT09ICcnKVxuICAgICAgICAgICAgICAgIGNvbnRpbnVlO1xuICAgICAgICAgICAgLyogYzggaWdub3JlIHN0YXJ0ICovXG4gICAgICAgICAgICBpZiAodHlwZW9mIHAgIT09ICdzdHJpbmcnICYmICEocCBpbnN0YW5jZW9mIEFTVCAmJiBwLiNwYXJlbnQgPT09IHRoaXMpKSB7XG4gICAgICAgICAgICAgICAgdGhyb3cgbmV3IEVycm9yKCdpbnZhbGlkIHBhcnQ6ICcgKyBwKTtcbiAgICAgICAgICAgIH1cbiAgICAgICAgICAgIC8qIGM4IGlnbm9yZSBzdG9wICovXG4gICAgICAgICAgICB0aGlzLiNwYXJ0cy5wdXNoKHApO1xuICAgICAgICB9XG4gICAgfVxuICAgIHRvSlNPTigpIHtcbiAgICAgICAgY29uc3QgcmV0ID0gdGhpcy50eXBlID09PSBudWxsXG4gICAgICAgICAgICA/IHRoaXMuI3BhcnRzLnNsaWNlKCkubWFwKHAgPT4gKHR5cGVvZiBwID09PSAnc3RyaW5nJyA/IHAgOiBwLnRvSlNPTigpKSlcbiAgICAgICAgICAgIDogW3RoaXMudHlwZSwgLi4udGhpcy4jcGFydHMubWFwKHAgPT4gcC50b0pTT04oKSldO1xuICAgICAgICBpZiAodGhpcy5pc1N0YXJ0KCkgJiYgIXRoaXMudHlwZSlcbiAgICAgICAgICAgIHJldC51bnNoaWZ0KFtdKTtcbiAgICAgICAgaWYgKHRoaXMuaXNFbmQoKSAmJlxuICAgICAgICAgICAgKHRoaXMgPT09IHRoaXMuI3Jvb3QgfHxcbiAgICAgICAgICAgICAgICAodGhpcy4jcm9vdC4jZmlsbGVkTmVncyAmJiB0aGlzLiNwYXJlbnQ/LnR5cGUgPT09ICchJykpKSB7XG4gICAgICAgICAgICByZXQucHVzaCh7fSk7XG4gICAgICAgIH1cbiAgICAgICAgcmV0dXJuIHJldDtcbiAgICB9XG4gICAgaXNTdGFydCgpIHtcbiAgICAgICAgaWYgKHRoaXMuI3Jvb3QgPT09IHRoaXMpXG4gICAgICAgICAgICByZXR1cm4gdHJ1ZTtcbiAgICAgICAgLy8gaWYgKHRoaXMudHlwZSkgcmV0dXJuICEhdGhpcy4jcGFyZW50Py5pc1N0YXJ0KClcbiAgICAgICAgaWYgKCF0aGlzLiNwYXJlbnQ/LmlzU3RhcnQoKSlcbiAgICAgICAgICAgIHJldHVybiBmYWxzZTtcbiAgICAgICAgaWYgKHRoaXMuI3BhcmVudEluZGV4ID09PSAwKVxuICAgICAgICAgICAgcmV0dXJuIHRydWU7XG4gICAgICAgIC8vIGlmIGV2ZXJ5dGhpbmcgQUhFQUQgb2YgdGhpcyBpcyBhIG5lZ2F0aW9uLCB0aGVuIGl0J3Mgc3RpbGwgdGhlIFwic3RhcnRcIlxuICAgICAgICBjb25zdCBwID0gdGhpcy4jcGFyZW50O1xuICAgICAgICBmb3IgKGxldCBpID0gMDsgaSA8IHRoaXMuI3BhcmVudEluZGV4OyBpKyspIHtcbiAgICAgICAgICAgIGNvbnN0IHBwID0gcC4jcGFydHNbaV07XG4gICAgICAgICAgICBpZiAoIShwcCBpbnN0YW5jZW9mIEFTVCAmJiBwcC50eXBlID09PSAnIScpKSB7XG4gICAgICAgICAgICAgICAgcmV0dXJuIGZhbHNlO1xuICAgICAgICAgICAgfVxuICAgICAgICB9XG4gICAgICAgIHJldHVybiB0cnVlO1xuICAgIH1cbiAgICBpc0VuZCgpIHtcbiAgICAgICAgaWYgKHRoaXMuI3Jvb3QgPT09IHRoaXMpXG4gICAgICAgICAgICByZXR1cm4gdHJ1ZTtcbiAgICAgICAgaWYgKHRoaXMuI3BhcmVudD8udHlwZSA9PT0gJyEnKVxuICAgICAgICAgICAgcmV0dXJuIHRydWU7XG4gICAgICAgIGlmICghdGhpcy4jcGFyZW50Py5pc0VuZCgpKVxuICAgICAgICAgICAgcmV0dXJuIGZhbHNlO1xuICAgICAgICBpZiAoIXRoaXMudHlwZSlcbiAgICAgICAgICAgIHJldHVybiB0aGlzLiNwYXJlbnQ/LmlzRW5kKCk7XG4gICAgICAgIC8vIGlmIG5vdCByb290LCBpdCdsbCBhbHdheXMgaGF2ZSBhIHBhcmVudFxuICAgICAgICAvKiBjOCBpZ25vcmUgc3RhcnQgKi9cbiAgICAgICAgY29uc3QgcGwgPSB0aGlzLiNwYXJlbnQgPyB0aGlzLiNwYXJlbnQuI3BhcnRzLmxlbmd0aCA6IDA7XG4gICAgICAgIC8qIGM4IGlnbm9yZSBzdG9wICovXG4gICAgICAgIHJldHVybiB0aGlzLiNwYXJlbnRJbmRleCA9PT0gcGwgLSAxO1xuICAgIH1cbiAgICBjb3B5SW4ocGFydCkge1xuICAgICAgICBpZiAodHlwZW9mIHBhcnQgPT09ICdzdHJpbmcnKVxuICAgICAgICAgICAgdGhpcy5wdXNoKHBhcnQpO1xuICAgICAgICBlbHNlXG4gICAgICAgICAgICB0aGlzLnB1c2gocGFydC5jbG9uZSh0aGlzKSk7XG4gICAgfVxuICAgIGNsb25lKHBhcmVudCkge1xuICAgICAgICBjb25zdCBjID0gbmV3IEFTVCh0aGlzLnR5cGUsIHBhcmVudCk7XG4gICAgICAgIGZvciAoY29uc3QgcCBvZiB0aGlzLiNwYXJ0cykge1xuICAgICAgICAgICAgYy5jb3B5SW4ocCk7XG4gICAgICAgIH1cbiAgICAgICAgcmV0dXJuIGM7XG4gICAgfVxuICAgIHN0YXRpYyAjcGFyc2VBU1Qoc3RyLCBhc3QsIHBvcywgb3B0KSB7XG4gICAgICAgIGxldCBlc2NhcGluZyA9IGZhbHNlO1xuICAgICAgICBsZXQgaW5CcmFjZSA9IGZhbHNlO1xuICAgICAgICBsZXQgYnJhY2VTdGFydCA9IC0xO1xuICAgICAgICBsZXQgYnJhY2VOZWcgPSBmYWxzZTtcbiAgICAgICAgaWYgKGFzdC50eXBlID09PSBudWxsKSB7XG4gICAgICAgICAgICAvLyBvdXRzaWRlIG9mIGEgZXh0Z2xvYiwgYXBwZW5kIHVudGlsIHdlIGZpbmQgYSBzdGFydFxuICAgICAgICAgICAgbGV0IGkgPSBwb3M7XG4gICAgICAgICAgICBsZXQgYWNjID0gJyc7XG4gICAgICAgICAgICB3aGlsZSAoaSA8IHN0ci5sZW5ndGgpIHtcbiAgICAgICAgICAgICAgICBjb25zdCBjID0gc3RyLmNoYXJBdChpKyspO1xuICAgICAgICAgICAgICAgIC8vIHN0aWxsIGFjY3VtdWxhdGUgZXNjYXBlcyBhdCB0aGlzIHBvaW50LCBidXQgd2UgZG8gaWdub3JlXG4gICAgICAgICAgICAgICAgLy8gc3RhcnRzIHRoYXQgYXJlIGVzY2FwZWRcbiAgICAgICAgICAgICAgICBpZiAoZXNjYXBpbmcgfHwgYyA9PT0gJ1xcXFwnKSB7XG4gICAgICAgICAgICAgICAgICAgIGVzY2FwaW5nID0gIWVzY2FwaW5nO1xuICAgICAgICAgICAgICAgICAgICBhY2MgKz0gYztcbiAgICAgICAgICAgICAgICAgICAgY29udGludWU7XG4gICAgICAgICAgICAgICAgfVxuICAgICAgICAgICAgICAgIGlmIChpbkJyYWNlKSB7XG4gICAgICAgICAgICAgICAgICAgIGlmIChpID09PSBicmFjZVN0YXJ0ICsgMSkge1xuICAgICAgICAgICAgICAgICAgICAgICAgaWYgKGMgPT09ICdeJyB8fCBjID09PSAnIScpIHtcbiAgICAgICAgICAgICAgICAgICAgICAgICAgICBicmFjZU5lZyA9IHRydWU7XG4gICAgICAgICAgICAgICAgICAgICAgICB9XG4gICAgICAgICAgICAgICAgICAgIH1cbiAgICAgICAgICAgICAgICAgICAgZWxzZSBpZiAoYyA9PT0gJ10nICYmICEoaSA9PT0gYnJhY2VTdGFydCArIDIgJiYgYnJhY2VOZWcpKSB7XG4gICAgICAgICAgICAgICAgICAgICAgICBpbkJyYWNlID0gZmFsc2U7XG4gICAgICAgICAgICAgICAgICAgIH1cbiAgICAgICAgICAgICAgICAgICAgYWNjICs9IGM7XG4gICAgICAgICAgICAgICAgICAgIGNvbnRpbnVlO1xuICAgICAgICAgICAgICAgIH1cbiAgICAgICAgICAgICAgICBlbHNlIGlmIChjID09PSAnWycpIHtcbiAgICAgICAgICAgICAgICAgICAgaW5CcmFjZSA9IHRydWU7XG4gICAgICAgICAgICAgICAgICAgIGJyYWNlU3RhcnQgPSBpO1xuICAgICAgICAgICAgICAgICAgICBicmFjZU5lZyA9IGZhbHNlO1xuICAgICAgICAgICAgICAgICAgICBhY2MgKz0gYztcbiAgICAgICAgICAgICAgICAgICAgY29udGludWU7XG4gICAgICAgICAgICAgICAgfVxuICAgICAgICAgICAgICAgIGlmICghb3B0Lm5vZXh0ICYmIGlzRXh0Z2xvYlR5cGUoYykgJiYgc3RyLmNoYXJBdChpKSA9PT0gJygnKSB7XG4gICAgICAgICAgICAgICAgICAgIGFzdC5wdXNoKGFjYyk7XG4gICAgICAgICAgICAgICAgICAgIGFjYyA9ICcnO1xuICAgICAgICAgICAgICAgICAgICBjb25zdCBleHQgPSBuZXcgQVNUKGMsIGFzdCk7XG4gICAgICAgICAgICAgICAgICAgIGkgPSBBU1QuI3BhcnNlQVNUKHN0ciwgZXh0LCBpLCBvcHQpO1xuICAgICAgICAgICAgICAgICAgICBhc3QucHVzaChleHQpO1xuICAgICAgICAgICAgICAgICAgICBjb250aW51ZTtcbiAgICAgICAgICAgICAgICB9XG4gICAgICAgICAgICAgICAgYWNjICs9IGM7XG4gICAgICAgICAgICB9XG4gICAgICAgICAgICBhc3QucHVzaChhY2MpO1xuICAgICAgICAgICAgcmV0dXJuIGk7XG4gICAgICAgIH1cbiAgICAgICAgLy8gc29tZSBraW5kIG9mIGV4dGdsb2IsIHBvcyBpcyBhdCB0aGUgKFxuICAgICAgICAvLyBmaW5kIHRoZSBuZXh0IHwgb3IgKVxuICAgICAgICBsZXQgaSA9IHBvcyArIDE7XG4gICAgICAgIGxldCBwYXJ0ID0gbmV3IEFTVChudWxsLCBhc3QpO1xuICAgICAgICBjb25zdCBwYXJ0cyA9IFtdO1xuICAgICAgICBsZXQgYWNjID0gJyc7XG4gICAgICAgIHdoaWxlIChpIDwgc3RyLmxlbmd0aCkge1xuICAgICAgICAgICAgY29uc3QgYyA9IHN0ci5jaGFyQXQoaSsrKTtcbiAgICAgICAgICAgIC8vIHN0aWxsIGFjY3VtdWxhdGUgZXNjYXBlcyBhdCB0aGlzIHBvaW50LCBidXQgd2UgZG8gaWdub3JlXG4gICAgICAgICAgICAvLyBzdGFydHMgdGhhdCBhcmUgZXNjYXBlZFxuICAgICAgICAgICAgaWYgKGVzY2FwaW5nIHx8IGMgPT09ICdcXFxcJykge1xuICAgICAgICAgICAgICAgIGVzY2FwaW5nID0gIWVzY2FwaW5nO1xuICAgICAgICAgICAgICAgIGFjYyArPSBjO1xuICAgICAgICAgICAgICAgIGNvbnRpbnVlO1xuICAgICAgICAgICAgfVxuICAgICAgICAgICAgaWYgKGluQnJhY2UpIHtcbiAgICAgICAgICAgICAgICBpZiAoaSA9PT0gYnJhY2VTdGFydCArIDEpIHtcbiAgICAgICAgICAgICAgICAgICAgaWYgKGMgPT09ICdeJyB8fCBjID09PSAnIScpIHtcbiAgICAgICAgICAgICAgICAgICAgICAgIGJyYWNlTmVnID0gdHJ1ZTtcbiAgICAgICAgICAgICAgICAgICAgfVxuICAgICAgICAgICAgICAgIH1cbiAgICAgICAgICAgICAgICBlbHNlIGlmIChjID09PSAnXScgJiYgIShpID09PSBicmFjZVN0YXJ0ICsgMiAmJiBicmFjZU5lZykpIHtcbiAgICAgICAgICAgICAgICAgICAgaW5CcmFjZSA9IGZhbHNlO1xuICAgICAgICAgICAgICAgIH1cbiAgICAgICAgICAgICAgICBhY2MgKz0gYztcbiAgICAgICAgICAgICAgICBjb250aW51ZTtcbiAgICAgICAgICAgIH1cbiAgICAgICAgICAgIGVsc2UgaWYgKGMgPT09ICdbJykge1xuICAgICAgICAgICAgICAgIGluQnJhY2UgPSB0cnVlO1xuICAgICAgICAgICAgICAgIGJyYWNlU3RhcnQgPSBpO1xuICAgICAgICAgICAgICAgIGJyYWNlTmVnID0gZmFsc2U7XG4gICAgICAgICAgICAgICAgYWNjICs9IGM7XG4gICAgICAgICAgICAgICAgY29udGludWU7XG4gICAgICAgICAgICB9XG4gICAgICAgICAgICBpZiAoaXNFeHRnbG9iVHlwZShjKSAmJiBzdHIuY2hhckF0KGkpID09PSAnKCcpIHtcbiAgICAgICAgICAgICAgICBwYXJ0LnB1c2goYWNjKTtcbiAgICAgICAgICAgICAgICBhY2MgPSAnJztcbiAgICAgICAgICAgICAgICBjb25zdCBleHQgPSBuZXcgQVNUKGMsIHBhcnQpO1xuICAgICAgICAgICAgICAgIHBhcnQucHVzaChleHQpO1xuICAgICAgICAgICAgICAgIGkgPSBBU1QuI3BhcnNlQVNUKHN0ciwgZXh0LCBpLCBvcHQpO1xuICAgICAgICAgICAgICAgIGNvbnRpbnVlO1xuICAgICAgICAgICAgfVxuICAgICAgICAgICAgaWYgKGMgPT09ICd8Jykge1xuICAgICAgICAgICAgICAgIHBhcnQucHVzaChhY2MpO1xuICAgICAgICAgICAgICAgIGFjYyA9ICcnO1xuICAgICAgICAgICAgICAgIHBhcnRzLnB1c2gocGFydCk7XG4gICAgICAgICAgICAgICAgcGFydCA9IG5ldyBBU1QobnVsbCwgYXN0KTtcbiAgICAgICAgICAgICAgICBjb250aW51ZTtcbiAgICAgICAgICAgIH1cbiAgICAgICAgICAgIGlmIChjID09PSAnKScpIHtcbiAgICAgICAgICAgICAgICBpZiAoYWNjID09PSAnJyAmJiBhc3QuI3BhcnRzLmxlbmd0aCA9PT0gMCkge1xuICAgICAgICAgICAgICAgICAgICBhc3QuI2VtcHR5RXh0ID0gdHJ1ZTtcbiAgICAgICAgICAgICAgICB9XG4gICAgICAgICAgICAgICAgcGFydC5wdXNoKGFjYyk7XG4gICAgICAgICAgICAgICAgYWNjID0gJyc7XG4gICAgICAgICAgICAgICAgYXN0LnB1c2goLi4ucGFydHMsIHBhcnQpO1xuICAgICAgICAgICAgICAgIHJldHVybiBpO1xuICAgICAgICAgICAgfVxuICAgICAgICAgICAgYWNjICs9IGM7XG4gICAgICAgIH1cbiAgICAgICAgLy8gdW5maW5pc2hlZCBleHRnbG9iXG4gICAgICAgIC8vIGlmIHdlIGdvdCBoZXJlLCBpdCB3YXMgYSBtYWxmb3JtZWQgZXh0Z2xvYiEgbm90IGFuIGV4dGdsb2IsIGJ1dFxuICAgICAgICAvLyBtYXliZSBzb21ldGhpbmcgZWxzZSBpbiB0aGVyZS5cbiAgICAgICAgYXN0LnR5cGUgPSBudWxsO1xuICAgICAgICBhc3QuI2hhc01hZ2ljID0gdW5kZWZpbmVkO1xuICAgICAgICBhc3QuI3BhcnRzID0gW3N0ci5zdWJzdHJpbmcocG9zIC0gMSldO1xuICAgICAgICByZXR1cm4gaTtcbiAgICB9XG4gICAgc3RhdGljIGZyb21HbG9iKHBhdHRlcm4sIG9wdGlvbnMgPSB7fSkge1xuICAgICAgICBjb25zdCBhc3QgPSBuZXcgQVNUKG51bGwsIHVuZGVmaW5lZCwgb3B0aW9ucyk7XG4gICAgICAgIEFTVC4jcGFyc2VBU1QocGF0dGVybiwgYXN0LCAwLCBvcHRpb25zKTtcbiAgICAgICAgcmV0dXJuIGFzdDtcbiAgICB9XG4gICAgLy8gcmV0dXJucyB0aGUgcmVndWxhciBleHByZXNzaW9uIGlmIHRoZXJlJ3MgbWFnaWMsIG9yIHRoZSB1bmVzY2FwZWRcbiAgICAvLyBzdHJpbmcgaWYgbm90LlxuICAgIHRvTU1QYXR0ZXJuKCkge1xuICAgICAgICAvLyBzaG91bGQgb25seSBiZSBjYWxsZWQgb24gcm9vdFxuICAgICAgICAvKiBjOCBpZ25vcmUgc3RhcnQgKi9cbiAgICAgICAgaWYgKHRoaXMgIT09IHRoaXMuI3Jvb3QpXG4gICAgICAgICAgICByZXR1cm4gdGhpcy4jcm9vdC50b01NUGF0dGVybigpO1xuICAgICAgICAvKiBjOCBpZ25vcmUgc3RvcCAqL1xuICAgICAgICBjb25zdCBnbG9iID0gdGhpcy50b1N0cmluZygpO1xuICAgICAgICBjb25zdCBbcmUsIGJvZHksIGhhc01hZ2ljLCB1ZmxhZ10gPSB0aGlzLnRvUmVnRXhwU291cmNlKCk7XG4gICAgICAgIC8vIGlmIHdlJ3JlIGluIG5vY2FzZSBtb2RlLCBhbmQgbm90IG5vY2FzZU1hZ2ljT25seSwgdGhlbiB3ZSBkb1xuICAgICAgICAvLyBzdGlsbCBuZWVkIGEgcmVndWxhciBleHByZXNzaW9uIGlmIHdlIGhhdmUgdG8gY2FzZS1pbnNlbnNpdGl2ZWx5XG4gICAgICAgIC8vIG1hdGNoIGNhcGl0YWwvbG93ZXJjYXNlIGNoYXJhY3RlcnMuXG4gICAgICAgIGNvbnN0IGFueU1hZ2ljID0gaGFzTWFnaWMgfHxcbiAgICAgICAgICAgIHRoaXMuI2hhc01hZ2ljIHx8XG4gICAgICAgICAgICAodGhpcy4jb3B0aW9ucy5ub2Nhc2UgJiZcbiAgICAgICAgICAgICAgICAhdGhpcy4jb3B0aW9ucy5ub2Nhc2VNYWdpY09ubHkgJiZcbiAgICAgICAgICAgICAgICBnbG9iLnRvVXBwZXJDYXNlKCkgIT09IGdsb2IudG9Mb3dlckNhc2UoKSk7XG4gICAgICAgIGlmICghYW55TWFnaWMpIHtcbiAgICAgICAgICAgIHJldHVybiBib2R5O1xuICAgICAgICB9XG4gICAgICAgIGNvbnN0IGZsYWdzID0gKHRoaXMuI29wdGlvbnMubm9jYXNlID8gJ2knIDogJycpICsgKHVmbGFnID8gJ3UnIDogJycpO1xuICAgICAgICByZXR1cm4gT2JqZWN0LmFzc2lnbihuZXcgUmVnRXhwKGBeJHtyZX0kYCwgZmxhZ3MpLCB7XG4gICAgICAgICAgICBfc3JjOiByZSxcbiAgICAgICAgICAgIF9nbG9iOiBnbG9iLFxuICAgICAgICB9KTtcbiAgICB9XG4gICAgZ2V0IG9wdGlvbnMoKSB7XG4gICAgICAgIHJldHVybiB0aGlzLiNvcHRpb25zO1xuICAgIH1cbiAgICAvLyByZXR1cm5zIHRoZSBzdHJpbmcgbWF0Y2gsIHRoZSByZWdleHAgc291cmNlLCB3aGV0aGVyIHRoZXJlJ3MgbWFnaWNcbiAgICAvLyBpbiB0aGUgcmVnZXhwIChzbyBhIHJlZ3VsYXIgZXhwcmVzc2lvbiBpcyByZXF1aXJlZCkgYW5kIHdoZXRoZXIgb3JcbiAgICAvLyBub3QgdGhlIHVmbGFnIGlzIG5lZWRlZCBmb3IgdGhlIHJlZ3VsYXIgZXhwcmVzc2lvbiAoZm9yIHBvc2l4IGNsYXNzZXMpXG4gICAgLy8gVE9ETzogaW5zdGVhZCBvZiBpbmplY3RpbmcgdGhlIHN0YXJ0L2VuZCBhdCB0aGlzIHBvaW50LCBqdXN0IHJldHVyblxuICAgIC8vIHRoZSBCT0RZIG9mIHRoZSByZWdleHAsIGFsb25nIHdpdGggdGhlIHN0YXJ0L2VuZCBwb3J0aW9ucyBzdWl0YWJsZVxuICAgIC8vIGZvciBiaW5kaW5nIHRoZSBzdGFydC9lbmQgaW4gZWl0aGVyIGEgam9pbmVkIGZ1bGwtcGF0aCBtYWtlUmUgY29udGV4dFxuICAgIC8vICh3aGVyZSB3ZSBiaW5kIHRvIChefC8pLCBvciBhIHN0YW5kYWxvbmUgbWF0Y2hQYXJ0IGNvbnRleHQgKHdoZXJlXG4gICAgLy8gd2UgYmluZCB0byBeLCBhbmQgbm90IC8pLiAgT3RoZXJ3aXNlIHNsYXNoZXMgZ2V0IGR1cGVkIVxuICAgIC8vXG4gICAgLy8gSW4gcGFydC1tYXRjaGluZyBtb2RlLCB0aGUgc3RhcnQgaXM6XG4gICAgLy8gLSBpZiBub3QgaXNTdGFydDogbm90aGluZ1xuICAgIC8vIC0gaWYgdHJhdmVyc2FsIHBvc3NpYmxlLCBidXQgbm90IGFsbG93ZWQ6IF4oPyFcXC5cXC4/JClcbiAgICAvLyAtIGlmIGRvdHMgYWxsb3dlZCBvciBub3QgcG9zc2libGU6IF5cbiAgICAvLyAtIGlmIGRvdHMgcG9zc2libGUgYW5kIG5vdCBhbGxvd2VkOiBeKD8hXFwuKVxuICAgIC8vIGVuZCBpczpcbiAgICAvLyAtIGlmIG5vdCBpc0VuZCgpOiBub3RoaW5nXG4gICAgLy8gLSBlbHNlOiAkXG4gICAgLy9cbiAgICAvLyBJbiBmdWxsLXBhdGggbWF0Y2hpbmcgbW9kZSwgd2UgcHV0IHRoZSBzbGFzaCBhdCB0aGUgU1RBUlQgb2YgdGhlXG4gICAgLy8gcGF0dGVybiwgc28gc3RhcnQgaXM6XG4gICAgLy8gLSBpZiBmaXJzdCBwYXR0ZXJuOiBzYW1lIGFzIHBhcnQtbWF0Y2hpbmcgbW9kZVxuICAgIC8vIC0gaWYgbm90IGlzU3RhcnQoKTogbm90aGluZ1xuICAgIC8vIC0gaWYgdHJhdmVyc2FsIHBvc3NpYmxlLCBidXQgbm90IGFsbG93ZWQ6IC8oPyFcXC5cXC4/KD86JHwvKSlcbiAgICAvLyAtIGlmIGRvdHMgYWxsb3dlZCBvciBub3QgcG9zc2libGU6IC9cbiAgICAvLyAtIGlmIGRvdHMgcG9zc2libGUgYW5kIG5vdCBhbGxvd2VkOiAvKD8hXFwuKVxuICAgIC8vIGVuZCBpczpcbiAgICAvLyAtIGlmIGxhc3QgcGF0dGVybiwgc2FtZSBhcyBwYXJ0LW1hdGNoaW5nIG1vZGVcbiAgICAvLyAtIGVsc2Ugbm90aGluZ1xuICAgIC8vXG4gICAgLy8gQWx3YXlzIHB1dCB0aGUgKD86JHwvKSBvbiBuZWdhdGVkIHRhaWxzLCB0aG91Z2gsIGJlY2F1c2UgdGhhdCBoYXMgdG8gYmVcbiAgICAvLyB0aGVyZSB0byBiaW5kIHRoZSBlbmQgb2YgdGhlIG5lZ2F0ZWQgcGF0dGVybiBwb3J0aW9uLCBhbmQgaXQncyBlYXNpZXIgdG9cbiAgICAvLyBqdXN0IHN0aWNrIGl0IGluIG5vdyByYXRoZXIgdGhhbiB0cnkgdG8gaW5qZWN0IGl0IGxhdGVyIGluIHRoZSBtaWRkbGUgb2ZcbiAgICAvLyB0aGUgcGF0dGVybi5cbiAgICAvL1xuICAgIC8vIFdlIGNhbiBqdXN0IGFsd2F5cyByZXR1cm4gdGhlIHNhbWUgZW5kLCBhbmQgbGVhdmUgaXQgdXAgdG8gdGhlIGNhbGxlclxuICAgIC8vIHRvIGtub3cgd2hldGhlciBpdCdzIGdvaW5nIHRvIGJlIHVzZWQgam9pbmVkIG9yIGluIHBhcnRzLlxuICAgIC8vIEFuZCwgaWYgdGhlIHN0YXJ0IGlzIGFkanVzdGVkIHNsaWdodGx5LCBjYW4gZG8gdGhlIHNhbWUgdGhlcmU6XG4gICAgLy8gLSBpZiBub3QgaXNTdGFydDogbm90aGluZ1xuICAgIC8vIC0gaWYgdHJhdmVyc2FsIHBvc3NpYmxlLCBidXQgbm90IGFsbG93ZWQ6ICg/Oi98XikoPyFcXC5cXC4/JClcbiAgICAvLyAtIGlmIGRvdHMgYWxsb3dlZCBvciBub3QgcG9zc2libGU6ICg/Oi98XilcbiAgICAvLyAtIGlmIGRvdHMgcG9zc2libGUgYW5kIG5vdCBhbGxvd2VkOiAoPzovfF4pKD8hXFwuKVxuICAgIC8vXG4gICAgLy8gQnV0IGl0J3MgYmV0dGVyIHRvIGhhdmUgYSBzaW1wbGVyIGJpbmRpbmcgd2l0aG91dCBhIGNvbmRpdGlvbmFsLCBmb3JcbiAgICAvLyBwZXJmb3JtYW5jZSwgc28gcHJvYmFibHkgYmV0dGVyIHRvIHJldHVybiBib3RoIHN0YXJ0IG9wdGlvbnMuXG4gICAgLy9cbiAgICAvLyBUaGVuIHRoZSBjYWxsZXIganVzdCBpZ25vcmVzIHRoZSBlbmQgaWYgaXQncyBub3QgdGhlIGZpcnN0IHBhdHRlcm4sXG4gICAgLy8gYW5kIHRoZSBzdGFydCBhbHdheXMgZ2V0cyBhcHBsaWVkLlxuICAgIC8vXG4gICAgLy8gQnV0IHRoYXQncyBhbHdheXMgZ29pbmcgdG8gYmUgJCBpZiBpdCdzIHRoZSBlbmRpbmcgcGF0dGVybiwgb3Igbm90aGluZyxcbiAgICAvLyBzbyB0aGUgY2FsbGVyIGNhbiBqdXN0IGF0dGFjaCAkIGF0IHRoZSBlbmQgb2YgdGhlIHBhdHRlcm4gd2hlbiBidWlsZGluZy5cbiAgICAvL1xuICAgIC8vIFNvIHRoZSB0b2RvIGlzOlxuICAgIC8vIC0gYmV0dGVyIGRldGVjdCB3aGF0IGtpbmQgb2Ygc3RhcnQgaXMgbmVlZGVkXG4gICAgLy8gLSByZXR1cm4gYm90aCBmbGF2b3JzIG9mIHN0YXJ0aW5nIHBhdHRlcm5cbiAgICAvLyAtIGF0dGFjaCAkIGF0IHRoZSBlbmQgb2YgdGhlIHBhdHRlcm4gd2hlbiBjcmVhdGluZyB0aGUgYWN0dWFsIFJlZ0V4cFxuICAgIC8vXG4gICAgLy8gQWgsIGJ1dCB3YWl0LCBubywgdGhhdCBhbGwgb25seSBhcHBsaWVzIHRvIHRoZSByb290IHdoZW4gdGhlIGZpcnN0IHBhdHRlcm5cbiAgICAvLyBpcyBub3QgYW4gZXh0Z2xvYi4gSWYgdGhlIGZpcnN0IHBhdHRlcm4gSVMgYW4gZXh0Z2xvYiwgdGhlbiB3ZSBuZWVkIGFsbFxuICAgIC8vIHRoYXQgZG90IHByZXZlbnRpb24gYml6IHRvIGxpdmUgaW4gdGhlIGV4dGdsb2IgcG9ydGlvbnMsIGJlY2F1c2UgZWdcbiAgICAvLyArKCp8LngqKSBjYW4gbWF0Y2ggLnh5IGJ1dCBub3QgLnl4LlxuICAgIC8vXG4gICAgLy8gU28sIHJldHVybiB0aGUgdHdvIGZsYXZvcnMgaWYgaXQncyAjcm9vdCBhbmQgdGhlIGZpcnN0IGNoaWxkIGlzIG5vdCBhblxuICAgIC8vIEFTVCwgb3RoZXJ3aXNlIGxlYXZlIGl0IHRvIHRoZSBjaGlsZCBBU1QgdG8gaGFuZGxlIGl0LCBhbmQgdGhlcmUsXG4gICAgLy8gdXNlIHRoZSAoPzpefC8pIHN0eWxlIG9mIHN0YXJ0IGJpbmRpbmcuXG4gICAgLy9cbiAgICAvLyBFdmVuIHNpbXBsaWZpZWQgZnVydGhlcjpcbiAgICAvLyAtIFNpbmNlIHRoZSBzdGFydCBmb3IgYSBqb2luIGlzIGVnIC8oPyFcXC4pIGFuZCB0aGUgc3RhcnQgZm9yIGEgcGFydFxuICAgIC8vIGlzIF4oPyFcXC4pLCB3ZSBjYW4ganVzdCBwcmVwZW5kICg/IVxcLikgdG8gdGhlIHBhdHRlcm4gKGVpdGhlciByb290XG4gICAgLy8gb3Igc3RhcnQgb3Igd2hhdGV2ZXIpIGFuZCBwcmVwZW5kIF4gb3IgLyBhdCB0aGUgUmVnZXhwIGNvbnN0cnVjdGlvbi5cbiAgICB0b1JlZ0V4cFNvdXJjZShhbGxvd0RvdCkge1xuICAgICAgICBjb25zdCBkb3QgPSBhbGxvd0RvdCA/PyAhIXRoaXMuI29wdGlvbnMuZG90O1xuICAgICAgICBpZiAodGhpcy4jcm9vdCA9PT0gdGhpcylcbiAgICAgICAgICAgIHRoaXMuI2ZpbGxOZWdzKCk7XG4gICAgICAgIGlmICghdGhpcy50eXBlKSB7XG4gICAgICAgICAgICBjb25zdCBub0VtcHR5ID0gdGhpcy5pc1N0YXJ0KCkgJiYgdGhpcy5pc0VuZCgpO1xuICAgICAgICAgICAgY29uc3Qgc3JjID0gdGhpcy4jcGFydHNcbiAgICAgICAgICAgICAgICAubWFwKHAgPT4ge1xuICAgICAgICAgICAgICAgIGNvbnN0IFtyZSwgXywgaGFzTWFnaWMsIHVmbGFnXSA9IHR5cGVvZiBwID09PSAnc3RyaW5nJ1xuICAgICAgICAgICAgICAgICAgICA/IEFTVC4jcGFyc2VHbG9iKHAsIHRoaXMuI2hhc01hZ2ljLCBub0VtcHR5KVxuICAgICAgICAgICAgICAgICAgICA6IHAudG9SZWdFeHBTb3VyY2UoYWxsb3dEb3QpO1xuICAgICAgICAgICAgICAgIHRoaXMuI2hhc01hZ2ljID0gdGhpcy4jaGFzTWFnaWMgfHwgaGFzTWFnaWM7XG4gICAgICAgICAgICAgICAgdGhpcy4jdWZsYWcgPSB0aGlzLiN1ZmxhZyB8fCB1ZmxhZztcbiAgICAgICAgICAgICAgICByZXR1cm4gcmU7XG4gICAgICAgICAgICB9KVxuICAgICAgICAgICAgICAgIC5qb2luKCcnKTtcbiAgICAgICAgICAgIGxldCBzdGFydCA9ICcnO1xuICAgICAgICAgICAgaWYgKHRoaXMuaXNTdGFydCgpKSB7XG4gICAgICAgICAgICAgICAgaWYgKHR5cGVvZiB0aGlzLiNwYXJ0c1swXSA9PT0gJ3N0cmluZycpIHtcbiAgICAgICAgICAgICAgICAgICAgLy8gdGhpcyBpcyB0aGUgc3RyaW5nIHRoYXQgd2lsbCBtYXRjaCB0aGUgc3RhcnQgb2YgdGhlIHBhdHRlcm4sXG4gICAgICAgICAgICAgICAgICAgIC8vIHNvIHdlIG5lZWQgdG8gcHJvdGVjdCBhZ2FpbnN0IGRvdHMgYW5kIHN1Y2guXG4gICAgICAgICAgICAgICAgICAgIC8vICcuJyBhbmQgJy4uJyBjYW5ub3QgbWF0Y2ggdW5sZXNzIHRoZSBwYXR0ZXJuIGlzIHRoYXQgZXhhY3RseSxcbiAgICAgICAgICAgICAgICAgICAgLy8gZXZlbiBpZiBpdCBzdGFydHMgd2l0aCAuIG9yIGRvdDp0cnVlIGlzIHNldC5cbiAgICAgICAgICAgICAgICAgICAgY29uc3QgZG90VHJhdkFsbG93ZWQgPSB0aGlzLiNwYXJ0cy5sZW5ndGggPT09IDEgJiYganVzdERvdHMuaGFzKHRoaXMuI3BhcnRzWzBdKTtcbiAgICAgICAgICAgICAgICAgICAgaWYgKCFkb3RUcmF2QWxsb3dlZCkge1xuICAgICAgICAgICAgICAgICAgICAgICAgY29uc3QgYXBzID0gYWRkUGF0dGVyblN0YXJ0O1xuICAgICAgICAgICAgICAgICAgICAgICAgLy8gY2hlY2sgaWYgd2UgaGF2ZSBhIHBvc3NpYmlsaXR5IG9mIG1hdGNoaW5nIC4gb3IgLi4sXG4gICAgICAgICAgICAgICAgICAgICAgICAvLyBhbmQgcHJldmVudCB0aGF0LlxuICAgICAgICAgICAgICAgICAgICAgICAgY29uc3QgbmVlZE5vVHJhdiA9IFxuICAgICAgICAgICAgICAgICAgICAgICAgLy8gZG90cyBhcmUgYWxsb3dlZCwgYW5kIHRoZSBwYXR0ZXJuIHN0YXJ0cyB3aXRoIFsgb3IgLlxuICAgICAgICAgICAgICAgICAgICAgICAgKGRvdCAmJiBhcHMuaGFzKHNyYy5jaGFyQXQoMCkpKSB8fFxuICAgICAgICAgICAgICAgICAgICAgICAgICAgIC8vIHRoZSBwYXR0ZXJuIHN0YXJ0cyB3aXRoIFxcLiwgYW5kIHRoZW4gWyBvciAuXG4gICAgICAgICAgICAgICAgICAgICAgICAgICAgKHNyYy5zdGFydHNXaXRoKCdcXFxcLicpICYmIGFwcy5oYXMoc3JjLmNoYXJBdCgyKSkpIHx8XG4gICAgICAgICAgICAgICAgICAgICAgICAgICAgLy8gdGhlIHBhdHRlcm4gc3RhcnRzIHdpdGggXFwuXFwuLCBhbmQgdGhlbiBbIG9yIC5cbiAgICAgICAgICAgICAgICAgICAgICAgICAgICAoc3JjLnN0YXJ0c1dpdGgoJ1xcXFwuXFxcXC4nKSAmJiBhcHMuaGFzKHNyYy5jaGFyQXQoNCkpKTtcbiAgICAgICAgICAgICAgICAgICAgICAgIC8vIG5vIG5lZWQgdG8gcHJldmVudCBkb3RzIGlmIGl0IGNhbid0IG1hdGNoIGEgZG90LCBvciBpZiBhXG4gICAgICAgICAgICAgICAgICAgICAgICAvLyBzdWItcGF0dGVybiB3aWxsIGJlIHByZXZlbnRpbmcgaXQgYW55d2F5LlxuICAgICAgICAgICAgICAgICAgICAgICAgY29uc3QgbmVlZE5vRG90ID0gIWRvdCAmJiAhYWxsb3dEb3QgJiYgYXBzLmhhcyhzcmMuY2hhckF0KDApKTtcbiAgICAgICAgICAgICAgICAgICAgICAgIHN0YXJ0ID0gbmVlZE5vVHJhdiA/IHN0YXJ0Tm9UcmF2ZXJzYWwgOiBuZWVkTm9Eb3QgPyBzdGFydE5vRG90IDogJyc7XG4gICAgICAgICAgICAgICAgICAgIH1cbiAgICAgICAgICAgICAgICB9XG4gICAgICAgICAgICB9XG4gICAgICAgICAgICAvLyBhcHBlbmQgdGhlIFwiZW5kIG9mIHBhdGggcG9ydGlvblwiIHBhdHRlcm4gdG8gbmVnYXRpb24gdGFpbHNcbiAgICAgICAgICAgIGxldCBlbmQgPSAnJztcbiAgICAgICAgICAgIGlmICh0aGlzLmlzRW5kKCkgJiZcbiAgICAgICAgICAgICAgICB0aGlzLiNyb290LiNmaWxsZWROZWdzICYmXG4gICAgICAgICAgICAgICAgdGhpcy4jcGFyZW50Py50eXBlID09PSAnIScpIHtcbiAgICAgICAgICAgICAgICBlbmQgPSAnKD86JHxcXFxcLyknO1xuICAgICAgICAgICAgfVxuICAgICAgICAgICAgY29uc3QgZmluYWwgPSBzdGFydCArIHNyYyArIGVuZDtcbiAgICAgICAgICAgIHJldHVybiBbXG4gICAgICAgICAgICAgICAgZmluYWwsXG4gICAgICAgICAgICAgICAgKDAsIHVuZXNjYXBlX2pzXzEudW5lc2NhcGUpKHNyYyksXG4gICAgICAgICAgICAgICAgKHRoaXMuI2hhc01hZ2ljID0gISF0aGlzLiNoYXNNYWdpYyksXG4gICAgICAgICAgICAgICAgdGhpcy4jdWZsYWcsXG4gICAgICAgICAgICBdO1xuICAgICAgICB9XG4gICAgICAgIC8vIFdlIG5lZWQgdG8gY2FsY3VsYXRlIHRoZSBib2R5ICp0d2ljZSogaWYgaXQncyBhIHJlcGVhdCBwYXR0ZXJuXG4gICAgICAgIC8vIGF0IHRoZSBzdGFydCwgb25jZSBpbiBub2RvdCBtb2RlLCB0aGVuIGFnYWluIGluIGRvdCBtb2RlLCBzbyBhXG4gICAgICAgIC8vIHBhdHRlcm4gbGlrZSAqKD8pIGNhbiBtYXRjaCAneC55J1xuICAgICAgICBjb25zdCByZXBlYXRlZCA9IHRoaXMudHlwZSA9PT0gJyonIHx8IHRoaXMudHlwZSA9PT0gJysnO1xuICAgICAgICAvLyBzb21lIGtpbmQgb2YgZXh0Z2xvYlxuICAgICAgICBjb25zdCBzdGFydCA9IHRoaXMudHlwZSA9PT0gJyEnID8gJyg/Oig/ISg/OicgOiAnKD86JztcbiAgICAgICAgbGV0IGJvZHkgPSB0aGlzLiNwYXJ0c1RvUmVnRXhwKGRvdCk7XG4gICAgICAgIGlmICh0aGlzLmlzU3RhcnQoKSAmJiB0aGlzLmlzRW5kKCkgJiYgIWJvZHkgJiYgdGhpcy50eXBlICE9PSAnIScpIHtcbiAgICAgICAgICAgIC8vIGludmFsaWQgZXh0Z2xvYiwgaGFzIHRvIGF0IGxlYXN0IGJlICpzb21ldGhpbmcqIHByZXNlbnQsIGlmIGl0J3NcbiAgICAgICAgICAgIC8vIHRoZSBlbnRpcmUgcGF0aCBwb3J0aW9uLlxuICAgICAgICAgICAgY29uc3QgcyA9IHRoaXMudG9TdHJpbmcoKTtcbiAgICAgICAgICAgIHRoaXMuI3BhcnRzID0gW3NdO1xuICAgICAgICAgICAgdGhpcy50eXBlID0gbnVsbDtcbiAgICAgICAgICAgIHRoaXMuI2hhc01hZ2ljID0gdW5kZWZpbmVkO1xuICAgICAgICAgICAgcmV0dXJuIFtzLCAoMCwgdW5lc2NhcGVfanNfMS51bmVzY2FwZSkodGhpcy50b1N0cmluZygpKSwgZmFsc2UsIGZhbHNlXTtcbiAgICAgICAgfVxuICAgICAgICAvLyBYWFggYWJzdHJhY3Qgb3V0IHRoaXMgbWFwIG1ldGhvZFxuICAgICAgICBsZXQgYm9keURvdEFsbG93ZWQgPSAhcmVwZWF0ZWQgfHwgYWxsb3dEb3QgfHwgZG90IHx8ICFzdGFydE5vRG90XG4gICAgICAgICAgICA/ICcnXG4gICAgICAgICAgICA6IHRoaXMuI3BhcnRzVG9SZWdFeHAodHJ1ZSk7XG4gICAgICAgIGlmIChib2R5RG90QWxsb3dlZCA9PT0gYm9keSkge1xuICAgICAgICAgICAgYm9keURvdEFsbG93ZWQgPSAnJztcbiAgICAgICAgfVxuICAgICAgICBpZiAoYm9keURvdEFsbG93ZWQpIHtcbiAgICAgICAgICAgIGJvZHkgPSBgKD86JHtib2R5fSkoPzoke2JvZHlEb3RBbGxvd2VkfSkqP2A7XG4gICAgICAgIH1cbiAgICAgICAgLy8gYW4gZW1wdHkgISgpIGlzIGV4YWN0bHkgZXF1aXZhbGVudCB0byBhIHN0YXJOb0VtcHR5XG4gICAgICAgIGxldCBmaW5hbCA9ICcnO1xuICAgICAgICBpZiAodGhpcy50eXBlID09PSAnIScgJiYgdGhpcy4jZW1wdHlFeHQpIHtcbiAgICAgICAgICAgIGZpbmFsID0gKHRoaXMuaXNTdGFydCgpICYmICFkb3QgPyBzdGFydE5vRG90IDogJycpICsgc3Rhck5vRW1wdHk7XG4gICAgICAgIH1cbiAgICAgICAgZWxzZSB7XG4gICAgICAgICAgICBjb25zdCBjbG9zZSA9IHRoaXMudHlwZSA9PT0gJyEnXG4gICAgICAgICAgICAgICAgPyAvLyAhKCkgbXVzdCBtYXRjaCBzb21ldGhpbmcsYnV0ICEoeCkgY2FuIG1hdGNoICcnXG4gICAgICAgICAgICAgICAgICAgICcpKScgK1xuICAgICAgICAgICAgICAgICAgICAgICAgKHRoaXMuaXNTdGFydCgpICYmICFkb3QgJiYgIWFsbG93RG90ID8gc3RhcnROb0RvdCA6ICcnKSArXG4gICAgICAgICAgICAgICAgICAgICAgICBzdGFyICtcbiAgICAgICAgICAgICAgICAgICAgICAgICcpJ1xuICAgICAgICAgICAgICAgIDogdGhpcy50eXBlID09PSAnQCdcbiAgICAgICAgICAgICAgICAgICAgPyAnKSdcbiAgICAgICAgICAgICAgICAgICAgOiB0aGlzLnR5cGUgPT09ICc/J1xuICAgICAgICAgICAgICAgICAgICAgICAgPyAnKT8nXG4gICAgICAgICAgICAgICAgICAgICAgICA6IHRoaXMudHlwZSA9PT0gJysnICYmIGJvZHlEb3RBbGxvd2VkXG4gICAgICAgICAgICAgICAgICAgICAgICAgICAgPyAnKSdcbiAgICAgICAgICAgICAgICAgICAgICAgICAgICA6IHRoaXMudHlwZSA9PT0gJyonICYmIGJvZHlEb3RBbGxvd2VkXG4gICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgID8gYCk/YFxuICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICA6IGApJHt0aGlzLnR5cGV9YDtcbiAgICAgICAgICAgIGZpbmFsID0gc3RhcnQgKyBib2R5ICsgY2xvc2U7XG4gICAgICAgIH1cbiAgICAgICAgcmV0dXJuIFtcbiAgICAgICAgICAgIGZpbmFsLFxuICAgICAgICAgICAgKDAsIHVuZXNjYXBlX2pzXzEudW5lc2NhcGUpKGJvZHkpLFxuICAgICAgICAgICAgKHRoaXMuI2hhc01hZ2ljID0gISF0aGlzLiNoYXNNYWdpYyksXG4gICAgICAgICAgICB0aGlzLiN1ZmxhZyxcbiAgICAgICAgXTtcbiAgICB9XG4gICAgI3BhcnRzVG9SZWdFeHAoZG90KSB7XG4gICAgICAgIHJldHVybiB0aGlzLiNwYXJ0c1xuICAgICAgICAgICAgLm1hcChwID0+IHtcbiAgICAgICAgICAgIC8vIGV4dGdsb2IgQVNUcyBzaG91bGQgb25seSBjb250YWluIHBhcmVudCBBU1RzXG4gICAgICAgICAgICAvKiBjOCBpZ25vcmUgc3RhcnQgKi9cbiAgICAgICAgICAgIGlmICh0eXBlb2YgcCA9PT0gJ3N0cmluZycpIHtcbiAgICAgICAgICAgICAgICB0aHJvdyBuZXcgRXJyb3IoJ3N0cmluZyB0eXBlIGluIGV4dGdsb2IgYXN0Pz8nKTtcbiAgICAgICAgICAgIH1cbiAgICAgICAgICAgIC8qIGM4IGlnbm9yZSBzdG9wICovXG4gICAgICAgICAgICAvLyBjYW4gaWdub3JlIGhhc01hZ2ljLCBiZWNhdXNlIGV4dGdsb2JzIGFyZSBhbHJlYWR5IGFsd2F5cyBtYWdpY1xuICAgICAgICAgICAgY29uc3QgW3JlLCBfLCBfaGFzTWFnaWMsIHVmbGFnXSA9IHAudG9SZWdFeHBTb3VyY2UoZG90KTtcbiAgICAgICAgICAgIHRoaXMuI3VmbGFnID0gdGhpcy4jdWZsYWcgfHwgdWZsYWc7XG4gICAgICAgICAgICByZXR1cm4gcmU7XG4gICAgICAgIH0pXG4gICAgICAgICAgICAuZmlsdGVyKHAgPT4gISh0aGlzLmlzU3RhcnQoKSAmJiB0aGlzLmlzRW5kKCkpIHx8ICEhcClcbiAgICAgICAgICAgIC5qb2luKCd8Jyk7XG4gICAgfVxuICAgIHN0YXRpYyAjcGFyc2VHbG9iKGdsb2IsIGhhc01hZ2ljLCBub0VtcHR5ID0gZmFsc2UpIHtcbiAgICAgICAgbGV0IGVzY2FwaW5nID0gZmFsc2U7XG4gICAgICAgIGxldCByZSA9ICcnO1xuICAgICAgICBsZXQgdWZsYWcgPSBmYWxzZTtcbiAgICAgICAgZm9yIChsZXQgaSA9IDA7IGkgPCBnbG9iLmxlbmd0aDsgaSsrKSB7XG4gICAgICAgICAgICBjb25zdCBjID0gZ2xvYi5jaGFyQXQoaSk7XG4gICAgICAgICAgICBpZiAoZXNjYXBpbmcpIHtcbiAgICAgICAgICAgICAgICBlc2NhcGluZyA9IGZhbHNlO1xuICAgICAgICAgICAgICAgIHJlICs9IChyZVNwZWNpYWxzLmhhcyhjKSA/ICdcXFxcJyA6ICcnKSArIGM7XG4gICAgICAgICAgICAgICAgY29udGludWU7XG4gICAgICAgICAgICB9XG4gICAgICAgICAgICBpZiAoYyA9PT0gJ1xcXFwnKSB7XG4gICAgICAgICAgICAgICAgaWYgKGkgPT09IGdsb2IubGVuZ3RoIC0gMSkge1xuICAgICAgICAgICAgICAgICAgICByZSArPSAnXFxcXFxcXFwnO1xuICAgICAgICAgICAgICAgIH1cbiAgICAgICAgICAgICAgICBlbHNlIHtcbiAgICAgICAgICAgICAgICAgICAgZXNjYXBpbmcgPSB0cnVlO1xuICAgICAgICAgICAgICAgIH1cbiAgICAgICAgICAgICAgICBjb250aW51ZTtcbiAgICAgICAgICAgIH1cbiAgICAgICAgICAgIGlmIChjID09PSAnWycpIHtcbiAgICAgICAgICAgICAgICBjb25zdCBbc3JjLCBuZWVkVWZsYWcsIGNvbnN1bWVkLCBtYWdpY10gPSAoMCwgYnJhY2VfZXhwcmVzc2lvbnNfanNfMS5wYXJzZUNsYXNzKShnbG9iLCBpKTtcbiAgICAgICAgICAgICAgICBpZiAoY29uc3VtZWQpIHtcbiAgICAgICAgICAgICAgICAgICAgcmUgKz0gc3JjO1xuICAgICAgICAgICAgICAgICAgICB1ZmxhZyA9IHVmbGFnIHx8IG5lZWRVZmxhZztcbiAgICAgICAgICAgICAgICAgICAgaSArPSBjb25zdW1lZCAtIDE7XG4gICAgICAgICAgICAgICAgICAgIGhhc01hZ2ljID0gaGFzTWFnaWMgfHwgbWFnaWM7XG4gICAgICAgICAgICAgICAgICAgIGNvbnRpbnVlO1xuICAgICAgICAgICAgICAgIH1cbiAgICAgICAgICAgIH1cbiAgICAgICAgICAgIGlmIChjID09PSAnKicpIHtcbiAgICAgICAgICAgICAgICBpZiAobm9FbXB0eSAmJiBnbG9iID09PSAnKicpXG4gICAgICAgICAgICAgICAgICAgIHJlICs9IHN0YXJOb0VtcHR5O1xuICAgICAgICAgICAgICAgIGVsc2VcbiAgICAgICAgICAgICAgICAgICAgcmUgKz0gc3RhcjtcbiAgICAgICAgICAgICAgICBoYXNNYWdpYyA9IHRydWU7XG4gICAgICAgICAgICAgICAgY29udGludWU7XG4gICAgICAgICAgICB9XG4gICAgICAgICAgICBpZiAoYyA9PT0gJz8nKSB7XG4gICAgICAgICAgICAgICAgcmUgKz0gcW1hcms7XG4gICAgICAgICAgICAgICAgaGFzTWFnaWMgPSB0cnVlO1xuICAgICAgICAgICAgICAgIGNvbnRpbnVlO1xuICAgICAgICAgICAgfVxuICAgICAgICAgICAgcmUgKz0gcmVnRXhwRXNjYXBlKGMpO1xuICAgICAgICB9XG4gICAgICAgIHJldHVybiBbcmUsICgwLCB1bmVzY2FwZV9qc18xLnVuZXNjYXBlKShnbG9iKSwgISFoYXNNYWdpYywgdWZsYWddO1xuICAgIH1cbn1cbmV4cG9ydHMuQVNUID0gQVNUO1xuLy8jIHNvdXJjZU1hcHBpbmdVUkw9YXN0LmpzLm1hcCIsIlwidXNlIHN0cmljdFwiO1xuLy8gdHJhbnNsYXRlIHRoZSB2YXJpb3VzIHBvc2l4IGNoYXJhY3RlciBjbGFzc2VzIGludG8gdW5pY29kZSBwcm9wZXJ0aWVzXG4vLyB0aGlzIHdvcmtzIGFjcm9zcyBhbGwgdW5pY29kZSBsb2NhbGVzXG5PYmplY3QuZGVmaW5lUHJvcGVydHkoZXhwb3J0cywgXCJfX2VzTW9kdWxlXCIsIHsgdmFsdWU6IHRydWUgfSk7XG5leHBvcnRzLnBhcnNlQ2xhc3MgPSB2b2lkIDA7XG4vLyB7IDxwb3NpeCBjbGFzcz46IFs8dHJhbnNsYXRpb24+LCAvdSBmbGFnIHJlcXVpcmVkLCBuZWdhdGVkXVxuY29uc3QgcG9zaXhDbGFzc2VzID0ge1xuICAgICdbOmFsbnVtOl0nOiBbJ1xcXFxwe0x9XFxcXHB7Tmx9XFxcXHB7TmR9JywgdHJ1ZV0sXG4gICAgJ1s6YWxwaGE6XSc6IFsnXFxcXHB7TH1cXFxccHtObH0nLCB0cnVlXSxcbiAgICAnWzphc2NpaTpdJzogWydcXFxceCcgKyAnMDAtXFxcXHgnICsgJzdmJywgZmFsc2VdLFxuICAgICdbOmJsYW5rOl0nOiBbJ1xcXFxwe1pzfVxcXFx0JywgdHJ1ZV0sXG4gICAgJ1s6Y250cmw6XSc6IFsnXFxcXHB7Q2N9JywgdHJ1ZV0sXG4gICAgJ1s6ZGlnaXQ6XSc6IFsnXFxcXHB7TmR9JywgdHJ1ZV0sXG4gICAgJ1s6Z3JhcGg6XSc6IFsnXFxcXHB7Wn1cXFxccHtDfScsIHRydWUsIHRydWVdLFxuICAgICdbOmxvd2VyOl0nOiBbJ1xcXFxwe0xsfScsIHRydWVdLFxuICAgICdbOnByaW50Ol0nOiBbJ1xcXFxwe0N9JywgdHJ1ZV0sXG4gICAgJ1s6cHVuY3Q6XSc6IFsnXFxcXHB7UH0nLCB0cnVlXSxcbiAgICAnWzpzcGFjZTpdJzogWydcXFxccHtafVxcXFx0XFxcXHJcXFxcblxcXFx2XFxcXGYnLCB0cnVlXSxcbiAgICAnWzp1cHBlcjpdJzogWydcXFxccHtMdX0nLCB0cnVlXSxcbiAgICAnWzp3b3JkOl0nOiBbJ1xcXFxwe0x9XFxcXHB7Tmx9XFxcXHB7TmR9XFxcXHB7UGN9JywgdHJ1ZV0sXG4gICAgJ1s6eGRpZ2l0Ol0nOiBbJ0EtRmEtZjAtOScsIGZhbHNlXSxcbn07XG4vLyBvbmx5IG5lZWQgdG8gZXNjYXBlIGEgZmV3IHRoaW5ncyBpbnNpZGUgb2YgYnJhY2UgZXhwcmVzc2lvbnNcbi8vIGVzY2FwZXM6IFsgXFwgXSAtXG5jb25zdCBicmFjZUVzY2FwZSA9IChzKSA9PiBzLnJlcGxhY2UoL1tbXFxdXFxcXC1dL2csICdcXFxcJCYnKTtcbi8vIGVzY2FwZSBhbGwgcmVnZXhwIG1hZ2ljIGNoYXJhY3RlcnNcbmNvbnN0IHJlZ2V4cEVzY2FwZSA9IChzKSA9PiBzLnJlcGxhY2UoL1stW1xcXXt9KCkqKz8uLFxcXFxeJHwjXFxzXS9nLCAnXFxcXCQmJyk7XG4vLyBldmVyeXRoaW5nIGhhcyBhbHJlYWR5IGJlZW4gZXNjYXBlZCwgd2UganVzdCBoYXZlIHRvIGpvaW5cbmNvbnN0IHJhbmdlc1RvU3RyaW5nID0gKHJhbmdlcykgPT4gcmFuZ2VzLmpvaW4oJycpO1xuLy8gdGFrZXMgYSBnbG9iIHN0cmluZyBhdCBhIHBvc2l4IGJyYWNlIGV4cHJlc3Npb24sIGFuZCByZXR1cm5zXG4vLyBhbiBlcXVpdmFsZW50IHJlZ3VsYXIgZXhwcmVzc2lvbiBzb3VyY2UsIGFuZCBib29sZWFuIGluZGljYXRpbmdcbi8vIHdoZXRoZXIgdGhlIC91IGZsYWcgbmVlZHMgdG8gYmUgYXBwbGllZCwgYW5kIHRoZSBudW1iZXIgb2YgY2hhcnNcbi8vIGNvbnN1bWVkIHRvIHBhcnNlIHRoZSBjaGFyYWN0ZXIgY2xhc3MuXG4vLyBUaGlzIGFsc28gcmVtb3ZlcyBvdXQgb2Ygb3JkZXIgcmFuZ2VzLCBhbmQgcmV0dXJucyAoJC4pIGlmIHRoZVxuLy8gZW50aXJlIGNsYXNzIGp1c3Qgbm8gZ29vZC5cbmNvbnN0IHBhcnNlQ2xhc3MgPSAoZ2xvYiwgcG9zaXRpb24pID0+IHtcbiAgICBjb25zdCBwb3MgPSBwb3NpdGlvbjtcbiAgICAvKiBjOCBpZ25vcmUgc3RhcnQgKi9cbiAgICBpZiAoZ2xvYi5jaGFyQXQocG9zKSAhPT0gJ1snKSB7XG4gICAgICAgIHRocm93IG5ldyBFcnJvcignbm90IGluIGEgYnJhY2UgZXhwcmVzc2lvbicpO1xuICAgIH1cbiAgICAvKiBjOCBpZ25vcmUgc3RvcCAqL1xuICAgIGNvbnN0IHJhbmdlcyA9IFtdO1xuICAgIGNvbnN0IG5lZ3MgPSBbXTtcbiAgICBsZXQgaSA9IHBvcyArIDE7XG4gICAgbGV0IHNhd1N0YXJ0ID0gZmFsc2U7XG4gICAgbGV0IHVmbGFnID0gZmFsc2U7XG4gICAgbGV0IGVzY2FwaW5nID0gZmFsc2U7XG4gICAgbGV0IG5lZ2F0ZSA9IGZhbHNlO1xuICAgIGxldCBlbmRQb3MgPSBwb3M7XG4gICAgbGV0IHJhbmdlU3RhcnQgPSAnJztcbiAgICBXSElMRTogd2hpbGUgKGkgPCBnbG9iLmxlbmd0aCkge1xuICAgICAgICBjb25zdCBjID0gZ2xvYi5jaGFyQXQoaSk7XG4gICAgICAgIGlmICgoYyA9PT0gJyEnIHx8IGMgPT09ICdeJykgJiYgaSA9PT0gcG9zICsgMSkge1xuICAgICAgICAgICAgbmVnYXRlID0gdHJ1ZTtcbiAgICAgICAgICAgIGkrKztcbiAgICAgICAgICAgIGNvbnRpbnVlO1xuICAgICAgICB9XG4gICAgICAgIGlmIChjID09PSAnXScgJiYgc2F3U3RhcnQgJiYgIWVzY2FwaW5nKSB7XG4gICAgICAgICAgICBlbmRQb3MgPSBpICsgMTtcbiAgICAgICAgICAgIGJyZWFrO1xuICAgICAgICB9XG4gICAgICAgIHNhd1N0YXJ0ID0gdHJ1ZTtcbiAgICAgICAgaWYgKGMgPT09ICdcXFxcJykge1xuICAgICAgICAgICAgaWYgKCFlc2NhcGluZykge1xuICAgICAgICAgICAgICAgIGVzY2FwaW5nID0gdHJ1ZTtcbiAgICAgICAgICAgICAgICBpKys7XG4gICAgICAgICAgICAgICAgY29udGludWU7XG4gICAgICAgICAgICB9XG4gICAgICAgICAgICAvLyBlc2NhcGVkIFxcIGNoYXIsIGZhbGwgdGhyb3VnaCBhbmQgdHJlYXQgbGlrZSBub3JtYWwgY2hhclxuICAgICAgICB9XG4gICAgICAgIGlmIChjID09PSAnWycgJiYgIWVzY2FwaW5nKSB7XG4gICAgICAgICAgICAvLyBlaXRoZXIgYSBwb3NpeCBjbGFzcywgYSBjb2xsYXRpb24gZXF1aXZhbGVudCwgb3IganVzdCBhIFtcbiAgICAgICAgICAgIGZvciAoY29uc3QgW2NscywgW3VuaXAsIHUsIG5lZ11dIG9mIE9iamVjdC5lbnRyaWVzKHBvc2l4Q2xhc3NlcykpIHtcbiAgICAgICAgICAgICAgICBpZiAoZ2xvYi5zdGFydHNXaXRoKGNscywgaSkpIHtcbiAgICAgICAgICAgICAgICAgICAgLy8gaW52YWxpZCwgW2EtW10gaXMgZmluZSwgYnV0IG5vdCBbYS1bOmFscGhhXV1cbiAgICAgICAgICAgICAgICAgICAgaWYgKHJhbmdlU3RhcnQpIHtcbiAgICAgICAgICAgICAgICAgICAgICAgIHJldHVybiBbJyQuJywgZmFsc2UsIGdsb2IubGVuZ3RoIC0gcG9zLCB0cnVlXTtcbiAgICAgICAgICAgICAgICAgICAgfVxuICAgICAgICAgICAgICAgICAgICBpICs9IGNscy5sZW5ndGg7XG4gICAgICAgICAgICAgICAgICAgIGlmIChuZWcpXG4gICAgICAgICAgICAgICAgICAgICAgICBuZWdzLnB1c2godW5pcCk7XG4gICAgICAgICAgICAgICAgICAgIGVsc2VcbiAgICAgICAgICAgICAgICAgICAgICAgIHJhbmdlcy5wdXNoKHVuaXApO1xuICAgICAgICAgICAgICAgICAgICB1ZmxhZyA9IHVmbGFnIHx8IHU7XG4gICAgICAgICAgICAgICAgICAgIGNvbnRpbnVlIFdISUxFO1xuICAgICAgICAgICAgICAgIH1cbiAgICAgICAgICAgIH1cbiAgICAgICAgfVxuICAgICAgICAvLyBub3cgaXQncyBqdXN0IGEgbm9ybWFsIGNoYXJhY3RlciwgZWZmZWN0aXZlbHlcbiAgICAgICAgZXNjYXBpbmcgPSBmYWxzZTtcbiAgICAgICAgaWYgKHJhbmdlU3RhcnQpIHtcbiAgICAgICAgICAgIC8vIHRocm93IHRoaXMgcmFuZ2UgYXdheSBpZiBpdCdzIG5vdCB2YWxpZCwgYnV0IG90aGVyc1xuICAgICAgICAgICAgLy8gY2FuIHN0aWxsIG1hdGNoLlxuICAgICAgICAgICAgaWYgKGMgPiByYW5nZVN0YXJ0KSB7XG4gICAgICAgICAgICAgICAgcmFuZ2VzLnB1c2goYnJhY2VFc2NhcGUocmFuZ2VTdGFydCkgKyAnLScgKyBicmFjZUVzY2FwZShjKSk7XG4gICAgICAgICAgICB9XG4gICAgICAgICAgICBlbHNlIGlmIChjID09PSByYW5nZVN0YXJ0KSB7XG4gICAgICAgICAgICAgICAgcmFuZ2VzLnB1c2goYnJhY2VFc2NhcGUoYykpO1xuICAgICAgICAgICAgfVxuICAgICAgICAgICAgcmFuZ2VTdGFydCA9ICcnO1xuICAgICAgICAgICAgaSsrO1xuICAgICAgICAgICAgY29udGludWU7XG4gICAgICAgIH1cbiAgICAgICAgLy8gbm93IG1pZ2h0IGJlIHRoZSBzdGFydCBvZiBhIHJhbmdlLlxuICAgICAgICAvLyBjYW4gYmUgZWl0aGVyIGMtZCBvciBjLV0gb3IgYzxtb3JlLi4uPl0gb3IgY10gYXQgdGhpcyBwb2ludFxuICAgICAgICBpZiAoZ2xvYi5zdGFydHNXaXRoKCctXScsIGkgKyAxKSkge1xuICAgICAgICAgICAgcmFuZ2VzLnB1c2goYnJhY2VFc2NhcGUoYyArICctJykpO1xuICAgICAgICAgICAgaSArPSAyO1xuICAgICAgICAgICAgY29udGludWU7XG4gICAgICAgIH1cbiAgICAgICAgaWYgKGdsb2Iuc3RhcnRzV2l0aCgnLScsIGkgKyAxKSkge1xuICAgICAgICAgICAgcmFuZ2VTdGFydCA9IGM7XG4gICAgICAgICAgICBpICs9IDI7XG4gICAgICAgICAgICBjb250aW51ZTtcbiAgICAgICAgfVxuICAgICAgICAvLyBub3QgdGhlIHN0YXJ0IG9mIGEgcmFuZ2UsIGp1c3QgYSBzaW5nbGUgY2hhcmFjdGVyXG4gICAgICAgIHJhbmdlcy5wdXNoKGJyYWNlRXNjYXBlKGMpKTtcbiAgICAgICAgaSsrO1xuICAgIH1cbiAgICBpZiAoZW5kUG9zIDwgaSkge1xuICAgICAgICAvLyBkaWRuJ3Qgc2VlIHRoZSBlbmQgb2YgdGhlIGNsYXNzLCBub3QgYSB2YWxpZCBjbGFzcyxcbiAgICAgICAgLy8gYnV0IG1pZ2h0IHN0aWxsIGJlIHZhbGlkIGFzIGEgbGl0ZXJhbCBtYXRjaC5cbiAgICAgICAgcmV0dXJuIFsnJywgZmFsc2UsIDAsIGZhbHNlXTtcbiAgICB9XG4gICAgLy8gaWYgd2UgZ290IG5vIHJhbmdlcyBhbmQgbm8gbmVnYXRlcywgdGhlbiB3ZSBoYXZlIGEgcmFuZ2UgdGhhdFxuICAgIC8vIGNhbm5vdCBwb3NzaWJseSBtYXRjaCBhbnl0aGluZywgYW5kIHRoYXQgcG9pc29ucyB0aGUgd2hvbGUgZ2xvYlxuICAgIGlmICghcmFuZ2VzLmxlbmd0aCAmJiAhbmVncy5sZW5ndGgpIHtcbiAgICAgICAgcmV0dXJuIFsnJC4nLCBmYWxzZSwgZ2xvYi5sZW5ndGggLSBwb3MsIHRydWVdO1xuICAgIH1cbiAgICAvLyBpZiB3ZSBnb3Qgb25lIHBvc2l0aXZlIHJhbmdlLCBhbmQgaXQncyBhIHNpbmdsZSBjaGFyYWN0ZXIsIHRoZW4gdGhhdCdzXG4gICAgLy8gbm90IGFjdHVhbGx5IGEgbWFnaWMgcGF0dGVybiwgaXQncyBqdXN0IHRoYXQgb25lIGxpdGVyYWwgY2hhcmFjdGVyLlxuICAgIC8vIHdlIHNob3VsZCBub3QgdHJlYXQgdGhhdCBhcyBcIm1hZ2ljXCIsIHdlIHNob3VsZCBqdXN0IHJldHVybiB0aGUgbGl0ZXJhbFxuICAgIC8vIGNoYXJhY3Rlci4gW19dIGlzIGEgcGVyZmVjdGx5IHZhbGlkIHdheSB0byBlc2NhcGUgZ2xvYiBtYWdpYyBjaGFycy5cbiAgICBpZiAobmVncy5sZW5ndGggPT09IDAgJiZcbiAgICAgICAgcmFuZ2VzLmxlbmd0aCA9PT0gMSAmJlxuICAgICAgICAvXlxcXFw/LiQvLnRlc3QocmFuZ2VzWzBdKSAmJlxuICAgICAgICAhbmVnYXRlKSB7XG4gICAgICAgIGNvbnN0IHIgPSByYW5nZXNbMF0ubGVuZ3RoID09PSAyID8gcmFuZ2VzWzBdLnNsaWNlKC0xKSA6IHJhbmdlc1swXTtcbiAgICAgICAgcmV0dXJuIFtyZWdleHBFc2NhcGUociksIGZhbHNlLCBlbmRQb3MgLSBwb3MsIGZhbHNlXTtcbiAgICB9XG4gICAgY29uc3Qgc3JhbmdlcyA9ICdbJyArIChuZWdhdGUgPyAnXicgOiAnJykgKyByYW5nZXNUb1N0cmluZyhyYW5nZXMpICsgJ10nO1xuICAgIGNvbnN0IHNuZWdzID0gJ1snICsgKG5lZ2F0ZSA/ICcnIDogJ14nKSArIHJhbmdlc1RvU3RyaW5nKG5lZ3MpICsgJ10nO1xuICAgIGNvbnN0IGNvbWIgPSByYW5nZXMubGVuZ3RoICYmIG5lZ3MubGVuZ3RoXG4gICAgICAgID8gJygnICsgc3JhbmdlcyArICd8JyArIHNuZWdzICsgJyknXG4gICAgICAgIDogcmFuZ2VzLmxlbmd0aFxuICAgICAgICAgICAgPyBzcmFuZ2VzXG4gICAgICAgICAgICA6IHNuZWdzO1xuICAgIHJldHVybiBbY29tYiwgdWZsYWcsIGVuZFBvcyAtIHBvcywgdHJ1ZV07XG59O1xuZXhwb3J0cy5wYXJzZUNsYXNzID0gcGFyc2VDbGFzcztcbi8vIyBzb3VyY2VNYXBwaW5nVVJMPWJyYWNlLWV4cHJlc3Npb25zLmpzLm1hcCIsIlwidXNlIHN0cmljdFwiO1xuT2JqZWN0LmRlZmluZVByb3BlcnR5KGV4cG9ydHMsIFwiX19lc01vZHVsZVwiLCB7IHZhbHVlOiB0cnVlIH0pO1xuZXhwb3J0cy5lc2NhcGUgPSB2b2lkIDA7XG4vKipcbiAqIEVzY2FwZSBhbGwgbWFnaWMgY2hhcmFjdGVycyBpbiBhIGdsb2IgcGF0dGVybi5cbiAqXG4gKiBJZiB0aGUge0BsaW5rIHdpbmRvd3NQYXRoc05vRXNjYXBlIHwgR2xvYk9wdGlvbnMud2luZG93c1BhdGhzTm9Fc2NhcGV9XG4gKiBvcHRpb24gaXMgdXNlZCwgdGhlbiBjaGFyYWN0ZXJzIGFyZSBlc2NhcGVkIGJ5IHdyYXBwaW5nIGluIGBbXWAsIGJlY2F1c2VcbiAqIGEgbWFnaWMgY2hhcmFjdGVyIHdyYXBwZWQgaW4gYSBjaGFyYWN0ZXIgY2xhc3MgY2FuIG9ubHkgYmUgc2F0aXNmaWVkIGJ5XG4gKiB0aGF0IGV4YWN0IGNoYXJhY3Rlci4gIEluIHRoaXMgbW9kZSwgYFxcYCBpcyBfbm90XyBlc2NhcGVkLCBiZWNhdXNlIGl0IGlzXG4gKiBub3QgaW50ZXJwcmV0ZWQgYXMgYSBtYWdpYyBjaGFyYWN0ZXIsIGJ1dCBpbnN0ZWFkIGFzIGEgcGF0aCBzZXBhcmF0b3IuXG4gKi9cbmNvbnN0IGVzY2FwZSA9IChzLCB7IHdpbmRvd3NQYXRoc05vRXNjYXBlID0gZmFsc2UsIH0gPSB7fSkgPT4ge1xuICAgIC8vIGRvbid0IG5lZWQgdG8gZXNjYXBlICtAISBiZWNhdXNlIHdlIGVzY2FwZSB0aGUgcGFyZW5zXG4gICAgLy8gdGhhdCBtYWtlIHRob3NlIG1hZ2ljLCBhbmQgZXNjYXBpbmcgISBhcyBbIV0gaXNuJ3QgdmFsaWQsXG4gICAgLy8gYmVjYXVzZSBbIV1dIGlzIGEgdmFsaWQgZ2xvYiBjbGFzcyBtZWFuaW5nIG5vdCAnXScuXG4gICAgcmV0dXJuIHdpbmRvd3NQYXRoc05vRXNjYXBlXG4gICAgICAgID8gcy5yZXBsYWNlKC9bPyooKVtcXF1dL2csICdbJCZdJylcbiAgICAgICAgOiBzLnJlcGxhY2UoL1s/KigpW1xcXVxcXFxdL2csICdcXFxcJCYnKTtcbn07XG5leHBvcnRzLmVzY2FwZSA9IGVzY2FwZTtcbi8vIyBzb3VyY2VNYXBwaW5nVVJMPWVzY2FwZS5qcy5tYXAiLCJcInVzZSBzdHJpY3RcIjtcbnZhciBfX2ltcG9ydERlZmF1bHQgPSAodGhpcyAmJiB0aGlzLl9faW1wb3J0RGVmYXVsdCkgfHwgZnVuY3Rpb24gKG1vZCkge1xuICAgIHJldHVybiAobW9kICYmIG1vZC5fX2VzTW9kdWxlKSA/IG1vZCA6IHsgXCJkZWZhdWx0XCI6IG1vZCB9O1xufTtcbk9iamVjdC5kZWZpbmVQcm9wZXJ0eShleHBvcnRzLCBcIl9fZXNNb2R1bGVcIiwgeyB2YWx1ZTogdHJ1ZSB9KTtcbmV4cG9ydHMudW5lc2NhcGUgPSBleHBvcnRzLmVzY2FwZSA9IGV4cG9ydHMuQVNUID0gZXhwb3J0cy5NaW5pbWF0Y2ggPSBleHBvcnRzLm1hdGNoID0gZXhwb3J0cy5tYWtlUmUgPSBleHBvcnRzLmJyYWNlRXhwYW5kID0gZXhwb3J0cy5kZWZhdWx0cyA9IGV4cG9ydHMuZmlsdGVyID0gZXhwb3J0cy5HTE9CU1RBUiA9IGV4cG9ydHMuc2VwID0gZXhwb3J0cy5taW5pbWF0Y2ggPSB2b2lkIDA7XG5jb25zdCBicmFjZV9leHBhbnNpb25fMSA9IF9faW1wb3J0RGVmYXVsdChyZXF1aXJlKFwiYnJhY2UtZXhwYW5zaW9uXCIpKTtcbmNvbnN0IGFzc2VydF92YWxpZF9wYXR0ZXJuX2pzXzEgPSByZXF1aXJlKFwiLi9hc3NlcnQtdmFsaWQtcGF0dGVybi5qc1wiKTtcbmNvbnN0IGFzdF9qc18xID0gcmVxdWlyZShcIi4vYXN0LmpzXCIpO1xuY29uc3QgZXNjYXBlX2pzXzEgPSByZXF1aXJlKFwiLi9lc2NhcGUuanNcIik7XG5jb25zdCB1bmVzY2FwZV9qc18xID0gcmVxdWlyZShcIi4vdW5lc2NhcGUuanNcIik7XG5jb25zdCBtaW5pbWF0Y2ggPSAocCwgcGF0dGVybiwgb3B0aW9ucyA9IHt9KSA9PiB7XG4gICAgKDAsIGFzc2VydF92YWxpZF9wYXR0ZXJuX2pzXzEuYXNzZXJ0VmFsaWRQYXR0ZXJuKShwYXR0ZXJuKTtcbiAgICAvLyBzaG9ydGN1dDogY29tbWVudHMgbWF0Y2ggbm90aGluZy5cbiAgICBpZiAoIW9wdGlvbnMubm9jb21tZW50ICYmIHBhdHRlcm4uY2hhckF0KDApID09PSAnIycpIHtcbiAgICAgICAgcmV0dXJuIGZhbHNlO1xuICAgIH1cbiAgICByZXR1cm4gbmV3IE1pbmltYXRjaChwYXR0ZXJuLCBvcHRpb25zKS5tYXRjaChwKTtcbn07XG5leHBvcnRzLm1pbmltYXRjaCA9IG1pbmltYXRjaDtcbi8vIE9wdGltaXplZCBjaGVja2luZyBmb3IgdGhlIG1vc3QgY29tbW9uIGdsb2IgcGF0dGVybnMuXG5jb25zdCBzdGFyRG90RXh0UkUgPSAvXlxcKisoW14rQCE/XFwqXFxbXFwoXSopJC87XG5jb25zdCBzdGFyRG90RXh0VGVzdCA9IChleHQpID0+IChmKSA9PiAhZi5zdGFydHNXaXRoKCcuJykgJiYgZi5lbmRzV2l0aChleHQpO1xuY29uc3Qgc3RhckRvdEV4dFRlc3REb3QgPSAoZXh0KSA9PiAoZikgPT4gZi5lbmRzV2l0aChleHQpO1xuY29uc3Qgc3RhckRvdEV4dFRlc3ROb2Nhc2UgPSAoZXh0KSA9PiB7XG4gICAgZXh0ID0gZXh0LnRvTG93ZXJDYXNlKCk7XG4gICAgcmV0dXJuIChmKSA9PiAhZi5zdGFydHNXaXRoKCcuJykgJiYgZi50b0xvd2VyQ2FzZSgpLmVuZHNXaXRoKGV4dCk7XG59O1xuY29uc3Qgc3RhckRvdEV4dFRlc3ROb2Nhc2VEb3QgPSAoZXh0KSA9PiB7XG4gICAgZXh0ID0gZXh0LnRvTG93ZXJDYXNlKCk7XG4gICAgcmV0dXJuIChmKSA9PiBmLnRvTG93ZXJDYXNlKCkuZW5kc1dpdGgoZXh0KTtcbn07XG5jb25zdCBzdGFyRG90U3RhclJFID0gL15cXCorXFwuXFwqKyQvO1xuY29uc3Qgc3RhckRvdFN0YXJUZXN0ID0gKGYpID0+ICFmLnN0YXJ0c1dpdGgoJy4nKSAmJiBmLmluY2x1ZGVzKCcuJyk7XG5jb25zdCBzdGFyRG90U3RhclRlc3REb3QgPSAoZikgPT4gZiAhPT0gJy4nICYmIGYgIT09ICcuLicgJiYgZi5pbmNsdWRlcygnLicpO1xuY29uc3QgZG90U3RhclJFID0gL15cXC5cXCorJC87XG5jb25zdCBkb3RTdGFyVGVzdCA9IChmKSA9PiBmICE9PSAnLicgJiYgZiAhPT0gJy4uJyAmJiBmLnN0YXJ0c1dpdGgoJy4nKTtcbmNvbnN0IHN0YXJSRSA9IC9eXFwqKyQvO1xuY29uc3Qgc3RhclRlc3QgPSAoZikgPT4gZi5sZW5ndGggIT09IDAgJiYgIWYuc3RhcnRzV2l0aCgnLicpO1xuY29uc3Qgc3RhclRlc3REb3QgPSAoZikgPT4gZi5sZW5ndGggIT09IDAgJiYgZiAhPT0gJy4nICYmIGYgIT09ICcuLic7XG5jb25zdCBxbWFya3NSRSA9IC9eXFw/KyhbXitAIT9cXCpcXFtcXChdKik/JC87XG5jb25zdCBxbWFya3NUZXN0Tm9jYXNlID0gKFskMCwgZXh0ID0gJyddKSA9PiB7XG4gICAgY29uc3Qgbm9leHQgPSBxbWFya3NUZXN0Tm9FeHQoWyQwXSk7XG4gICAgaWYgKCFleHQpXG4gICAgICAgIHJldHVybiBub2V4dDtcbiAgICBleHQgPSBleHQudG9Mb3dlckNhc2UoKTtcbiAgICByZXR1cm4gKGYpID0+IG5vZXh0KGYpICYmIGYudG9Mb3dlckNhc2UoKS5lbmRzV2l0aChleHQpO1xufTtcbmNvbnN0IHFtYXJrc1Rlc3ROb2Nhc2VEb3QgPSAoWyQwLCBleHQgPSAnJ10pID0+IHtcbiAgICBjb25zdCBub2V4dCA9IHFtYXJrc1Rlc3ROb0V4dERvdChbJDBdKTtcbiAgICBpZiAoIWV4dClcbiAgICAgICAgcmV0dXJuIG5vZXh0O1xuICAgIGV4dCA9IGV4dC50b0xvd2VyQ2FzZSgpO1xuICAgIHJldHVybiAoZikgPT4gbm9leHQoZikgJiYgZi50b0xvd2VyQ2FzZSgpLmVuZHNXaXRoKGV4dCk7XG59O1xuY29uc3QgcW1hcmtzVGVzdERvdCA9IChbJDAsIGV4dCA9ICcnXSkgPT4ge1xuICAgIGNvbnN0IG5vZXh0ID0gcW1hcmtzVGVzdE5vRXh0RG90KFskMF0pO1xuICAgIHJldHVybiAhZXh0ID8gbm9leHQgOiAoZikgPT4gbm9leHQoZikgJiYgZi5lbmRzV2l0aChleHQpO1xufTtcbmNvbnN0IHFtYXJrc1Rlc3QgPSAoWyQwLCBleHQgPSAnJ10pID0+IHtcbiAgICBjb25zdCBub2V4dCA9IHFtYXJrc1Rlc3ROb0V4dChbJDBdKTtcbiAgICByZXR1cm4gIWV4dCA/IG5vZXh0IDogKGYpID0+IG5vZXh0KGYpICYmIGYuZW5kc1dpdGgoZXh0KTtcbn07XG5jb25zdCBxbWFya3NUZXN0Tm9FeHQgPSAoWyQwXSkgPT4ge1xuICAgIGNvbnN0IGxlbiA9ICQwLmxlbmd0aDtcbiAgICByZXR1cm4gKGYpID0+IGYubGVuZ3RoID09PSBsZW4gJiYgIWYuc3RhcnRzV2l0aCgnLicpO1xufTtcbmNvbnN0IHFtYXJrc1Rlc3ROb0V4dERvdCA9IChbJDBdKSA9PiB7XG4gICAgY29uc3QgbGVuID0gJDAubGVuZ3RoO1xuICAgIHJldHVybiAoZikgPT4gZi5sZW5ndGggPT09IGxlbiAmJiBmICE9PSAnLicgJiYgZiAhPT0gJy4uJztcbn07XG4vKiBjOCBpZ25vcmUgc3RhcnQgKi9cbmNvbnN0IGRlZmF1bHRQbGF0Zm9ybSA9ICh0eXBlb2YgcHJvY2VzcyA9PT0gJ29iamVjdCcgJiYgcHJvY2Vzc1xuICAgID8gKHR5cGVvZiBwcm9jZXNzLmVudiA9PT0gJ29iamVjdCcgJiZcbiAgICAgICAgcHJvY2Vzcy5lbnYgJiZcbiAgICAgICAgcHJvY2Vzcy5lbnYuX19NSU5JTUFUQ0hfVEVTVElOR19QTEFURk9STV9fKSB8fFxuICAgICAgICBwcm9jZXNzLnBsYXRmb3JtXG4gICAgOiAncG9zaXgnKTtcbmNvbnN0IHBhdGggPSB7XG4gICAgd2luMzI6IHsgc2VwOiAnXFxcXCcgfSxcbiAgICBwb3NpeDogeyBzZXA6ICcvJyB9LFxufTtcbi8qIGM4IGlnbm9yZSBzdG9wICovXG5leHBvcnRzLnNlcCA9IGRlZmF1bHRQbGF0Zm9ybSA9PT0gJ3dpbjMyJyA/IHBhdGgud2luMzIuc2VwIDogcGF0aC5wb3NpeC5zZXA7XG5leHBvcnRzLm1pbmltYXRjaC5zZXAgPSBleHBvcnRzLnNlcDtcbmV4cG9ydHMuR0xPQlNUQVIgPSBTeW1ib2woJ2dsb2JzdGFyICoqJyk7XG5leHBvcnRzLm1pbmltYXRjaC5HTE9CU1RBUiA9IGV4cG9ydHMuR0xPQlNUQVI7XG4vLyBhbnkgc2luZ2xlIHRoaW5nIG90aGVyIHRoYW4gL1xuLy8gZG9uJ3QgbmVlZCB0byBlc2NhcGUgLyB3aGVuIHVzaW5nIG5ldyBSZWdFeHAoKVxuY29uc3QgcW1hcmsgPSAnW14vXSc7XG4vLyAqID0+IGFueSBudW1iZXIgb2YgY2hhcmFjdGVyc1xuY29uc3Qgc3RhciA9IHFtYXJrICsgJyo/Jztcbi8vICoqIHdoZW4gZG90cyBhcmUgYWxsb3dlZC4gIEFueXRoaW5nIGdvZXMsIGV4Y2VwdCAuLiBhbmQgLlxuLy8gbm90ICheIG9yIC8gZm9sbG93ZWQgYnkgb25lIG9yIHR3byBkb3RzIGZvbGxvd2VkIGJ5ICQgb3IgLyksXG4vLyBmb2xsb3dlZCBieSBhbnl0aGluZywgYW55IG51bWJlciBvZiB0aW1lcy5cbmNvbnN0IHR3b1N0YXJEb3QgPSAnKD86KD8hKD86XFxcXC98XikoPzpcXFxcLnsxLDJ9KSgkfFxcXFwvKSkuKSo/Jztcbi8vIG5vdCBhIF4gb3IgLyBmb2xsb3dlZCBieSBhIGRvdCxcbi8vIGZvbGxvd2VkIGJ5IGFueXRoaW5nLCBhbnkgbnVtYmVyIG9mIHRpbWVzLlxuY29uc3QgdHdvU3Rhck5vRG90ID0gJyg/Oig/ISg/OlxcXFwvfF4pXFxcXC4pLikqPyc7XG5jb25zdCBmaWx0ZXIgPSAocGF0dGVybiwgb3B0aW9ucyA9IHt9KSA9PiAocCkgPT4gKDAsIGV4cG9ydHMubWluaW1hdGNoKShwLCBwYXR0ZXJuLCBvcHRpb25zKTtcbmV4cG9ydHMuZmlsdGVyID0gZmlsdGVyO1xuZXhwb3J0cy5taW5pbWF0Y2guZmlsdGVyID0gZXhwb3J0cy5maWx0ZXI7XG5jb25zdCBleHQgPSAoYSwgYiA9IHt9KSA9PiBPYmplY3QuYXNzaWduKHt9LCBhLCBiKTtcbmNvbnN0IGRlZmF1bHRzID0gKGRlZikgPT4ge1xuICAgIGlmICghZGVmIHx8IHR5cGVvZiBkZWYgIT09ICdvYmplY3QnIHx8ICFPYmplY3Qua2V5cyhkZWYpLmxlbmd0aCkge1xuICAgICAgICByZXR1cm4gZXhwb3J0cy5taW5pbWF0Y2g7XG4gICAgfVxuICAgIGNvbnN0IG9yaWcgPSBleHBvcnRzLm1pbmltYXRjaDtcbiAgICBjb25zdCBtID0gKHAsIHBhdHRlcm4sIG9wdGlvbnMgPSB7fSkgPT4gb3JpZyhwLCBwYXR0ZXJuLCBleHQoZGVmLCBvcHRpb25zKSk7XG4gICAgcmV0dXJuIE9iamVjdC5hc3NpZ24obSwge1xuICAgICAgICBNaW5pbWF0Y2g6IGNsYXNzIE1pbmltYXRjaCBleHRlbmRzIG9yaWcuTWluaW1hdGNoIHtcbiAgICAgICAgICAgIGNvbnN0cnVjdG9yKHBhdHRlcm4sIG9wdGlvbnMgPSB7fSkge1xuICAgICAgICAgICAgICAgIHN1cGVyKHBhdHRlcm4sIGV4dChkZWYsIG9wdGlvbnMpKTtcbiAgICAgICAgICAgIH1cbiAgICAgICAgICAgIHN0YXRpYyBkZWZhdWx0cyhvcHRpb25zKSB7XG4gICAgICAgICAgICAgICAgcmV0dXJuIG9yaWcuZGVmYXVsdHMoZXh0KGRlZiwgb3B0aW9ucykpLk1pbmltYXRjaDtcbiAgICAgICAgICAgIH1cbiAgICAgICAgfSxcbiAgICAgICAgQVNUOiBjbGFzcyBBU1QgZXh0ZW5kcyBvcmlnLkFTVCB7XG4gICAgICAgICAgICAvKiBjOCBpZ25vcmUgc3RhcnQgKi9cbiAgICAgICAgICAgIGNvbnN0cnVjdG9yKHR5cGUsIHBhcmVudCwgb3B0aW9ucyA9IHt9KSB7XG4gICAgICAgICAgICAgICAgc3VwZXIodHlwZSwgcGFyZW50LCBleHQoZGVmLCBvcHRpb25zKSk7XG4gICAgICAgICAgICB9XG4gICAgICAgICAgICAvKiBjOCBpZ25vcmUgc3RvcCAqL1xuICAgICAgICAgICAgc3RhdGljIGZyb21HbG9iKHBhdHRlcm4sIG9wdGlvbnMgPSB7fSkge1xuICAgICAgICAgICAgICAgIHJldHVybiBvcmlnLkFTVC5mcm9tR2xvYihwYXR0ZXJuLCBleHQoZGVmLCBvcHRpb25zKSk7XG4gICAgICAgICAgICB9XG4gICAgICAgIH0sXG4gICAgICAgIHVuZXNjYXBlOiAocywgb3B0aW9ucyA9IHt9KSA9PiBvcmlnLnVuZXNjYXBlKHMsIGV4dChkZWYsIG9wdGlvbnMpKSxcbiAgICAgICAgZXNjYXBlOiAocywgb3B0aW9ucyA9IHt9KSA9PiBvcmlnLmVzY2FwZShzLCBleHQoZGVmLCBvcHRpb25zKSksXG4gICAgICAgIGZpbHRlcjogKHBhdHRlcm4sIG9wdGlvbnMgPSB7fSkgPT4gb3JpZy5maWx0ZXIocGF0dGVybiwgZXh0KGRlZiwgb3B0aW9ucykpLFxuICAgICAgICBkZWZhdWx0czogKG9wdGlvbnMpID0+IG9yaWcuZGVmYXVsdHMoZXh0KGRlZiwgb3B0aW9ucykpLFxuICAgICAgICBtYWtlUmU6IChwYXR0ZXJuLCBvcHRpb25zID0ge30pID0+IG9yaWcubWFrZVJlKHBhdHRlcm4sIGV4dChkZWYsIG9wdGlvbnMpKSxcbiAgICAgICAgYnJhY2VFeHBhbmQ6IChwYXR0ZXJuLCBvcHRpb25zID0ge30pID0+IG9yaWcuYnJhY2VFeHBhbmQocGF0dGVybiwgZXh0KGRlZiwgb3B0aW9ucykpLFxuICAgICAgICBtYXRjaDogKGxpc3QsIHBhdHRlcm4sIG9wdGlvbnMgPSB7fSkgPT4gb3JpZy5tYXRjaChsaXN0LCBwYXR0ZXJuLCBleHQoZGVmLCBvcHRpb25zKSksXG4gICAgICAgIHNlcDogb3JpZy5zZXAsXG4gICAgICAgIEdMT0JTVEFSOiBleHBvcnRzLkdMT0JTVEFSLFxuICAgIH0pO1xufTtcbmV4cG9ydHMuZGVmYXVsdHMgPSBkZWZhdWx0cztcbmV4cG9ydHMubWluaW1hdGNoLmRlZmF1bHRzID0gZXhwb3J0cy5kZWZhdWx0cztcbi8vIEJyYWNlIGV4cGFuc2lvbjpcbi8vIGF7YixjfWQgLT4gYWJkIGFjZFxuLy8gYXtiLH1jIC0+IGFiYyBhY1xuLy8gYXswLi4zfWQgLT4gYTBkIGExZCBhMmQgYTNkXG4vLyBhe2IsY3tkLGV9Zn1nIC0+IGFiZyBhY2RmZyBhY2VmZ1xuLy8gYXtiLGN9ZHtlLGZ9ZyAtPiBhYmRlZyBhY2RlZyBhYmRlZyBhYmRmZ1xuLy9cbi8vIEludmFsaWQgc2V0cyBhcmUgbm90IGV4cGFuZGVkLlxuLy8gYXsyLi59YiAtPiBhezIuLn1iXG4vLyBhe2J9YyAtPiBhe2J9Y1xuY29uc3QgYnJhY2VFeHBhbmQgPSAocGF0dGVybiwgb3B0aW9ucyA9IHt9KSA9PiB7XG4gICAgKDAsIGFzc2VydF92YWxpZF9wYXR0ZXJuX2pzXzEuYXNzZXJ0VmFsaWRQYXR0ZXJuKShwYXR0ZXJuKTtcbiAgICAvLyBUaGFua3MgdG8gWWV0aW5nIExpIDxodHRwczovL2dpdGh1Yi5jb20veWV0aW5nbGk+IGZvclxuICAgIC8vIGltcHJvdmluZyB0aGlzIHJlZ2V4cCB0byBhdm9pZCBhIFJlRE9TIHZ1bG5lcmFiaWxpdHkuXG4gICAgaWYgKG9wdGlvbnMubm9icmFjZSB8fCAhL1xceyg/Oig/IVxceykuKSpcXH0vLnRlc3QocGF0dGVybikpIHtcbiAgICAgICAgLy8gc2hvcnRjdXQuIG5vIG5lZWQgdG8gZXhwYW5kLlxuICAgICAgICByZXR1cm4gW3BhdHRlcm5dO1xuICAgIH1cbiAgICByZXR1cm4gKDAsIGJyYWNlX2V4cGFuc2lvbl8xLmRlZmF1bHQpKHBhdHRlcm4pO1xufTtcbmV4cG9ydHMuYnJhY2VFeHBhbmQgPSBicmFjZUV4cGFuZDtcbmV4cG9ydHMubWluaW1hdGNoLmJyYWNlRXhwYW5kID0gZXhwb3J0cy5icmFjZUV4cGFuZDtcbi8vIHBhcnNlIGEgY29tcG9uZW50IG9mIHRoZSBleHBhbmRlZCBzZXQuXG4vLyBBdCB0aGlzIHBvaW50LCBubyBwYXR0ZXJuIG1heSBjb250YWluIFwiL1wiIGluIGl0XG4vLyBzbyB3ZSdyZSBnb2luZyB0byByZXR1cm4gYSAyZCBhcnJheSwgd2hlcmUgZWFjaCBlbnRyeSBpcyB0aGUgZnVsbFxuLy8gcGF0dGVybiwgc3BsaXQgb24gJy8nLCBhbmQgdGhlbiB0dXJuZWQgaW50byBhIHJlZ3VsYXIgZXhwcmVzc2lvbi5cbi8vIEEgcmVnZXhwIGlzIG1hZGUgYXQgdGhlIGVuZCB3aGljaCBqb2lucyBlYWNoIGFycmF5IHdpdGggYW5cbi8vIGVzY2FwZWQgLywgYW5kIGFub3RoZXIgZnVsbCBvbmUgd2hpY2ggam9pbnMgZWFjaCByZWdleHAgd2l0aCB8LlxuLy9cbi8vIEZvbGxvd2luZyB0aGUgbGVhZCBvZiBCYXNoIDQuMSwgbm90ZSB0aGF0IFwiKipcIiBvbmx5IGhhcyBzcGVjaWFsIG1lYW5pbmdcbi8vIHdoZW4gaXQgaXMgdGhlICpvbmx5KiB0aGluZyBpbiBhIHBhdGggcG9ydGlvbi4gIE90aGVyd2lzZSwgYW55IHNlcmllc1xuLy8gb2YgKiBpcyBlcXVpdmFsZW50IHRvIGEgc2luZ2xlICouICBHbG9ic3RhciBiZWhhdmlvciBpcyBlbmFibGVkIGJ5XG4vLyBkZWZhdWx0LCBhbmQgY2FuIGJlIGRpc2FibGVkIGJ5IHNldHRpbmcgb3B0aW9ucy5ub2dsb2JzdGFyLlxuY29uc3QgbWFrZVJlID0gKHBhdHRlcm4sIG9wdGlvbnMgPSB7fSkgPT4gbmV3IE1pbmltYXRjaChwYXR0ZXJuLCBvcHRpb25zKS5tYWtlUmUoKTtcbmV4cG9ydHMubWFrZVJlID0gbWFrZVJlO1xuZXhwb3J0cy5taW5pbWF0Y2gubWFrZVJlID0gZXhwb3J0cy5tYWtlUmU7XG5jb25zdCBtYXRjaCA9IChsaXN0LCBwYXR0ZXJuLCBvcHRpb25zID0ge30pID0+IHtcbiAgICBjb25zdCBtbSA9IG5ldyBNaW5pbWF0Y2gocGF0dGVybiwgb3B0aW9ucyk7XG4gICAgbGlzdCA9IGxpc3QuZmlsdGVyKGYgPT4gbW0ubWF0Y2goZikpO1xuICAgIGlmIChtbS5vcHRpb25zLm5vbnVsbCAmJiAhbGlzdC5sZW5ndGgpIHtcbiAgICAgICAgbGlzdC5wdXNoKHBhdHRlcm4pO1xuICAgIH1cbiAgICByZXR1cm4gbGlzdDtcbn07XG5leHBvcnRzLm1hdGNoID0gbWF0Y2g7XG5leHBvcnRzLm1pbmltYXRjaC5tYXRjaCA9IGV4cG9ydHMubWF0Y2g7XG4vLyByZXBsYWNlIHN0dWZmIGxpa2UgXFwqIHdpdGggKlxuY29uc3QgZ2xvYk1hZ2ljID0gL1s/Kl18WytAIV1cXCguKj9cXCl8XFxbfFxcXS87XG5jb25zdCByZWdFeHBFc2NhcGUgPSAocykgPT4gcy5yZXBsYWNlKC9bLVtcXF17fSgpKis/LixcXFxcXiR8I1xcc10vZywgJ1xcXFwkJicpO1xuY2xhc3MgTWluaW1hdGNoIHtcbiAgICBvcHRpb25zO1xuICAgIHNldDtcbiAgICBwYXR0ZXJuO1xuICAgIHdpbmRvd3NQYXRoc05vRXNjYXBlO1xuICAgIG5vbmVnYXRlO1xuICAgIG5lZ2F0ZTtcbiAgICBjb21tZW50O1xuICAgIGVtcHR5O1xuICAgIHByZXNlcnZlTXVsdGlwbGVTbGFzaGVzO1xuICAgIHBhcnRpYWw7XG4gICAgZ2xvYlNldDtcbiAgICBnbG9iUGFydHM7XG4gICAgbm9jYXNlO1xuICAgIGlzV2luZG93cztcbiAgICBwbGF0Zm9ybTtcbiAgICB3aW5kb3dzTm9NYWdpY1Jvb3Q7XG4gICAgcmVnZXhwO1xuICAgIGNvbnN0cnVjdG9yKHBhdHRlcm4sIG9wdGlvbnMgPSB7fSkge1xuICAgICAgICAoMCwgYXNzZXJ0X3ZhbGlkX3BhdHRlcm5fanNfMS5hc3NlcnRWYWxpZFBhdHRlcm4pKHBhdHRlcm4pO1xuICAgICAgICBvcHRpb25zID0gb3B0aW9ucyB8fCB7fTtcbiAgICAgICAgdGhpcy5vcHRpb25zID0gb3B0aW9ucztcbiAgICAgICAgdGhpcy5wYXR0ZXJuID0gcGF0dGVybjtcbiAgICAgICAgdGhpcy5wbGF0Zm9ybSA9IG9wdGlvbnMucGxhdGZvcm0gfHwgZGVmYXVsdFBsYXRmb3JtO1xuICAgICAgICB0aGlzLmlzV2luZG93cyA9IHRoaXMucGxhdGZvcm0gPT09ICd3aW4zMic7XG4gICAgICAgIHRoaXMud2luZG93c1BhdGhzTm9Fc2NhcGUgPVxuICAgICAgICAgICAgISFvcHRpb25zLndpbmRvd3NQYXRoc05vRXNjYXBlIHx8IG9wdGlvbnMuYWxsb3dXaW5kb3dzRXNjYXBlID09PSBmYWxzZTtcbiAgICAgICAgaWYgKHRoaXMud2luZG93c1BhdGhzTm9Fc2NhcGUpIHtcbiAgICAgICAgICAgIHRoaXMucGF0dGVybiA9IHRoaXMucGF0dGVybi5yZXBsYWNlKC9cXFxcL2csICcvJyk7XG4gICAgICAgIH1cbiAgICAgICAgdGhpcy5wcmVzZXJ2ZU11bHRpcGxlU2xhc2hlcyA9ICEhb3B0aW9ucy5wcmVzZXJ2ZU11bHRpcGxlU2xhc2hlcztcbiAgICAgICAgdGhpcy5yZWdleHAgPSBudWxsO1xuICAgICAgICB0aGlzLm5lZ2F0ZSA9IGZhbHNlO1xuICAgICAgICB0aGlzLm5vbmVnYXRlID0gISFvcHRpb25zLm5vbmVnYXRlO1xuICAgICAgICB0aGlzLmNvbW1lbnQgPSBmYWxzZTtcbiAgICAgICAgdGhpcy5lbXB0eSA9IGZhbHNlO1xuICAgICAgICB0aGlzLnBhcnRpYWwgPSAhIW9wdGlvbnMucGFydGlhbDtcbiAgICAgICAgdGhpcy5ub2Nhc2UgPSAhIXRoaXMub3B0aW9ucy5ub2Nhc2U7XG4gICAgICAgIHRoaXMud2luZG93c05vTWFnaWNSb290ID1cbiAgICAgICAgICAgIG9wdGlvbnMud2luZG93c05vTWFnaWNSb290ICE9PSB1bmRlZmluZWRcbiAgICAgICAgICAgICAgICA/IG9wdGlvbnMud2luZG93c05vTWFnaWNSb290XG4gICAgICAgICAgICAgICAgOiAhISh0aGlzLmlzV2luZG93cyAmJiB0aGlzLm5vY2FzZSk7XG4gICAgICAgIHRoaXMuZ2xvYlNldCA9IFtdO1xuICAgICAgICB0aGlzLmdsb2JQYXJ0cyA9IFtdO1xuICAgICAgICB0aGlzLnNldCA9IFtdO1xuICAgICAgICAvLyBtYWtlIHRoZSBzZXQgb2YgcmVnZXhwcyBldGMuXG4gICAgICAgIHRoaXMubWFrZSgpO1xuICAgIH1cbiAgICBoYXNNYWdpYygpIHtcbiAgICAgICAgaWYgKHRoaXMub3B0aW9ucy5tYWdpY2FsQnJhY2VzICYmIHRoaXMuc2V0Lmxlbmd0aCA+IDEpIHtcbiAgICAgICAgICAgIHJldHVybiB0cnVlO1xuICAgICAgICB9XG4gICAgICAgIGZvciAoY29uc3QgcGF0dGVybiBvZiB0aGlzLnNldCkge1xuICAgICAgICAgICAgZm9yIChjb25zdCBwYXJ0IG9mIHBhdHRlcm4pIHtcbiAgICAgICAgICAgICAgICBpZiAodHlwZW9mIHBhcnQgIT09ICdzdHJpbmcnKVxuICAgICAgICAgICAgICAgICAgICByZXR1cm4gdHJ1ZTtcbiAgICAgICAgICAgIH1cbiAgICAgICAgfVxuICAgICAgICByZXR1cm4gZmFsc2U7XG4gICAgfVxuICAgIGRlYnVnKC4uLl8pIHsgfVxuICAgIG1ha2UoKSB7XG4gICAgICAgIGNvbnN0IHBhdHRlcm4gPSB0aGlzLnBhdHRlcm47XG4gICAgICAgIGNvbnN0IG9wdGlvbnMgPSB0aGlzLm9wdGlvbnM7XG4gICAgICAgIC8vIGVtcHR5IHBhdHRlcm5zIGFuZCBjb21tZW50cyBtYXRjaCBub3RoaW5nLlxuICAgICAgICBpZiAoIW9wdGlvbnMubm9jb21tZW50ICYmIHBhdHRlcm4uY2hhckF0KDApID09PSAnIycpIHtcbiAgICAgICAgICAgIHRoaXMuY29tbWVudCA9IHRydWU7XG4gICAgICAgICAgICByZXR1cm47XG4gICAgICAgIH1cbiAgICAgICAgaWYgKCFwYXR0ZXJuKSB7XG4gICAgICAgICAgICB0aGlzLmVtcHR5ID0gdHJ1ZTtcbiAgICAgICAgICAgIHJldHVybjtcbiAgICAgICAgfVxuICAgICAgICAvLyBzdGVwIDE6IGZpZ3VyZSBvdXQgbmVnYXRpb24sIGV0Yy5cbiAgICAgICAgdGhpcy5wYXJzZU5lZ2F0ZSgpO1xuICAgICAgICAvLyBzdGVwIDI6IGV4cGFuZCBicmFjZXNcbiAgICAgICAgdGhpcy5nbG9iU2V0ID0gWy4uLm5ldyBTZXQodGhpcy5icmFjZUV4cGFuZCgpKV07XG4gICAgICAgIGlmIChvcHRpb25zLmRlYnVnKSB7XG4gICAgICAgICAgICB0aGlzLmRlYnVnID0gKC4uLmFyZ3MpID0+IGNvbnNvbGUuZXJyb3IoLi4uYXJncyk7XG4gICAgICAgIH1cbiAgICAgICAgdGhpcy5kZWJ1Zyh0aGlzLnBhdHRlcm4sIHRoaXMuZ2xvYlNldCk7XG4gICAgICAgIC8vIHN0ZXAgMzogbm93IHdlIGhhdmUgYSBzZXQsIHNvIHR1cm4gZWFjaCBvbmUgaW50byBhIHNlcmllcyBvZlxuICAgICAgICAvLyBwYXRoLXBvcnRpb24gbWF0Y2hpbmcgcGF0dGVybnMuXG4gICAgICAgIC8vIFRoZXNlIHdpbGwgYmUgcmVnZXhwcywgZXhjZXB0IGluIHRoZSBjYXNlIG9mIFwiKipcIiwgd2hpY2ggaXNcbiAgICAgICAgLy8gc2V0IHRvIHRoZSBHTE9CU1RBUiBvYmplY3QgZm9yIGdsb2JzdGFyIGJlaGF2aW9yLFxuICAgICAgICAvLyBhbmQgd2lsbCBub3QgY29udGFpbiBhbnkgLyBjaGFyYWN0ZXJzXG4gICAgICAgIC8vXG4gICAgICAgIC8vIEZpcnN0LCB3ZSBwcmVwcm9jZXNzIHRvIG1ha2UgdGhlIGdsb2IgcGF0dGVybiBzZXRzIGEgYml0IHNpbXBsZXJcbiAgICAgICAgLy8gYW5kIGRlZHVwZWQuICBUaGVyZSBhcmUgc29tZSBwZXJmLWtpbGxpbmcgcGF0dGVybnMgdGhhdCBjYW4gY2F1c2VcbiAgICAgICAgLy8gcHJvYmxlbXMgd2l0aCBhIGdsb2Igd2FsaywgYnV0IHdlIGNhbiBzaW1wbGlmeSB0aGVtIGRvd24gYSBiaXQuXG4gICAgICAgIGNvbnN0IHJhd0dsb2JQYXJ0cyA9IHRoaXMuZ2xvYlNldC5tYXAocyA9PiB0aGlzLnNsYXNoU3BsaXQocykpO1xuICAgICAgICB0aGlzLmdsb2JQYXJ0cyA9IHRoaXMucHJlcHJvY2VzcyhyYXdHbG9iUGFydHMpO1xuICAgICAgICB0aGlzLmRlYnVnKHRoaXMucGF0dGVybiwgdGhpcy5nbG9iUGFydHMpO1xuICAgICAgICAvLyBnbG9iIC0tPiByZWdleHBzXG4gICAgICAgIGxldCBzZXQgPSB0aGlzLmdsb2JQYXJ0cy5tYXAoKHMsIF8sIF9fKSA9PiB7XG4gICAgICAgICAgICBpZiAodGhpcy5pc1dpbmRvd3MgJiYgdGhpcy53aW5kb3dzTm9NYWdpY1Jvb3QpIHtcbiAgICAgICAgICAgICAgICAvLyBjaGVjayBpZiBpdCdzIGEgZHJpdmUgb3IgdW5jIHBhdGguXG4gICAgICAgICAgICAgICAgY29uc3QgaXNVTkMgPSBzWzBdID09PSAnJyAmJlxuICAgICAgICAgICAgICAgICAgICBzWzFdID09PSAnJyAmJlxuICAgICAgICAgICAgICAgICAgICAoc1syXSA9PT0gJz8nIHx8ICFnbG9iTWFnaWMudGVzdChzWzJdKSkgJiZcbiAgICAgICAgICAgICAgICAgICAgIWdsb2JNYWdpYy50ZXN0KHNbM10pO1xuICAgICAgICAgICAgICAgIGNvbnN0IGlzRHJpdmUgPSAvXlthLXpdOi9pLnRlc3Qoc1swXSk7XG4gICAgICAgICAgICAgICAgaWYgKGlzVU5DKSB7XG4gICAgICAgICAgICAgICAgICAgIHJldHVybiBbLi4ucy5zbGljZSgwLCA0KSwgLi4ucy5zbGljZSg0KS5tYXAoc3MgPT4gdGhpcy5wYXJzZShzcykpXTtcbiAgICAgICAgICAgICAgICB9XG4gICAgICAgICAgICAgICAgZWxzZSBpZiAoaXNEcml2ZSkge1xuICAgICAgICAgICAgICAgICAgICByZXR1cm4gW3NbMF0sIC4uLnMuc2xpY2UoMSkubWFwKHNzID0+IHRoaXMucGFyc2Uoc3MpKV07XG4gICAgICAgICAgICAgICAgfVxuICAgICAgICAgICAgfVxuICAgICAgICAgICAgcmV0dXJuIHMubWFwKHNzID0+IHRoaXMucGFyc2Uoc3MpKTtcbiAgICAgICAgfSk7XG4gICAgICAgIHRoaXMuZGVidWcodGhpcy5wYXR0ZXJuLCBzZXQpO1xuICAgICAgICAvLyBmaWx0ZXIgb3V0IGV2ZXJ5dGhpbmcgdGhhdCBkaWRuJ3QgY29tcGlsZSBwcm9wZXJseS5cbiAgICAgICAgdGhpcy5zZXQgPSBzZXQuZmlsdGVyKHMgPT4gcy5pbmRleE9mKGZhbHNlKSA9PT0gLTEpO1xuICAgICAgICAvLyBkbyBub3QgdHJlYXQgdGhlID8gaW4gVU5DIHBhdGhzIGFzIG1hZ2ljXG4gICAgICAgIGlmICh0aGlzLmlzV2luZG93cykge1xuICAgICAgICAgICAgZm9yIChsZXQgaSA9IDA7IGkgPCB0aGlzLnNldC5sZW5ndGg7IGkrKykge1xuICAgICAgICAgICAgICAgIGNvbnN0IHAgPSB0aGlzLnNldFtpXTtcbiAgICAgICAgICAgICAgICBpZiAocFswXSA9PT0gJycgJiZcbiAgICAgICAgICAgICAgICAgICAgcFsxXSA9PT0gJycgJiZcbiAgICAgICAgICAgICAgICAgICAgdGhpcy5nbG9iUGFydHNbaV1bMl0gPT09ICc/JyAmJlxuICAgICAgICAgICAgICAgICAgICB0eXBlb2YgcFszXSA9PT0gJ3N0cmluZycgJiZcbiAgICAgICAgICAgICAgICAgICAgL15bYS16XTokL2kudGVzdChwWzNdKSkge1xuICAgICAgICAgICAgICAgICAgICBwWzJdID0gJz8nO1xuICAgICAgICAgICAgICAgIH1cbiAgICAgICAgICAgIH1cbiAgICAgICAgfVxuICAgICAgICB0aGlzLmRlYnVnKHRoaXMucGF0dGVybiwgdGhpcy5zZXQpO1xuICAgIH1cbiAgICAvLyB2YXJpb3VzIHRyYW5zZm9ybXMgdG8gZXF1aXZhbGVudCBwYXR0ZXJuIHNldHMgdGhhdCBhcmVcbiAgICAvLyBmYXN0ZXIgdG8gcHJvY2VzcyBpbiBhIGZpbGVzeXN0ZW0gd2Fsay4gIFRoZSBnb2FsIGlzIHRvXG4gICAgLy8gZWxpbWluYXRlIHdoYXQgd2UgY2FuLCBhbmQgcHVzaCBhbGwgKiogcGF0dGVybnMgYXMgZmFyXG4gICAgLy8gdG8gdGhlIHJpZ2h0IGFzIHBvc3NpYmxlLCBldmVuIGlmIGl0IGluY3JlYXNlcyB0aGUgbnVtYmVyXG4gICAgLy8gb2YgcGF0dGVybnMgdGhhdCB3ZSBoYXZlIHRvIHByb2Nlc3MuXG4gICAgcHJlcHJvY2VzcyhnbG9iUGFydHMpIHtcbiAgICAgICAgLy8gaWYgd2UncmUgbm90IGluIGdsb2JzdGFyIG1vZGUsIHRoZW4gdHVybiBhbGwgKiogaW50byAqXG4gICAgICAgIGlmICh0aGlzLm9wdGlvbnMubm9nbG9ic3Rhcikge1xuICAgICAgICAgICAgZm9yIChsZXQgaSA9IDA7IGkgPCBnbG9iUGFydHMubGVuZ3RoOyBpKyspIHtcbiAgICAgICAgICAgICAgICBmb3IgKGxldCBqID0gMDsgaiA8IGdsb2JQYXJ0c1tpXS5sZW5ndGg7IGorKykge1xuICAgICAgICAgICAgICAgICAgICBpZiAoZ2xvYlBhcnRzW2ldW2pdID09PSAnKionKSB7XG4gICAgICAgICAgICAgICAgICAgICAgICBnbG9iUGFydHNbaV1bal0gPSAnKic7XG4gICAgICAgICAgICAgICAgICAgIH1cbiAgICAgICAgICAgICAgICB9XG4gICAgICAgICAgICB9XG4gICAgICAgIH1cbiAgICAgICAgY29uc3QgeyBvcHRpbWl6YXRpb25MZXZlbCA9IDEgfSA9IHRoaXMub3B0aW9ucztcbiAgICAgICAgaWYgKG9wdGltaXphdGlvbkxldmVsID49IDIpIHtcbiAgICAgICAgICAgIC8vIGFnZ3Jlc3NpdmUgb3B0aW1pemF0aW9uIGZvciB0aGUgcHVycG9zZSBvZiBmcyB3YWxraW5nXG4gICAgICAgICAgICBnbG9iUGFydHMgPSB0aGlzLmZpcnN0UGhhc2VQcmVQcm9jZXNzKGdsb2JQYXJ0cyk7XG4gICAgICAgICAgICBnbG9iUGFydHMgPSB0aGlzLnNlY29uZFBoYXNlUHJlUHJvY2VzcyhnbG9iUGFydHMpO1xuICAgICAgICB9XG4gICAgICAgIGVsc2UgaWYgKG9wdGltaXphdGlvbkxldmVsID49IDEpIHtcbiAgICAgICAgICAgIC8vIGp1c3QgYmFzaWMgb3B0aW1pemF0aW9ucyB0byByZW1vdmUgc29tZSAuLiBwYXJ0c1xuICAgICAgICAgICAgZ2xvYlBhcnRzID0gdGhpcy5sZXZlbE9uZU9wdGltaXplKGdsb2JQYXJ0cyk7XG4gICAgICAgIH1cbiAgICAgICAgZWxzZSB7XG4gICAgICAgICAgICAvLyBqdXN0IGNvbGxhcHNlIG11bHRpcGxlICoqIHBvcnRpb25zIGludG8gb25lXG4gICAgICAgICAgICBnbG9iUGFydHMgPSB0aGlzLmFkamFzY2VudEdsb2JzdGFyT3B0aW1pemUoZ2xvYlBhcnRzKTtcbiAgICAgICAgfVxuICAgICAgICByZXR1cm4gZ2xvYlBhcnRzO1xuICAgIH1cbiAgICAvLyBqdXN0IGdldCByaWQgb2YgYWRqYXNjZW50ICoqIHBvcnRpb25zXG4gICAgYWRqYXNjZW50R2xvYnN0YXJPcHRpbWl6ZShnbG9iUGFydHMpIHtcbiAgICAgICAgcmV0dXJuIGdsb2JQYXJ0cy5tYXAocGFydHMgPT4ge1xuICAgICAgICAgICAgbGV0IGdzID0gLTE7XG4gICAgICAgICAgICB3aGlsZSAoLTEgIT09IChncyA9IHBhcnRzLmluZGV4T2YoJyoqJywgZ3MgKyAxKSkpIHtcbiAgICAgICAgICAgICAgICBsZXQgaSA9IGdzO1xuICAgICAgICAgICAgICAgIHdoaWxlIChwYXJ0c1tpICsgMV0gPT09ICcqKicpIHtcbiAgICAgICAgICAgICAgICAgICAgaSsrO1xuICAgICAgICAgICAgICAgIH1cbiAgICAgICAgICAgICAgICBpZiAoaSAhPT0gZ3MpIHtcbiAgICAgICAgICAgICAgICAgICAgcGFydHMuc3BsaWNlKGdzLCBpIC0gZ3MpO1xuICAgICAgICAgICAgICAgIH1cbiAgICAgICAgICAgIH1cbiAgICAgICAgICAgIHJldHVybiBwYXJ0cztcbiAgICAgICAgfSk7XG4gICAgfVxuICAgIC8vIGdldCByaWQgb2YgYWRqYXNjZW50ICoqIGFuZCByZXNvbHZlIC4uIHBvcnRpb25zXG4gICAgbGV2ZWxPbmVPcHRpbWl6ZShnbG9iUGFydHMpIHtcbiAgICAgICAgcmV0dXJuIGdsb2JQYXJ0cy5tYXAocGFydHMgPT4ge1xuICAgICAgICAgICAgcGFydHMgPSBwYXJ0cy5yZWR1Y2UoKHNldCwgcGFydCkgPT4ge1xuICAgICAgICAgICAgICAgIGNvbnN0IHByZXYgPSBzZXRbc2V0Lmxlbmd0aCAtIDFdO1xuICAgICAgICAgICAgICAgIGlmIChwYXJ0ID09PSAnKionICYmIHByZXYgPT09ICcqKicpIHtcbiAgICAgICAgICAgICAgICAgICAgcmV0dXJuIHNldDtcbiAgICAgICAgICAgICAgICB9XG4gICAgICAgICAgICAgICAgaWYgKHBhcnQgPT09ICcuLicpIHtcbiAgICAgICAgICAgICAgICAgICAgaWYgKHByZXYgJiYgcHJldiAhPT0gJy4uJyAmJiBwcmV2ICE9PSAnLicgJiYgcHJldiAhPT0gJyoqJykge1xuICAgICAgICAgICAgICAgICAgICAgICAgc2V0LnBvcCgpO1xuICAgICAgICAgICAgICAgICAgICAgICAgcmV0dXJuIHNldDtcbiAgICAgICAgICAgICAgICAgICAgfVxuICAgICAgICAgICAgICAgIH1cbiAgICAgICAgICAgICAgICBzZXQucHVzaChwYXJ0KTtcbiAgICAgICAgICAgICAgICByZXR1cm4gc2V0O1xuICAgICAgICAgICAgfSwgW10pO1xuICAgICAgICAgICAgcmV0dXJuIHBhcnRzLmxlbmd0aCA9PT0gMCA/IFsnJ10gOiBwYXJ0cztcbiAgICAgICAgfSk7XG4gICAgfVxuICAgIGxldmVsVHdvRmlsZU9wdGltaXplKHBhcnRzKSB7XG4gICAgICAgIGlmICghQXJyYXkuaXNBcnJheShwYXJ0cykpIHtcbiAgICAgICAgICAgIHBhcnRzID0gdGhpcy5zbGFzaFNwbGl0KHBhcnRzKTtcbiAgICAgICAgfVxuICAgICAgICBsZXQgZGlkU29tZXRoaW5nID0gZmFsc2U7XG4gICAgICAgIGRvIHtcbiAgICAgICAgICAgIGRpZFNvbWV0aGluZyA9IGZhbHNlO1xuICAgICAgICAgICAgLy8gPHByZT4vPGU+LzxyZXN0PiAtPiA8cHJlPi88cmVzdD5cbiAgICAgICAgICAgIGlmICghdGhpcy5wcmVzZXJ2ZU11bHRpcGxlU2xhc2hlcykge1xuICAgICAgICAgICAgICAgIGZvciAobGV0IGkgPSAxOyBpIDwgcGFydHMubGVuZ3RoIC0gMTsgaSsrKSB7XG4gICAgICAgICAgICAgICAgICAgIGNvbnN0IHAgPSBwYXJ0c1tpXTtcbiAgICAgICAgICAgICAgICAgICAgLy8gZG9uJ3Qgc3F1ZWV6ZSBvdXQgVU5DIHBhdHRlcm5zXG4gICAgICAgICAgICAgICAgICAgIGlmIChpID09PSAxICYmIHAgPT09ICcnICYmIHBhcnRzWzBdID09PSAnJylcbiAgICAgICAgICAgICAgICAgICAgICAgIGNvbnRpbnVlO1xuICAgICAgICAgICAgICAgICAgICBpZiAocCA9PT0gJy4nIHx8IHAgPT09ICcnKSB7XG4gICAgICAgICAgICAgICAgICAgICAgICBkaWRTb21ldGhpbmcgPSB0cnVlO1xuICAgICAgICAgICAgICAgICAgICAgICAgcGFydHMuc3BsaWNlKGksIDEpO1xuICAgICAgICAgICAgICAgICAgICAgICAgaS0tO1xuICAgICAgICAgICAgICAgICAgICB9XG4gICAgICAgICAgICAgICAgfVxuICAgICAgICAgICAgICAgIGlmIChwYXJ0c1swXSA9PT0gJy4nICYmXG4gICAgICAgICAgICAgICAgICAgIHBhcnRzLmxlbmd0aCA9PT0gMiAmJlxuICAgICAgICAgICAgICAgICAgICAocGFydHNbMV0gPT09ICcuJyB8fCBwYXJ0c1sxXSA9PT0gJycpKSB7XG4gICAgICAgICAgICAgICAgICAgIGRpZFNvbWV0aGluZyA9IHRydWU7XG4gICAgICAgICAgICAgICAgICAgIHBhcnRzLnBvcCgpO1xuICAgICAgICAgICAgICAgIH1cbiAgICAgICAgICAgIH1cbiAgICAgICAgICAgIC8vIDxwcmU+LzxwPi8uLi88cmVzdD4gLT4gPHByZT4vPHJlc3Q+XG4gICAgICAgICAgICBsZXQgZGQgPSAwO1xuICAgICAgICAgICAgd2hpbGUgKC0xICE9PSAoZGQgPSBwYXJ0cy5pbmRleE9mKCcuLicsIGRkICsgMSkpKSB7XG4gICAgICAgICAgICAgICAgY29uc3QgcCA9IHBhcnRzW2RkIC0gMV07XG4gICAgICAgICAgICAgICAgaWYgKHAgJiYgcCAhPT0gJy4nICYmIHAgIT09ICcuLicgJiYgcCAhPT0gJyoqJykge1xuICAgICAgICAgICAgICAgICAgICBkaWRTb21ldGhpbmcgPSB0cnVlO1xuICAgICAgICAgICAgICAgICAgICBwYXJ0cy5zcGxpY2UoZGQgLSAxLCAyKTtcbiAgICAgICAgICAgICAgICAgICAgZGQgLT0gMjtcbiAgICAgICAgICAgICAgICB9XG4gICAgICAgICAgICB9XG4gICAgICAgIH0gd2hpbGUgKGRpZFNvbWV0aGluZyk7XG4gICAgICAgIHJldHVybiBwYXJ0cy5sZW5ndGggPT09IDAgPyBbJyddIDogcGFydHM7XG4gICAgfVxuICAgIC8vIEZpcnN0IHBoYXNlOiBzaW5nbGUtcGF0dGVybiBwcm9jZXNzaW5nXG4gICAgLy8gPHByZT4gaXMgMSBvciBtb3JlIHBvcnRpb25zXG4gICAgLy8gPHJlc3Q+IGlzIDEgb3IgbW9yZSBwb3J0aW9uc1xuICAgIC8vIDxwPiBpcyBhbnkgcG9ydGlvbiBvdGhlciB0aGFuIC4sIC4uLCAnJywgb3IgKipcbiAgICAvLyA8ZT4gaXMgLiBvciAnJ1xuICAgIC8vXG4gICAgLy8gKiovLi4gaXMgKmJydXRhbCogZm9yIGZpbGVzeXN0ZW0gd2Fsa2luZyBwZXJmb3JtYW5jZSwgYmVjYXVzZVxuICAgIC8vIGl0IGVmZmVjdGl2ZWx5IHJlc2V0cyB0aGUgcmVjdXJzaXZlIHdhbGsgZWFjaCB0aW1lIGl0IG9jY3VycyxcbiAgICAvLyBhbmQgKiogY2Fubm90IGJlIHJlZHVjZWQgb3V0IGJ5IGEgLi4gcGF0dGVybiBwYXJ0IGxpa2UgYSByZWdleHBcbiAgICAvLyBvciBtb3N0IHN0cmluZ3MgKG90aGVyIHRoYW4gLi4sIC4sIGFuZCAnJykgY2FuIGJlLlxuICAgIC8vXG4gICAgLy8gPHByZT4vKiovLi4vPHA+LzxwPi88cmVzdD4gLT4gezxwcmU+Ly4uLzxwPi88cD4vPHJlc3Q+LDxwcmU+LyoqLzxwPi88cD4vPHJlc3Q+fVxuICAgIC8vIDxwcmU+LzxlPi88cmVzdD4gLT4gPHByZT4vPHJlc3Q+XG4gICAgLy8gPHByZT4vPHA+Ly4uLzxyZXN0PiAtPiA8cHJlPi88cmVzdD5cbiAgICAvLyAqKi8qKi88cmVzdD4gLT4gKiovPHJlc3Q+XG4gICAgLy9cbiAgICAvLyAqKi8qLzxyZXN0PiAtPiAqLyoqLzxyZXN0PiA8PT0gbm90IHZhbGlkIGJlY2F1c2UgKiogZG9lc24ndCBmb2xsb3dcbiAgICAvLyB0aGlzIFdPVUxEIGJlIGFsbG93ZWQgaWYgKiogZGlkIGZvbGxvdyBzeW1saW5rcywgb3IgKiBkaWRuJ3RcbiAgICBmaXJzdFBoYXNlUHJlUHJvY2VzcyhnbG9iUGFydHMpIHtcbiAgICAgICAgbGV0IGRpZFNvbWV0aGluZyA9IGZhbHNlO1xuICAgICAgICBkbyB7XG4gICAgICAgICAgICBkaWRTb21ldGhpbmcgPSBmYWxzZTtcbiAgICAgICAgICAgIC8vIDxwcmU+LyoqLy4uLzxwPi88cD4vPHJlc3Q+IC0+IHs8cHJlPi8uLi88cD4vPHA+LzxyZXN0Piw8cHJlPi8qKi88cD4vPHA+LzxyZXN0Pn1cbiAgICAgICAgICAgIGZvciAobGV0IHBhcnRzIG9mIGdsb2JQYXJ0cykge1xuICAgICAgICAgICAgICAgIGxldCBncyA9IC0xO1xuICAgICAgICAgICAgICAgIHdoaWxlICgtMSAhPT0gKGdzID0gcGFydHMuaW5kZXhPZignKionLCBncyArIDEpKSkge1xuICAgICAgICAgICAgICAgICAgICBsZXQgZ3NzID0gZ3M7XG4gICAgICAgICAgICAgICAgICAgIHdoaWxlIChwYXJ0c1tnc3MgKyAxXSA9PT0gJyoqJykge1xuICAgICAgICAgICAgICAgICAgICAgICAgLy8gPHByZT4vKiovKiovPHJlc3Q+IC0+IDxwcmU+LyoqLzxyZXN0PlxuICAgICAgICAgICAgICAgICAgICAgICAgZ3NzKys7XG4gICAgICAgICAgICAgICAgICAgIH1cbiAgICAgICAgICAgICAgICAgICAgLy8gZWcsIGlmIGdzIGlzIDIgYW5kIGdzcyBpcyA0LCB0aGF0IG1lYW5zIHdlIGhhdmUgMyAqKlxuICAgICAgICAgICAgICAgICAgICAvLyBwYXJ0cywgYW5kIGNhbiByZW1vdmUgMiBvZiB0aGVtLlxuICAgICAgICAgICAgICAgICAgICBpZiAoZ3NzID4gZ3MpIHtcbiAgICAgICAgICAgICAgICAgICAgICAgIHBhcnRzLnNwbGljZShncyArIDEsIGdzcyAtIGdzKTtcbiAgICAgICAgICAgICAgICAgICAgfVxuICAgICAgICAgICAgICAgICAgICBsZXQgbmV4dCA9IHBhcnRzW2dzICsgMV07XG4gICAgICAgICAgICAgICAgICAgIGNvbnN0IHAgPSBwYXJ0c1tncyArIDJdO1xuICAgICAgICAgICAgICAgICAgICBjb25zdCBwMiA9IHBhcnRzW2dzICsgM107XG4gICAgICAgICAgICAgICAgICAgIGlmIChuZXh0ICE9PSAnLi4nKVxuICAgICAgICAgICAgICAgICAgICAgICAgY29udGludWU7XG4gICAgICAgICAgICAgICAgICAgIGlmICghcCB8fFxuICAgICAgICAgICAgICAgICAgICAgICAgcCA9PT0gJy4nIHx8XG4gICAgICAgICAgICAgICAgICAgICAgICBwID09PSAnLi4nIHx8XG4gICAgICAgICAgICAgICAgICAgICAgICAhcDIgfHxcbiAgICAgICAgICAgICAgICAgICAgICAgIHAyID09PSAnLicgfHxcbiAgICAgICAgICAgICAgICAgICAgICAgIHAyID09PSAnLi4nKSB7XG4gICAgICAgICAgICAgICAgICAgICAgICBjb250aW51ZTtcbiAgICAgICAgICAgICAgICAgICAgfVxuICAgICAgICAgICAgICAgICAgICBkaWRTb21ldGhpbmcgPSB0cnVlO1xuICAgICAgICAgICAgICAgICAgICAvLyBlZGl0IHBhcnRzIGluIHBsYWNlLCBhbmQgcHVzaCB0aGUgbmV3IG9uZVxuICAgICAgICAgICAgICAgICAgICBwYXJ0cy5zcGxpY2UoZ3MsIDEpO1xuICAgICAgICAgICAgICAgICAgICBjb25zdCBvdGhlciA9IHBhcnRzLnNsaWNlKDApO1xuICAgICAgICAgICAgICAgICAgICBvdGhlcltnc10gPSAnKionO1xuICAgICAgICAgICAgICAgICAgICBnbG9iUGFydHMucHVzaChvdGhlcik7XG4gICAgICAgICAgICAgICAgICAgIGdzLS07XG4gICAgICAgICAgICAgICAgfVxuICAgICAgICAgICAgICAgIC8vIDxwcmU+LzxlPi88cmVzdD4gLT4gPHByZT4vPHJlc3Q+XG4gICAgICAgICAgICAgICAgaWYgKCF0aGlzLnByZXNlcnZlTXVsdGlwbGVTbGFzaGVzKSB7XG4gICAgICAgICAgICAgICAgICAgIGZvciAobGV0IGkgPSAxOyBpIDwgcGFydHMubGVuZ3RoIC0gMTsgaSsrKSB7XG4gICAgICAgICAgICAgICAgICAgICAgICBjb25zdCBwID0gcGFydHNbaV07XG4gICAgICAgICAgICAgICAgICAgICAgICAvLyBkb24ndCBzcXVlZXplIG91dCBVTkMgcGF0dGVybnNcbiAgICAgICAgICAgICAgICAgICAgICAgIGlmIChpID09PSAxICYmIHAgPT09ICcnICYmIHBhcnRzWzBdID09PSAnJylcbiAgICAgICAgICAgICAgICAgICAgICAgICAgICBjb250aW51ZTtcbiAgICAgICAgICAgICAgICAgICAgICAgIGlmIChwID09PSAnLicgfHwgcCA9PT0gJycpIHtcbiAgICAgICAgICAgICAgICAgICAgICAgICAgICBkaWRTb21ldGhpbmcgPSB0cnVlO1xuICAgICAgICAgICAgICAgICAgICAgICAgICAgIHBhcnRzLnNwbGljZShpLCAxKTtcbiAgICAgICAgICAgICAgICAgICAgICAgICAgICBpLS07XG4gICAgICAgICAgICAgICAgICAgICAgICB9XG4gICAgICAgICAgICAgICAgICAgIH1cbiAgICAgICAgICAgICAgICAgICAgaWYgKHBhcnRzWzBdID09PSAnLicgJiZcbiAgICAgICAgICAgICAgICAgICAgICAgIHBhcnRzLmxlbmd0aCA9PT0gMiAmJlxuICAgICAgICAgICAgICAgICAgICAgICAgKHBhcnRzWzFdID09PSAnLicgfHwgcGFydHNbMV0gPT09ICcnKSkge1xuICAgICAgICAgICAgICAgICAgICAgICAgZGlkU29tZXRoaW5nID0gdHJ1ZTtcbiAgICAgICAgICAgICAgICAgICAgICAgIHBhcnRzLnBvcCgpO1xuICAgICAgICAgICAgICAgICAgICB9XG4gICAgICAgICAgICAgICAgfVxuICAgICAgICAgICAgICAgIC8vIDxwcmU+LzxwPi8uLi88cmVzdD4gLT4gPHByZT4vPHJlc3Q+XG4gICAgICAgICAgICAgICAgbGV0IGRkID0gMDtcbiAgICAgICAgICAgICAgICB3aGlsZSAoLTEgIT09IChkZCA9IHBhcnRzLmluZGV4T2YoJy4uJywgZGQgKyAxKSkpIHtcbiAgICAgICAgICAgICAgICAgICAgY29uc3QgcCA9IHBhcnRzW2RkIC0gMV07XG4gICAgICAgICAgICAgICAgICAgIGlmIChwICYmIHAgIT09ICcuJyAmJiBwICE9PSAnLi4nICYmIHAgIT09ICcqKicpIHtcbiAgICAgICAgICAgICAgICAgICAgICAgIGRpZFNvbWV0aGluZyA9IHRydWU7XG4gICAgICAgICAgICAgICAgICAgICAgICBjb25zdCBuZWVkRG90ID0gZGQgPT09IDEgJiYgcGFydHNbZGQgKyAxXSA9PT0gJyoqJztcbiAgICAgICAgICAgICAgICAgICAgICAgIGNvbnN0IHNwbGluID0gbmVlZERvdCA/IFsnLiddIDogW107XG4gICAgICAgICAgICAgICAgICAgICAgICBwYXJ0cy5zcGxpY2UoZGQgLSAxLCAyLCAuLi5zcGxpbik7XG4gICAgICAgICAgICAgICAgICAgICAgICBpZiAocGFydHMubGVuZ3RoID09PSAwKVxuICAgICAgICAgICAgICAgICAgICAgICAgICAgIHBhcnRzLnB1c2goJycpO1xuICAgICAgICAgICAgICAgICAgICAgICAgZGQgLT0gMjtcbiAgICAgICAgICAgICAgICAgICAgfVxuICAgICAgICAgICAgICAgIH1cbiAgICAgICAgICAgIH1cbiAgICAgICAgfSB3aGlsZSAoZGlkU29tZXRoaW5nKTtcbiAgICAgICAgcmV0dXJuIGdsb2JQYXJ0cztcbiAgICB9XG4gICAgLy8gc2Vjb25kIHBoYXNlOiBtdWx0aS1wYXR0ZXJuIGRlZHVwZXNcbiAgICAvLyB7PHByZT4vKi88cmVzdD4sPHByZT4vPHA+LzxyZXN0Pn0gLT4gPHByZT4vKi88cmVzdD5cbiAgICAvLyB7PHByZT4vPHJlc3Q+LDxwcmU+LzxyZXN0Pn0gLT4gPHByZT4vPHJlc3Q+XG4gICAgLy8gezxwcmU+LyoqLzxyZXN0Piw8cHJlPi88cmVzdD59IC0+IDxwcmU+LyoqLzxyZXN0PlxuICAgIC8vXG4gICAgLy8gezxwcmU+LyoqLzxyZXN0Piw8cHJlPi8qKi88cD4vPHJlc3Q+fSAtPiA8cHJlPi8qKi88cmVzdD5cbiAgICAvLyBeLS0gbm90IHZhbGlkIGJlY2F1c2UgKiogZG9lbnMndCBmb2xsb3cgc3ltbGlua3NcbiAgICBzZWNvbmRQaGFzZVByZVByb2Nlc3MoZ2xvYlBhcnRzKSB7XG4gICAgICAgIGZvciAobGV0IGkgPSAwOyBpIDwgZ2xvYlBhcnRzLmxlbmd0aCAtIDE7IGkrKykge1xuICAgICAgICAgICAgZm9yIChsZXQgaiA9IGkgKyAxOyBqIDwgZ2xvYlBhcnRzLmxlbmd0aDsgaisrKSB7XG4gICAgICAgICAgICAgICAgY29uc3QgbWF0Y2hlZCA9IHRoaXMucGFydHNNYXRjaChnbG9iUGFydHNbaV0sIGdsb2JQYXJ0c1tqXSwgIXRoaXMucHJlc2VydmVNdWx0aXBsZVNsYXNoZXMpO1xuICAgICAgICAgICAgICAgIGlmIChtYXRjaGVkKSB7XG4gICAgICAgICAgICAgICAgICAgIGdsb2JQYXJ0c1tpXSA9IFtdO1xuICAgICAgICAgICAgICAgICAgICBnbG9iUGFydHNbal0gPSBtYXRjaGVkO1xuICAgICAgICAgICAgICAgICAgICBicmVhaztcbiAgICAgICAgICAgICAgICB9XG4gICAgICAgICAgICB9XG4gICAgICAgIH1cbiAgICAgICAgcmV0dXJuIGdsb2JQYXJ0cy5maWx0ZXIoZ3MgPT4gZ3MubGVuZ3RoKTtcbiAgICB9XG4gICAgcGFydHNNYXRjaChhLCBiLCBlbXB0eUdTTWF0Y2ggPSBmYWxzZSkge1xuICAgICAgICBsZXQgYWkgPSAwO1xuICAgICAgICBsZXQgYmkgPSAwO1xuICAgICAgICBsZXQgcmVzdWx0ID0gW107XG4gICAgICAgIGxldCB3aGljaCA9ICcnO1xuICAgICAgICB3aGlsZSAoYWkgPCBhLmxlbmd0aCAmJiBiaSA8IGIubGVuZ3RoKSB7XG4gICAgICAgICAgICBpZiAoYVthaV0gPT09IGJbYmldKSB7XG4gICAgICAgICAgICAgICAgcmVzdWx0LnB1c2god2hpY2ggPT09ICdiJyA/IGJbYmldIDogYVthaV0pO1xuICAgICAgICAgICAgICAgIGFpKys7XG4gICAgICAgICAgICAgICAgYmkrKztcbiAgICAgICAgICAgIH1cbiAgICAgICAgICAgIGVsc2UgaWYgKGVtcHR5R1NNYXRjaCAmJiBhW2FpXSA9PT0gJyoqJyAmJiBiW2JpXSA9PT0gYVthaSArIDFdKSB7XG4gICAgICAgICAgICAgICAgcmVzdWx0LnB1c2goYVthaV0pO1xuICAgICAgICAgICAgICAgIGFpKys7XG4gICAgICAgICAgICB9XG4gICAgICAgICAgICBlbHNlIGlmIChlbXB0eUdTTWF0Y2ggJiYgYltiaV0gPT09ICcqKicgJiYgYVthaV0gPT09IGJbYmkgKyAxXSkge1xuICAgICAgICAgICAgICAgIHJlc3VsdC5wdXNoKGJbYmldKTtcbiAgICAgICAgICAgICAgICBiaSsrO1xuICAgICAgICAgICAgfVxuICAgICAgICAgICAgZWxzZSBpZiAoYVthaV0gPT09ICcqJyAmJlxuICAgICAgICAgICAgICAgIGJbYmldICYmXG4gICAgICAgICAgICAgICAgKHRoaXMub3B0aW9ucy5kb3QgfHwgIWJbYmldLnN0YXJ0c1dpdGgoJy4nKSkgJiZcbiAgICAgICAgICAgICAgICBiW2JpXSAhPT0gJyoqJykge1xuICAgICAgICAgICAgICAgIGlmICh3aGljaCA9PT0gJ2InKVxuICAgICAgICAgICAgICAgICAgICByZXR1cm4gZmFsc2U7XG4gICAgICAgICAgICAgICAgd2hpY2ggPSAnYSc7XG4gICAgICAgICAgICAgICAgcmVzdWx0LnB1c2goYVthaV0pO1xuICAgICAgICAgICAgICAgIGFpKys7XG4gICAgICAgICAgICAgICAgYmkrKztcbiAgICAgICAgICAgIH1cbiAgICAgICAgICAgIGVsc2UgaWYgKGJbYmldID09PSAnKicgJiZcbiAgICAgICAgICAgICAgICBhW2FpXSAmJlxuICAgICAgICAgICAgICAgICh0aGlzLm9wdGlvbnMuZG90IHx8ICFhW2FpXS5zdGFydHNXaXRoKCcuJykpICYmXG4gICAgICAgICAgICAgICAgYVthaV0gIT09ICcqKicpIHtcbiAgICAgICAgICAgICAgICBpZiAod2hpY2ggPT09ICdhJylcbiAgICAgICAgICAgICAgICAgICAgcmV0dXJuIGZhbHNlO1xuICAgICAgICAgICAgICAgIHdoaWNoID0gJ2InO1xuICAgICAgICAgICAgICAgIHJlc3VsdC5wdXNoKGJbYmldKTtcbiAgICAgICAgICAgICAgICBhaSsrO1xuICAgICAgICAgICAgICAgIGJpKys7XG4gICAgICAgICAgICB9XG4gICAgICAgICAgICBlbHNlIHtcbiAgICAgICAgICAgICAgICByZXR1cm4gZmFsc2U7XG4gICAgICAgICAgICB9XG4gICAgICAgIH1cbiAgICAgICAgLy8gaWYgd2UgZmFsbCBvdXQgb2YgdGhlIGxvb3AsIGl0IG1lYW5zIHRoZXkgdHdvIGFyZSBpZGVudGljYWxcbiAgICAgICAgLy8gYXMgbG9uZyBhcyB0aGVpciBsZW5ndGhzIG1hdGNoXG4gICAgICAgIHJldHVybiBhLmxlbmd0aCA9PT0gYi5sZW5ndGggJiYgcmVzdWx0O1xuICAgIH1cbiAgICBwYXJzZU5lZ2F0ZSgpIHtcbiAgICAgICAgaWYgKHRoaXMubm9uZWdhdGUpXG4gICAgICAgICAgICByZXR1cm47XG4gICAgICAgIGNvbnN0IHBhdHRlcm4gPSB0aGlzLnBhdHRlcm47XG4gICAgICAgIGxldCBuZWdhdGUgPSBmYWxzZTtcbiAgICAgICAgbGV0IG5lZ2F0ZU9mZnNldCA9IDA7XG4gICAgICAgIGZvciAobGV0IGkgPSAwOyBpIDwgcGF0dGVybi5sZW5ndGggJiYgcGF0dGVybi5jaGFyQXQoaSkgPT09ICchJzsgaSsrKSB7XG4gICAgICAgICAgICBuZWdhdGUgPSAhbmVnYXRlO1xuICAgICAgICAgICAgbmVnYXRlT2Zmc2V0Kys7XG4gICAgICAgIH1cbiAgICAgICAgaWYgKG5lZ2F0ZU9mZnNldClcbiAgICAgICAgICAgIHRoaXMucGF0dGVybiA9IHBhdHRlcm4uc2xpY2UobmVnYXRlT2Zmc2V0KTtcbiAgICAgICAgdGhpcy5uZWdhdGUgPSBuZWdhdGU7XG4gICAgfVxuICAgIC8vIHNldCBwYXJ0aWFsIHRvIHRydWUgdG8gdGVzdCBpZiwgZm9yIGV4YW1wbGUsXG4gICAgLy8gXCIvYS9iXCIgbWF0Y2hlcyB0aGUgc3RhcnQgb2YgXCIvKi9iLyovZFwiXG4gICAgLy8gUGFydGlhbCBtZWFucywgaWYgeW91IHJ1biBvdXQgb2YgZmlsZSBiZWZvcmUgeW91IHJ1blxuICAgIC8vIG91dCBvZiBwYXR0ZXJuLCB0aGVuIHRoYXQncyBmaW5lLCBhcyBsb25nIGFzIGFsbFxuICAgIC8vIHRoZSBwYXJ0cyBtYXRjaC5cbiAgICBtYXRjaE9uZShmaWxlLCBwYXR0ZXJuLCBwYXJ0aWFsID0gZmFsc2UpIHtcbiAgICAgICAgY29uc3Qgb3B0aW9ucyA9IHRoaXMub3B0aW9ucztcbiAgICAgICAgLy8gVU5DIHBhdGhzIGxpa2UgLy8/L1g6Ly4uLiBjYW4gbWF0Y2ggWDovLi4uIGFuZCB2aWNlIHZlcnNhXG4gICAgICAgIC8vIERyaXZlIGxldHRlcnMgaW4gYWJzb2x1dGUgZHJpdmUgb3IgdW5jIHBhdGhzIGFyZSBhbHdheXMgY29tcGFyZWRcbiAgICAgICAgLy8gY2FzZS1pbnNlbnNpdGl2ZWx5LlxuICAgICAgICBpZiAodGhpcy5pc1dpbmRvd3MpIHtcbiAgICAgICAgICAgIGNvbnN0IGZpbGVEcml2ZSA9IHR5cGVvZiBmaWxlWzBdID09PSAnc3RyaW5nJyAmJiAvXlthLXpdOiQvaS50ZXN0KGZpbGVbMF0pO1xuICAgICAgICAgICAgY29uc3QgZmlsZVVOQyA9ICFmaWxlRHJpdmUgJiZcbiAgICAgICAgICAgICAgICBmaWxlWzBdID09PSAnJyAmJlxuICAgICAgICAgICAgICAgIGZpbGVbMV0gPT09ICcnICYmXG4gICAgICAgICAgICAgICAgZmlsZVsyXSA9PT0gJz8nICYmXG4gICAgICAgICAgICAgICAgL15bYS16XTokL2kudGVzdChmaWxlWzNdKTtcbiAgICAgICAgICAgIGNvbnN0IHBhdHRlcm5Ecml2ZSA9IHR5cGVvZiBwYXR0ZXJuWzBdID09PSAnc3RyaW5nJyAmJiAvXlthLXpdOiQvaS50ZXN0KHBhdHRlcm5bMF0pO1xuICAgICAgICAgICAgY29uc3QgcGF0dGVyblVOQyA9ICFwYXR0ZXJuRHJpdmUgJiZcbiAgICAgICAgICAgICAgICBwYXR0ZXJuWzBdID09PSAnJyAmJlxuICAgICAgICAgICAgICAgIHBhdHRlcm5bMV0gPT09ICcnICYmXG4gICAgICAgICAgICAgICAgcGF0dGVyblsyXSA9PT0gJz8nICYmXG4gICAgICAgICAgICAgICAgdHlwZW9mIHBhdHRlcm5bM10gPT09ICdzdHJpbmcnICYmXG4gICAgICAgICAgICAgICAgL15bYS16XTokL2kudGVzdChwYXR0ZXJuWzNdKTtcbiAgICAgICAgICAgIGNvbnN0IGZkaSA9IGZpbGVVTkMgPyAzIDogZmlsZURyaXZlID8gMCA6IHVuZGVmaW5lZDtcbiAgICAgICAgICAgIGNvbnN0IHBkaSA9IHBhdHRlcm5VTkMgPyAzIDogcGF0dGVybkRyaXZlID8gMCA6IHVuZGVmaW5lZDtcbiAgICAgICAgICAgIGlmICh0eXBlb2YgZmRpID09PSAnbnVtYmVyJyAmJiB0eXBlb2YgcGRpID09PSAnbnVtYmVyJykge1xuICAgICAgICAgICAgICAgIGNvbnN0IFtmZCwgcGRdID0gW2ZpbGVbZmRpXSwgcGF0dGVybltwZGldXTtcbiAgICAgICAgICAgICAgICBpZiAoZmQudG9Mb3dlckNhc2UoKSA9PT0gcGQudG9Mb3dlckNhc2UoKSkge1xuICAgICAgICAgICAgICAgICAgICBwYXR0ZXJuW3BkaV0gPSBmZDtcbiAgICAgICAgICAgICAgICAgICAgaWYgKHBkaSA+IGZkaSkge1xuICAgICAgICAgICAgICAgICAgICAgICAgcGF0dGVybiA9IHBhdHRlcm4uc2xpY2UocGRpKTtcbiAgICAgICAgICAgICAgICAgICAgfVxuICAgICAgICAgICAgICAgICAgICBlbHNlIGlmIChmZGkgPiBwZGkpIHtcbiAgICAgICAgICAgICAgICAgICAgICAgIGZpbGUgPSBmaWxlLnNsaWNlKGZkaSk7XG4gICAgICAgICAgICAgICAgICAgIH1cbiAgICAgICAgICAgICAgICB9XG4gICAgICAgICAgICB9XG4gICAgICAgIH1cbiAgICAgICAgLy8gcmVzb2x2ZSBhbmQgcmVkdWNlIC4gYW5kIC4uIHBvcnRpb25zIGluIHRoZSBmaWxlIGFzIHdlbGwuXG4gICAgICAgIC8vIGRvbnQnIG5lZWQgdG8gZG8gdGhlIHNlY29uZCBwaGFzZSwgYmVjYXVzZSBpdCdzIG9ubHkgb25lIHN0cmluZ1tdXG4gICAgICAgIGNvbnN0IHsgb3B0aW1pemF0aW9uTGV2ZWwgPSAxIH0gPSB0aGlzLm9wdGlvbnM7XG4gICAgICAgIGlmIChvcHRpbWl6YXRpb25MZXZlbCA+PSAyKSB7XG4gICAgICAgICAgICBmaWxlID0gdGhpcy5sZXZlbFR3b0ZpbGVPcHRpbWl6ZShmaWxlKTtcbiAgICAgICAgfVxuICAgICAgICB0aGlzLmRlYnVnKCdtYXRjaE9uZScsIHRoaXMsIHsgZmlsZSwgcGF0dGVybiB9KTtcbiAgICAgICAgdGhpcy5kZWJ1ZygnbWF0Y2hPbmUnLCBmaWxlLmxlbmd0aCwgcGF0dGVybi5sZW5ndGgpO1xuICAgICAgICBmb3IgKHZhciBmaSA9IDAsIHBpID0gMCwgZmwgPSBmaWxlLmxlbmd0aCwgcGwgPSBwYXR0ZXJuLmxlbmd0aDsgZmkgPCBmbCAmJiBwaSA8IHBsOyBmaSsrLCBwaSsrKSB7XG4gICAgICAgICAgICB0aGlzLmRlYnVnKCdtYXRjaE9uZSBsb29wJyk7XG4gICAgICAgICAgICB2YXIgcCA9IHBhdHRlcm5bcGldO1xuICAgICAgICAgICAgdmFyIGYgPSBmaWxlW2ZpXTtcbiAgICAgICAgICAgIHRoaXMuZGVidWcocGF0dGVybiwgcCwgZik7XG4gICAgICAgICAgICAvLyBzaG91bGQgYmUgaW1wb3NzaWJsZS5cbiAgICAgICAgICAgIC8vIHNvbWUgaW52YWxpZCByZWdleHAgc3R1ZmYgaW4gdGhlIHNldC5cbiAgICAgICAgICAgIC8qIGM4IGlnbm9yZSBzdGFydCAqL1xuICAgICAgICAgICAgaWYgKHAgPT09IGZhbHNlKSB7XG4gICAgICAgICAgICAgICAgcmV0dXJuIGZhbHNlO1xuICAgICAgICAgICAgfVxuICAgICAgICAgICAgLyogYzggaWdub3JlIHN0b3AgKi9cbiAgICAgICAgICAgIGlmIChwID09PSBleHBvcnRzLkdMT0JTVEFSKSB7XG4gICAgICAgICAgICAgICAgdGhpcy5kZWJ1ZygnR0xPQlNUQVInLCBbcGF0dGVybiwgcCwgZl0pO1xuICAgICAgICAgICAgICAgIC8vIFwiKipcIlxuICAgICAgICAgICAgICAgIC8vIGEvKiovYi8qKi9jIHdvdWxkIG1hdGNoIHRoZSBmb2xsb3dpbmc6XG4gICAgICAgICAgICAgICAgLy8gYS9iL3gveS96L2NcbiAgICAgICAgICAgICAgICAvLyBhL3gveS96L2IvY1xuICAgICAgICAgICAgICAgIC8vIGEvYi94L2IveC9jXG4gICAgICAgICAgICAgICAgLy8gYS9iL2NcbiAgICAgICAgICAgICAgICAvLyBUbyBkbyB0aGlzLCB0YWtlIHRoZSByZXN0IG9mIHRoZSBwYXR0ZXJuIGFmdGVyXG4gICAgICAgICAgICAgICAgLy8gdGhlICoqLCBhbmQgc2VlIGlmIGl0IHdvdWxkIG1hdGNoIHRoZSBmaWxlIHJlbWFpbmRlci5cbiAgICAgICAgICAgICAgICAvLyBJZiBzbywgcmV0dXJuIHN1Y2Nlc3MuXG4gICAgICAgICAgICAgICAgLy8gSWYgbm90LCB0aGUgKiogXCJzd2FsbG93c1wiIGEgc2VnbWVudCwgYW5kIHRyeSBhZ2Fpbi5cbiAgICAgICAgICAgICAgICAvLyBUaGlzIGlzIHJlY3Vyc2l2ZWx5IGF3ZnVsLlxuICAgICAgICAgICAgICAgIC8vXG4gICAgICAgICAgICAgICAgLy8gYS8qKi9iLyoqL2MgbWF0Y2hpbmcgYS9iL3gveS96L2NcbiAgICAgICAgICAgICAgICAvLyAtIGEgbWF0Y2hlcyBhXG4gICAgICAgICAgICAgICAgLy8gLSBkb3VibGVzdGFyXG4gICAgICAgICAgICAgICAgLy8gICAtIG1hdGNoT25lKGIveC95L3ovYywgYi8qKi9jKVxuICAgICAgICAgICAgICAgIC8vICAgICAtIGIgbWF0Y2hlcyBiXG4gICAgICAgICAgICAgICAgLy8gICAgIC0gZG91Ymxlc3RhclxuICAgICAgICAgICAgICAgIC8vICAgICAgIC0gbWF0Y2hPbmUoeC95L3ovYywgYykgLT4gbm9cbiAgICAgICAgICAgICAgICAvLyAgICAgICAtIG1hdGNoT25lKHkvei9jLCBjKSAtPiBub1xuICAgICAgICAgICAgICAgIC8vICAgICAgIC0gbWF0Y2hPbmUoei9jLCBjKSAtPiBub1xuICAgICAgICAgICAgICAgIC8vICAgICAgIC0gbWF0Y2hPbmUoYywgYykgeWVzLCBoaXRcbiAgICAgICAgICAgICAgICB2YXIgZnIgPSBmaTtcbiAgICAgICAgICAgICAgICB2YXIgcHIgPSBwaSArIDE7XG4gICAgICAgICAgICAgICAgaWYgKHByID09PSBwbCkge1xuICAgICAgICAgICAgICAgICAgICB0aGlzLmRlYnVnKCcqKiBhdCB0aGUgZW5kJyk7XG4gICAgICAgICAgICAgICAgICAgIC8vIGEgKiogYXQgdGhlIGVuZCB3aWxsIGp1c3Qgc3dhbGxvdyB0aGUgcmVzdC5cbiAgICAgICAgICAgICAgICAgICAgLy8gV2UgaGF2ZSBmb3VuZCBhIG1hdGNoLlxuICAgICAgICAgICAgICAgICAgICAvLyBob3dldmVyLCBpdCB3aWxsIG5vdCBzd2FsbG93IC8ueCwgdW5sZXNzXG4gICAgICAgICAgICAgICAgICAgIC8vIG9wdGlvbnMuZG90IGlzIHNldC5cbiAgICAgICAgICAgICAgICAgICAgLy8gLiBhbmQgLi4gYXJlICpuZXZlciogbWF0Y2hlZCBieSAqKiwgZm9yIGV4cGxvc2l2ZWx5XG4gICAgICAgICAgICAgICAgICAgIC8vIGV4cG9uZW50aWFsIHJlYXNvbnMuXG4gICAgICAgICAgICAgICAgICAgIGZvciAoOyBmaSA8IGZsOyBmaSsrKSB7XG4gICAgICAgICAgICAgICAgICAgICAgICBpZiAoZmlsZVtmaV0gPT09ICcuJyB8fFxuICAgICAgICAgICAgICAgICAgICAgICAgICAgIGZpbGVbZmldID09PSAnLi4nIHx8XG4gICAgICAgICAgICAgICAgICAgICAgICAgICAgKCFvcHRpb25zLmRvdCAmJiBmaWxlW2ZpXS5jaGFyQXQoMCkgPT09ICcuJykpXG4gICAgICAgICAgICAgICAgICAgICAgICAgICAgcmV0dXJuIGZhbHNlO1xuICAgICAgICAgICAgICAgICAgICB9XG4gICAgICAgICAgICAgICAgICAgIHJldHVybiB0cnVlO1xuICAgICAgICAgICAgICAgIH1cbiAgICAgICAgICAgICAgICAvLyBvaywgbGV0J3Mgc2VlIGlmIHdlIGNhbiBzd2FsbG93IHdoYXRldmVyIHdlIGNhbi5cbiAgICAgICAgICAgICAgICB3aGlsZSAoZnIgPCBmbCkge1xuICAgICAgICAgICAgICAgICAgICB2YXIgc3dhbGxvd2VlID0gZmlsZVtmcl07XG4gICAgICAgICAgICAgICAgICAgIHRoaXMuZGVidWcoJ1xcbmdsb2JzdGFyIHdoaWxlJywgZmlsZSwgZnIsIHBhdHRlcm4sIHByLCBzd2FsbG93ZWUpO1xuICAgICAgICAgICAgICAgICAgICAvLyBYWFggcmVtb3ZlIHRoaXMgc2xpY2UuICBKdXN0IHBhc3MgdGhlIHN0YXJ0IGluZGV4LlxuICAgICAgICAgICAgICAgICAgICBpZiAodGhpcy5tYXRjaE9uZShmaWxlLnNsaWNlKGZyKSwgcGF0dGVybi5zbGljZShwciksIHBhcnRpYWwpKSB7XG4gICAgICAgICAgICAgICAgICAgICAgICB0aGlzLmRlYnVnKCdnbG9ic3RhciBmb3VuZCBtYXRjaCEnLCBmciwgZmwsIHN3YWxsb3dlZSk7XG4gICAgICAgICAgICAgICAgICAgICAgICAvLyBmb3VuZCBhIG1hdGNoLlxuICAgICAgICAgICAgICAgICAgICAgICAgcmV0dXJuIHRydWU7XG4gICAgICAgICAgICAgICAgICAgIH1cbiAgICAgICAgICAgICAgICAgICAgZWxzZSB7XG4gICAgICAgICAgICAgICAgICAgICAgICAvLyBjYW4ndCBzd2FsbG93IFwiLlwiIG9yIFwiLi5cIiBldmVyLlxuICAgICAgICAgICAgICAgICAgICAgICAgLy8gY2FuIG9ubHkgc3dhbGxvdyBcIi5mb29cIiB3aGVuIGV4cGxpY2l0bHkgYXNrZWQuXG4gICAgICAgICAgICAgICAgICAgICAgICBpZiAoc3dhbGxvd2VlID09PSAnLicgfHxcbiAgICAgICAgICAgICAgICAgICAgICAgICAgICBzd2FsbG93ZWUgPT09ICcuLicgfHxcbiAgICAgICAgICAgICAgICAgICAgICAgICAgICAoIW9wdGlvbnMuZG90ICYmIHN3YWxsb3dlZS5jaGFyQXQoMCkgPT09ICcuJykpIHtcbiAgICAgICAgICAgICAgICAgICAgICAgICAgICB0aGlzLmRlYnVnKCdkb3QgZGV0ZWN0ZWQhJywgZmlsZSwgZnIsIHBhdHRlcm4sIHByKTtcbiAgICAgICAgICAgICAgICAgICAgICAgICAgICBicmVhaztcbiAgICAgICAgICAgICAgICAgICAgICAgIH1cbiAgICAgICAgICAgICAgICAgICAgICAgIC8vICoqIHN3YWxsb3dzIGEgc2VnbWVudCwgYW5kIGNvbnRpbnVlLlxuICAgICAgICAgICAgICAgICAgICAgICAgdGhpcy5kZWJ1ZygnZ2xvYnN0YXIgc3dhbGxvdyBhIHNlZ21lbnQsIGFuZCBjb250aW51ZScpO1xuICAgICAgICAgICAgICAgICAgICAgICAgZnIrKztcbiAgICAgICAgICAgICAgICAgICAgfVxuICAgICAgICAgICAgICAgIH1cbiAgICAgICAgICAgICAgICAvLyBubyBtYXRjaCB3YXMgZm91bmQuXG4gICAgICAgICAgICAgICAgLy8gSG93ZXZlciwgaW4gcGFydGlhbCBtb2RlLCB3ZSBjYW4ndCBzYXkgdGhpcyBpcyBuZWNlc3NhcmlseSBvdmVyLlxuICAgICAgICAgICAgICAgIC8qIGM4IGlnbm9yZSBzdGFydCAqL1xuICAgICAgICAgICAgICAgIGlmIChwYXJ0aWFsKSB7XG4gICAgICAgICAgICAgICAgICAgIC8vIHJhbiBvdXQgb2YgZmlsZVxuICAgICAgICAgICAgICAgICAgICB0aGlzLmRlYnVnKCdcXG4+Pj4gbm8gbWF0Y2gsIHBhcnRpYWw/JywgZmlsZSwgZnIsIHBhdHRlcm4sIHByKTtcbiAgICAgICAgICAgICAgICAgICAgaWYgKGZyID09PSBmbCkge1xuICAgICAgICAgICAgICAgICAgICAgICAgcmV0dXJuIHRydWU7XG4gICAgICAgICAgICAgICAgICAgIH1cbiAgICAgICAgICAgICAgICB9XG4gICAgICAgICAgICAgICAgLyogYzggaWdub3JlIHN0b3AgKi9cbiAgICAgICAgICAgICAgICByZXR1cm4gZmFsc2U7XG4gICAgICAgICAgICB9XG4gICAgICAgICAgICAvLyBzb21ldGhpbmcgb3RoZXIgdGhhbiAqKlxuICAgICAgICAgICAgLy8gbm9uLW1hZ2ljIHBhdHRlcm5zIGp1c3QgaGF2ZSB0byBtYXRjaCBleGFjdGx5XG4gICAgICAgICAgICAvLyBwYXR0ZXJucyB3aXRoIG1hZ2ljIGhhdmUgYmVlbiB0dXJuZWQgaW50byByZWdleHBzLlxuICAgICAgICAgICAgbGV0IGhpdDtcbiAgICAgICAgICAgIGlmICh0eXBlb2YgcCA9PT0gJ3N0cmluZycpIHtcbiAgICAgICAgICAgICAgICBoaXQgPSBmID09PSBwO1xuICAgICAgICAgICAgICAgIHRoaXMuZGVidWcoJ3N0cmluZyBtYXRjaCcsIHAsIGYsIGhpdCk7XG4gICAgICAgICAgICB9XG4gICAgICAgICAgICBlbHNlIHtcbiAgICAgICAgICAgICAgICBoaXQgPSBwLnRlc3QoZik7XG4gICAgICAgICAgICAgICAgdGhpcy5kZWJ1ZygncGF0dGVybiBtYXRjaCcsIHAsIGYsIGhpdCk7XG4gICAgICAgICAgICB9XG4gICAgICAgICAgICBpZiAoIWhpdClcbiAgICAgICAgICAgICAgICByZXR1cm4gZmFsc2U7XG4gICAgICAgIH1cbiAgICAgICAgLy8gTm90ZTogZW5kaW5nIGluIC8gbWVhbnMgdGhhdCB3ZSdsbCBnZXQgYSBmaW5hbCBcIlwiXG4gICAgICAgIC8vIGF0IHRoZSBlbmQgb2YgdGhlIHBhdHRlcm4uICBUaGlzIGNhbiBvbmx5IG1hdGNoIGFcbiAgICAgICAgLy8gY29ycmVzcG9uZGluZyBcIlwiIGF0IHRoZSBlbmQgb2YgdGhlIGZpbGUuXG4gICAgICAgIC8vIElmIHRoZSBmaWxlIGVuZHMgaW4gLywgdGhlbiBpdCBjYW4gb25seSBtYXRjaCBhXG4gICAgICAgIC8vIGEgcGF0dGVybiB0aGF0IGVuZHMgaW4gLywgdW5sZXNzIHRoZSBwYXR0ZXJuIGp1c3RcbiAgICAgICAgLy8gZG9lc24ndCBoYXZlIGFueSBtb3JlIGZvciBpdC4gQnV0LCBhL2IvIHNob3VsZCAqbm90KlxuICAgICAgICAvLyBtYXRjaCBcImEvYi8qXCIsIGV2ZW4gdGhvdWdoIFwiXCIgbWF0Y2hlcyBhZ2FpbnN0IHRoZVxuICAgICAgICAvLyBbXi9dKj8gcGF0dGVybiwgZXhjZXB0IGluIHBhcnRpYWwgbW9kZSwgd2hlcmUgaXQgbWlnaHRcbiAgICAgICAgLy8gc2ltcGx5IG5vdCBiZSByZWFjaGVkIHlldC5cbiAgICAgICAgLy8gSG93ZXZlciwgYS9iLyBzaG91bGQgc3RpbGwgc2F0aXNmeSBhLypcbiAgICAgICAgLy8gbm93IGVpdGhlciB3ZSBmZWxsIG9mZiB0aGUgZW5kIG9mIHRoZSBwYXR0ZXJuLCBvciB3ZSdyZSBkb25lLlxuICAgICAgICBpZiAoZmkgPT09IGZsICYmIHBpID09PSBwbCkge1xuICAgICAgICAgICAgLy8gcmFuIG91dCBvZiBwYXR0ZXJuIGFuZCBmaWxlbmFtZSBhdCB0aGUgc2FtZSB0aW1lLlxuICAgICAgICAgICAgLy8gYW4gZXhhY3QgaGl0IVxuICAgICAgICAgICAgcmV0dXJuIHRydWU7XG4gICAgICAgIH1cbiAgICAgICAgZWxzZSBpZiAoZmkgPT09IGZsKSB7XG4gICAgICAgICAgICAvLyByYW4gb3V0IG9mIGZpbGUsIGJ1dCBzdGlsbCBoYWQgcGF0dGVybiBsZWZ0LlxuICAgICAgICAgICAgLy8gdGhpcyBpcyBvayBpZiB3ZSdyZSBkb2luZyB0aGUgbWF0Y2ggYXMgcGFydCBvZlxuICAgICAgICAgICAgLy8gYSBnbG9iIGZzIHRyYXZlcnNhbC5cbiAgICAgICAgICAgIHJldHVybiBwYXJ0aWFsO1xuICAgICAgICB9XG4gICAgICAgIGVsc2UgaWYgKHBpID09PSBwbCkge1xuICAgICAgICAgICAgLy8gcmFuIG91dCBvZiBwYXR0ZXJuLCBzdGlsbCBoYXZlIGZpbGUgbGVmdC5cbiAgICAgICAgICAgIC8vIHRoaXMgaXMgb25seSBhY2NlcHRhYmxlIGlmIHdlJ3JlIG9uIHRoZSB2ZXJ5IGxhc3RcbiAgICAgICAgICAgIC8vIGVtcHR5IHNlZ21lbnQgb2YgYSBmaWxlIHdpdGggYSB0cmFpbGluZyBzbGFzaC5cbiAgICAgICAgICAgIC8vIGEvKiBzaG91bGQgbWF0Y2ggYS9iL1xuICAgICAgICAgICAgcmV0dXJuIGZpID09PSBmbCAtIDEgJiYgZmlsZVtmaV0gPT09ICcnO1xuICAgICAgICAgICAgLyogYzggaWdub3JlIHN0YXJ0ICovXG4gICAgICAgIH1cbiAgICAgICAgZWxzZSB7XG4gICAgICAgICAgICAvLyBzaG91bGQgYmUgdW5yZWFjaGFibGUuXG4gICAgICAgICAgICB0aHJvdyBuZXcgRXJyb3IoJ3d0Zj8nKTtcbiAgICAgICAgfVxuICAgICAgICAvKiBjOCBpZ25vcmUgc3RvcCAqL1xuICAgIH1cbiAgICBicmFjZUV4cGFuZCgpIHtcbiAgICAgICAgcmV0dXJuICgwLCBleHBvcnRzLmJyYWNlRXhwYW5kKSh0aGlzLnBhdHRlcm4sIHRoaXMub3B0aW9ucyk7XG4gICAgfVxuICAgIHBhcnNlKHBhdHRlcm4pIHtcbiAgICAgICAgKDAsIGFzc2VydF92YWxpZF9wYXR0ZXJuX2pzXzEuYXNzZXJ0VmFsaWRQYXR0ZXJuKShwYXR0ZXJuKTtcbiAgICAgICAgY29uc3Qgb3B0aW9ucyA9IHRoaXMub3B0aW9ucztcbiAgICAgICAgLy8gc2hvcnRjdXRzXG4gICAgICAgIGlmIChwYXR0ZXJuID09PSAnKionKVxuICAgICAgICAgICAgcmV0dXJuIGV4cG9ydHMuR0xPQlNUQVI7XG4gICAgICAgIGlmIChwYXR0ZXJuID09PSAnJylcbiAgICAgICAgICAgIHJldHVybiAnJztcbiAgICAgICAgLy8gZmFyIGFuZCBhd2F5LCB0aGUgbW9zdCBjb21tb24gZ2xvYiBwYXR0ZXJuIHBhcnRzIGFyZVxuICAgICAgICAvLyAqLCAqLiosIGFuZCAqLjxleHQ+ICBBZGQgYSBmYXN0IGNoZWNrIG1ldGhvZCBmb3IgdGhvc2UuXG4gICAgICAgIGxldCBtO1xuICAgICAgICBsZXQgZmFzdFRlc3QgPSBudWxsO1xuICAgICAgICBpZiAoKG0gPSBwYXR0ZXJuLm1hdGNoKHN0YXJSRSkpKSB7XG4gICAgICAgICAgICBmYXN0VGVzdCA9IG9wdGlvbnMuZG90ID8gc3RhclRlc3REb3QgOiBzdGFyVGVzdDtcbiAgICAgICAgfVxuICAgICAgICBlbHNlIGlmICgobSA9IHBhdHRlcm4ubWF0Y2goc3RhckRvdEV4dFJFKSkpIHtcbiAgICAgICAgICAgIGZhc3RUZXN0ID0gKG9wdGlvbnMubm9jYXNlXG4gICAgICAgICAgICAgICAgPyBvcHRpb25zLmRvdFxuICAgICAgICAgICAgICAgICAgICA/IHN0YXJEb3RFeHRUZXN0Tm9jYXNlRG90XG4gICAgICAgICAgICAgICAgICAgIDogc3RhckRvdEV4dFRlc3ROb2Nhc2VcbiAgICAgICAgICAgICAgICA6IG9wdGlvbnMuZG90XG4gICAgICAgICAgICAgICAgICAgID8gc3RhckRvdEV4dFRlc3REb3RcbiAgICAgICAgICAgICAgICAgICAgOiBzdGFyRG90RXh0VGVzdCkobVsxXSk7XG4gICAgICAgIH1cbiAgICAgICAgZWxzZSBpZiAoKG0gPSBwYXR0ZXJuLm1hdGNoKHFtYXJrc1JFKSkpIHtcbiAgICAgICAgICAgIGZhc3RUZXN0ID0gKG9wdGlvbnMubm9jYXNlXG4gICAgICAgICAgICAgICAgPyBvcHRpb25zLmRvdFxuICAgICAgICAgICAgICAgICAgICA/IHFtYXJrc1Rlc3ROb2Nhc2VEb3RcbiAgICAgICAgICAgICAgICAgICAgOiBxbWFya3NUZXN0Tm9jYXNlXG4gICAgICAgICAgICAgICAgOiBvcHRpb25zLmRvdFxuICAgICAgICAgICAgICAgICAgICA/IHFtYXJrc1Rlc3REb3RcbiAgICAgICAgICAgICAgICAgICAgOiBxbWFya3NUZXN0KShtKTtcbiAgICAgICAgfVxuICAgICAgICBlbHNlIGlmICgobSA9IHBhdHRlcm4ubWF0Y2goc3RhckRvdFN0YXJSRSkpKSB7XG4gICAgICAgICAgICBmYXN0VGVzdCA9IG9wdGlvbnMuZG90ID8gc3RhckRvdFN0YXJUZXN0RG90IDogc3RhckRvdFN0YXJUZXN0O1xuICAgICAgICB9XG4gICAgICAgIGVsc2UgaWYgKChtID0gcGF0dGVybi5tYXRjaChkb3RTdGFyUkUpKSkge1xuICAgICAgICAgICAgZmFzdFRlc3QgPSBkb3RTdGFyVGVzdDtcbiAgICAgICAgfVxuICAgICAgICBjb25zdCByZSA9IGFzdF9qc18xLkFTVC5mcm9tR2xvYihwYXR0ZXJuLCB0aGlzLm9wdGlvbnMpLnRvTU1QYXR0ZXJuKCk7XG4gICAgICAgIGlmIChmYXN0VGVzdCAmJiB0eXBlb2YgcmUgPT09ICdvYmplY3QnKSB7XG4gICAgICAgICAgICAvLyBBdm9pZHMgb3ZlcnJpZGluZyBpbiBmcm96ZW4gZW52aXJvbm1lbnRzXG4gICAgICAgICAgICBSZWZsZWN0LmRlZmluZVByb3BlcnR5KHJlLCAndGVzdCcsIHsgdmFsdWU6IGZhc3RUZXN0IH0pO1xuICAgICAgICB9XG4gICAgICAgIHJldHVybiByZTtcbiAgICB9XG4gICAgbWFrZVJlKCkge1xuICAgICAgICBpZiAodGhpcy5yZWdleHAgfHwgdGhpcy5yZWdleHAgPT09IGZhbHNlKVxuICAgICAgICAgICAgcmV0dXJuIHRoaXMucmVnZXhwO1xuICAgICAgICAvLyBhdCB0aGlzIHBvaW50LCB0aGlzLnNldCBpcyBhIDJkIGFycmF5IG9mIHBhcnRpYWxcbiAgICAgICAgLy8gcGF0dGVybiBzdHJpbmdzLCBvciBcIioqXCIuXG4gICAgICAgIC8vXG4gICAgICAgIC8vIEl0J3MgYmV0dGVyIHRvIHVzZSAubWF0Y2goKS4gIFRoaXMgZnVuY3Rpb24gc2hvdWxkbid0XG4gICAgICAgIC8vIGJlIHVzZWQsIHJlYWxseSwgYnV0IGl0J3MgcHJldHR5IGNvbnZlbmllbnQgc29tZXRpbWVzLFxuICAgICAgICAvLyB3aGVuIHlvdSBqdXN0IHdhbnQgdG8gd29yayB3aXRoIGEgcmVnZXguXG4gICAgICAgIGNvbnN0IHNldCA9IHRoaXMuc2V0O1xuICAgICAgICBpZiAoIXNldC5sZW5ndGgpIHtcbiAgICAgICAgICAgIHRoaXMucmVnZXhwID0gZmFsc2U7XG4gICAgICAgICAgICByZXR1cm4gdGhpcy5yZWdleHA7XG4gICAgICAgIH1cbiAgICAgICAgY29uc3Qgb3B0aW9ucyA9IHRoaXMub3B0aW9ucztcbiAgICAgICAgY29uc3QgdHdvU3RhciA9IG9wdGlvbnMubm9nbG9ic3RhclxuICAgICAgICAgICAgPyBzdGFyXG4gICAgICAgICAgICA6IG9wdGlvbnMuZG90XG4gICAgICAgICAgICAgICAgPyB0d29TdGFyRG90XG4gICAgICAgICAgICAgICAgOiB0d29TdGFyTm9Eb3Q7XG4gICAgICAgIGNvbnN0IGZsYWdzID0gbmV3IFNldChvcHRpb25zLm5vY2FzZSA/IFsnaSddIDogW10pO1xuICAgICAgICAvLyByZWdleHBpZnkgbm9uLWdsb2JzdGFyIHBhdHRlcm5zXG4gICAgICAgIC8vIGlmICoqIGlzIG9ubHkgaXRlbSwgdGhlbiB3ZSBqdXN0IGRvIG9uZSB0d29TdGFyXG4gICAgICAgIC8vIGlmICoqIGlzIGZpcnN0LCBhbmQgdGhlcmUgYXJlIG1vcmUsIHByZXBlbmQgKFxcL3x0d29TdGFyXFwvKT8gdG8gbmV4dFxuICAgICAgICAvLyBpZiAqKiBpcyBsYXN0LCBhcHBlbmQgKFxcL3R3b1N0YXJ8KSB0byBwcmV2aW91c1xuICAgICAgICAvLyBpZiAqKiBpcyBpbiB0aGUgbWlkZGxlLCBhcHBlbmQgKFxcL3xcXC90d29TdGFyXFwvKSB0byBwcmV2aW91c1xuICAgICAgICAvLyB0aGVuIGZpbHRlciBvdXQgR0xPQlNUQVIgc3ltYm9sc1xuICAgICAgICBsZXQgcmUgPSBzZXRcbiAgICAgICAgICAgIC5tYXAocGF0dGVybiA9PiB7XG4gICAgICAgICAgICBjb25zdCBwcCA9IHBhdHRlcm4ubWFwKHAgPT4ge1xuICAgICAgICAgICAgICAgIGlmIChwIGluc3RhbmNlb2YgUmVnRXhwKSB7XG4gICAgICAgICAgICAgICAgICAgIGZvciAoY29uc3QgZiBvZiBwLmZsYWdzLnNwbGl0KCcnKSlcbiAgICAgICAgICAgICAgICAgICAgICAgIGZsYWdzLmFkZChmKTtcbiAgICAgICAgICAgICAgICB9XG4gICAgICAgICAgICAgICAgcmV0dXJuIHR5cGVvZiBwID09PSAnc3RyaW5nJ1xuICAgICAgICAgICAgICAgICAgICA/IHJlZ0V4cEVzY2FwZShwKVxuICAgICAgICAgICAgICAgICAgICA6IHAgPT09IGV4cG9ydHMuR0xPQlNUQVJcbiAgICAgICAgICAgICAgICAgICAgICAgID8gZXhwb3J0cy5HTE9CU1RBUlxuICAgICAgICAgICAgICAgICAgICAgICAgOiBwLl9zcmM7XG4gICAgICAgICAgICB9KTtcbiAgICAgICAgICAgIHBwLmZvckVhY2goKHAsIGkpID0+IHtcbiAgICAgICAgICAgICAgICBjb25zdCBuZXh0ID0gcHBbaSArIDFdO1xuICAgICAgICAgICAgICAgIGNvbnN0IHByZXYgPSBwcFtpIC0gMV07XG4gICAgICAgICAgICAgICAgaWYgKHAgIT09IGV4cG9ydHMuR0xPQlNUQVIgfHwgcHJldiA9PT0gZXhwb3J0cy5HTE9CU1RBUikge1xuICAgICAgICAgICAgICAgICAgICByZXR1cm47XG4gICAgICAgICAgICAgICAgfVxuICAgICAgICAgICAgICAgIGlmIChwcmV2ID09PSB1bmRlZmluZWQpIHtcbiAgICAgICAgICAgICAgICAgICAgaWYgKG5leHQgIT09IHVuZGVmaW5lZCAmJiBuZXh0ICE9PSBleHBvcnRzLkdMT0JTVEFSKSB7XG4gICAgICAgICAgICAgICAgICAgICAgICBwcFtpICsgMV0gPSAnKD86XFxcXC98JyArIHR3b1N0YXIgKyAnXFxcXC8pPycgKyBuZXh0O1xuICAgICAgICAgICAgICAgICAgICB9XG4gICAgICAgICAgICAgICAgICAgIGVsc2Uge1xuICAgICAgICAgICAgICAgICAgICAgICAgcHBbaV0gPSB0d29TdGFyO1xuICAgICAgICAgICAgICAgICAgICB9XG4gICAgICAgICAgICAgICAgfVxuICAgICAgICAgICAgICAgIGVsc2UgaWYgKG5leHQgPT09IHVuZGVmaW5lZCkge1xuICAgICAgICAgICAgICAgICAgICBwcFtpIC0gMV0gPSBwcmV2ICsgJyg/OlxcXFwvfCcgKyB0d29TdGFyICsgJyk/JztcbiAgICAgICAgICAgICAgICB9XG4gICAgICAgICAgICAgICAgZWxzZSBpZiAobmV4dCAhPT0gZXhwb3J0cy5HTE9CU1RBUikge1xuICAgICAgICAgICAgICAgICAgICBwcFtpIC0gMV0gPSBwcmV2ICsgJyg/OlxcXFwvfFxcXFwvJyArIHR3b1N0YXIgKyAnXFxcXC8pJyArIG5leHQ7XG4gICAgICAgICAgICAgICAgICAgIHBwW2kgKyAxXSA9IGV4cG9ydHMuR0xPQlNUQVI7XG4gICAgICAgICAgICAgICAgfVxuICAgICAgICAgICAgfSk7XG4gICAgICAgICAgICByZXR1cm4gcHAuZmlsdGVyKHAgPT4gcCAhPT0gZXhwb3J0cy5HTE9CU1RBUikuam9pbignLycpO1xuICAgICAgICB9KVxuICAgICAgICAgICAgLmpvaW4oJ3wnKTtcbiAgICAgICAgLy8gbmVlZCB0byB3cmFwIGluIHBhcmVucyBpZiB3ZSBoYWQgbW9yZSB0aGFuIG9uZSB0aGluZyB3aXRoIHwsXG4gICAgICAgIC8vIG90aGVyd2lzZSBvbmx5IHRoZSBmaXJzdCB3aWxsIGJlIGFuY2hvcmVkIHRvIF4gYW5kIHRoZSBsYXN0IHRvICRcbiAgICAgICAgY29uc3QgW29wZW4sIGNsb3NlXSA9IHNldC5sZW5ndGggPiAxID8gWycoPzonLCAnKSddIDogWycnLCAnJ107XG4gICAgICAgIC8vIG11c3QgbWF0Y2ggZW50aXJlIHBhdHRlcm5cbiAgICAgICAgLy8gZW5kaW5nIGluIGEgKiBvciAqKiB3aWxsIG1ha2UgaXQgbGVzcyBzdHJpY3QuXG4gICAgICAgIHJlID0gJ14nICsgb3BlbiArIHJlICsgY2xvc2UgKyAnJCc7XG4gICAgICAgIC8vIGNhbiBtYXRjaCBhbnl0aGluZywgYXMgbG9uZyBhcyBpdCdzIG5vdCB0aGlzLlxuICAgICAgICBpZiAodGhpcy5uZWdhdGUpXG4gICAgICAgICAgICByZSA9ICdeKD8hJyArIHJlICsgJykuKyQnO1xuICAgICAgICB0cnkge1xuICAgICAgICAgICAgdGhpcy5yZWdleHAgPSBuZXcgUmVnRXhwKHJlLCBbLi4uZmxhZ3NdLmpvaW4oJycpKTtcbiAgICAgICAgICAgIC8qIGM4IGlnbm9yZSBzdGFydCAqL1xuICAgICAgICB9XG4gICAgICAgIGNhdGNoIChleCkge1xuICAgICAgICAgICAgLy8gc2hvdWxkIGJlIGltcG9zc2libGVcbiAgICAgICAgICAgIHRoaXMucmVnZXhwID0gZmFsc2U7XG4gICAgICAgIH1cbiAgICAgICAgLyogYzggaWdub3JlIHN0b3AgKi9cbiAgICAgICAgcmV0dXJuIHRoaXMucmVnZXhwO1xuICAgIH1cbiAgICBzbGFzaFNwbGl0KHApIHtcbiAgICAgICAgLy8gaWYgcCBzdGFydHMgd2l0aCAvLyBvbiB3aW5kb3dzLCB3ZSBwcmVzZXJ2ZSB0aGF0XG4gICAgICAgIC8vIHNvIHRoYXQgVU5DIHBhdGhzIGFyZW4ndCBicm9rZW4uICBPdGhlcndpc2UsIGFueSBudW1iZXIgb2ZcbiAgICAgICAgLy8gLyBjaGFyYWN0ZXJzIGFyZSBjb2FsZXNjZWQgaW50byBvbmUsIHVubGVzc1xuICAgICAgICAvLyBwcmVzZXJ2ZU11bHRpcGxlU2xhc2hlcyBpcyBzZXQgdG8gdHJ1ZS5cbiAgICAgICAgaWYgKHRoaXMucHJlc2VydmVNdWx0aXBsZVNsYXNoZXMpIHtcbiAgICAgICAgICAgIHJldHVybiBwLnNwbGl0KCcvJyk7XG4gICAgICAgIH1cbiAgICAgICAgZWxzZSBpZiAodGhpcy5pc1dpbmRvd3MgJiYgL15cXC9cXC9bXlxcL10rLy50ZXN0KHApKSB7XG4gICAgICAgICAgICAvLyBhZGQgYW4gZXh0cmEgJycgZm9yIHRoZSBvbmUgd2UgbG9zZVxuICAgICAgICAgICAgcmV0dXJuIFsnJywgLi4ucC5zcGxpdCgvXFwvKy8pXTtcbiAgICAgICAgfVxuICAgICAgICBlbHNlIHtcbiAgICAgICAgICAgIHJldHVybiBwLnNwbGl0KC9cXC8rLyk7XG4gICAgICAgIH1cbiAgICB9XG4gICAgbWF0Y2goZiwgcGFydGlhbCA9IHRoaXMucGFydGlhbCkge1xuICAgICAgICB0aGlzLmRlYnVnKCdtYXRjaCcsIGYsIHRoaXMucGF0dGVybik7XG4gICAgICAgIC8vIHNob3J0LWNpcmN1aXQgaW4gdGhlIGNhc2Ugb2YgYnVzdGVkIHRoaW5ncy5cbiAgICAgICAgLy8gY29tbWVudHMsIGV0Yy5cbiAgICAgICAgaWYgKHRoaXMuY29tbWVudCkge1xuICAgICAgICAgICAgcmV0dXJuIGZhbHNlO1xuICAgICAgICB9XG4gICAgICAgIGlmICh0aGlzLmVtcHR5KSB7XG4gICAgICAgICAgICByZXR1cm4gZiA9PT0gJyc7XG4gICAgICAgIH1cbiAgICAgICAgaWYgKGYgPT09ICcvJyAmJiBwYXJ0aWFsKSB7XG4gICAgICAgICAgICByZXR1cm4gdHJ1ZTtcbiAgICAgICAgfVxuICAgICAgICBjb25zdCBvcHRpb25zID0gdGhpcy5vcHRpb25zO1xuICAgICAgICAvLyB3aW5kb3dzOiBuZWVkIHRvIHVzZSAvLCBub3QgXFxcbiAgICAgICAgaWYgKHRoaXMuaXNXaW5kb3dzKSB7XG4gICAgICAgICAgICBmID0gZi5zcGxpdCgnXFxcXCcpLmpvaW4oJy8nKTtcbiAgICAgICAgfVxuICAgICAgICAvLyB0cmVhdCB0aGUgdGVzdCBwYXRoIGFzIGEgc2V0IG9mIHBhdGhwYXJ0cy5cbiAgICAgICAgY29uc3QgZmYgPSB0aGlzLnNsYXNoU3BsaXQoZik7XG4gICAgICAgIHRoaXMuZGVidWcodGhpcy5wYXR0ZXJuLCAnc3BsaXQnLCBmZik7XG4gICAgICAgIC8vIGp1c3QgT05FIG9mIHRoZSBwYXR0ZXJuIHNldHMgaW4gdGhpcy5zZXQgbmVlZHMgdG8gbWF0Y2hcbiAgICAgICAgLy8gaW4gb3JkZXIgZm9yIGl0IHRvIGJlIHZhbGlkLiAgSWYgbmVnYXRpbmcsIHRoZW4ganVzdCBvbmVcbiAgICAgICAgLy8gbWF0Y2ggbWVhbnMgdGhhdCB3ZSBoYXZlIGZhaWxlZC5cbiAgICAgICAgLy8gRWl0aGVyIHdheSwgcmV0dXJuIG9uIHRoZSBmaXJzdCBoaXQuXG4gICAgICAgIGNvbnN0IHNldCA9IHRoaXMuc2V0O1xuICAgICAgICB0aGlzLmRlYnVnKHRoaXMucGF0dGVybiwgJ3NldCcsIHNldCk7XG4gICAgICAgIC8vIEZpbmQgdGhlIGJhc2VuYW1lIG9mIHRoZSBwYXRoIGJ5IGxvb2tpbmcgZm9yIHRoZSBsYXN0IG5vbi1lbXB0eSBzZWdtZW50XG4gICAgICAgIGxldCBmaWxlbmFtZSA9IGZmW2ZmLmxlbmd0aCAtIDFdO1xuICAgICAgICBpZiAoIWZpbGVuYW1lKSB7XG4gICAgICAgICAgICBmb3IgKGxldCBpID0gZmYubGVuZ3RoIC0gMjsgIWZpbGVuYW1lICYmIGkgPj0gMDsgaS0tKSB7XG4gICAgICAgICAgICAgICAgZmlsZW5hbWUgPSBmZltpXTtcbiAgICAgICAgICAgIH1cbiAgICAgICAgfVxuICAgICAgICBmb3IgKGxldCBpID0gMDsgaSA8IHNldC5sZW5ndGg7IGkrKykge1xuICAgICAgICAgICAgY29uc3QgcGF0dGVybiA9IHNldFtpXTtcbiAgICAgICAgICAgIGxldCBmaWxlID0gZmY7XG4gICAgICAgICAgICBpZiAob3B0aW9ucy5tYXRjaEJhc2UgJiYgcGF0dGVybi5sZW5ndGggPT09IDEpIHtcbiAgICAgICAgICAgICAgICBmaWxlID0gW2ZpbGVuYW1lXTtcbiAgICAgICAgICAgIH1cbiAgICAgICAgICAgIGNvbnN0IGhpdCA9IHRoaXMubWF0Y2hPbmUoZmlsZSwgcGF0dGVybiwgcGFydGlhbCk7XG4gICAgICAgICAgICBpZiAoaGl0KSB7XG4gICAgICAgICAgICAgICAgaWYgKG9wdGlvbnMuZmxpcE5lZ2F0ZSkge1xuICAgICAgICAgICAgICAgICAgICByZXR1cm4gdHJ1ZTtcbiAgICAgICAgICAgICAgICB9XG4gICAgICAgICAgICAgICAgcmV0dXJuICF0aGlzLm5lZ2F0ZTtcbiAgICAgICAgICAgIH1cbiAgICAgICAgfVxuICAgICAgICAvLyBkaWRuJ3QgZ2V0IGFueSBoaXRzLiAgdGhpcyBpcyBzdWNjZXNzIGlmIGl0J3MgYSBuZWdhdGl2ZVxuICAgICAgICAvLyBwYXR0ZXJuLCBmYWlsdXJlIG90aGVyd2lzZS5cbiAgICAgICAgaWYgKG9wdGlvbnMuZmxpcE5lZ2F0ZSkge1xuICAgICAgICAgICAgcmV0dXJuIGZhbHNlO1xuICAgICAgICB9XG4gICAgICAgIHJldHVybiB0aGlzLm5lZ2F0ZTtcbiAgICB9XG4gICAgc3RhdGljIGRlZmF1bHRzKGRlZikge1xuICAgICAgICByZXR1cm4gZXhwb3J0cy5taW5pbWF0Y2guZGVmYXVsdHMoZGVmKS5NaW5pbWF0Y2g7XG4gICAgfVxufVxuZXhwb3J0cy5NaW5pbWF0Y2ggPSBNaW5pbWF0Y2g7XG4vKiBjOCBpZ25vcmUgc3RhcnQgKi9cbnZhciBhc3RfanNfMiA9IHJlcXVpcmUoXCIuL2FzdC5qc1wiKTtcbk9iamVjdC5kZWZpbmVQcm9wZXJ0eShleHBvcnRzLCBcIkFTVFwiLCB7IGVudW1lcmFibGU6IHRydWUsIGdldDogZnVuY3Rpb24gKCkgeyByZXR1cm4gYXN0X2pzXzIuQVNUOyB9IH0pO1xudmFyIGVzY2FwZV9qc18yID0gcmVxdWlyZShcIi4vZXNjYXBlLmpzXCIpO1xuT2JqZWN0LmRlZmluZVByb3BlcnR5KGV4cG9ydHMsIFwiZXNjYXBlXCIsIHsgZW51bWVyYWJsZTogdHJ1ZSwgZ2V0OiBmdW5jdGlvbiAoKSB7IHJldHVybiBlc2NhcGVfanNfMi5lc2NhcGU7IH0gfSk7XG52YXIgdW5lc2NhcGVfanNfMiA9IHJlcXVpcmUoXCIuL3VuZXNjYXBlLmpzXCIpO1xuT2JqZWN0LmRlZmluZVByb3BlcnR5KGV4cG9ydHMsIFwidW5lc2NhcGVcIiwgeyBlbnVtZXJhYmxlOiB0cnVlLCBnZXQ6IGZ1bmN0aW9uICgpIHsgcmV0dXJuIHVuZXNjYXBlX2pzXzIudW5lc2NhcGU7IH0gfSk7XG4vKiBjOCBpZ25vcmUgc3RvcCAqL1xuZXhwb3J0cy5taW5pbWF0Y2guQVNUID0gYXN0X2pzXzEuQVNUO1xuZXhwb3J0cy5taW5pbWF0Y2guTWluaW1hdGNoID0gTWluaW1hdGNoO1xuZXhwb3J0cy5taW5pbWF0Y2guZXNjYXBlID0gZXNjYXBlX2pzXzEuZXNjYXBlO1xuZXhwb3J0cy5taW5pbWF0Y2gudW5lc2NhcGUgPSB1bmVzY2FwZV9qc18xLnVuZXNjYXBlO1xuLy8jIHNvdXJjZU1hcHBpbmdVUkw9aW5kZXguanMubWFwIiwiXCJ1c2Ugc3RyaWN0XCI7XG5PYmplY3QuZGVmaW5lUHJvcGVydHkoZXhwb3J0cywgXCJfX2VzTW9kdWxlXCIsIHsgdmFsdWU6IHRydWUgfSk7XG5leHBvcnRzLnVuZXNjYXBlID0gdm9pZCAwO1xuLyoqXG4gKiBVbi1lc2NhcGUgYSBzdHJpbmcgdGhhdCBoYXMgYmVlbiBlc2NhcGVkIHdpdGgge0BsaW5rIGVzY2FwZX0uXG4gKlxuICogSWYgdGhlIHtAbGluayB3aW5kb3dzUGF0aHNOb0VzY2FwZX0gb3B0aW9uIGlzIHVzZWQsIHRoZW4gc3F1YXJlLWJyYWNlXG4gKiBlc2NhcGVzIGFyZSByZW1vdmVkLCBidXQgbm90IGJhY2tzbGFzaCBlc2NhcGVzLiAgRm9yIGV4YW1wbGUsIGl0IHdpbGwgdHVyblxuICogdGhlIHN0cmluZyBgJ1sqXSdgIGludG8gYCpgLCBidXQgaXQgd2lsbCBub3QgdHVybiBgJ1xcXFwqJ2AgaW50byBgJyonYCxcbiAqIGJlY3Vhc2UgYFxcYCBpcyBhIHBhdGggc2VwYXJhdG9yIGluIGB3aW5kb3dzUGF0aHNOb0VzY2FwZWAgbW9kZS5cbiAqXG4gKiBXaGVuIGB3aW5kb3dzUGF0aHNOb0VzY2FwZWAgaXMgbm90IHNldCwgdGhlbiBib3RoIGJyYWNlIGVzY2FwZXMgYW5kXG4gKiBiYWNrc2xhc2ggZXNjYXBlcyBhcmUgcmVtb3ZlZC5cbiAqXG4gKiBTbGFzaGVzIChhbmQgYmFja3NsYXNoZXMgaW4gYHdpbmRvd3NQYXRoc05vRXNjYXBlYCBtb2RlKSBjYW5ub3QgYmUgZXNjYXBlZFxuICogb3IgdW5lc2NhcGVkLlxuICovXG5jb25zdCB1bmVzY2FwZSA9IChzLCB7IHdpbmRvd3NQYXRoc05vRXNjYXBlID0gZmFsc2UsIH0gPSB7fSkgPT4ge1xuICAgIHJldHVybiB3aW5kb3dzUGF0aHNOb0VzY2FwZVxuICAgICAgICA/IHMucmVwbGFjZSgvXFxbKFteXFwvXFxcXF0pXFxdL2csICckMScpXG4gICAgICAgIDogcy5yZXBsYWNlKC8oKD8hXFxcXCkufF4pXFxbKFteXFwvXFxcXF0pXFxdL2csICckMSQyJykucmVwbGFjZSgvXFxcXChbXlxcL10pL2csICckMScpO1xufTtcbmV4cG9ydHMudW5lc2NhcGUgPSB1bmVzY2FwZTtcbi8vIyBzb3VyY2VNYXBwaW5nVVJMPXVuZXNjYXBlLmpzLm1hcCIsIm1vZHVsZS5leHBvcnRzID0gcmVxdWlyZShcImNoaWxkX3Byb2Nlc3NcIik7IiwibW9kdWxlLmV4cG9ydHMgPSByZXF1aXJlKFwiZXZlbnRzXCIpOyIsIm1vZHVsZS5leHBvcnRzID0gcmVxdWlyZShcImZzXCIpOyIsIm1vZHVsZS5leHBvcnRzID0gcmVxdWlyZShcInBhdGhcIik7IiwibW9kdWxlLmV4cG9ydHMgPSByZXF1aXJlKFwicHJvY2Vzc1wiKTsiLCIvLyBUaGUgbW9kdWxlIGNhY2hlXG52YXIgX193ZWJwYWNrX21vZHVsZV9jYWNoZV9fID0ge307XG5cbi8vIFRoZSByZXF1aXJlIGZ1bmN0aW9uXG5mdW5jdGlvbiBfX3dlYnBhY2tfcmVxdWlyZV9fKG1vZHVsZUlkKSB7XG5cdC8vIENoZWNrIGlmIG1vZHVsZSBpcyBpbiBjYWNoZVxuXHR2YXIgY2FjaGVkTW9kdWxlID0gX193ZWJwYWNrX21vZHVsZV9jYWNoZV9fW21vZHVsZUlkXTtcblx0aWYgKGNhY2hlZE1vZHVsZSAhPT0gdW5kZWZpbmVkKSB7XG5cdFx0cmV0dXJuIGNhY2hlZE1vZHVsZS5leHBvcnRzO1xuXHR9XG5cdC8vIENyZWF0ZSBhIG5ldyBtb2R1bGUgKGFuZCBwdXQgaXQgaW50byB0aGUgY2FjaGUpXG5cdHZhciBtb2R1bGUgPSBfX3dlYnBhY2tfbW9kdWxlX2NhY2hlX19bbW9kdWxlSWRdID0ge1xuXHRcdC8vIG5vIG1vZHVsZS5pZCBuZWVkZWRcblx0XHQvLyBubyBtb2R1bGUubG9hZGVkIG5lZWRlZFxuXHRcdGV4cG9ydHM6IHt9XG5cdH07XG5cblx0Ly8gRXhlY3V0ZSB0aGUgbW9kdWxlIGZ1bmN0aW9uXG5cdF9fd2VicGFja19tb2R1bGVzX19bbW9kdWxlSWRdLmNhbGwobW9kdWxlLmV4cG9ydHMsIG1vZHVsZSwgbW9kdWxlLmV4cG9ydHMsIF9fd2VicGFja19yZXF1aXJlX18pO1xuXG5cdC8vIFJldHVybiB0aGUgZXhwb3J0cyBvZiB0aGUgbW9kdWxlXG5cdHJldHVybiBtb2R1bGUuZXhwb3J0cztcbn1cblxuIiwiIyEvdXNyL2Jpbi9lbnYgbm9kZVxuXG4vKlxuICogQ29weXJpZ2h0IChjKSAyMDI0IEh1YXdlaSBEZXZpY2UgQ28uLCBMdGQuXG4gKiBMaWNlbnNlZCB1bmRlciB0aGUgQXBhY2hlIExpY2Vuc2UsIFZlcnNpb24gMi4wICh0aGUgXCJMaWNlbnNlXCIpO1xuICogeW91IG1heSBub3QgdXNlIHRoaXMgZmlsZSBleGNlcHQgaW4gY29tcGxpYW5jZSB3aXRoIHRoZSBMaWNlbnNlLlxuICogWW91IG1heSBvYnRhaW4gYSBjb3B5IG9mIHRoZSBMaWNlbnNlIGF0XG4gKlxuICogaHR0cDovL3d3dy5hcGFjaGUub3JnL2xpY2Vuc2VzL0xJQ0VOU0UtMi4wXG4gKlxuICogVW5sZXNzIHJlcXVpcmVkIGJ5IGFwcGxpY2FibGUgbGF3IG9yIGFncmVlZCB0byBpbiB3cml0aW5nLCBzb2Z0d2FyZVxuICogZGlzdHJpYnV0ZWQgdW5kZXIgdGhlIExpY2Vuc2UgaXMgZGlzdHJpYnV0ZWQgb24gYW4gXCJBUyBJU1wiIEJBU0lTLFxuICogV0lUSE9VVCBXQVJSQU5USUVTIE9SIENPTkRJVElPTlMgT0YgQU5ZIEtJTkQsIGVpdGhlciBleHByZXNzIG9yIGltcGxpZWQuXG4gKiBTZWUgdGhlIExpY2Vuc2UgZm9yIHRoZSBzcGVjaWZpYyBsYW5ndWFnZSBnb3Zlcm5pbmcgcGVybWlzc2lvbnMgYW5kXG4gKiBsaW1pdGF0aW9ucyB1bmRlciB0aGUgTGljZW5zZS5cbiAqL1xuXG5pbXBvcnQgeyBwcm9ncmFtIH0gZnJvbSBcImNvbW1hbmRlclwiXG5pbXBvcnQgKiBhcyBmcyBmcm9tIFwiZnNcIlxuaW1wb3J0ICogYXMgcGF0aCBmcm9tIFwicGF0aFwiXG5pbXBvcnQgKiBhcyBjaGlsZF9wcm9jZXNzIGZyb20gXCJjaGlsZF9wcm9jZXNzXCJcbmltcG9ydCB7IG1pbmltYXRjaCB9IGZyb20gJ21pbmltYXRjaCdcblxuY29uc3QgcmVhZGRpclN5bmNSZWN1cnNpdmU6IChkaXI6IHN0cmluZykgPT4gc3RyaW5nW10gPSAoZGlyOiBzdHJpbmcpID0+XG4gICAgZnMucmVhZGRpclN5bmMoZGlyKS5yZWR1Y2UoKGZpbGVzOiBzdHJpbmdbXSwgZmlsZTogc3RyaW5nKSA9PiB7XG4gICAgICAgIGNvbnN0IG5hbWUgPSBwYXRoLmpvaW4oZGlyLCBmaWxlKVxuICAgICAgICByZXR1cm4gZnMubHN0YXRTeW5jKG5hbWUpLmlzRGlyZWN0b3J5KCkgPyBbLi4uZmlsZXMsIC4uLnJlYWRkaXJTeW5jUmVjdXJzaXZlKG5hbWUpXSA6IFsuLi5maWxlcywgbmFtZV1cbiAgICB9LCBbXSlcblxuY29uc3Qgb3B0aW9ucyA9IHByb2dyYW1cbiAgICAub3B0aW9uKCctLWlucHV0LWZpbGVzIDxwYXRoPicsICdQYXRoIHRvIGlucHV0IGZpbGUocyksIGNvbW1hIHNlcGFyYXRlZCcpXG4gICAgLm9wdGlvbignLS1vdXRwdXQtZGlyIDxwYXRoPicsICdQYXRoIHRvIG91dHB1dCBkaXInKVxuICAgIC5vcHRpb24oJy0tY29tcGlsZXIgPHBhdGg+JywgJ1BhdGggdG8gY29tcGlsZXInKVxuICAgIC5vcHRpb24oJy0tbGluay1uYW1lIDxwYXRoPicsICdOYW1lIG9mIGNvbWJpbmVkIGxpbmstbmFtZS5hYmMnLCBcImFsbFwiKVxuICAgIC5vcHRpb24oJy0tdGFyZ2V0IDxuaW5qYXxtYWtlPicsICdUYXJnZXQgYnVpbGQgc3lzdGVtJywgXCJuaW5qYVwiKVxuICAgIC5vcHRpb24oJy0tZmlsZS1vcHRpb24nLCAnV2hlbiBwcm92aWRlZCBwYXNzIHRoZSBzb3VyY2UgYXMgLS1maWxlIDxwYXRoPiByYXRoZXIgdGhhbiBhIGZyZWUgb3B0aW9uJylcbiAgICAub3B0aW9uKCctLWFvdC1saWJzIDxsaWJzPicsICdDb21tYS1zZXBhcmF0ZWQgQU9UIGxpYnJhcmllcyB0byBpbmNsdWRlJylcbiAgICAub3B0aW9uKCctLW9ubHktYW90IDxmaWxlPicsICdBT1QgYW4gLmFiYyB0YWtpbmcgLS1hb3QtbGlicyBpbnRvIGFjY291bnQnKVxuICAgIC5vcHRpb24oJy0tYW90LXRhcmdldCA8YXJtfGFybTY0fHg4Nnx4ODZfNjQ+JywgJ0NvbXBpbGF0aW9uIHRhcmdldCBmb3IgQU9UJylcblxuICAgIC5wYXJzZSgpXG4gICAgLm9wdHMoKVxuXG5pZiAob3B0aW9ucy5vbmx5QW90KVxuICAgIG1haW5Bb3QocGF0aC5yZXNvbHZlKG9wdGlvbnMub25seUFvdCkpXG5lbHNlXG4gICAgbWFpbihvcHRpb25zLmlucHV0RmlsZXMsIHBhdGgucmVzb2x2ZShvcHRpb25zLm91dHB1dERpciksIG9wdGlvbnMubGlua05hbWUsIG9wdGlvbnMudGFyZ2V0KVxuXG5mdW5jdGlvbiBmaW5kTWF0Y2hpbmcoYmFzZTogc3RyaW5nLCBpbmNsdWRlOiBzdHJpbmdbXSwgZXhjbHVkZTogc3RyaW5nW10pOiBzdHJpbmdbXSB7XG4gICAgcmV0dXJuIHJlYWRkaXJTeW5jUmVjdXJzaXZlKGJhc2UpXG4gICAgICAgIC5tYXAoaXQgPT4gcGF0aC5yZXNvbHZlKGl0KSlcbiAgICAgICAgLmZpbHRlcihpdCA9PiBpbmNsdWRlLnNvbWUodmFsdWUgPT4gbWluaW1hdGNoKGl0LCBwYXRoLmpvaW4oYmFzZSwgdmFsdWUpLCB7bWF0Y2hCYXNlOiB0cnVlfSkpKVxuICAgICAgICAuZmlsdGVyKGl0ID0+ICFleGNsdWRlLnNvbWUodmFsdWUgPT4gbWluaW1hdGNoKGl0LCBwYXRoLmpvaW4oYmFzZSwgdmFsdWUpLCB7bWF0Y2hCYXNlOiB0cnVlfSkpKVxufVxuXG5mdW5jdGlvbiBwcm9kdWNlUGFpcnMoZmlsZXM6IHN0cmluZ1tdLFxuICAgICAgICAgICAgICAgICAgICAgIGJhc2VEaXI6IHN0cmluZyxcbiAgICAgICAgICAgICAgICAgICAgICByb290RGlyOiBzdHJpbmcgfCB1bmRlZmluZWQsXG4gICAgICAgICAgICAgICAgICAgICAgYnVpbGREaXI6IHN0cmluZyB8IHVuZGVmaW5lZCk6IHsgaW5wdXQ6IHN0cmluZywgb3V0cHV0OiBzdHJpbmcgfVtdIHtcbiAgICByZXR1cm4gZmlsZXMubWFwKHNyY0ZpbGUgPT4ge1xuICAgICAgICBjb25zdCBmaWxlQnVpbGREaXIgPSBidWlsZERpclxuICAgICAgICAgICAgPyBwYXRoLmpvaW4oYnVpbGREaXIsIHBhdGgucmVsYXRpdmUocm9vdERpciA/PyBiYXNlRGlyLCBwYXRoLmRpcm5hbWUoc3JjRmlsZSkpKVxuICAgICAgICAgICAgOiBwYXRoLmRpcm5hbWUoc3JjRmlsZSlcbiAgICAgICAgZnMubWtkaXJTeW5jKGZpbGVCdWlsZERpciwge3JlY3Vyc2l2ZTogdHJ1ZX0pXG4gICAgICAgIHJldHVybiB7XG4gICAgICAgICAgICBpbnB1dDogc3JjRmlsZSxcbiAgICAgICAgICAgIG91dHB1dDogYCR7cGF0aC5qb2luKGZpbGVCdWlsZERpciwgcGF0aC5iYXNlbmFtZShzcmNGaWxlKS5yZXBsYWNlKHBhdGguZXh0bmFtZShzcmNGaWxlKSwgXCIuYWJjXCIpKX1gXG4gICAgICAgIH1cbiAgICB9KVxufVxuXG5mdW5jdGlvbiBhcmNoRGlyKCk6IHN0cmluZyB7XG4gICAgY29uc3QgYXJjaCA9IHByb2Nlc3MuYXJjaFxuICAgIGxldCBzZGtBcmNoID0gXCJcIjtcbiAgICBzd2l0Y2ggKGFyY2gpIHtcbiAgICAgICAgY2FzZSBcIng2NFwiOlxuICAgICAgICAgICAgc2RrQXJjaCA9IFwiXCJcbiAgICAgICAgICAgIGJyZWFrXG4gICAgICAgIGNhc2UgXCJhcm02NFwiOlxuICAgICAgICAgICAgc2RrQXJjaCA9IFwiYXJtNjRcIlxuICAgICAgICAgICAgYnJlYWtcbiAgICAgICAgZGVmYXVsdDogdGhyb3cgbmV3IEVycm9yKGBVbmV4cGVjdGVkIGFyY2g6ICR7YXJjaH1gKVxuXG4gICAgfVxuICAgIGNvbnN0IHBsYXRmb3JtID0gcHJvY2Vzcy5wbGF0Zm9ybVxuICAgIGxldCBzZGtQbGF0Zm9ybSA9IFwiXCJcbiAgICBzd2l0Y2ggKHBsYXRmb3JtKSB7XG4gICAgICAgIGNhc2UgXCJsaW51eFwiOiBzZGtQbGF0Zm9ybSA9IFwibGludXhcIlxuICAgICAgICAgICAgYnJlYWtcbiAgICAgICAgY2FzZSBcIndpbjMyXCI6IHNka1BsYXRmb3JtID0gXCJ3aW5kb3dzXCJcbiAgICAgICAgICAgIGJyZWFrXG4gICAgICAgIGNhc2UgXCJkYXJ3aW5cIjogc2RrUGxhdGZvcm0gPSBcIm1hY29zXCJcbiAgICAgICAgICAgIGJyZWFrXG4gICAgICAgIGRlZmF1bHQ6IHRocm93IG5ldyBFcnJvcihgVW5zdXBwb3J0ZWQgcGxhdGZvcm0gJHtwbGF0Zm9ybX1gKVxuICAgIH1cbiAgICBjb25zdCBzdWZmaXggPSBcImhvc3RfdG9vbHNcIlxuICAgIHJldHVybiBbc2RrUGxhdGZvcm0sIHNka0FyY2gsIHN1ZmZpeF0uZmlsdGVyKGl0ID0+IGl0ICE9IFwiXCIpLmpvaW4oXCJfXCIpXG59XG5cbmZ1bmN0aW9uIHByb2R1Y2VNYWtlZmlsZShjb21waWxlcjogc3RyaW5nLFxuICAgICAgICAgICAgICAgICAgICAgICAgIGZpbGVzOiB7aW5wdXQ6IHN0cmluZywgb3V0cHV0OiBzdHJpbmd9W10sXG4gICAgICAgICAgICAgICAgICAgICAgICAgb3V0cHV0RGlyOiBzdHJpbmcsXG4gICAgICAgICAgICAgICAgICAgICAgICAgY29uZmlnOiBzdHJpbmcsXG4gICAgICAgICAgICAgICAgICAgICAgICAgbGlua05hbWU6IHN0cmluZyk6IHN0cmluZyB7XG4gICAgbGV0IHJlc3VsdDogc3RyaW5nW10gPSBbXVxuICAgIGxldCBhbGw6IHN0cmluZ1tdID0gW11cbiAgICByZXN1bHQucHVzaChcImRlZmF1bHQ6IGFsbFwiKVxuICAgIGxldCBiYXNlbmFtZSA9IHBhdGguYmFzZW5hbWUoY29tcGlsZXIpXG4gICAgbGV0IGxpbmtlciA9IGNvbXBpbGVyLnJlcGxhY2UoYmFzZW5hbWUsICdhcmtsaW5rJylcblxuICAgIGZpbGVzLmZvckVhY2goaXQgPT4ge1xuICAgICAgICBhbGwucHVzaChpdC5vdXRwdXQpXG4gICAgICAgIHJlc3VsdC5wdXNoKGAke2l0Lm91dHB1dH06ICR7aXQuaW5wdXR9YClcbiAgICAgICAgcmVzdWx0LnB1c2goYFxcdCR7Y29tcGlsZXJ9IC0tZXRzLW1vZHVsZSAtLWFya3RzY29uZmlnICR7cGF0aC5yZXNvbHZlKGNvbmZpZyl9ICR7b3B0aW9ucy5maWxlT3B0aW9uID8gXCItLWZpbGVcIiA6IFwiXCJ9ICR7aXQuaW5wdXR9IC0tb3V0cHV0ICR7aXQub3V0cHV0fWApXG4gICAgfSlcbiAgICByZXN1bHQucHVzaChgY29tcGlsZTogJHthbGwuam9pbignICcpfWApXG4gICAgcmVzdWx0LnB1c2goYGxpbms6IGNvbXBpbGVgKVxuICAgIHJlc3VsdC5wdXNoKGBcXHQke2xpbmtlcn0gLS1vdXRwdXQgJHtvdXRwdXREaXJ9LyR7bGlua05hbWV9LmFiYyAtLSAke2FsbC5qb2luKCcgJyl9YClcbiAgICByZXN1bHQucHVzaChgYWxsOiBsaW5rYClcbiAgICByZXR1cm4gcmVzdWx0LmpvaW4oJ1xcbicpXG59XG5cbmZ1bmN0aW9uIHByb2R1Y2VOaW5qYWZpbGUoY29tcGlsZXI6IHN0cmluZyxcbiAgICAgICAgICAgICAgICAgICAgICAgICAgZmlsZXM6IHtpbnB1dDogc3RyaW5nLCBvdXRwdXQ6IHN0cmluZ31bXSxcbiAgICAgICAgICAgICAgICAgICAgICAgICAgb3V0cHV0RGlyOiBzdHJpbmcsXG4gICAgICAgICAgICAgICAgICAgICAgICAgIGNvbmZpZzogc3RyaW5nLFxuICAgICAgICAgICAgICAgICAgICAgICAgICBsaW5rTmFtZTogc3RyaW5nXG4gICAgICAgICAgICAgICAgICAgICAgICApOiBzdHJpbmcge1xuICAgIC8vIFdlIGhhdmUgbm8gUGFuZGEgU0RLIGZvciBtYWNPUy5cbiAgICBjb25zdCB0b29sc19wcmVmaXggPSAgcHJvY2Vzcy5wbGF0Zm9ybSA9PSBcImRhcndpblwiID8gXCJlY2hvIFwiIDogXCJcIlxuICAgIGxldCByZXN1bHQ6IHN0cmluZ1tdID0gW11cbiAgICBsZXQgYWxsOiBzdHJpbmdbXSA9IFtdXG4gICAgbGV0IGJhc2VuYW1lID0gcGF0aC5iYXNlbmFtZShjb21waWxlcilcbiAgICBsZXQgbGlua2VyID0gY29tcGlsZXIucmVwbGFjZShiYXNlbmFtZSwgJ2Fya2xpbmsnKVxuXG4gICAgbGV0IHByZWZpeCA9IGBcbnJ1bGUgYXJrdHNfY29tcGlsZXJcbiAgICBjb21tYW5kID0gJHt0b29sc19wcmVmaXh9JHtjb21waWxlcn0gLS1ldHMtbW9kdWxlIC0tYXJrdHNjb25maWcgJHtwYXRoLnJlc29sdmUoY29uZmlnKX0gJHtvcHRpb25zLmZpbGVPcHRpb24gPyBcIi0tZmlsZVwiIDogXCJcIn0gJGluIC0tb3V0cHV0ICRvdXRcbiAgICBkZXNjcmlwdGlvbiA9IFwiQ29tcGlsaW5nIEFSS1RTICRvdXRcIlxucnVsZSBhcmt0c19saW5rZXJcbiAgICBjb21tYW5kID0gJHt0b29sc19wcmVmaXh9JHtsaW5rZXJ9IC0tb3V0cHV0ICRvdXQgLS0gJGluXG4gICAgZGVzY3JpcHRpb24gPSBcIkxpbmtpbmcgQVJLVFMgJG91dFwiYFxuICAgIGZpbGVzLmZvckVhY2goaXQgPT4ge1xuICAgICAgICBhbGwucHVzaChpdC5vdXRwdXQpXG4gICAgICAgIHJlc3VsdC5wdXNoKGBidWlsZCAke2l0Lm91dHB1dH06IGFya3RzX2NvbXBpbGVyICR7aXQuaW5wdXR9XFxuYClcbiAgICB9KVxuICAgIHJlc3VsdC5wdXNoKGBidWlsZCBjb21waWxlOiBwaG9ueSAke2FsbC5qb2luKCcgJyl9YClcbiAgICByZXN1bHQucHVzaChgYnVpbGQgJHtvdXRwdXREaXJ9LyR7bGlua05hbWV9LmFiYzogYXJrdHNfbGlua2VyICR7YWxsLmpvaW4oJyAnKX1cXG5gKVxuICAgIHJlc3VsdC5wdXNoKGBidWlsZCBsaW5rOiBwaG9ueSAke291dHB1dERpcn0vJHtsaW5rTmFtZX0uYWJjYClcbiAgICByZXN1bHQucHVzaChgYnVpbGQgYWxsOiBwaG9ueSBsaW5rYClcbiAgICByZXN1bHQucHVzaChcImRlZmF1bHQgYWxsXFxuXCIpXG4gICAgcmV0dXJuIHByZWZpeCArICdcXG4nICsgcmVzdWx0LmpvaW4oJ1xcbicpXG59XG5cbmZ1bmN0aW9uIG1haW4oaW5wdXRGaWxlOiBzdHJpbmcsIG91dHB1dERpcjogc3RyaW5nLCBsaW5rTmFtZTogc3RyaW5nLCB0YXJnZXQ6IHN0cmluZykge1xuICAgIGxldCBjb25maWcgPSBKU09OLnBhcnNlKGZzLnJlYWRGaWxlU3luYyhpbnB1dEZpbGUsICd1dGY4JykpXG4gICAgbGV0IGJhc2VEaXIgPSBwYXRoLnJlc29sdmUocGF0aC5kaXJuYW1lKGlucHV0RmlsZSkpXG4gICAgbGV0IGluY2x1ZGUgPSAoY29uZmlnLmluY2x1ZGUgYXMgc3RyaW5nW10pLm1hcChpdCA9PiBpdC5yZXBsYWNlKCdcXFxcLicsICcuJykpXG4gICAgbGV0IGV4Y2x1ZGUgPSBjb25maWcuZXhjbHVkZSA/IChjb25maWcuZXhjbHVkZSBhcyBzdHJpbmdbXSkubWFwKGl0ID0+IGl0LnJlcGxhY2UoJ1xcXFwuJywgJy4nKSkgOiBbXVxuICAgIGNvbnN0IGJ1aWxkRGlyID0gY29uZmlnLmNvbXBpbGVyT3B0aW9ucy5vdXREaXIgPyAocGF0aC5yZXNvbHZlKGNvbmZpZy5jb21waWxlck9wdGlvbnMub3V0RGlyKSkgOiB1bmRlZmluZWRcbiAgICBjb25zdCByb290RGlyID0gY29uZmlnLmNvbXBpbGVyT3B0aW9ucy5yb290RGlyID8gKHBhdGgucmVzb2x2ZShjb25maWcuY29tcGlsZXJPcHRpb25zLnJvb3REaXIpKSA6IHVuZGVmaW5lZFxuICAgIGNvbnN0IGZpbGVzID0gcHJvZHVjZVBhaXJzKGZpbmRNYXRjaGluZyhiYXNlRGlyLCBpbmNsdWRlLCBleGNsdWRlKSwgYmFzZURpciwgcm9vdERpciwgYnVpbGREaXIpXG4gICAgaWYgKGZpbGVzLmxlbmd0aCA9PSAwKSB7XG4gICAgICAgIHRocm93IG5ldyBFcnJvcihgTm8gZmlsZXMgbWF0Y2hpbmcgaW5jbHVkZSBcIiR7aW5jbHVkZS5qb2luKFwiLFwiKX1cIiBleGNsdWRlIFwiJHtleGNsdWRlLmpvaW4oXCIsXCIpfVwiYClcbiAgICB9XG4gICAgZnMubWtkaXJTeW5jKG91dHB1dERpciwgeyByZWN1cnNpdmU6IHRydWUgfSlcbiAgICBpZiAodGFyZ2V0ID09ICdtYWtlJykge1xuICAgICAgICBsZXQgbWFrZXIgPSBwcm9kdWNlTWFrZWZpbGUocGF0aC5yZXNvbHZlKG9wdGlvbnMuY29tcGlsZXIpLCBmaWxlcywgb3V0cHV0RGlyLCBpbnB1dEZpbGUsIGxpbmtOYW1lKVxuICAgICAgICBmcy53cml0ZUZpbGVTeW5jKGAke291dHB1dERpcn0vTWFrZWZpbGVgLCBtYWtlcilcbiAgICB9IGVsc2Uge1xuICAgICAgICBsZXQgbmluamEgPSBwcm9kdWNlTmluamFmaWxlKHBhdGgucmVzb2x2ZShvcHRpb25zLmNvbXBpbGVyKSwgZmlsZXMsIG91dHB1dERpciwgaW5wdXRGaWxlLCBsaW5rTmFtZSlcbiAgICAgICAgZnMud3JpdGVGaWxlU3luYyhgJHtvdXRwdXREaXJ9L2J1aWxkLm5pbmphYCwgbmluamEpXG4gICAgfVxufVxuXG5mdW5jdGlvbiBtYWluQW90KGFiYzogc3RyaW5nKSB7XG4gICAgbGV0IHNkayA9IG9wdGlvbnMuc2RrID8/IHBhdGgucmVzb2x2ZShwYXRoLmpvaW4oX19kaXJuYW1lLCAnLi4nLCAnLi4nLCAncGFuZGEnLCAnbm9kZV9tb2R1bGVzJywgJ0BwYW5kYScsICdzZGsnKSlcbiAgICBsZXQgYW90ID0gcGF0aC5qb2luKHNkaywgYXJjaERpcigpLCAnYmluJywgJ2Fya19hb3QnKVxuICAgIGxldCBzdGRsaWIgPSBwYXRoLnJlc29sdmUocGF0aC5qb2luKHNkaywgXCJldHNcIiwgXCJldHNzdGRsaWIuYWJjXCIpKVxuICAgIGNvbnN0IGFvdExpYnMgPSBbc3RkbGliXVxuICAgIGlmIChvcHRpb25zLmFvdExpYnMpIGFvdExpYnMucHVzaCguLi4gb3B0aW9ucy5hb3RMaWJzLnNwbGl0KFwiLFwiKSlcbiAgICBsZXQgYXJnczogc3RyaW5nW10gPSBbXVxuICAgIGlmIChwcm9jZXNzLnBsYXRmb3JtID09IFwiZGFyd2luXCIpIHtcbiAgICAgICAgLy8gTm8gdG9vbHMgb24gbWFjT1MsIGp1c3QgZWNob1xuICAgICAgICBhcmdzLnB1c2goYW90KVxuICAgICAgICBhb3QgPSBcImVjaG9cIlxuICAgIH1cbiAgICBsZXQgcmVzdWx0ID0gYWJjLnJlcGxhY2UoJy5hYmMnLCAnLmFuJylcbiAgICBhcmdzLnB1c2goLi4uIG9wdGlvbnMuYW90VGFyZ2V0ID8gW2AtLWNvbXBpbGVyLWNyb3NzLWFyY2g9JHtvcHRpb25zLmFvdFRhcmdldH1gXSA6IFtdKVxuICAgIGFyZ3MucHVzaCguLi4gW1xuICAgICAgICBgLS1sb2FkLXJ1bnRpbWVzPWV0c2AsXG4gICAgICAgIGAtLWJvb3QtcGFuZGEtZmlsZXM9JHthb3RMaWJzLmpvaW4oJzonKX06JHthYmN9YCxcbiAgICAgICAgYC0tcGFvYy1wYW5kYS1maWxlcz0ke2FiY31gLFxuICAgICAgICBgLS1wYW9jLW91dHB1dD0ke3Jlc3VsdH1gXG4gICAgXSlcbiAgICBjb25zb2xlLmxvZyhgQU9UIGNvbXBpbGUgJHthYmN9Li4uYClcbiAgICBjb25zdCBjaGlsZCA9IGNoaWxkX3Byb2Nlc3Muc3Bhd24oYW90LCBhcmdzKVxuICAgIGNoaWxkLnN0ZG91dC5vbignZGF0YScsIChkYXRhKSA9PiB7XG4gICAgICAgIHByb2Nlc3Muc3Rkb3V0LndyaXRlKGRhdGEpO1xuICAgIH0pXG4gICAgY2hpbGQuc3RkZXJyLm9uKCdkYXRhJywgKGRhdGEpID0+IHtcbiAgICAgICAgcHJvY2Vzcy5zdGRlcnIud3JpdGUoZGF0YSk7XG4gICAgfSlcbiAgICBjaGlsZC5vbignY2xvc2UnLCAoY29kZSkgPT4ge1xuICAgICAgICBpZiAoY29kZSAhPSAwKVxuICAgICAgICAgICAgY29uc29sZS5sb2coYENvbW1hbmQgJHthb3R9ICR7YXJncy5qb2luKFwiIFwiKX0gZmFpbGVkIHdpdGggcmV0dXJuIGNvZGUgJHtjb2RlfWApXG4gICAgICAgIGVsc2VcbiAgICAgICAgICAgIGNvbnNvbGUubG9nKGBQcm9kdWNlZCBBT1QgZmlsZSAke3Jlc3VsdH06ICR7TWF0aC5yb3VuZChmcy5zdGF0U3luYyhyZXN1bHQpLnNpemUgLyAxMDI0IC8gMTAyNCl9TWApXG4gICAgICAgIHByb2Nlc3MuZXhpdChjb2RlKVxuICAgIH0pXG4gICAgY2hpbGQub24oJ2V4aXQnLCAoY29kZSwgc2lnbmFsKSA9PiB7XG4gICAgICAgIGlmIChzaWduYWwpIHtcbiAgICAgICAgICAgIGNvbnNvbGUubG9nKGBSZWNlaXZlZCBzaWduYWw6ICR7c2lnbmFsfSBmcm9tICcke2FvdH0gJHthcmdzLmpvaW4oJyAnKX0nYClcbiAgICAgICAgICAgIHByb2Nlc3MuZXhpdCgxKVxuICAgICAgICB9XG4gICAgfSlcbn1cbiJdLCJuYW1lcyI6W10sInNvdXJjZVJvb3QiOiIifQ==