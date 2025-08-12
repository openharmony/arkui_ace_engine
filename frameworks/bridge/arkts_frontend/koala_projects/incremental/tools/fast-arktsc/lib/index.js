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
const brace_expansion_1 = __importDefault(__webpack_require__(/*! brace-expansion */ "../../node_modules/minimatch/node_modules/brace-expansion/index.js"));
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

/***/ "../../node_modules/minimatch/node_modules/brace-expansion/index.js":
/*!**************************************************************************!*\
  !*** ../../node_modules/minimatch/node_modules/brace-expansion/index.js ***!
  \**************************************************************************/
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
    const groupSize = 100;
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
    if (all.length <= groupSize) {
        result.push(`build ${outputDir}/${linkName}.abc: arkts_linker ${all.join(' ')}\n`);
    }
    else {
        // If too much file, divide into groups avoid 'posix_spawn: Argument list too long' issue
        const allParts = [];
        for (let i = 0; i < all.length; i += groupSize) {
            const batch = all.slice(i, i + groupSize);
            const partName = `${outputDir}/${linkName}.part${allParts.length + 1}.abc`;
            allParts.push(partName);
            result.push(`build ${partName}: arkts_linker ${batch.join(' ')}\n`);
        }
        result.push(`build ${outputDir}/${linkName}.abc: arkts_linker ${allParts.join(' ')}`);
    }
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
    var _a, _b;
    let sdk = (_a = options.sdk) !== null && _a !== void 0 ? _a : path.resolve(path.join(__dirname, '..', '..', 'panda', 'node_modules', '@panda', 'sdk'));
    let aot = path.join(sdk, archDir(), 'bin', 'ark_aot');
    let stdlib = path.resolve(path.join(sdk, "ets", "etsstdlib.abc"));
    const aotLibs = abc.indexOf("etsstdlib") == -1 ? [stdlib] : [];
    if (options.aotLibs)
        aotLibs.push(...options.aotLibs.split(","));
    let args = [];
    if (process.platform == "darwin") {
        // No tools on macOS, just echo
        args.push(aot);
        aot = "echo";
    }
    let dir = (_b = options.outputDir) !== null && _b !== void 0 ? _b : path.dirname(abc);
    let result = path.join(dir, path.basename(abc).replace('.abc', '.an'));
    args.push(...options.aotTarget ? [`--compiler-cross-arch=${options.aotTarget}`] : []);
    args.push(...[
        `--load-runtimes=ets`,
        `--boot-panda-files=${aotLibs.map(it => path.resolve(it)).concat(abc).join(':')}`,
        `--paoc-panda-files=${abc}`,
        `--paoc-output=${result}`
    ]);
    console.log(`AOT compile ${abc} to ${result}...`);
    console.log(`Launch ${aot} ${args.join(" ")}`);
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
        process.exit(code !== null && code !== void 0 ? code : undefined);
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
//# sourceMappingURL=data:application/json;charset=utf-8;base64,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QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBLGlEQUFpRCxrQ0FBa0M7QUFDbkY7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0EsdUJBQXVCO0FBQ3ZCO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0Esd0JBQXdCLHVCQUF1QjtBQUMvQztBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQSx5Q0FBeUM7QUFDekM7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBLDRDQUE0QyxHQUFHO0FBQy9DO0FBQ0E7QUFDQSxTQUFTO0FBQ1Q7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0EsYUFBYTtBQUNiO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBLHlCQUF5QixLQUFLLE1BQU0sZUFBZTtBQUNuRDtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQSxzQ0FBc0MsVUFBVTtBQUNoRDtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBLFNBQVM7QUFDVDtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBLHdCQUF3QixpQkFBaUI7QUFDekM7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQSxXQUFXO0FBQ1g7Ozs7Ozs7Ozs7O0FDL2tCYTtBQUNiO0FBQ0E7QUFDQSw4Q0FBNkMsRUFBRSxhQUFhLEVBQUM7QUFDN0Qsa0JBQWtCO0FBQ2xCLEtBQUs7QUFDTDtBQUNBLHVCQUF1QixFQUFFLElBQUksR0FBRyxJQUFJLEdBQUc7QUFDdkMsdUJBQXVCLEVBQUUsSUFBSSxHQUFHO0FBQ2hDO0FBQ0EsdUJBQXVCLEdBQUc7QUFDMUIsdUJBQXVCLEdBQUc7QUFDMUIsdUJBQXVCLEdBQUc7QUFDMUIsdUJBQXVCLEVBQUUsSUFBSSxFQUFFO0FBQy9CLHVCQUF1QixHQUFHO0FBQzFCLHVCQUF1QixFQUFFO0FBQ3pCLHVCQUF1QixFQUFFO0FBQ3pCLHVCQUF1QixFQUFFO0FBQ3pCLHVCQUF1QixHQUFHO0FBQzFCLHNCQUFzQixFQUFFLElBQUksR0FBRyxJQUFJLEdBQUcsSUFBSSxHQUFHO0FBQzdDO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBLDhDQUE4QztBQUM5QztBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQSxrQkFBa0I7QUFDbEI7Ozs7Ozs7Ozs7O0FDdkphO0FBQ2IsOENBQTZDLEVBQUUsYUFBYSxFQUFDO0FBQzdELGNBQWM7QUFDZDtBQUNBO0FBQ0E7QUFDQSxXQUFXO0FBQ1g7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBLHFCQUFxQixnQ0FBZ0MsSUFBSTtBQUN6RDtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBLGNBQWM7QUFDZDs7Ozs7Ozs7Ozs7QUNyQmE7QUFDYjtBQUNBLDZDQUE2QztBQUM3QztBQUNBLDhDQUE2QyxFQUFFLGFBQWEsRUFBQztBQUM3RCxnQkFBZ0IsR0FBRyxjQUFjLEdBQUcsV0FBVyxHQUFHLGlCQUFpQixHQUFHLGFBQWEsR0FBRyxjQUFjLEdBQUcsbUJBQW1CLEdBQUcsZ0JBQWdCLEdBQUcsY0FBYyxHQUFHLGdCQUFnQixHQUFHLFdBQVcsR0FBRyxpQkFBaUI7QUFDbk4sMENBQTBDLG1CQUFPLENBQUMsMkZBQWlCO0FBQ25FLGtDQUFrQyxtQkFBTyxDQUFDLHFHQUEyQjtBQUNyRSxpQkFBaUIsbUJBQU8sQ0FBQyxtRUFBVTtBQUNuQyxvQkFBb0IsbUJBQU8sQ0FBQyx5RUFBYTtBQUN6QyxzQkFBc0IsbUJBQU8sQ0FBQyw2RUFBZTtBQUM3QywyQ0FBMkM7QUFDM0M7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQSxpQkFBaUI7QUFDakI7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBLGFBQWEsV0FBVztBQUN4QixhQUFhLFVBQVU7QUFDdkI7QUFDQTtBQUNBLFdBQVc7QUFDWCxxQkFBcUI7QUFDckIsZ0JBQWdCO0FBQ2hCLDBCQUEwQjtBQUMxQjtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0EsMENBQTBDLElBQUk7QUFDOUM7QUFDQTtBQUNBO0FBQ0EscUNBQXFDO0FBQ3JDLGNBQWM7QUFDZCx3QkFBd0I7QUFDeEIsc0JBQXNCLHFCQUFxQjtBQUMzQztBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0EsdUNBQXVDO0FBQ3ZDO0FBQ0E7QUFDQSw2Q0FBNkM7QUFDN0M7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBLFNBQVM7QUFDVDtBQUNBO0FBQ0Esa0RBQWtEO0FBQ2xEO0FBQ0E7QUFDQTtBQUNBLGlEQUFpRDtBQUNqRDtBQUNBO0FBQ0EsU0FBUztBQUNULGtDQUFrQztBQUNsQyxnQ0FBZ0M7QUFDaEMsc0NBQXNDO0FBQ3RDO0FBQ0Esc0NBQXNDO0FBQ3RDLDJDQUEyQztBQUMzQywyQ0FBMkM7QUFDM0M7QUFDQTtBQUNBLEtBQUs7QUFDTDtBQUNBLGdCQUFnQjtBQUNoQiwwQkFBMEI7QUFDMUI7QUFDQSxLQUFLLElBQUk7QUFDVCxLQUFLLEdBQUc7QUFDUixLQUFLLEtBQUs7QUFDVixLQUFLLElBQUksSUFBSSxFQUFFO0FBQ2YsS0FBSyxJQUFJLEVBQUUsSUFBSTtBQUNmO0FBQ0E7QUFDQSxLQUFLLElBQUksT0FBTyxJQUFJO0FBQ3BCLEtBQUssRUFBRSxPQUFPLEVBQUU7QUFDaEIsMENBQTBDO0FBQzFDO0FBQ0E7QUFDQTtBQUNBLCtCQUErQixRQUFRLE1BQU07QUFDN0M7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBLG1CQUFtQjtBQUNuQiw2QkFBNkI7QUFDN0I7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBLHFDQUFxQztBQUNyQyxjQUFjO0FBQ2Qsd0JBQXdCO0FBQ3hCLDBDQUEwQztBQUMxQztBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBLGFBQWE7QUFDYix1QkFBdUI7QUFDdkI7QUFDQTtBQUNBLDhDQUE4QztBQUM5QztBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQSxxQ0FBcUM7QUFDckM7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQSxTQUFTO0FBQ1Q7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBLDRCQUE0QixxQkFBcUI7QUFDakQ7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBLDRCQUE0QixzQkFBc0I7QUFDbEQsZ0NBQWdDLHlCQUF5QjtBQUN6RDtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQSxnQkFBZ0Isd0JBQXdCO0FBQ3hDO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQSxTQUFTO0FBQ1Q7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBLGFBQWE7QUFDYjtBQUNBLFNBQVM7QUFDVDtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBLGdDQUFnQyxzQkFBc0I7QUFDdEQ7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0EsVUFBVTtBQUNWO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0Esc0NBQXNDO0FBQ3RDO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0EsOENBQThDO0FBQzlDO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBLG9DQUFvQyxzQkFBc0I7QUFDMUQ7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBLFVBQVU7QUFDVjtBQUNBO0FBQ0E7QUFDQSxRQUFRLGlDQUFpQztBQUN6QyxRQUFRLDJCQUEyQjtBQUNuQyxRQUFRLDhCQUE4QjtBQUN0QztBQUNBLFFBQVEscUNBQXFDO0FBQzdDO0FBQ0E7QUFDQSx3QkFBd0IsMEJBQTBCO0FBQ2xELGdDQUFnQyxzQkFBc0I7QUFDdEQ7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBLHdCQUF3QixpREFBaUQ7QUFDekU7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0EsZ0JBQWdCLHdCQUF3QjtBQUN4QztBQUNBO0FBQ0E7QUFDQSx1Q0FBdUMsZUFBZTtBQUN0RDtBQUNBLHdFQUF3RSxvQkFBb0I7QUFDNUY7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0EsMkJBQTJCLFNBQVM7QUFDcEM7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBLGlEQUFpRCxpQkFBaUI7QUFDbEU7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0EsYUFBYTtBQUNiO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBLGFBQWE7QUFDYjtBQUNBLFNBQVM7QUFDVDtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtB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YW5jZWQtbWF0Y2gvaW5kZXguanMiLCJ3ZWJwYWNrOi8vQGtvYWxhdWkvZmFzdC1hcmt0c2MvLi4vLi4vbm9kZV9tb2R1bGVzL2NvbW1hbmRlci9pbmRleC5qcyIsIndlYnBhY2s6Ly9Aa29hbGF1aS9mYXN0LWFya3RzYy8uLi8uLi9ub2RlX21vZHVsZXMvY29tbWFuZGVyL2xpYi9hcmd1bWVudC5qcyIsIndlYnBhY2s6Ly9Aa29hbGF1aS9mYXN0LWFya3RzYy8uLi8uLi9ub2RlX21vZHVsZXMvY29tbWFuZGVyL2xpYi9jb21tYW5kLmpzIiwid2VicGFjazovL0Brb2FsYXVpL2Zhc3QtYXJrdHNjLy4uLy4uL25vZGVfbW9kdWxlcy9jb21tYW5kZXIvbGliL2Vycm9yLmpzIiwid2VicGFjazovL0Brb2FsYXVpL2Zhc3QtYXJrdHNjLy4uLy4uL25vZGVfbW9kdWxlcy9jb21tYW5kZXIvbGliL2hlbHAuanMiLCJ3ZWJwYWNrOi8vQGtvYWxhdWkvZmFzdC1hcmt0c2MvLi4vLi4vbm9kZV9tb2R1bGVzL2NvbW1hbmRlci9saWIvb3B0aW9uLmpzIiwid2VicGFjazovL0Brb2FsYXVpL2Zhc3QtYXJrdHNjLy4uLy4uL25vZGVfbW9kdWxlcy9jb21tYW5kZXIvbGliL3N1Z2dlc3RTaW1pbGFyLmpzIiwid2VicGFjazovL0Brb2FsYXVpL2Zhc3QtYXJrdHNjLy4uLy4uL25vZGVfbW9kdWxlcy9taW5pbWF0Y2gvZGlzdC9jb21tb25qcy9hc3NlcnQtdmFsaWQtcGF0dGVybi5qcyIsIndlYnBhY2s6Ly9Aa29hbGF1aS9mYXN0LWFya3RzYy8uLi8uLi9ub2RlX21vZHVsZXMvbWluaW1hdGNoL2Rpc3QvY29tbW9uanMvYXN0LmpzIiwid2VicGFjazovL0Brb2FsYXVpL2Zhc3QtYXJrdHNjLy4uLy4uL25vZGVfbW9kdWxlcy9taW5pbWF0Y2gvZGlzdC9jb21tb25qcy9icmFjZS1leHByZXNzaW9ucy5qcyIsIndlYnBhY2s6Ly9Aa29hbGF1aS9mYXN0LWFya3RzYy8uLi8uLi9ub2RlX21vZHVsZXMvbWluaW1hdGNoL2Rpc3QvY29tbW9uanMvZXNjYXBlLmpzIiwid2VicGFjazovL0Brb2FsYXVpL2Zhc3QtYXJrdHNjLy4uLy4uL25vZGVfbW9kdWxlcy9taW5pbWF0Y2gvZGlzdC9jb21tb25qcy9pbmRleC5qcyIsIndlYnBhY2s6Ly9Aa29hbGF1aS9mYXN0LWFya3RzYy8uLi8uLi9ub2RlX21vZHVsZXMvbWluaW1hdGNoL2Rpc3QvY29tbW9uanMvdW5lc2NhcGUuanMiLCJ3ZWJwYWNrOi8vQGtvYWxhdWkvZmFzdC1hcmt0c2MvLi4vLi4vbm9kZV9tb2R1bGVzL21pbmltYXRjaC9ub2RlX21vZHVsZXMvYnJhY2UtZXhwYW5zaW9uL2luZGV4LmpzIiwid2VicGFjazovL0Brb2FsYXVpL2Zhc3QtYXJrdHNjL2V4dGVybmFsIG5vZGUtY29tbW9uanMgXCJjaGlsZF9wcm9jZXNzXCIiLCJ3ZWJwYWNrOi8vQGtvYWxhdWkvZmFzdC1hcmt0c2MvZXh0ZXJuYWwgbm9kZS1jb21tb25qcyBcImV2ZW50c1wiIiwid2VicGFjazovL0Brb2FsYXVpL2Zhc3QtYXJrdHNjL2V4dGVybmFsIG5vZGUtY29tbW9uanMgXCJmc1wiIiwid2VicGFjazovL0Brb2FsYXVpL2Zhc3QtYXJrdHNjL2V4dGVybmFsIG5vZGUtY29tbW9uanMgXCJwYXRoXCIiLCJ3ZWJwYWNrOi8vQGtvYWxhdWkvZmFzdC1hcmt0c2MvZXh0ZXJuYWwgbm9kZS1jb21tb25qcyBcInByb2Nlc3NcIiIsIndlYnBhY2s6Ly9Aa29hbGF1aS9mYXN0LWFya3RzYy93ZWJwYWNrL2Jvb3RzdHJhcCIsIndlYnBhY2s6Ly9Aa29hbGF1aS9mYXN0LWFya3RzYy8uL3NyYy9tYWluLnRzIl0sInNvdXJjZXNDb250ZW50IjpbIid1c2Ugc3RyaWN0Jztcbm1vZHVsZS5leHBvcnRzID0gYmFsYW5jZWQ7XG5mdW5jdGlvbiBiYWxhbmNlZChhLCBiLCBzdHIpIHtcbiAgaWYgKGEgaW5zdGFuY2VvZiBSZWdFeHApIGEgPSBtYXliZU1hdGNoKGEsIHN0cik7XG4gIGlmIChiIGluc3RhbmNlb2YgUmVnRXhwKSBiID0gbWF5YmVNYXRjaChiLCBzdHIpO1xuXG4gIHZhciByID0gcmFuZ2UoYSwgYiwgc3RyKTtcblxuICByZXR1cm4gciAmJiB7XG4gICAgc3RhcnQ6IHJbMF0sXG4gICAgZW5kOiByWzFdLFxuICAgIHByZTogc3RyLnNsaWNlKDAsIHJbMF0pLFxuICAgIGJvZHk6IHN0ci5zbGljZShyWzBdICsgYS5sZW5ndGgsIHJbMV0pLFxuICAgIHBvc3Q6IHN0ci5zbGljZShyWzFdICsgYi5sZW5ndGgpXG4gIH07XG59XG5cbmZ1bmN0aW9uIG1heWJlTWF0Y2gocmVnLCBzdHIpIHtcbiAgdmFyIG0gPSBzdHIubWF0Y2gocmVnKTtcbiAgcmV0dXJuIG0gPyBtWzBdIDogbnVsbDtcbn1cblxuYmFsYW5jZWQucmFuZ2UgPSByYW5nZTtcbmZ1bmN0aW9uIHJhbmdlKGEsIGIsIHN0cikge1xuICB2YXIgYmVncywgYmVnLCBsZWZ0LCByaWdodCwgcmVzdWx0O1xuICB2YXIgYWkgPSBzdHIuaW5kZXhPZihhKTtcbiAgdmFyIGJpID0gc3RyLmluZGV4T2YoYiwgYWkgKyAxKTtcbiAgdmFyIGkgPSBhaTtcblxuICBpZiAoYWkgPj0gMCAmJiBiaSA+IDApIHtcbiAgICBpZihhPT09Yikge1xuICAgICAgcmV0dXJuIFthaSwgYmldO1xuICAgIH1cbiAgICBiZWdzID0gW107XG4gICAgbGVmdCA9IHN0ci5sZW5ndGg7XG5cbiAgICB3aGlsZSAoaSA+PSAwICYmICFyZXN1bHQpIHtcbiAgICAgIGlmIChpID09IGFpKSB7XG4gICAgICAgIGJlZ3MucHVzaChpKTtcbiAgICAgICAgYWkgPSBzdHIuaW5kZXhPZihhLCBpICsgMSk7XG4gICAgICB9IGVsc2UgaWYgKGJlZ3MubGVuZ3RoID09IDEpIHtcbiAgICAgICAgcmVzdWx0ID0gWyBiZWdzLnBvcCgpLCBiaSBdO1xuICAgICAgfSBlbHNlIHtcbiAgICAgICAgYmVnID0gYmVncy5wb3AoKTtcbiAgICAgICAgaWYgKGJlZyA8IGxlZnQpIHtcbiAgICAgICAgICBsZWZ0ID0gYmVnO1xuICAgICAgICAgIHJpZ2h0ID0gYmk7XG4gICAgICAgIH1cblxuICAgICAgICBiaSA9IHN0ci5pbmRleE9mKGIsIGkgKyAxKTtcbiAgICAgIH1cblxuICAgICAgaSA9IGFpIDwgYmkgJiYgYWkgPj0gMCA/IGFpIDogYmk7XG4gICAgfVxuXG4gICAgaWYgKGJlZ3MubGVuZ3RoKSB7XG4gICAgICByZXN1bHQgPSBbIGxlZnQsIHJpZ2h0IF07XG4gICAgfVxuICB9XG5cbiAgcmV0dXJuIHJlc3VsdDtcbn1cbiIsImNvbnN0IHsgQXJndW1lbnQgfSA9IHJlcXVpcmUoJy4vbGliL2FyZ3VtZW50LmpzJyk7XG5jb25zdCB7IENvbW1hbmQgfSA9IHJlcXVpcmUoJy4vbGliL2NvbW1hbmQuanMnKTtcbmNvbnN0IHsgQ29tbWFuZGVyRXJyb3IsIEludmFsaWRBcmd1bWVudEVycm9yIH0gPSByZXF1aXJlKCcuL2xpYi9lcnJvci5qcycpO1xuY29uc3QgeyBIZWxwIH0gPSByZXF1aXJlKCcuL2xpYi9oZWxwLmpzJyk7XG5jb25zdCB7IE9wdGlvbiB9ID0gcmVxdWlyZSgnLi9saWIvb3B0aW9uLmpzJyk7XG5cbi8vIEB0cy1jaGVja1xuXG4vKipcbiAqIEV4cG9zZSB0aGUgcm9vdCBjb21tYW5kLlxuICovXG5cbmV4cG9ydHMgPSBtb2R1bGUuZXhwb3J0cyA9IG5ldyBDb21tYW5kKCk7XG5leHBvcnRzLnByb2dyYW0gPSBleHBvcnRzOyAvLyBNb3JlIGV4cGxpY2l0IGFjY2VzcyB0byBnbG9iYWwgY29tbWFuZC5cbi8vIEltcGxpY2l0IGV4cG9ydCBvZiBjcmVhdGVBcmd1bWVudCwgY3JlYXRlQ29tbWFuZCwgYW5kIGNyZWF0ZU9wdGlvbi5cblxuLyoqXG4gKiBFeHBvc2UgY2xhc3Nlc1xuICovXG5cbmV4cG9ydHMuQXJndW1lbnQgPSBBcmd1bWVudDtcbmV4cG9ydHMuQ29tbWFuZCA9IENvbW1hbmQ7XG5leHBvcnRzLkNvbW1hbmRlckVycm9yID0gQ29tbWFuZGVyRXJyb3I7XG5leHBvcnRzLkhlbHAgPSBIZWxwO1xuZXhwb3J0cy5JbnZhbGlkQXJndW1lbnRFcnJvciA9IEludmFsaWRBcmd1bWVudEVycm9yO1xuZXhwb3J0cy5JbnZhbGlkT3B0aW9uQXJndW1lbnRFcnJvciA9IEludmFsaWRBcmd1bWVudEVycm9yOyAvLyBEZXByZWNhdGVkXG5leHBvcnRzLk9wdGlvbiA9IE9wdGlvbjtcbiIsImNvbnN0IHsgSW52YWxpZEFyZ3VtZW50RXJyb3IgfSA9IHJlcXVpcmUoJy4vZXJyb3IuanMnKTtcblxuLy8gQHRzLWNoZWNrXG5cbmNsYXNzIEFyZ3VtZW50IHtcbiAgLyoqXG4gICAqIEluaXRpYWxpemUgYSBuZXcgY29tbWFuZCBhcmd1bWVudCB3aXRoIHRoZSBnaXZlbiBuYW1lIGFuZCBkZXNjcmlwdGlvbi5cbiAgICogVGhlIGRlZmF1bHQgaXMgdGhhdCB0aGUgYXJndW1lbnQgaXMgcmVxdWlyZWQsIGFuZCB5b3UgY2FuIGV4cGxpY2l0bHlcbiAgICogaW5kaWNhdGUgdGhpcyB3aXRoIDw+IGFyb3VuZCB0aGUgbmFtZS4gUHV0IFtdIGFyb3VuZCB0aGUgbmFtZSBmb3IgYW4gb3B0aW9uYWwgYXJndW1lbnQuXG4gICAqXG4gICAqIEBwYXJhbSB7c3RyaW5nfSBuYW1lXG4gICAqIEBwYXJhbSB7c3RyaW5nfSBbZGVzY3JpcHRpb25dXG4gICAqL1xuXG4gIGNvbnN0cnVjdG9yKG5hbWUsIGRlc2NyaXB0aW9uKSB7XG4gICAgdGhpcy5kZXNjcmlwdGlvbiA9IGRlc2NyaXB0aW9uIHx8ICcnO1xuICAgIHRoaXMudmFyaWFkaWMgPSBmYWxzZTtcbiAgICB0aGlzLnBhcnNlQXJnID0gdW5kZWZpbmVkO1xuICAgIHRoaXMuZGVmYXVsdFZhbHVlID0gdW5kZWZpbmVkO1xuICAgIHRoaXMuZGVmYXVsdFZhbHVlRGVzY3JpcHRpb24gPSB1bmRlZmluZWQ7XG4gICAgdGhpcy5hcmdDaG9pY2VzID0gdW5kZWZpbmVkO1xuXG4gICAgc3dpdGNoIChuYW1lWzBdKSB7XG4gICAgICBjYXNlICc8JzogLy8gZS5nLiA8cmVxdWlyZWQ+XG4gICAgICAgIHRoaXMucmVxdWlyZWQgPSB0cnVlO1xuICAgICAgICB0aGlzLl9uYW1lID0gbmFtZS5zbGljZSgxLCAtMSk7XG4gICAgICAgIGJyZWFrO1xuICAgICAgY2FzZSAnWyc6IC8vIGUuZy4gW29wdGlvbmFsXVxuICAgICAgICB0aGlzLnJlcXVpcmVkID0gZmFsc2U7XG4gICAgICAgIHRoaXMuX25hbWUgPSBuYW1lLnNsaWNlKDEsIC0xKTtcbiAgICAgICAgYnJlYWs7XG4gICAgICBkZWZhdWx0OlxuICAgICAgICB0aGlzLnJlcXVpcmVkID0gdHJ1ZTtcbiAgICAgICAgdGhpcy5fbmFtZSA9IG5hbWU7XG4gICAgICAgIGJyZWFrO1xuICAgIH1cblxuICAgIGlmICh0aGlzLl9uYW1lLmxlbmd0aCA+IDMgJiYgdGhpcy5fbmFtZS5zbGljZSgtMykgPT09ICcuLi4nKSB7XG4gICAgICB0aGlzLnZhcmlhZGljID0gdHJ1ZTtcbiAgICAgIHRoaXMuX25hbWUgPSB0aGlzLl9uYW1lLnNsaWNlKDAsIC0zKTtcbiAgICB9XG4gIH1cblxuICAvKipcbiAgICogUmV0dXJuIGFyZ3VtZW50IG5hbWUuXG4gICAqXG4gICAqIEByZXR1cm4ge3N0cmluZ31cbiAgICovXG5cbiAgbmFtZSgpIHtcbiAgICByZXR1cm4gdGhpcy5fbmFtZTtcbiAgfVxuXG4gIC8qKlxuICAgKiBAYXBpIHByaXZhdGVcbiAgICovXG5cbiAgX2NvbmNhdFZhbHVlKHZhbHVlLCBwcmV2aW91cykge1xuICAgIGlmIChwcmV2aW91cyA9PT0gdGhpcy5kZWZhdWx0VmFsdWUgfHwgIUFycmF5LmlzQXJyYXkocHJldmlvdXMpKSB7XG4gICAgICByZXR1cm4gW3ZhbHVlXTtcbiAgICB9XG5cbiAgICByZXR1cm4gcHJldmlvdXMuY29uY2F0KHZhbHVlKTtcbiAgfVxuXG4gIC8qKlxuICAgKiBTZXQgdGhlIGRlZmF1bHQgdmFsdWUsIGFuZCBvcHRpb25hbGx5IHN1cHBseSB0aGUgZGVzY3JpcHRpb24gdG8gYmUgZGlzcGxheWVkIGluIHRoZSBoZWxwLlxuICAgKlxuICAgKiBAcGFyYW0ge2FueX0gdmFsdWVcbiAgICogQHBhcmFtIHtzdHJpbmd9IFtkZXNjcmlwdGlvbl1cbiAgICogQHJldHVybiB7QXJndW1lbnR9XG4gICAqL1xuXG4gIGRlZmF1bHQodmFsdWUsIGRlc2NyaXB0aW9uKSB7XG4gICAgdGhpcy5kZWZhdWx0VmFsdWUgPSB2YWx1ZTtcbiAgICB0aGlzLmRlZmF1bHRWYWx1ZURlc2NyaXB0aW9uID0gZGVzY3JpcHRpb247XG4gICAgcmV0dXJuIHRoaXM7XG4gIH1cblxuICAvKipcbiAgICogU2V0IHRoZSBjdXN0b20gaGFuZGxlciBmb3IgcHJvY2Vzc2luZyBDTEkgY29tbWFuZCBhcmd1bWVudHMgaW50byBhcmd1bWVudCB2YWx1ZXMuXG4gICAqXG4gICAqIEBwYXJhbSB7RnVuY3Rpb259IFtmbl1cbiAgICogQHJldHVybiB7QXJndW1lbnR9XG4gICAqL1xuXG4gIGFyZ1BhcnNlcihmbikge1xuICAgIHRoaXMucGFyc2VBcmcgPSBmbjtcbiAgICByZXR1cm4gdGhpcztcbiAgfVxuXG4gIC8qKlxuICAgKiBPbmx5IGFsbG93IGFyZ3VtZW50IHZhbHVlIHRvIGJlIG9uZSBvZiBjaG9pY2VzLlxuICAgKlxuICAgKiBAcGFyYW0ge3N0cmluZ1tdfSB2YWx1ZXNcbiAgICogQHJldHVybiB7QXJndW1lbnR9XG4gICAqL1xuXG4gIGNob2ljZXModmFsdWVzKSB7XG4gICAgdGhpcy5hcmdDaG9pY2VzID0gdmFsdWVzLnNsaWNlKCk7XG4gICAgdGhpcy5wYXJzZUFyZyA9IChhcmcsIHByZXZpb3VzKSA9PiB7XG4gICAgICBpZiAoIXRoaXMuYXJnQ2hvaWNlcy5pbmNsdWRlcyhhcmcpKSB7XG4gICAgICAgIHRocm93IG5ldyBJbnZhbGlkQXJndW1lbnRFcnJvcihgQWxsb3dlZCBjaG9pY2VzIGFyZSAke3RoaXMuYXJnQ2hvaWNlcy5qb2luKCcsICcpfS5gKTtcbiAgICAgIH1cbiAgICAgIGlmICh0aGlzLnZhcmlhZGljKSB7XG4gICAgICAgIHJldHVybiB0aGlzLl9jb25jYXRWYWx1ZShhcmcsIHByZXZpb3VzKTtcbiAgICAgIH1cbiAgICAgIHJldHVybiBhcmc7XG4gICAgfTtcbiAgICByZXR1cm4gdGhpcztcbiAgfVxuXG4gIC8qKlxuICAgKiBNYWtlIGFyZ3VtZW50IHJlcXVpcmVkLlxuICAgKi9cbiAgYXJnUmVxdWlyZWQoKSB7XG4gICAgdGhpcy5yZXF1aXJlZCA9IHRydWU7XG4gICAgcmV0dXJuIHRoaXM7XG4gIH1cblxuICAvKipcbiAgICogTWFrZSBhcmd1bWVudCBvcHRpb25hbC5cbiAgICovXG4gIGFyZ09wdGlvbmFsKCkge1xuICAgIHRoaXMucmVxdWlyZWQgPSBmYWxzZTtcbiAgICByZXR1cm4gdGhpcztcbiAgfVxufVxuXG4vKipcbiAqIFRha2VzIGFuIGFyZ3VtZW50IGFuZCByZXR1cm5zIGl0cyBodW1hbiByZWFkYWJsZSBlcXVpdmFsZW50IGZvciBoZWxwIHVzYWdlLlxuICpcbiAqIEBwYXJhbSB7QXJndW1lbnR9IGFyZ1xuICogQHJldHVybiB7c3RyaW5nfVxuICogQGFwaSBwcml2YXRlXG4gKi9cblxuZnVuY3Rpb24gaHVtYW5SZWFkYWJsZUFyZ05hbWUoYXJnKSB7XG4gIGNvbnN0IG5hbWVPdXRwdXQgPSBhcmcubmFtZSgpICsgKGFyZy52YXJpYWRpYyA9PT0gdHJ1ZSA/ICcuLi4nIDogJycpO1xuXG4gIHJldHVybiBhcmcucmVxdWlyZWRcbiAgICA/ICc8JyArIG5hbWVPdXRwdXQgKyAnPidcbiAgICA6ICdbJyArIG5hbWVPdXRwdXQgKyAnXSc7XG59XG5cbmV4cG9ydHMuQXJndW1lbnQgPSBBcmd1bWVudDtcbmV4cG9ydHMuaHVtYW5SZWFkYWJsZUFyZ05hbWUgPSBodW1hblJlYWRhYmxlQXJnTmFtZTtcbiIsImNvbnN0IEV2ZW50RW1pdHRlciA9IHJlcXVpcmUoJ2V2ZW50cycpLkV2ZW50RW1pdHRlcjtcbmNvbnN0IGNoaWxkUHJvY2VzcyA9IHJlcXVpcmUoJ2NoaWxkX3Byb2Nlc3MnKTtcbmNvbnN0IHBhdGggPSByZXF1aXJlKCdwYXRoJyk7XG5jb25zdCBmcyA9IHJlcXVpcmUoJ2ZzJyk7XG5jb25zdCBwcm9jZXNzID0gcmVxdWlyZSgncHJvY2VzcycpO1xuXG5jb25zdCB7IEFyZ3VtZW50LCBodW1hblJlYWRhYmxlQXJnTmFtZSB9ID0gcmVxdWlyZSgnLi9hcmd1bWVudC5qcycpO1xuY29uc3QgeyBDb21tYW5kZXJFcnJvciB9ID0gcmVxdWlyZSgnLi9lcnJvci5qcycpO1xuY29uc3QgeyBIZWxwIH0gPSByZXF1aXJlKCcuL2hlbHAuanMnKTtcbmNvbnN0IHsgT3B0aW9uLCBzcGxpdE9wdGlvbkZsYWdzLCBEdWFsT3B0aW9ucyB9ID0gcmVxdWlyZSgnLi9vcHRpb24uanMnKTtcbmNvbnN0IHsgc3VnZ2VzdFNpbWlsYXIgfSA9IHJlcXVpcmUoJy4vc3VnZ2VzdFNpbWlsYXInKTtcblxuLy8gQHRzLWNoZWNrXG5cbmNsYXNzIENvbW1hbmQgZXh0ZW5kcyBFdmVudEVtaXR0ZXIge1xuICAvKipcbiAgICogSW5pdGlhbGl6ZSBhIG5ldyBgQ29tbWFuZGAuXG4gICAqXG4gICAqIEBwYXJhbSB7c3RyaW5nfSBbbmFtZV1cbiAgICovXG5cbiAgY29uc3RydWN0b3IobmFtZSkge1xuICAgIHN1cGVyKCk7XG4gICAgLyoqIEB0eXBlIHtDb21tYW5kW119ICovXG4gICAgdGhpcy5jb21tYW5kcyA9IFtdO1xuICAgIC8qKiBAdHlwZSB7T3B0aW9uW119ICovXG4gICAgdGhpcy5vcHRpb25zID0gW107XG4gICAgdGhpcy5wYXJlbnQgPSBudWxsO1xuICAgIHRoaXMuX2FsbG93VW5rbm93bk9wdGlvbiA9IGZhbHNlO1xuICAgIHRoaXMuX2FsbG93RXhjZXNzQXJndW1lbnRzID0gdHJ1ZTtcbiAgICAvKiogQHR5cGUge0FyZ3VtZW50W119ICovXG4gICAgdGhpcy5fYXJncyA9IFtdO1xuICAgIC8qKiBAdHlwZSB7c3RyaW5nW119ICovXG4gICAgdGhpcy5hcmdzID0gW107IC8vIGNsaSBhcmdzIHdpdGggb3B0aW9ucyByZW1vdmVkXG4gICAgdGhpcy5yYXdBcmdzID0gW107XG4gICAgdGhpcy5wcm9jZXNzZWRBcmdzID0gW107IC8vIGxpa2UgLmFyZ3MgYnV0IGFmdGVyIGN1c3RvbSBwcm9jZXNzaW5nIGFuZCBjb2xsZWN0aW5nIHZhcmlhZGljXG4gICAgdGhpcy5fc2NyaXB0UGF0aCA9IG51bGw7XG4gICAgdGhpcy5fbmFtZSA9IG5hbWUgfHwgJyc7XG4gICAgdGhpcy5fb3B0aW9uVmFsdWVzID0ge307XG4gICAgdGhpcy5fb3B0aW9uVmFsdWVTb3VyY2VzID0ge307IC8vIGRlZmF1bHQsIGVudiwgY2xpIGV0Y1xuICAgIHRoaXMuX3N0b3JlT3B0aW9uc0FzUHJvcGVydGllcyA9IGZhbHNlO1xuICAgIHRoaXMuX2FjdGlvbkhhbmRsZXIgPSBudWxsO1xuICAgIHRoaXMuX2V4ZWN1dGFibGVIYW5kbGVyID0gZmFsc2U7XG4gICAgdGhpcy5fZXhlY3V0YWJsZUZpbGUgPSBudWxsOyAvLyBjdXN0b20gbmFtZSBmb3IgZXhlY3V0YWJsZVxuICAgIHRoaXMuX2V4ZWN1dGFibGVEaXIgPSBudWxsOyAvLyBjdXN0b20gc2VhcmNoIGRpcmVjdG9yeSBmb3Igc3ViY29tbWFuZHNcbiAgICB0aGlzLl9kZWZhdWx0Q29tbWFuZE5hbWUgPSBudWxsO1xuICAgIHRoaXMuX2V4aXRDYWxsYmFjayA9IG51bGw7XG4gICAgdGhpcy5fYWxpYXNlcyA9IFtdO1xuICAgIHRoaXMuX2NvbWJpbmVGbGFnQW5kT3B0aW9uYWxWYWx1ZSA9IHRydWU7XG4gICAgdGhpcy5fZGVzY3JpcHRpb24gPSAnJztcbiAgICB0aGlzLl9zdW1tYXJ5ID0gJyc7XG4gICAgdGhpcy5fYXJnc0Rlc2NyaXB0aW9uID0gdW5kZWZpbmVkOyAvLyBsZWdhY3lcbiAgICB0aGlzLl9lbmFibGVQb3NpdGlvbmFsT3B0aW9ucyA9IGZhbHNlO1xuICAgIHRoaXMuX3Bhc3NUaHJvdWdoT3B0aW9ucyA9IGZhbHNlO1xuICAgIHRoaXMuX2xpZmVDeWNsZUhvb2tzID0ge307IC8vIGEgaGFzaCBvZiBhcnJheXNcbiAgICAvKiogQHR5cGUge2Jvb2xlYW4gfCBzdHJpbmd9ICovXG4gICAgdGhpcy5fc2hvd0hlbHBBZnRlckVycm9yID0gZmFsc2U7XG4gICAgdGhpcy5fc2hvd1N1Z2dlc3Rpb25BZnRlckVycm9yID0gdHJ1ZTtcblxuICAgIC8vIHNlZSAuY29uZmlndXJlT3V0cHV0KCkgZm9yIGRvY3NcbiAgICB0aGlzLl9vdXRwdXRDb25maWd1cmF0aW9uID0ge1xuICAgICAgd3JpdGVPdXQ6IChzdHIpID0+IHByb2Nlc3Muc3Rkb3V0LndyaXRlKHN0ciksXG4gICAgICB3cml0ZUVycjogKHN0cikgPT4gcHJvY2Vzcy5zdGRlcnIud3JpdGUoc3RyKSxcbiAgICAgIGdldE91dEhlbHBXaWR0aDogKCkgPT4gcHJvY2Vzcy5zdGRvdXQuaXNUVFkgPyBwcm9jZXNzLnN0ZG91dC5jb2x1bW5zIDogdW5kZWZpbmVkLFxuICAgICAgZ2V0RXJySGVscFdpZHRoOiAoKSA9PiBwcm9jZXNzLnN0ZGVyci5pc1RUWSA/IHByb2Nlc3Muc3RkZXJyLmNvbHVtbnMgOiB1bmRlZmluZWQsXG4gICAgICBvdXRwdXRFcnJvcjogKHN0ciwgd3JpdGUpID0+IHdyaXRlKHN0cilcbiAgICB9O1xuXG4gICAgdGhpcy5faGlkZGVuID0gZmFsc2U7XG4gICAgdGhpcy5faGFzSGVscE9wdGlvbiA9IHRydWU7XG4gICAgdGhpcy5faGVscEZsYWdzID0gJy1oLCAtLWhlbHAnO1xuICAgIHRoaXMuX2hlbHBEZXNjcmlwdGlvbiA9ICdkaXNwbGF5IGhlbHAgZm9yIGNvbW1hbmQnO1xuICAgIHRoaXMuX2hlbHBTaG9ydEZsYWcgPSAnLWgnO1xuICAgIHRoaXMuX2hlbHBMb25nRmxhZyA9ICctLWhlbHAnO1xuICAgIHRoaXMuX2FkZEltcGxpY2l0SGVscENvbW1hbmQgPSB1bmRlZmluZWQ7IC8vIERlbGliZXJhdGVseSB1bmRlZmluZWQsIG5vdCBkZWNpZGVkIHdoZXRoZXIgdHJ1ZSBvciBmYWxzZVxuICAgIHRoaXMuX2hlbHBDb21tYW5kTmFtZSA9ICdoZWxwJztcbiAgICB0aGlzLl9oZWxwQ29tbWFuZG5hbWVBbmRBcmdzID0gJ2hlbHAgW2NvbW1hbmRdJztcbiAgICB0aGlzLl9oZWxwQ29tbWFuZERlc2NyaXB0aW9uID0gJ2Rpc3BsYXkgaGVscCBmb3IgY29tbWFuZCc7XG4gICAgdGhpcy5faGVscENvbmZpZ3VyYXRpb24gPSB7fTtcbiAgfVxuXG4gIC8qKlxuICAgKiBDb3B5IHNldHRpbmdzIHRoYXQgYXJlIHVzZWZ1bCB0byBoYXZlIGluIGNvbW1vbiBhY3Jvc3Mgcm9vdCBjb21tYW5kIGFuZCBzdWJjb21tYW5kcy5cbiAgICpcbiAgICogKFVzZWQgaW50ZXJuYWxseSB3aGVuIGFkZGluZyBhIGNvbW1hbmQgdXNpbmcgYC5jb21tYW5kKClgIHNvIHN1YmNvbW1hbmRzIGluaGVyaXQgcGFyZW50IHNldHRpbmdzLilcbiAgICpcbiAgICogQHBhcmFtIHtDb21tYW5kfSBzb3VyY2VDb21tYW5kXG4gICAqIEByZXR1cm4ge0NvbW1hbmR9IGB0aGlzYCBjb21tYW5kIGZvciBjaGFpbmluZ1xuICAgKi9cbiAgY29weUluaGVyaXRlZFNldHRpbmdzKHNvdXJjZUNvbW1hbmQpIHtcbiAgICB0aGlzLl9vdXRwdXRDb25maWd1cmF0aW9uID0gc291cmNlQ29tbWFuZC5fb3V0cHV0Q29uZmlndXJhdGlvbjtcbiAgICB0aGlzLl9oYXNIZWxwT3B0aW9uID0gc291cmNlQ29tbWFuZC5faGFzSGVscE9wdGlvbjtcbiAgICB0aGlzLl9oZWxwRmxhZ3MgPSBzb3VyY2VDb21tYW5kLl9oZWxwRmxhZ3M7XG4gICAgdGhpcy5faGVscERlc2NyaXB0aW9uID0gc291cmNlQ29tbWFuZC5faGVscERlc2NyaXB0aW9uO1xuICAgIHRoaXMuX2hlbHBTaG9ydEZsYWcgPSBzb3VyY2VDb21tYW5kLl9oZWxwU2hvcnRGbGFnO1xuICAgIHRoaXMuX2hlbHBMb25nRmxhZyA9IHNvdXJjZUNvbW1hbmQuX2hlbHBMb25nRmxhZztcbiAgICB0aGlzLl9oZWxwQ29tbWFuZE5hbWUgPSBzb3VyY2VDb21tYW5kLl9oZWxwQ29tbWFuZE5hbWU7XG4gICAgdGhpcy5faGVscENvbW1hbmRuYW1lQW5kQXJncyA9IHNvdXJjZUNvbW1hbmQuX2hlbHBDb21tYW5kbmFtZUFuZEFyZ3M7XG4gICAgdGhpcy5faGVscENvbW1hbmREZXNjcmlwdGlvbiA9IHNvdXJjZUNvbW1hbmQuX2hlbHBDb21tYW5kRGVzY3JpcHRpb247XG4gICAgdGhpcy5faGVscENvbmZpZ3VyYXRpb24gPSBzb3VyY2VDb21tYW5kLl9oZWxwQ29uZmlndXJhdGlvbjtcbiAgICB0aGlzLl9leGl0Q2FsbGJhY2sgPSBzb3VyY2VDb21tYW5kLl9leGl0Q2FsbGJhY2s7XG4gICAgdGhpcy5fc3RvcmVPcHRpb25zQXNQcm9wZXJ0aWVzID0gc291cmNlQ29tbWFuZC5fc3RvcmVPcHRpb25zQXNQcm9wZXJ0aWVzO1xuICAgIHRoaXMuX2NvbWJpbmVGbGFnQW5kT3B0aW9uYWxWYWx1ZSA9IHNvdXJjZUNvbW1hbmQuX2NvbWJpbmVGbGFnQW5kT3B0aW9uYWxWYWx1ZTtcbiAgICB0aGlzLl9hbGxvd0V4Y2Vzc0FyZ3VtZW50cyA9IHNvdXJjZUNvbW1hbmQuX2FsbG93RXhjZXNzQXJndW1lbnRzO1xuICAgIHRoaXMuX2VuYWJsZVBvc2l0aW9uYWxPcHRpb25zID0gc291cmNlQ29tbWFuZC5fZW5hYmxlUG9zaXRpb25hbE9wdGlvbnM7XG4gICAgdGhpcy5fc2hvd0hlbHBBZnRlckVycm9yID0gc291cmNlQ29tbWFuZC5fc2hvd0hlbHBBZnRlckVycm9yO1xuICAgIHRoaXMuX3Nob3dTdWdnZXN0aW9uQWZ0ZXJFcnJvciA9IHNvdXJjZUNvbW1hbmQuX3Nob3dTdWdnZXN0aW9uQWZ0ZXJFcnJvcjtcblxuICAgIHJldHVybiB0aGlzO1xuICB9XG5cbiAgLyoqXG4gICAqIERlZmluZSBhIGNvbW1hbmQuXG4gICAqXG4gICAqIFRoZXJlIGFyZSB0d28gc3R5bGVzIG9mIGNvbW1hbmQ6IHBheSBhdHRlbnRpb24gdG8gd2hlcmUgdG8gcHV0IHRoZSBkZXNjcmlwdGlvbi5cbiAgICpcbiAgICogQGV4YW1wbGVcbiAgICogLy8gQ29tbWFuZCBpbXBsZW1lbnRlZCB1c2luZyBhY3Rpb24gaGFuZGxlciAoZGVzY3JpcHRpb24gaXMgc3VwcGxpZWQgc2VwYXJhdGVseSB0byBgLmNvbW1hbmRgKVxuICAgKiBwcm9ncmFtXG4gICAqICAgLmNvbW1hbmQoJ2Nsb25lIDxzb3VyY2U+IFtkZXN0aW5hdGlvbl0nKVxuICAgKiAgIC5kZXNjcmlwdGlvbignY2xvbmUgYSByZXBvc2l0b3J5IGludG8gYSBuZXdseSBjcmVhdGVkIGRpcmVjdG9yeScpXG4gICAqICAgLmFjdGlvbigoc291cmNlLCBkZXN0aW5hdGlvbikgPT4ge1xuICAgKiAgICAgY29uc29sZS5sb2coJ2Nsb25lIGNvbW1hbmQgY2FsbGVkJyk7XG4gICAqICAgfSk7XG4gICAqXG4gICAqIC8vIENvbW1hbmQgaW1wbGVtZW50ZWQgdXNpbmcgc2VwYXJhdGUgZXhlY3V0YWJsZSBmaWxlIChkZXNjcmlwdGlvbiBpcyBzZWNvbmQgcGFyYW1ldGVyIHRvIGAuY29tbWFuZGApXG4gICAqIHByb2dyYW1cbiAgICogICAuY29tbWFuZCgnc3RhcnQgPHNlcnZpY2U+JywgJ3N0YXJ0IG5hbWVkIHNlcnZpY2UnKVxuICAgKiAgIC5jb21tYW5kKCdzdG9wIFtzZXJ2aWNlXScsICdzdG9wIG5hbWVkIHNlcnZpY2UsIG9yIGFsbCBpZiBubyBuYW1lIHN1cHBsaWVkJyk7XG4gICAqXG4gICAqIEBwYXJhbSB7c3RyaW5nfSBuYW1lQW5kQXJncyAtIGNvbW1hbmQgbmFtZSBhbmQgYXJndW1lbnRzLCBhcmdzIGFyZSBgPHJlcXVpcmVkPmAgb3IgYFtvcHRpb25hbF1gIGFuZCBsYXN0IG1heSBhbHNvIGJlIGB2YXJpYWRpYy4uLmBcbiAgICogQHBhcmFtIHtPYmplY3R8c3RyaW5nfSBbYWN0aW9uT3B0c09yRXhlY0Rlc2NdIC0gY29uZmlndXJhdGlvbiBvcHRpb25zIChmb3IgYWN0aW9uKSwgb3IgZGVzY3JpcHRpb24gKGZvciBleGVjdXRhYmxlKVxuICAgKiBAcGFyYW0ge09iamVjdH0gW2V4ZWNPcHRzXSAtIGNvbmZpZ3VyYXRpb24gb3B0aW9ucyAoZm9yIGV4ZWN1dGFibGUpXG4gICAqIEByZXR1cm4ge0NvbW1hbmR9IHJldHVybnMgbmV3IGNvbW1hbmQgZm9yIGFjdGlvbiBoYW5kbGVyLCBvciBgdGhpc2AgZm9yIGV4ZWN1dGFibGUgY29tbWFuZFxuICAgKi9cblxuICBjb21tYW5kKG5hbWVBbmRBcmdzLCBhY3Rpb25PcHRzT3JFeGVjRGVzYywgZXhlY09wdHMpIHtcbiAgICBsZXQgZGVzYyA9IGFjdGlvbk9wdHNPckV4ZWNEZXNjO1xuICAgIGxldCBvcHRzID0gZXhlY09wdHM7XG4gICAgaWYgKHR5cGVvZiBkZXNjID09PSAnb2JqZWN0JyAmJiBkZXNjICE9PSBudWxsKSB7XG4gICAgICBvcHRzID0gZGVzYztcbiAgICAgIGRlc2MgPSBudWxsO1xuICAgIH1cbiAgICBvcHRzID0gb3B0cyB8fCB7fTtcbiAgICBjb25zdCBbLCBuYW1lLCBhcmdzXSA9IG5hbWVBbmRBcmdzLm1hdGNoKC8oW14gXSspICooLiopLyk7XG5cbiAgICBjb25zdCBjbWQgPSB0aGlzLmNyZWF0ZUNvbW1hbmQobmFtZSk7XG4gICAgaWYgKGRlc2MpIHtcbiAgICAgIGNtZC5kZXNjcmlwdGlvbihkZXNjKTtcbiAgICAgIGNtZC5fZXhlY3V0YWJsZUhhbmRsZXIgPSB0cnVlO1xuICAgIH1cbiAgICBpZiAob3B0cy5pc0RlZmF1bHQpIHRoaXMuX2RlZmF1bHRDb21tYW5kTmFtZSA9IGNtZC5fbmFtZTtcbiAgICBjbWQuX2hpZGRlbiA9ICEhKG9wdHMubm9IZWxwIHx8IG9wdHMuaGlkZGVuKTsgLy8gbm9IZWxwIGlzIGRlcHJlY2F0ZWQgb2xkIG5hbWUgZm9yIGhpZGRlblxuICAgIGNtZC5fZXhlY3V0YWJsZUZpbGUgPSBvcHRzLmV4ZWN1dGFibGVGaWxlIHx8IG51bGw7IC8vIEN1c3RvbSBuYW1lIGZvciBleGVjdXRhYmxlIGZpbGUsIHNldCBtaXNzaW5nIHRvIG51bGwgdG8gbWF0Y2ggY29uc3RydWN0b3JcbiAgICBpZiAoYXJncykgY21kLmFyZ3VtZW50cyhhcmdzKTtcbiAgICB0aGlzLmNvbW1hbmRzLnB1c2goY21kKTtcbiAgICBjbWQucGFyZW50ID0gdGhpcztcbiAgICBjbWQuY29weUluaGVyaXRlZFNldHRpbmdzKHRoaXMpO1xuXG4gICAgaWYgKGRlc2MpIHJldHVybiB0aGlzO1xuICAgIHJldHVybiBjbWQ7XG4gIH1cblxuICAvKipcbiAgICogRmFjdG9yeSByb3V0aW5lIHRvIGNyZWF0ZSBhIG5ldyB1bmF0dGFjaGVkIGNvbW1hbmQuXG4gICAqXG4gICAqIFNlZSAuY29tbWFuZCgpIGZvciBjcmVhdGluZyBhbiBhdHRhY2hlZCBzdWJjb21tYW5kLCB3aGljaCB1c2VzIHRoaXMgcm91dGluZSB0b1xuICAgKiBjcmVhdGUgdGhlIGNvbW1hbmQuIFlvdSBjYW4gb3ZlcnJpZGUgY3JlYXRlQ29tbWFuZCB0byBjdXN0b21pc2Ugc3ViY29tbWFuZHMuXG4gICAqXG4gICAqIEBwYXJhbSB7c3RyaW5nfSBbbmFtZV1cbiAgICogQHJldHVybiB7Q29tbWFuZH0gbmV3IGNvbW1hbmRcbiAgICovXG5cbiAgY3JlYXRlQ29tbWFuZChuYW1lKSB7XG4gICAgcmV0dXJuIG5ldyBDb21tYW5kKG5hbWUpO1xuICB9XG5cbiAgLyoqXG4gICAqIFlvdSBjYW4gY3VzdG9taXNlIHRoZSBoZWxwIHdpdGggYSBzdWJjbGFzcyBvZiBIZWxwIGJ5IG92ZXJyaWRpbmcgY3JlYXRlSGVscCxcbiAgICogb3IgYnkgb3ZlcnJpZGluZyBIZWxwIHByb3BlcnRpZXMgdXNpbmcgY29uZmlndXJlSGVscCgpLlxuICAgKlxuICAgKiBAcmV0dXJuIHtIZWxwfVxuICAgKi9cblxuICBjcmVhdGVIZWxwKCkge1xuICAgIHJldHVybiBPYmplY3QuYXNzaWduKG5ldyBIZWxwKCksIHRoaXMuY29uZmlndXJlSGVscCgpKTtcbiAgfVxuXG4gIC8qKlxuICAgKiBZb3UgY2FuIGN1c3RvbWlzZSB0aGUgaGVscCBieSBvdmVycmlkaW5nIEhlbHAgcHJvcGVydGllcyB1c2luZyBjb25maWd1cmVIZWxwKCksXG4gICAqIG9yIHdpdGggYSBzdWJjbGFzcyBvZiBIZWxwIGJ5IG92ZXJyaWRpbmcgY3JlYXRlSGVscCgpLlxuICAgKlxuICAgKiBAcGFyYW0ge09iamVjdH0gW2NvbmZpZ3VyYXRpb25dIC0gY29uZmlndXJhdGlvbiBvcHRpb25zXG4gICAqIEByZXR1cm4ge0NvbW1hbmR8T2JqZWN0fSBgdGhpc2AgY29tbWFuZCBmb3IgY2hhaW5pbmcsIG9yIHN0b3JlZCBjb25maWd1cmF0aW9uXG4gICAqL1xuXG4gIGNvbmZpZ3VyZUhlbHAoY29uZmlndXJhdGlvbikge1xuICAgIGlmIChjb25maWd1cmF0aW9uID09PSB1bmRlZmluZWQpIHJldHVybiB0aGlzLl9oZWxwQ29uZmlndXJhdGlvbjtcblxuICAgIHRoaXMuX2hlbHBDb25maWd1cmF0aW9uID0gY29uZmlndXJhdGlvbjtcbiAgICByZXR1cm4gdGhpcztcbiAgfVxuXG4gIC8qKlxuICAgKiBUaGUgZGVmYXVsdCBvdXRwdXQgZ29lcyB0byBzdGRvdXQgYW5kIHN0ZGVyci4gWW91IGNhbiBjdXN0b21pc2UgdGhpcyBmb3Igc3BlY2lhbFxuICAgKiBhcHBsaWNhdGlvbnMuIFlvdSBjYW4gYWxzbyBjdXN0b21pc2UgdGhlIGRpc3BsYXkgb2YgZXJyb3JzIGJ5IG92ZXJyaWRpbmcgb3V0cHV0RXJyb3IuXG4gICAqXG4gICAqIFRoZSBjb25maWd1cmF0aW9uIHByb3BlcnRpZXMgYXJlIGFsbCBmdW5jdGlvbnM6XG4gICAqXG4gICAqICAgICAvLyBmdW5jdGlvbnMgdG8gY2hhbmdlIHdoZXJlIGJlaW5nIHdyaXR0ZW4sIHN0ZG91dCBhbmQgc3RkZXJyXG4gICAqICAgICB3cml0ZU91dChzdHIpXG4gICAqICAgICB3cml0ZUVycihzdHIpXG4gICAqICAgICAvLyBtYXRjaGluZyBmdW5jdGlvbnMgdG8gc3BlY2lmeSB3aWR0aCBmb3Igd3JhcHBpbmcgaGVscFxuICAgKiAgICAgZ2V0T3V0SGVscFdpZHRoKClcbiAgICogICAgIGdldEVyckhlbHBXaWR0aCgpXG4gICAqICAgICAvLyBmdW5jdGlvbnMgYmFzZWQgb24gd2hhdCBpcyBiZWluZyB3cml0dGVuIG91dFxuICAgKiAgICAgb3V0cHV0RXJyb3Ioc3RyLCB3cml0ZSkgLy8gdXNlZCBmb3IgZGlzcGxheWluZyBlcnJvcnMsIGFuZCBub3QgdXNlZCBmb3IgZGlzcGxheWluZyBoZWxwXG4gICAqXG4gICAqIEBwYXJhbSB7T2JqZWN0fSBbY29uZmlndXJhdGlvbl0gLSBjb25maWd1cmF0aW9uIG9wdGlvbnNcbiAgICogQHJldHVybiB7Q29tbWFuZHxPYmplY3R9IGB0aGlzYCBjb21tYW5kIGZvciBjaGFpbmluZywgb3Igc3RvcmVkIGNvbmZpZ3VyYXRpb25cbiAgICovXG5cbiAgY29uZmlndXJlT3V0cHV0KGNvbmZpZ3VyYXRpb24pIHtcbiAgICBpZiAoY29uZmlndXJhdGlvbiA9PT0gdW5kZWZpbmVkKSByZXR1cm4gdGhpcy5fb3V0cHV0Q29uZmlndXJhdGlvbjtcblxuICAgIE9iamVjdC5hc3NpZ24odGhpcy5fb3V0cHV0Q29uZmlndXJhdGlvbiwgY29uZmlndXJhdGlvbik7XG4gICAgcmV0dXJuIHRoaXM7XG4gIH1cblxuICAvKipcbiAgICogRGlzcGxheSB0aGUgaGVscCBvciBhIGN1c3RvbSBtZXNzYWdlIGFmdGVyIGFuIGVycm9yIG9jY3Vycy5cbiAgICpcbiAgICogQHBhcmFtIHtib29sZWFufHN0cmluZ30gW2Rpc3BsYXlIZWxwXVxuICAgKiBAcmV0dXJuIHtDb21tYW5kfSBgdGhpc2AgY29tbWFuZCBmb3IgY2hhaW5pbmdcbiAgICovXG4gIHNob3dIZWxwQWZ0ZXJFcnJvcihkaXNwbGF5SGVscCA9IHRydWUpIHtcbiAgICBpZiAodHlwZW9mIGRpc3BsYXlIZWxwICE9PSAnc3RyaW5nJykgZGlzcGxheUhlbHAgPSAhIWRpc3BsYXlIZWxwO1xuICAgIHRoaXMuX3Nob3dIZWxwQWZ0ZXJFcnJvciA9IGRpc3BsYXlIZWxwO1xuICAgIHJldHVybiB0aGlzO1xuICB9XG5cbiAgLyoqXG4gICAqIERpc3BsYXkgc3VnZ2VzdGlvbiBvZiBzaW1pbGFyIGNvbW1hbmRzIGZvciB1bmtub3duIGNvbW1hbmRzLCBvciBvcHRpb25zIGZvciB1bmtub3duIG9wdGlvbnMuXG4gICAqXG4gICAqIEBwYXJhbSB7Ym9vbGVhbn0gW2Rpc3BsYXlTdWdnZXN0aW9uXVxuICAgKiBAcmV0dXJuIHtDb21tYW5kfSBgdGhpc2AgY29tbWFuZCBmb3IgY2hhaW5pbmdcbiAgICovXG4gIHNob3dTdWdnZXN0aW9uQWZ0ZXJFcnJvcihkaXNwbGF5U3VnZ2VzdGlvbiA9IHRydWUpIHtcbiAgICB0aGlzLl9zaG93U3VnZ2VzdGlvbkFmdGVyRXJyb3IgPSAhIWRpc3BsYXlTdWdnZXN0aW9uO1xuICAgIHJldHVybiB0aGlzO1xuICB9XG5cbiAgLyoqXG4gICAqIEFkZCBhIHByZXBhcmVkIHN1YmNvbW1hbmQuXG4gICAqXG4gICAqIFNlZSAuY29tbWFuZCgpIGZvciBjcmVhdGluZyBhbiBhdHRhY2hlZCBzdWJjb21tYW5kIHdoaWNoIGluaGVyaXRzIHNldHRpbmdzIGZyb20gaXRzIHBhcmVudC5cbiAgICpcbiAgICogQHBhcmFtIHtDb21tYW5kfSBjbWQgLSBuZXcgc3ViY29tbWFuZFxuICAgKiBAcGFyYW0ge09iamVjdH0gW29wdHNdIC0gY29uZmlndXJhdGlvbiBvcHRpb25zXG4gICAqIEByZXR1cm4ge0NvbW1hbmR9IGB0aGlzYCBjb21tYW5kIGZvciBjaGFpbmluZ1xuICAgKi9cblxuICBhZGRDb21tYW5kKGNtZCwgb3B0cykge1xuICAgIGlmICghY21kLl9uYW1lKSB7XG4gICAgICB0aHJvdyBuZXcgRXJyb3IoYENvbW1hbmQgcGFzc2VkIHRvIC5hZGRDb21tYW5kKCkgbXVzdCBoYXZlIGEgbmFtZVxuLSBzcGVjaWZ5IHRoZSBuYW1lIGluIENvbW1hbmQgY29uc3RydWN0b3Igb3IgdXNpbmcgLm5hbWUoKWApO1xuICAgIH1cblxuICAgIG9wdHMgPSBvcHRzIHx8IHt9O1xuICAgIGlmIChvcHRzLmlzRGVmYXVsdCkgdGhpcy5fZGVmYXVsdENvbW1hbmROYW1lID0gY21kLl9uYW1lO1xuICAgIGlmIChvcHRzLm5vSGVscCB8fCBvcHRzLmhpZGRlbikgY21kLl9oaWRkZW4gPSB0cnVlOyAvLyBtb2RpZnlpbmcgcGFzc2VkIGNvbW1hbmQgZHVlIHRvIGV4aXN0aW5nIGltcGxlbWVudGF0aW9uXG5cbiAgICB0aGlzLmNvbW1hbmRzLnB1c2goY21kKTtcbiAgICBjbWQucGFyZW50ID0gdGhpcztcbiAgICByZXR1cm4gdGhpcztcbiAgfVxuXG4gIC8qKlxuICAgKiBGYWN0b3J5IHJvdXRpbmUgdG8gY3JlYXRlIGEgbmV3IHVuYXR0YWNoZWQgYXJndW1lbnQuXG4gICAqXG4gICAqIFNlZSAuYXJndW1lbnQoKSBmb3IgY3JlYXRpbmcgYW4gYXR0YWNoZWQgYXJndW1lbnQsIHdoaWNoIHVzZXMgdGhpcyByb3V0aW5lIHRvXG4gICAqIGNyZWF0ZSB0aGUgYXJndW1lbnQuIFlvdSBjYW4gb3ZlcnJpZGUgY3JlYXRlQXJndW1lbnQgdG8gcmV0dXJuIGEgY3VzdG9tIGFyZ3VtZW50LlxuICAgKlxuICAgKiBAcGFyYW0ge3N0cmluZ30gbmFtZVxuICAgKiBAcGFyYW0ge3N0cmluZ30gW2Rlc2NyaXB0aW9uXVxuICAgKiBAcmV0dXJuIHtBcmd1bWVudH0gbmV3IGFyZ3VtZW50XG4gICAqL1xuXG4gIGNyZWF0ZUFyZ3VtZW50KG5hbWUsIGRlc2NyaXB0aW9uKSB7XG4gICAgcmV0dXJuIG5ldyBBcmd1bWVudChuYW1lLCBkZXNjcmlwdGlvbik7XG4gIH1cblxuICAvKipcbiAgICogRGVmaW5lIGFyZ3VtZW50IHN5bnRheCBmb3IgY29tbWFuZC5cbiAgICpcbiAgICogVGhlIGRlZmF1bHQgaXMgdGhhdCB0aGUgYXJndW1lbnQgaXMgcmVxdWlyZWQsIGFuZCB5b3UgY2FuIGV4cGxpY2l0bHlcbiAgICogaW5kaWNhdGUgdGhpcyB3aXRoIDw+IGFyb3VuZCB0aGUgbmFtZS4gUHV0IFtdIGFyb3VuZCB0aGUgbmFtZSBmb3IgYW4gb3B0aW9uYWwgYXJndW1lbnQuXG4gICAqXG4gICAqIEBleGFtcGxlXG4gICAqIHByb2dyYW0uYXJndW1lbnQoJzxpbnB1dC1maWxlPicpO1xuICAgKiBwcm9ncmFtLmFyZ3VtZW50KCdbb3V0cHV0LWZpbGVdJyk7XG4gICAqXG4gICAqIEBwYXJhbSB7c3RyaW5nfSBuYW1lXG4gICAqIEBwYXJhbSB7c3RyaW5nfSBbZGVzY3JpcHRpb25dXG4gICAqIEBwYXJhbSB7RnVuY3Rpb258Kn0gW2ZuXSAtIGN1c3RvbSBhcmd1bWVudCBwcm9jZXNzaW5nIGZ1bmN0aW9uXG4gICAqIEBwYXJhbSB7Kn0gW2RlZmF1bHRWYWx1ZV1cbiAgICogQHJldHVybiB7Q29tbWFuZH0gYHRoaXNgIGNvbW1hbmQgZm9yIGNoYWluaW5nXG4gICAqL1xuICBhcmd1bWVudChuYW1lLCBkZXNjcmlwdGlvbiwgZm4sIGRlZmF1bHRWYWx1ZSkge1xuICAgIGNvbnN0IGFyZ3VtZW50ID0gdGhpcy5jcmVhdGVBcmd1bWVudChuYW1lLCBkZXNjcmlwdGlvbik7XG4gICAgaWYgKHR5cGVvZiBmbiA9PT0gJ2Z1bmN0aW9uJykge1xuICAgICAgYXJndW1lbnQuZGVmYXVsdChkZWZhdWx0VmFsdWUpLmFyZ1BhcnNlcihmbik7XG4gICAgfSBlbHNlIHtcbiAgICAgIGFyZ3VtZW50LmRlZmF1bHQoZm4pO1xuICAgIH1cbiAgICB0aGlzLmFkZEFyZ3VtZW50KGFyZ3VtZW50KTtcbiAgICByZXR1cm4gdGhpcztcbiAgfVxuXG4gIC8qKlxuICAgKiBEZWZpbmUgYXJndW1lbnQgc3ludGF4IGZvciBjb21tYW5kLCBhZGRpbmcgbXVsdGlwbGUgYXQgb25jZSAod2l0aG91dCBkZXNjcmlwdGlvbnMpLlxuICAgKlxuICAgKiBTZWUgYWxzbyAuYXJndW1lbnQoKS5cbiAgICpcbiAgICogQGV4YW1wbGVcbiAgICogcHJvZ3JhbS5hcmd1bWVudHMoJzxjbWQ+IFtlbnZdJyk7XG4gICAqXG4gICAqIEBwYXJhbSB7c3RyaW5nfSBuYW1lc1xuICAgKiBAcmV0dXJuIHtDb21tYW5kfSBgdGhpc2AgY29tbWFuZCBmb3IgY2hhaW5pbmdcbiAgICovXG5cbiAgYXJndW1lbnRzKG5hbWVzKSB7XG4gICAgbmFtZXMuc3BsaXQoLyArLykuZm9yRWFjaCgoZGV0YWlsKSA9PiB7XG4gICAgICB0aGlzLmFyZ3VtZW50KGRldGFpbCk7XG4gICAgfSk7XG4gICAgcmV0dXJuIHRoaXM7XG4gIH1cblxuICAvKipcbiAgICogRGVmaW5lIGFyZ3VtZW50IHN5bnRheCBmb3IgY29tbWFuZCwgYWRkaW5nIGEgcHJlcGFyZWQgYXJndW1lbnQuXG4gICAqXG4gICAqIEBwYXJhbSB7QXJndW1lbnR9IGFyZ3VtZW50XG4gICAqIEByZXR1cm4ge0NvbW1hbmR9IGB0aGlzYCBjb21tYW5kIGZvciBjaGFpbmluZ1xuICAgKi9cbiAgYWRkQXJndW1lbnQoYXJndW1lbnQpIHtcbiAgICBjb25zdCBwcmV2aW91c0FyZ3VtZW50ID0gdGhpcy5fYXJncy5zbGljZSgtMSlbMF07XG4gICAgaWYgKHByZXZpb3VzQXJndW1lbnQgJiYgcHJldmlvdXNBcmd1bWVudC52YXJpYWRpYykge1xuICAgICAgdGhyb3cgbmV3IEVycm9yKGBvbmx5IHRoZSBsYXN0IGFyZ3VtZW50IGNhbiBiZSB2YXJpYWRpYyAnJHtwcmV2aW91c0FyZ3VtZW50Lm5hbWUoKX0nYCk7XG4gICAgfVxuICAgIGlmIChhcmd1bWVudC5yZXF1aXJlZCAmJiBhcmd1bWVudC5kZWZhdWx0VmFsdWUgIT09IHVuZGVmaW5lZCAmJiBhcmd1bWVudC5wYXJzZUFyZyA9PT0gdW5kZWZpbmVkKSB7XG4gICAgICB0aHJvdyBuZXcgRXJyb3IoYGEgZGVmYXVsdCB2YWx1ZSBmb3IgYSByZXF1aXJlZCBhcmd1bWVudCBpcyBuZXZlciB1c2VkOiAnJHthcmd1bWVudC5uYW1lKCl9J2ApO1xuICAgIH1cbiAgICB0aGlzLl9hcmdzLnB1c2goYXJndW1lbnQpO1xuICAgIHJldHVybiB0aGlzO1xuICB9XG5cbiAgLyoqXG4gICAqIE92ZXJyaWRlIGRlZmF1bHQgZGVjaXNpb24gd2hldGhlciB0byBhZGQgaW1wbGljaXQgaGVscCBjb21tYW5kLlxuICAgKlxuICAgKiAgICBhZGRIZWxwQ29tbWFuZCgpIC8vIGZvcmNlIG9uXG4gICAqICAgIGFkZEhlbHBDb21tYW5kKGZhbHNlKTsgLy8gZm9yY2Ugb2ZmXG4gICAqICAgIGFkZEhlbHBDb21tYW5kKCdoZWxwIFtjbWRdJywgJ2Rpc3BsYXkgaGVscCBmb3IgW2NtZF0nKTsgLy8gZm9yY2Ugb24gd2l0aCBjdXN0b20gZGV0YWlsc1xuICAgKlxuICAgKiBAcmV0dXJuIHtDb21tYW5kfSBgdGhpc2AgY29tbWFuZCBmb3IgY2hhaW5pbmdcbiAgICovXG5cbiAgYWRkSGVscENvbW1hbmQoZW5hYmxlT3JOYW1lQW5kQXJncywgZGVzY3JpcHRpb24pIHtcbiAgICBpZiAoZW5hYmxlT3JOYW1lQW5kQXJncyA9PT0gZmFsc2UpIHtcbiAgICAgIHRoaXMuX2FkZEltcGxpY2l0SGVscENvbW1hbmQgPSBmYWxzZTtcbiAgICB9IGVsc2Uge1xuICAgICAgdGhpcy5fYWRkSW1wbGljaXRIZWxwQ29tbWFuZCA9IHRydWU7XG4gICAgICBpZiAodHlwZW9mIGVuYWJsZU9yTmFtZUFuZEFyZ3MgPT09ICdzdHJpbmcnKSB7XG4gICAgICAgIHRoaXMuX2hlbHBDb21tYW5kTmFtZSA9IGVuYWJsZU9yTmFtZUFuZEFyZ3Muc3BsaXQoJyAnKVswXTtcbiAgICAgICAgdGhpcy5faGVscENvbW1hbmRuYW1lQW5kQXJncyA9IGVuYWJsZU9yTmFtZUFuZEFyZ3M7XG4gICAgICB9XG4gICAgICB0aGlzLl9oZWxwQ29tbWFuZERlc2NyaXB0aW9uID0gZGVzY3JpcHRpb24gfHwgdGhpcy5faGVscENvbW1hbmREZXNjcmlwdGlvbjtcbiAgICB9XG4gICAgcmV0dXJuIHRoaXM7XG4gIH1cblxuICAvKipcbiAgICogQHJldHVybiB7Ym9vbGVhbn1cbiAgICogQGFwaSBwcml2YXRlXG4gICAqL1xuXG4gIF9oYXNJbXBsaWNpdEhlbHBDb21tYW5kKCkge1xuICAgIGlmICh0aGlzLl9hZGRJbXBsaWNpdEhlbHBDb21tYW5kID09PSB1bmRlZmluZWQpIHtcbiAgICAgIHJldHVybiB0aGlzLmNvbW1hbmRzLmxlbmd0aCAmJiAhdGhpcy5fYWN0aW9uSGFuZGxlciAmJiAhdGhpcy5fZmluZENvbW1hbmQoJ2hlbHAnKTtcbiAgICB9XG4gICAgcmV0dXJuIHRoaXMuX2FkZEltcGxpY2l0SGVscENvbW1hbmQ7XG4gIH1cblxuICAvKipcbiAgICogQWRkIGhvb2sgZm9yIGxpZmUgY3ljbGUgZXZlbnQuXG4gICAqXG4gICAqIEBwYXJhbSB7c3RyaW5nfSBldmVudFxuICAgKiBAcGFyYW0ge0Z1bmN0aW9ufSBsaXN0ZW5lclxuICAgKiBAcmV0dXJuIHtDb21tYW5kfSBgdGhpc2AgY29tbWFuZCBmb3IgY2hhaW5pbmdcbiAgICovXG5cbiAgaG9vayhldmVudCwgbGlzdGVuZXIpIHtcbiAgICBjb25zdCBhbGxvd2VkVmFsdWVzID0gWydwcmVTdWJjb21tYW5kJywgJ3ByZUFjdGlvbicsICdwb3N0QWN0aW9uJ107XG4gICAgaWYgKCFhbGxvd2VkVmFsdWVzLmluY2x1ZGVzKGV2ZW50KSkge1xuICAgICAgdGhyb3cgbmV3IEVycm9yKGBVbmV4cGVjdGVkIHZhbHVlIGZvciBldmVudCBwYXNzZWQgdG8gaG9vayA6ICcke2V2ZW50fScuXG5FeHBlY3Rpbmcgb25lIG9mICcke2FsbG93ZWRWYWx1ZXMuam9pbihcIicsICdcIil9J2ApO1xuICAgIH1cbiAgICBpZiAodGhpcy5fbGlmZUN5Y2xlSG9va3NbZXZlbnRdKSB7XG4gICAgICB0aGlzLl9saWZlQ3ljbGVIb29rc1tldmVudF0ucHVzaChsaXN0ZW5lcik7XG4gICAgfSBlbHNlIHtcbiAgICAgIHRoaXMuX2xpZmVDeWNsZUhvb2tzW2V2ZW50XSA9IFtsaXN0ZW5lcl07XG4gICAgfVxuICAgIHJldHVybiB0aGlzO1xuICB9XG5cbiAgLyoqXG4gICAqIFJlZ2lzdGVyIGNhbGxiYWNrIHRvIHVzZSBhcyByZXBsYWNlbWVudCBmb3IgY2FsbGluZyBwcm9jZXNzLmV4aXQuXG4gICAqXG4gICAqIEBwYXJhbSB7RnVuY3Rpb259IFtmbl0gb3B0aW9uYWwgY2FsbGJhY2sgd2hpY2ggd2lsbCBiZSBwYXNzZWQgYSBDb21tYW5kZXJFcnJvciwgZGVmYXVsdHMgdG8gdGhyb3dpbmdcbiAgICogQHJldHVybiB7Q29tbWFuZH0gYHRoaXNgIGNvbW1hbmQgZm9yIGNoYWluaW5nXG4gICAqL1xuXG4gIGV4aXRPdmVycmlkZShmbikge1xuICAgIGlmIChmbikge1xuICAgICAgdGhpcy5fZXhpdENhbGxiYWNrID0gZm47XG4gICAgfSBlbHNlIHtcbiAgICAgIHRoaXMuX2V4aXRDYWxsYmFjayA9IChlcnIpID0+IHtcbiAgICAgICAgaWYgKGVyci5jb2RlICE9PSAnY29tbWFuZGVyLmV4ZWN1dGVTdWJDb21tYW5kQXN5bmMnKSB7XG4gICAgICAgICAgdGhyb3cgZXJyO1xuICAgICAgICB9IGVsc2Uge1xuICAgICAgICAgIC8vIEFzeW5jIGNhbGxiYWNrIGZyb20gc3Bhd24gZXZlbnRzLCBub3QgdXNlZnVsIHRvIHRocm93LlxuICAgICAgICB9XG4gICAgICB9O1xuICAgIH1cbiAgICByZXR1cm4gdGhpcztcbiAgfVxuXG4gIC8qKlxuICAgKiBDYWxsIHByb2Nlc3MuZXhpdCwgYW5kIF9leGl0Q2FsbGJhY2sgaWYgZGVmaW5lZC5cbiAgICpcbiAgICogQHBhcmFtIHtudW1iZXJ9IGV4aXRDb2RlIGV4aXQgY29kZSBmb3IgdXNpbmcgd2l0aCBwcm9jZXNzLmV4aXRcbiAgICogQHBhcmFtIHtzdHJpbmd9IGNvZGUgYW4gaWQgc3RyaW5nIHJlcHJlc2VudGluZyB0aGUgZXJyb3JcbiAgICogQHBhcmFtIHtzdHJpbmd9IG1lc3NhZ2UgaHVtYW4tcmVhZGFibGUgZGVzY3JpcHRpb24gb2YgdGhlIGVycm9yXG4gICAqIEByZXR1cm4gbmV2ZXJcbiAgICogQGFwaSBwcml2YXRlXG4gICAqL1xuXG4gIF9leGl0KGV4aXRDb2RlLCBjb2RlLCBtZXNzYWdlKSB7XG4gICAgaWYgKHRoaXMuX2V4aXRDYWxsYmFjaykge1xuICAgICAgdGhpcy5fZXhpdENhbGxiYWNrKG5ldyBDb21tYW5kZXJFcnJvcihleGl0Q29kZSwgY29kZSwgbWVzc2FnZSkpO1xuICAgICAgLy8gRXhwZWN0aW5nIHRoaXMgbGluZSBpcyBub3QgcmVhY2hlZC5cbiAgICB9XG4gICAgcHJvY2Vzcy5leGl0KGV4aXRDb2RlKTtcbiAgfVxuXG4gIC8qKlxuICAgKiBSZWdpc3RlciBjYWxsYmFjayBgZm5gIGZvciB0aGUgY29tbWFuZC5cbiAgICpcbiAgICogQGV4YW1wbGVcbiAgICogcHJvZ3JhbVxuICAgKiAgIC5jb21tYW5kKCdzZXJ2ZScpXG4gICAqICAgLmRlc2NyaXB0aW9uKCdzdGFydCBzZXJ2aWNlJylcbiAgICogICAuYWN0aW9uKGZ1bmN0aW9uKCkge1xuICAgKiAgICAgIC8vIGRvIHdvcmsgaGVyZVxuICAgKiAgIH0pO1xuICAgKlxuICAgKiBAcGFyYW0ge0Z1bmN0aW9ufSBmblxuICAgKiBAcmV0dXJuIHtDb21tYW5kfSBgdGhpc2AgY29tbWFuZCBmb3IgY2hhaW5pbmdcbiAgICovXG5cbiAgYWN0aW9uKGZuKSB7XG4gICAgY29uc3QgbGlzdGVuZXIgPSAoYXJncykgPT4ge1xuICAgICAgLy8gVGhlIC5hY3Rpb24gY2FsbGJhY2sgdGFrZXMgYW4gZXh0cmEgcGFyYW1ldGVyIHdoaWNoIGlzIHRoZSBjb21tYW5kIG9yIG9wdGlvbnMuXG4gICAgICBjb25zdCBleHBlY3RlZEFyZ3NDb3VudCA9IHRoaXMuX2FyZ3MubGVuZ3RoO1xuICAgICAgY29uc3QgYWN0aW9uQXJncyA9IGFyZ3Muc2xpY2UoMCwgZXhwZWN0ZWRBcmdzQ291bnQpO1xuICAgICAgaWYgKHRoaXMuX3N0b3JlT3B0aW9uc0FzUHJvcGVydGllcykge1xuICAgICAgICBhY3Rpb25BcmdzW2V4cGVjdGVkQXJnc0NvdW50XSA9IHRoaXM7IC8vIGJhY2t3YXJkcyBjb21wYXRpYmxlIFwib3B0aW9uc1wiXG4gICAgICB9IGVsc2Uge1xuICAgICAgICBhY3Rpb25BcmdzW2V4cGVjdGVkQXJnc0NvdW50XSA9IHRoaXMub3B0cygpO1xuICAgICAgfVxuICAgICAgYWN0aW9uQXJncy5wdXNoKHRoaXMpO1xuXG4gICAgICByZXR1cm4gZm4uYXBwbHkodGhpcywgYWN0aW9uQXJncyk7XG4gICAgfTtcbiAgICB0aGlzLl9hY3Rpb25IYW5kbGVyID0gbGlzdGVuZXI7XG4gICAgcmV0dXJuIHRoaXM7XG4gIH1cblxuICAvKipcbiAgICogRmFjdG9yeSByb3V0aW5lIHRvIGNyZWF0ZSBhIG5ldyB1bmF0dGFjaGVkIG9wdGlvbi5cbiAgICpcbiAgICogU2VlIC5vcHRpb24oKSBmb3IgY3JlYXRpbmcgYW4gYXR0YWNoZWQgb3B0aW9uLCB3aGljaCB1c2VzIHRoaXMgcm91dGluZSB0b1xuICAgKiBjcmVhdGUgdGhlIG9wdGlvbi4gWW91IGNhbiBvdmVycmlkZSBjcmVhdGVPcHRpb24gdG8gcmV0dXJuIGEgY3VzdG9tIG9wdGlvbi5cbiAgICpcbiAgICogQHBhcmFtIHtzdHJpbmd9IGZsYWdzXG4gICAqIEBwYXJhbSB7c3RyaW5nfSBbZGVzY3JpcHRpb25dXG4gICAqIEByZXR1cm4ge09wdGlvbn0gbmV3IG9wdGlvblxuICAgKi9cblxuICBjcmVhdGVPcHRpb24oZmxhZ3MsIGRlc2NyaXB0aW9uKSB7XG4gICAgcmV0dXJuIG5ldyBPcHRpb24oZmxhZ3MsIGRlc2NyaXB0aW9uKTtcbiAgfVxuXG4gIC8qKlxuICAgKiBBZGQgYW4gb3B0aW9uLlxuICAgKlxuICAgKiBAcGFyYW0ge09wdGlvbn0gb3B0aW9uXG4gICAqIEByZXR1cm4ge0NvbW1hbmR9IGB0aGlzYCBjb21tYW5kIGZvciBjaGFpbmluZ1xuICAgKi9cbiAgYWRkT3B0aW9uKG9wdGlvbikge1xuICAgIGNvbnN0IG9uYW1lID0gb3B0aW9uLm5hbWUoKTtcbiAgICBjb25zdCBuYW1lID0gb3B0aW9uLmF0dHJpYnV0ZU5hbWUoKTtcblxuICAgIC8vIHN0b3JlIGRlZmF1bHQgdmFsdWVcbiAgICBpZiAob3B0aW9uLm5lZ2F0ZSkge1xuICAgICAgLy8gLS1uby1mb28gaXMgc3BlY2lhbCBhbmQgZGVmYXVsdHMgZm9vIHRvIHRydWUsIHVubGVzcyBhIC0tZm9vIG9wdGlvbiBpcyBhbHJlYWR5IGRlZmluZWRcbiAgICAgIGNvbnN0IHBvc2l0aXZlTG9uZ0ZsYWcgPSBvcHRpb24ubG9uZy5yZXBsYWNlKC9eLS1uby0vLCAnLS0nKTtcbiAgICAgIGlmICghdGhpcy5fZmluZE9wdGlvbihwb3NpdGl2ZUxvbmdGbGFnKSkge1xuICAgICAgICB0aGlzLnNldE9wdGlvblZhbHVlV2l0aFNvdXJjZShuYW1lLCBvcHRpb24uZGVmYXVsdFZhbHVlID09PSB1bmRlZmluZWQgPyB0cnVlIDogb3B0aW9uLmRlZmF1bHRWYWx1ZSwgJ2RlZmF1bHQnKTtcbiAgICAgIH1cbiAgICB9IGVsc2UgaWYgKG9wdGlvbi5kZWZhdWx0VmFsdWUgIT09IHVuZGVmaW5lZCkge1xuICAgICAgdGhpcy5zZXRPcHRpb25WYWx1ZVdpdGhTb3VyY2UobmFtZSwgb3B0aW9uLmRlZmF1bHRWYWx1ZSwgJ2RlZmF1bHQnKTtcbiAgICB9XG5cbiAgICAvLyByZWdpc3RlciB0aGUgb3B0aW9uXG4gICAgdGhpcy5vcHRpb25zLnB1c2gob3B0aW9uKTtcblxuICAgIC8vIGhhbmRsZXIgZm9yIGNsaSBhbmQgZW52IHN1cHBsaWVkIHZhbHVlc1xuICAgIGNvbnN0IGhhbmRsZU9wdGlvblZhbHVlID0gKHZhbCwgaW52YWxpZFZhbHVlTWVzc2FnZSwgdmFsdWVTb3VyY2UpID0+IHtcbiAgICAgIC8vIHZhbCBpcyBudWxsIGZvciBvcHRpb25hbCBvcHRpb24gdXNlZCB3aXRob3V0IGFuIG9wdGlvbmFsLWFyZ3VtZW50LlxuICAgICAgLy8gdmFsIGlzIHVuZGVmaW5lZCBmb3IgYm9vbGVhbiBhbmQgbmVnYXRlZCBvcHRpb24uXG4gICAgICBpZiAodmFsID09IG51bGwgJiYgb3B0aW9uLnByZXNldEFyZyAhPT0gdW5kZWZpbmVkKSB7XG4gICAgICAgIHZhbCA9IG9wdGlvbi5wcmVzZXRBcmc7XG4gICAgICB9XG5cbiAgICAgIC8vIGN1c3RvbSBwcm9jZXNzaW5nXG4gICAgICBjb25zdCBvbGRWYWx1ZSA9IHRoaXMuZ2V0T3B0aW9uVmFsdWUobmFtZSk7XG4gICAgICBpZiAodmFsICE9PSBudWxsICYmIG9wdGlvbi5wYXJzZUFyZykge1xuICAgICAgICB0cnkge1xuICAgICAgICAgIHZhbCA9IG9wdGlvbi5wYXJzZUFyZyh2YWwsIG9sZFZhbHVlKTtcbiAgICAgICAgfSBjYXRjaCAoZXJyKSB7XG4gICAgICAgICAgaWYgKGVyci5jb2RlID09PSAnY29tbWFuZGVyLmludmFsaWRBcmd1bWVudCcpIHtcbiAgICAgICAgICAgIGNvbnN0IG1lc3NhZ2UgPSBgJHtpbnZhbGlkVmFsdWVNZXNzYWdlfSAke2Vyci5tZXNzYWdlfWA7XG4gICAgICAgICAgICB0aGlzLmVycm9yKG1lc3NhZ2UsIHsgZXhpdENvZGU6IGVyci5leGl0Q29kZSwgY29kZTogZXJyLmNvZGUgfSk7XG4gICAgICAgICAgfVxuICAgICAgICAgIHRocm93IGVycjtcbiAgICAgICAgfVxuICAgICAgfSBlbHNlIGlmICh2YWwgIT09IG51bGwgJiYgb3B0aW9uLnZhcmlhZGljKSB7XG4gICAgICAgIHZhbCA9IG9wdGlvbi5fY29uY2F0VmFsdWUodmFsLCBvbGRWYWx1ZSk7XG4gICAgICB9XG5cbiAgICAgIC8vIEZpbGwtaW4gYXBwcm9wcmlhdGUgbWlzc2luZyB2YWx1ZXMuIExvbmcgd2luZGVkIGJ1dCBlYXN5IHRvIGZvbGxvdy5cbiAgICAgIGlmICh2YWwgPT0gbnVsbCkge1xuICAgICAgICBpZiAob3B0aW9uLm5lZ2F0ZSkge1xuICAgICAgICAgIHZhbCA9IGZhbHNlO1xuICAgICAgICB9IGVsc2UgaWYgKG9wdGlvbi5pc0Jvb2xlYW4oKSB8fCBvcHRpb24ub3B0aW9uYWwpIHtcbiAgICAgICAgICB2YWwgPSB0cnVlO1xuICAgICAgICB9IGVsc2Uge1xuICAgICAgICAgIHZhbCA9ICcnOyAvLyBub3Qgbm9ybWFsLCBwYXJzZUFyZyBtaWdodCBoYXZlIGZhaWxlZCBvciBiZSBhIG1vY2sgZnVuY3Rpb24gZm9yIHRlc3RpbmdcbiAgICAgICAgfVxuICAgICAgfVxuICAgICAgdGhpcy5zZXRPcHRpb25WYWx1ZVdpdGhTb3VyY2UobmFtZSwgdmFsLCB2YWx1ZVNvdXJjZSk7XG4gICAgfTtcblxuICAgIHRoaXMub24oJ29wdGlvbjonICsgb25hbWUsICh2YWwpID0+IHtcbiAgICAgIGNvbnN0IGludmFsaWRWYWx1ZU1lc3NhZ2UgPSBgZXJyb3I6IG9wdGlvbiAnJHtvcHRpb24uZmxhZ3N9JyBhcmd1bWVudCAnJHt2YWx9JyBpcyBpbnZhbGlkLmA7XG4gICAgICBoYW5kbGVPcHRpb25WYWx1ZSh2YWwsIGludmFsaWRWYWx1ZU1lc3NhZ2UsICdjbGknKTtcbiAgICB9KTtcblxuICAgIGlmIChvcHRpb24uZW52VmFyKSB7XG4gICAgICB0aGlzLm9uKCdvcHRpb25FbnY6JyArIG9uYW1lLCAodmFsKSA9PiB7XG4gICAgICAgIGNvbnN0IGludmFsaWRWYWx1ZU1lc3NhZ2UgPSBgZXJyb3I6IG9wdGlvbiAnJHtvcHRpb24uZmxhZ3N9JyB2YWx1ZSAnJHt2YWx9JyBmcm9tIGVudiAnJHtvcHRpb24uZW52VmFyfScgaXMgaW52YWxpZC5gO1xuICAgICAgICBoYW5kbGVPcHRpb25WYWx1ZSh2YWwsIGludmFsaWRWYWx1ZU1lc3NhZ2UsICdlbnYnKTtcbiAgICAgIH0pO1xuICAgIH1cblxuICAgIHJldHVybiB0aGlzO1xuICB9XG5cbiAgLyoqXG4gICAqIEludGVybmFsIGltcGxlbWVudGF0aW9uIHNoYXJlZCBieSAub3B0aW9uKCkgYW5kIC5yZXF1aXJlZE9wdGlvbigpXG4gICAqXG4gICAqIEBhcGkgcHJpdmF0ZVxuICAgKi9cbiAgX29wdGlvbkV4KGNvbmZpZywgZmxhZ3MsIGRlc2NyaXB0aW9uLCBmbiwgZGVmYXVsdFZhbHVlKSB7XG4gICAgaWYgKHR5cGVvZiBmbGFncyA9PT0gJ29iamVjdCcgJiYgZmxhZ3MgaW5zdGFuY2VvZiBPcHRpb24pIHtcbiAgICAgIHRocm93IG5ldyBFcnJvcignVG8gYWRkIGFuIE9wdGlvbiBvYmplY3QgdXNlIGFkZE9wdGlvbigpIGluc3RlYWQgb2Ygb3B0aW9uKCkgb3IgcmVxdWlyZWRPcHRpb24oKScpO1xuICAgIH1cbiAgICBjb25zdCBvcHRpb24gPSB0aGlzLmNyZWF0ZU9wdGlvbihmbGFncywgZGVzY3JpcHRpb24pO1xuICAgIG9wdGlvbi5tYWtlT3B0aW9uTWFuZGF0b3J5KCEhY29uZmlnLm1hbmRhdG9yeSk7XG4gICAgaWYgKHR5cGVvZiBmbiA9PT0gJ2Z1bmN0aW9uJykge1xuICAgICAgb3B0aW9uLmRlZmF1bHQoZGVmYXVsdFZhbHVlKS5hcmdQYXJzZXIoZm4pO1xuICAgIH0gZWxzZSBpZiAoZm4gaW5zdGFuY2VvZiBSZWdFeHApIHtcbiAgICAgIC8vIGRlcHJlY2F0ZWRcbiAgICAgIGNvbnN0IHJlZ2V4ID0gZm47XG4gICAgICBmbiA9ICh2YWwsIGRlZikgPT4ge1xuICAgICAgICBjb25zdCBtID0gcmVnZXguZXhlYyh2YWwpO1xuICAgICAgICByZXR1cm4gbSA/IG1bMF0gOiBkZWY7XG4gICAgICB9O1xuICAgICAgb3B0aW9uLmRlZmF1bHQoZGVmYXVsdFZhbHVlKS5hcmdQYXJzZXIoZm4pO1xuICAgIH0gZWxzZSB7XG4gICAgICBvcHRpb24uZGVmYXVsdChmbik7XG4gICAgfVxuXG4gICAgcmV0dXJuIHRoaXMuYWRkT3B0aW9uKG9wdGlvbik7XG4gIH1cblxuICAvKipcbiAgICogRGVmaW5lIG9wdGlvbiB3aXRoIGBmbGFnc2AsIGBkZXNjcmlwdGlvbmAgYW5kIG9wdGlvbmFsXG4gICAqIGNvZXJjaW9uIGBmbmAuXG4gICAqXG4gICAqIFRoZSBgZmxhZ3NgIHN0cmluZyBjb250YWlucyB0aGUgc2hvcnQgYW5kL29yIGxvbmcgZmxhZ3MsXG4gICAqIHNlcGFyYXRlZCBieSBjb21tYSwgYSBwaXBlIG9yIHNwYWNlLiBUaGUgZm9sbG93aW5nIGFyZSBhbGwgdmFsaWRcbiAgICogYWxsIHdpbGwgb3V0cHV0IHRoaXMgd2F5IHdoZW4gYC0taGVscGAgaXMgdXNlZC5cbiAgICpcbiAgICogICAgIFwiLXAsIC0tcGVwcGVyXCJcbiAgICogICAgIFwiLXB8LS1wZXBwZXJcIlxuICAgKiAgICAgXCItcCAtLXBlcHBlclwiXG4gICAqXG4gICAqIEBleGFtcGxlXG4gICAqIC8vIHNpbXBsZSBib29sZWFuIGRlZmF1bHRpbmcgdG8gdW5kZWZpbmVkXG4gICAqIHByb2dyYW0ub3B0aW9uKCctcCwgLS1wZXBwZXInLCAnYWRkIHBlcHBlcicpO1xuICAgKlxuICAgKiBwcm9ncmFtLnBlcHBlclxuICAgKiAvLyA9PiB1bmRlZmluZWRcbiAgICpcbiAgICogLS1wZXBwZXJcbiAgICogcHJvZ3JhbS5wZXBwZXJcbiAgICogLy8gPT4gdHJ1ZVxuICAgKlxuICAgKiAvLyBzaW1wbGUgYm9vbGVhbiBkZWZhdWx0aW5nIHRvIHRydWUgKHVubGVzcyBub24tbmVnYXRlZCBvcHRpb24gaXMgYWxzbyBkZWZpbmVkKVxuICAgKiBwcm9ncmFtLm9wdGlvbignLUMsIC0tbm8tY2hlZXNlJywgJ3JlbW92ZSBjaGVlc2UnKTtcbiAgICpcbiAgICogcHJvZ3JhbS5jaGVlc2VcbiAgICogLy8gPT4gdHJ1ZVxuICAgKlxuICAgKiAtLW5vLWNoZWVzZVxuICAgKiBwcm9ncmFtLmNoZWVzZVxuICAgKiAvLyA9PiBmYWxzZVxuICAgKlxuICAgKiAvLyByZXF1aXJlZCBhcmd1bWVudFxuICAgKiBwcm9ncmFtLm9wdGlvbignLUMsIC0tY2hkaXIgPHBhdGg+JywgJ2NoYW5nZSB0aGUgd29ya2luZyBkaXJlY3RvcnknKTtcbiAgICpcbiAgICogLS1jaGRpciAvdG1wXG4gICAqIHByb2dyYW0uY2hkaXJcbiAgICogLy8gPT4gXCIvdG1wXCJcbiAgICpcbiAgICogLy8gb3B0aW9uYWwgYXJndW1lbnRcbiAgICogcHJvZ3JhbS5vcHRpb24oJy1jLCAtLWNoZWVzZSBbdHlwZV0nLCAnYWRkIGNoZWVzZSBbbWFyYmxlXScpO1xuICAgKlxuICAgKiBAcGFyYW0ge3N0cmluZ30gZmxhZ3NcbiAgICogQHBhcmFtIHtzdHJpbmd9IFtkZXNjcmlwdGlvbl1cbiAgICogQHBhcmFtIHtGdW5jdGlvbnwqfSBbZm5dIC0gY3VzdG9tIG9wdGlvbiBwcm9jZXNzaW5nIGZ1bmN0aW9uIG9yIGRlZmF1bHQgdmFsdWVcbiAgICogQHBhcmFtIHsqfSBbZGVmYXVsdFZhbHVlXVxuICAgKiBAcmV0dXJuIHtDb21tYW5kfSBgdGhpc2AgY29tbWFuZCBmb3IgY2hhaW5pbmdcbiAgICovXG5cbiAgb3B0aW9uKGZsYWdzLCBkZXNjcmlwdGlvbiwgZm4sIGRlZmF1bHRWYWx1ZSkge1xuICAgIHJldHVybiB0aGlzLl9vcHRpb25FeCh7fSwgZmxhZ3MsIGRlc2NyaXB0aW9uLCBmbiwgZGVmYXVsdFZhbHVlKTtcbiAgfVxuXG4gIC8qKlxuICAqIEFkZCBhIHJlcXVpcmVkIG9wdGlvbiB3aGljaCBtdXN0IGhhdmUgYSB2YWx1ZSBhZnRlciBwYXJzaW5nLiBUaGlzIHVzdWFsbHkgbWVhbnNcbiAgKiB0aGUgb3B0aW9uIG11c3QgYmUgc3BlY2lmaWVkIG9uIHRoZSBjb21tYW5kIGxpbmUuIChPdGhlcndpc2UgdGhlIHNhbWUgYXMgLm9wdGlvbigpLilcbiAgKlxuICAqIFRoZSBgZmxhZ3NgIHN0cmluZyBjb250YWlucyB0aGUgc2hvcnQgYW5kL29yIGxvbmcgZmxhZ3MsIHNlcGFyYXRlZCBieSBjb21tYSwgYSBwaXBlIG9yIHNwYWNlLlxuICAqXG4gICogQHBhcmFtIHtzdHJpbmd9IGZsYWdzXG4gICogQHBhcmFtIHtzdHJpbmd9IFtkZXNjcmlwdGlvbl1cbiAgKiBAcGFyYW0ge0Z1bmN0aW9ufCp9IFtmbl0gLSBjdXN0b20gb3B0aW9uIHByb2Nlc3NpbmcgZnVuY3Rpb24gb3IgZGVmYXVsdCB2YWx1ZVxuICAqIEBwYXJhbSB7Kn0gW2RlZmF1bHRWYWx1ZV1cbiAgKiBAcmV0dXJuIHtDb21tYW5kfSBgdGhpc2AgY29tbWFuZCBmb3IgY2hhaW5pbmdcbiAgKi9cblxuICByZXF1aXJlZE9wdGlvbihmbGFncywgZGVzY3JpcHRpb24sIGZuLCBkZWZhdWx0VmFsdWUpIHtcbiAgICByZXR1cm4gdGhpcy5fb3B0aW9uRXgoeyBtYW5kYXRvcnk6IHRydWUgfSwgZmxhZ3MsIGRlc2NyaXB0aW9uLCBmbiwgZGVmYXVsdFZhbHVlKTtcbiAgfVxuXG4gIC8qKlxuICAgKiBBbHRlciBwYXJzaW5nIG9mIHNob3J0IGZsYWdzIHdpdGggb3B0aW9uYWwgdmFsdWVzLlxuICAgKlxuICAgKiBAZXhhbXBsZVxuICAgKiAvLyBmb3IgYC5vcHRpb24oJy1mLC0tZmxhZyBbdmFsdWVdJyk6XG4gICAqIHByb2dyYW0uY29tYmluZUZsYWdBbmRPcHRpb25hbFZhbHVlKHRydWUpOyAgLy8gYC1mODBgIGlzIHRyZWF0ZWQgbGlrZSBgLS1mbGFnPTgwYCwgdGhpcyBpcyB0aGUgZGVmYXVsdCBiZWhhdmlvdXJcbiAgICogcHJvZ3JhbS5jb21iaW5lRmxhZ0FuZE9wdGlvbmFsVmFsdWUoZmFsc2UpIC8vIGAtZmJgIGlzIHRyZWF0ZWQgbGlrZSBgLWYgLWJgXG4gICAqXG4gICAqIEBwYXJhbSB7Qm9vbGVhbn0gW2NvbWJpbmU9dHJ1ZV0gLSBpZiBgdHJ1ZWAgb3Igb21pdHRlZCwgYW4gb3B0aW9uYWwgdmFsdWUgY2FuIGJlIHNwZWNpZmllZCBkaXJlY3RseSBhZnRlciB0aGUgZmxhZy5cbiAgICovXG4gIGNvbWJpbmVGbGFnQW5kT3B0aW9uYWxWYWx1ZShjb21iaW5lID0gdHJ1ZSkge1xuICAgIHRoaXMuX2NvbWJpbmVGbGFnQW5kT3B0aW9uYWxWYWx1ZSA9ICEhY29tYmluZTtcbiAgICByZXR1cm4gdGhpcztcbiAgfVxuXG4gIC8qKlxuICAgKiBBbGxvdyB1bmtub3duIG9wdGlvbnMgb24gdGhlIGNvbW1hbmQgbGluZS5cbiAgICpcbiAgICogQHBhcmFtIHtCb29sZWFufSBbYWxsb3dVbmtub3duPXRydWVdIC0gaWYgYHRydWVgIG9yIG9taXR0ZWQsIG5vIGVycm9yIHdpbGwgYmUgdGhyb3duXG4gICAqIGZvciB1bmtub3duIG9wdGlvbnMuXG4gICAqL1xuICBhbGxvd1Vua25vd25PcHRpb24oYWxsb3dVbmtub3duID0gdHJ1ZSkge1xuICAgIHRoaXMuX2FsbG93VW5rbm93bk9wdGlvbiA9ICEhYWxsb3dVbmtub3duO1xuICAgIHJldHVybiB0aGlzO1xuICB9XG5cbiAgLyoqXG4gICAqIEFsbG93IGV4Y2VzcyBjb21tYW5kLWFyZ3VtZW50cyBvbiB0aGUgY29tbWFuZCBsaW5lLiBQYXNzIGZhbHNlIHRvIG1ha2UgZXhjZXNzIGFyZ3VtZW50cyBhbiBlcnJvci5cbiAgICpcbiAgICogQHBhcmFtIHtCb29sZWFufSBbYWxsb3dFeGNlc3M9dHJ1ZV0gLSBpZiBgdHJ1ZWAgb3Igb21pdHRlZCwgbm8gZXJyb3Igd2lsbCBiZSB0aHJvd25cbiAgICogZm9yIGV4Y2VzcyBhcmd1bWVudHMuXG4gICAqL1xuICBhbGxvd0V4Y2Vzc0FyZ3VtZW50cyhhbGxvd0V4Y2VzcyA9IHRydWUpIHtcbiAgICB0aGlzLl9hbGxvd0V4Y2Vzc0FyZ3VtZW50cyA9ICEhYWxsb3dFeGNlc3M7XG4gICAgcmV0dXJuIHRoaXM7XG4gIH1cblxuICAvKipcbiAgICogRW5hYmxlIHBvc2l0aW9uYWwgb3B0aW9ucy4gUG9zaXRpb25hbCBtZWFucyBnbG9iYWwgb3B0aW9ucyBhcmUgc3BlY2lmaWVkIGJlZm9yZSBzdWJjb21tYW5kcyB3aGljaCBsZXRzXG4gICAqIHN1YmNvbW1hbmRzIHJldXNlIHRoZSBzYW1lIG9wdGlvbiBuYW1lcywgYW5kIGFsc28gZW5hYmxlcyBzdWJjb21tYW5kcyB0byB0dXJuIG9uIHBhc3NUaHJvdWdoT3B0aW9ucy5cbiAgICogVGhlIGRlZmF1bHQgYmVoYXZpb3VyIGlzIG5vbi1wb3NpdGlvbmFsIGFuZCBnbG9iYWwgb3B0aW9ucyBtYXkgYXBwZWFyIGFueXdoZXJlIG9uIHRoZSBjb21tYW5kIGxpbmUuXG4gICAqXG4gICAqIEBwYXJhbSB7Qm9vbGVhbn0gW3Bvc2l0aW9uYWw9dHJ1ZV1cbiAgICovXG4gIGVuYWJsZVBvc2l0aW9uYWxPcHRpb25zKHBvc2l0aW9uYWwgPSB0cnVlKSB7XG4gICAgdGhpcy5fZW5hYmxlUG9zaXRpb25hbE9wdGlvbnMgPSAhIXBvc2l0aW9uYWw7XG4gICAgcmV0dXJuIHRoaXM7XG4gIH1cblxuICAvKipcbiAgICogUGFzcyB0aHJvdWdoIG9wdGlvbnMgdGhhdCBjb21lIGFmdGVyIGNvbW1hbmQtYXJndW1lbnRzIHJhdGhlciB0aGFuIHRyZWF0IHRoZW0gYXMgY29tbWFuZC1vcHRpb25zLFxuICAgKiBzbyBhY3R1YWwgY29tbWFuZC1vcHRpb25zIGNvbWUgYmVmb3JlIGNvbW1hbmQtYXJndW1lbnRzLiBUdXJuaW5nIHRoaXMgb24gZm9yIGEgc3ViY29tbWFuZCByZXF1aXJlc1xuICAgKiBwb3NpdGlvbmFsIG9wdGlvbnMgdG8gaGF2ZSBiZWVuIGVuYWJsZWQgb24gdGhlIHByb2dyYW0gKHBhcmVudCBjb21tYW5kcykuXG4gICAqIFRoZSBkZWZhdWx0IGJlaGF2aW91ciBpcyBub24tcG9zaXRpb25hbCBhbmQgb3B0aW9ucyBtYXkgYXBwZWFyIGJlZm9yZSBvciBhZnRlciBjb21tYW5kLWFyZ3VtZW50cy5cbiAgICpcbiAgICogQHBhcmFtIHtCb29sZWFufSBbcGFzc1Rocm91Z2g9dHJ1ZV1cbiAgICogZm9yIHVua25vd24gb3B0aW9ucy5cbiAgICovXG4gIHBhc3NUaHJvdWdoT3B0aW9ucyhwYXNzVGhyb3VnaCA9IHRydWUpIHtcbiAgICB0aGlzLl9wYXNzVGhyb3VnaE9wdGlvbnMgPSAhIXBhc3NUaHJvdWdoO1xuICAgIGlmICghIXRoaXMucGFyZW50ICYmIHBhc3NUaHJvdWdoICYmICF0aGlzLnBhcmVudC5fZW5hYmxlUG9zaXRpb25hbE9wdGlvbnMpIHtcbiAgICAgIHRocm93IG5ldyBFcnJvcigncGFzc1Rocm91Z2hPcHRpb25zIGNhbiBub3QgYmUgdXNlZCB3aXRob3V0IHR1cm5pbmcgb24gZW5hYmxlUG9zaXRpb25hbE9wdGlvbnMgZm9yIHBhcmVudCBjb21tYW5kKHMpJyk7XG4gICAgfVxuICAgIHJldHVybiB0aGlzO1xuICB9XG5cbiAgLyoqXG4gICAgKiBXaGV0aGVyIHRvIHN0b3JlIG9wdGlvbiB2YWx1ZXMgYXMgcHJvcGVydGllcyBvbiBjb21tYW5kIG9iamVjdCxcbiAgICAqIG9yIHN0b3JlIHNlcGFyYXRlbHkgKHNwZWNpZnkgZmFsc2UpLiBJbiBib3RoIGNhc2VzIHRoZSBvcHRpb24gdmFsdWVzIGNhbiBiZSBhY2Nlc3NlZCB1c2luZyAub3B0cygpLlxuICAgICpcbiAgICAqIEBwYXJhbSB7Ym9vbGVhbn0gW3N0b3JlQXNQcm9wZXJ0aWVzPXRydWVdXG4gICAgKiBAcmV0dXJuIHtDb21tYW5kfSBgdGhpc2AgY29tbWFuZCBmb3IgY2hhaW5pbmdcbiAgICAqL1xuXG4gIHN0b3JlT3B0aW9uc0FzUHJvcGVydGllcyhzdG9yZUFzUHJvcGVydGllcyA9IHRydWUpIHtcbiAgICB0aGlzLl9zdG9yZU9wdGlvbnNBc1Byb3BlcnRpZXMgPSAhIXN0b3JlQXNQcm9wZXJ0aWVzO1xuICAgIGlmICh0aGlzLm9wdGlvbnMubGVuZ3RoKSB7XG4gICAgICB0aHJvdyBuZXcgRXJyb3IoJ2NhbGwgLnN0b3JlT3B0aW9uc0FzUHJvcGVydGllcygpIGJlZm9yZSBhZGRpbmcgb3B0aW9ucycpO1xuICAgIH1cbiAgICByZXR1cm4gdGhpcztcbiAgfVxuXG4gIC8qKlxuICAgKiBSZXRyaWV2ZSBvcHRpb24gdmFsdWUuXG4gICAqXG4gICAqIEBwYXJhbSB7c3RyaW5nfSBrZXlcbiAgICogQHJldHVybiB7T2JqZWN0fSB2YWx1ZVxuICAgKi9cblxuICBnZXRPcHRpb25WYWx1ZShrZXkpIHtcbiAgICBpZiAodGhpcy5fc3RvcmVPcHRpb25zQXNQcm9wZXJ0aWVzKSB7XG4gICAgICByZXR1cm4gdGhpc1trZXldO1xuICAgIH1cbiAgICByZXR1cm4gdGhpcy5fb3B0aW9uVmFsdWVzW2tleV07XG4gIH1cblxuICAvKipcbiAgICogU3RvcmUgb3B0aW9uIHZhbHVlLlxuICAgKlxuICAgKiBAcGFyYW0ge3N0cmluZ30ga2V5XG4gICAqIEBwYXJhbSB7T2JqZWN0fSB2YWx1ZVxuICAgKiBAcmV0dXJuIHtDb21tYW5kfSBgdGhpc2AgY29tbWFuZCBmb3IgY2hhaW5pbmdcbiAgICovXG5cbiAgc2V0T3B0aW9uVmFsdWUoa2V5LCB2YWx1ZSkge1xuICAgIHJldHVybiB0aGlzLnNldE9wdGlvblZhbHVlV2l0aFNvdXJjZShrZXksIHZhbHVlLCB1bmRlZmluZWQpO1xuICB9XG5cbiAgLyoqXG4gICAgKiBTdG9yZSBvcHRpb24gdmFsdWUgYW5kIHdoZXJlIHRoZSB2YWx1ZSBjYW1lIGZyb20uXG4gICAgKlxuICAgICogQHBhcmFtIHtzdHJpbmd9IGtleVxuICAgICogQHBhcmFtIHtPYmplY3R9IHZhbHVlXG4gICAgKiBAcGFyYW0ge3N0cmluZ30gc291cmNlIC0gZXhwZWN0ZWQgdmFsdWVzIGFyZSBkZWZhdWx0L2NvbmZpZy9lbnYvY2xpL2ltcGxpZWRcbiAgICAqIEByZXR1cm4ge0NvbW1hbmR9IGB0aGlzYCBjb21tYW5kIGZvciBjaGFpbmluZ1xuICAgICovXG5cbiAgc2V0T3B0aW9uVmFsdWVXaXRoU291cmNlKGtleSwgdmFsdWUsIHNvdXJjZSkge1xuICAgIGlmICh0aGlzLl9zdG9yZU9wdGlvbnNBc1Byb3BlcnRpZXMpIHtcbiAgICAgIHRoaXNba2V5XSA9IHZhbHVlO1xuICAgIH0gZWxzZSB7XG4gICAgICB0aGlzLl9vcHRpb25WYWx1ZXNba2V5XSA9IHZhbHVlO1xuICAgIH1cbiAgICB0aGlzLl9vcHRpb25WYWx1ZVNvdXJjZXNba2V5XSA9IHNvdXJjZTtcbiAgICByZXR1cm4gdGhpcztcbiAgfVxuXG4gIC8qKlxuICAgICogR2V0IHNvdXJjZSBvZiBvcHRpb24gdmFsdWUuXG4gICAgKiBFeHBlY3RlZCB2YWx1ZXMgYXJlIGRlZmF1bHQgfCBjb25maWcgfCBlbnYgfCBjbGkgfCBpbXBsaWVkXG4gICAgKlxuICAgICogQHBhcmFtIHtzdHJpbmd9IGtleVxuICAgICogQHJldHVybiB7c3RyaW5nfVxuICAgICovXG5cbiAgZ2V0T3B0aW9uVmFsdWVTb3VyY2Uoa2V5KSB7XG4gICAgcmV0dXJuIHRoaXMuX29wdGlvblZhbHVlU291cmNlc1trZXldO1xuICB9XG5cbiAgLyoqXG4gICAgKiBHZXQgc291cmNlIG9mIG9wdGlvbiB2YWx1ZS4gU2VlIGFsc28gLm9wdHNXaXRoR2xvYmFscygpLlxuICAgICogRXhwZWN0ZWQgdmFsdWVzIGFyZSBkZWZhdWx0IHwgY29uZmlnIHwgZW52IHwgY2xpIHwgaW1wbGllZFxuICAgICpcbiAgICAqIEBwYXJhbSB7c3RyaW5nfSBrZXlcbiAgICAqIEByZXR1cm4ge3N0cmluZ31cbiAgICAqL1xuXG4gIGdldE9wdGlvblZhbHVlU291cmNlV2l0aEdsb2JhbHMoa2V5KSB7XG4gICAgLy8gZ2xvYmFsIG92ZXJ3cml0ZXMgbG9jYWwsIGxpa2Ugb3B0c1dpdGhHbG9iYWxzXG4gICAgbGV0IHNvdXJjZTtcbiAgICBnZXRDb21tYW5kQW5kUGFyZW50cyh0aGlzKS5mb3JFYWNoKChjbWQpID0+IHtcbiAgICAgIGlmIChjbWQuZ2V0T3B0aW9uVmFsdWVTb3VyY2Uoa2V5KSAhPT0gdW5kZWZpbmVkKSB7XG4gICAgICAgIHNvdXJjZSA9IGNtZC5nZXRPcHRpb25WYWx1ZVNvdXJjZShrZXkpO1xuICAgICAgfVxuICAgIH0pO1xuICAgIHJldHVybiBzb3VyY2U7XG4gIH1cblxuICAvKipcbiAgICogR2V0IHVzZXIgYXJndW1lbnRzIGZyb20gaW1wbGllZCBvciBleHBsaWNpdCBhcmd1bWVudHMuXG4gICAqIFNpZGUtZWZmZWN0czogc2V0IF9zY3JpcHRQYXRoIGlmIGFyZ3MgaW5jbHVkZWQgc2NyaXB0LiBVc2VkIGZvciBkZWZhdWx0IHByb2dyYW0gbmFtZSwgYW5kIHN1YmNvbW1hbmQgc2VhcmNoZXMuXG4gICAqXG4gICAqIEBhcGkgcHJpdmF0ZVxuICAgKi9cblxuICBfcHJlcGFyZVVzZXJBcmdzKGFyZ3YsIHBhcnNlT3B0aW9ucykge1xuICAgIGlmIChhcmd2ICE9PSB1bmRlZmluZWQgJiYgIUFycmF5LmlzQXJyYXkoYXJndikpIHtcbiAgICAgIHRocm93IG5ldyBFcnJvcignZmlyc3QgcGFyYW1ldGVyIHRvIHBhcnNlIG11c3QgYmUgYXJyYXkgb3IgdW5kZWZpbmVkJyk7XG4gICAgfVxuICAgIHBhcnNlT3B0aW9ucyA9IHBhcnNlT3B0aW9ucyB8fCB7fTtcblxuICAgIC8vIERlZmF1bHQgdG8gdXNpbmcgcHJvY2Vzcy5hcmd2XG4gICAgaWYgKGFyZ3YgPT09IHVuZGVmaW5lZCkge1xuICAgICAgYXJndiA9IHByb2Nlc3MuYXJndjtcbiAgICAgIC8vIEB0cy1pZ25vcmU6IHVua25vd24gcHJvcGVydHlcbiAgICAgIGlmIChwcm9jZXNzLnZlcnNpb25zICYmIHByb2Nlc3MudmVyc2lvbnMuZWxlY3Ryb24pIHtcbiAgICAgICAgcGFyc2VPcHRpb25zLmZyb20gPSAnZWxlY3Ryb24nO1xuICAgICAgfVxuICAgIH1cbiAgICB0aGlzLnJhd0FyZ3MgPSBhcmd2LnNsaWNlKCk7XG5cbiAgICAvLyBtYWtlIGl0IGEgbGl0dGxlIGVhc2llciBmb3IgY2FsbGVycyBieSBzdXBwb3J0aW5nIHZhcmlvdXMgYXJndiBjb252ZW50aW9uc1xuICAgIGxldCB1c2VyQXJncztcbiAgICBzd2l0Y2ggKHBhcnNlT3B0aW9ucy5mcm9tKSB7XG4gICAgICBjYXNlIHVuZGVmaW5lZDpcbiAgICAgIGNhc2UgJ25vZGUnOlxuICAgICAgICB0aGlzLl9zY3JpcHRQYXRoID0gYXJndlsxXTtcbiAgICAgICAgdXNlckFyZ3MgPSBhcmd2LnNsaWNlKDIpO1xuICAgICAgICBicmVhaztcbiAgICAgIGNhc2UgJ2VsZWN0cm9uJzpcbiAgICAgICAgLy8gQHRzLWlnbm9yZTogdW5rbm93biBwcm9wZXJ0eVxuICAgICAgICBpZiAocHJvY2Vzcy5kZWZhdWx0QXBwKSB7XG4gICAgICAgICAgdGhpcy5fc2NyaXB0UGF0aCA9IGFyZ3ZbMV07XG4gICAgICAgICAgdXNlckFyZ3MgPSBhcmd2LnNsaWNlKDIpO1xuICAgICAgICB9IGVsc2Uge1xuICAgICAgICAgIHVzZXJBcmdzID0gYXJndi5zbGljZSgxKTtcbiAgICAgICAgfVxuICAgICAgICBicmVhaztcbiAgICAgIGNhc2UgJ3VzZXInOlxuICAgICAgICB1c2VyQXJncyA9IGFyZ3Yuc2xpY2UoMCk7XG4gICAgICAgIGJyZWFrO1xuICAgICAgZGVmYXVsdDpcbiAgICAgICAgdGhyb3cgbmV3IEVycm9yKGB1bmV4cGVjdGVkIHBhcnNlIG9wdGlvbiB7IGZyb206ICcke3BhcnNlT3B0aW9ucy5mcm9tfScgfWApO1xuICAgIH1cblxuICAgIC8vIEZpbmQgZGVmYXVsdCBuYW1lIGZvciBwcm9ncmFtIGZyb20gYXJndW1lbnRzLlxuICAgIGlmICghdGhpcy5fbmFtZSAmJiB0aGlzLl9zY3JpcHRQYXRoKSB0aGlzLm5hbWVGcm9tRmlsZW5hbWUodGhpcy5fc2NyaXB0UGF0aCk7XG4gICAgdGhpcy5fbmFtZSA9IHRoaXMuX25hbWUgfHwgJ3Byb2dyYW0nO1xuXG4gICAgcmV0dXJuIHVzZXJBcmdzO1xuICB9XG5cbiAgLyoqXG4gICAqIFBhcnNlIGBhcmd2YCwgc2V0dGluZyBvcHRpb25zIGFuZCBpbnZva2luZyBjb21tYW5kcyB3aGVuIGRlZmluZWQuXG4gICAqXG4gICAqIFRoZSBkZWZhdWx0IGV4cGVjdGF0aW9uIGlzIHRoYXQgdGhlIGFyZ3VtZW50cyBhcmUgZnJvbSBub2RlIGFuZCBoYXZlIHRoZSBhcHBsaWNhdGlvbiBhcyBhcmd2WzBdXG4gICAqIGFuZCB0aGUgc2NyaXB0IGJlaW5nIHJ1biBpbiBhcmd2WzFdLCB3aXRoIHVzZXIgcGFyYW1ldGVycyBhZnRlciB0aGF0LlxuICAgKlxuICAgKiBAZXhhbXBsZVxuICAgKiBwcm9ncmFtLnBhcnNlKHByb2Nlc3MuYXJndik7XG4gICAqIHByb2dyYW0ucGFyc2UoKTsgLy8gaW1wbGljaXRseSB1c2UgcHJvY2Vzcy5hcmd2IGFuZCBhdXRvLWRldGVjdCBub2RlIHZzIGVsZWN0cm9uIGNvbnZlbnRpb25zXG4gICAqIHByb2dyYW0ucGFyc2UobXktYXJncywgeyBmcm9tOiAndXNlcicgfSk7IC8vIGp1c3QgdXNlciBzdXBwbGllZCBhcmd1bWVudHMsIG5vdGhpbmcgc3BlY2lhbCBhYm91dCBhcmd2WzBdXG4gICAqXG4gICAqIEBwYXJhbSB7c3RyaW5nW119IFthcmd2XSAtIG9wdGlvbmFsLCBkZWZhdWx0cyB0byBwcm9jZXNzLmFyZ3ZcbiAgICogQHBhcmFtIHtPYmplY3R9IFtwYXJzZU9wdGlvbnNdIC0gb3B0aW9uYWxseSBzcGVjaWZ5IHN0eWxlIG9mIG9wdGlvbnMgd2l0aCBmcm9tOiBub2RlL3VzZXIvZWxlY3Ryb25cbiAgICogQHBhcmFtIHtzdHJpbmd9IFtwYXJzZU9wdGlvbnMuZnJvbV0gLSB3aGVyZSB0aGUgYXJncyBhcmUgZnJvbTogJ25vZGUnLCAndXNlcicsICdlbGVjdHJvbidcbiAgICogQHJldHVybiB7Q29tbWFuZH0gYHRoaXNgIGNvbW1hbmQgZm9yIGNoYWluaW5nXG4gICAqL1xuXG4gIHBhcnNlKGFyZ3YsIHBhcnNlT3B0aW9ucykge1xuICAgIGNvbnN0IHVzZXJBcmdzID0gdGhpcy5fcHJlcGFyZVVzZXJBcmdzKGFyZ3YsIHBhcnNlT3B0aW9ucyk7XG4gICAgdGhpcy5fcGFyc2VDb21tYW5kKFtdLCB1c2VyQXJncyk7XG5cbiAgICByZXR1cm4gdGhpcztcbiAgfVxuXG4gIC8qKlxuICAgKiBQYXJzZSBgYXJndmAsIHNldHRpbmcgb3B0aW9ucyBhbmQgaW52b2tpbmcgY29tbWFuZHMgd2hlbiBkZWZpbmVkLlxuICAgKlxuICAgKiBVc2UgcGFyc2VBc3luYyBpbnN0ZWFkIG9mIHBhcnNlIGlmIGFueSBvZiB5b3VyIGFjdGlvbiBoYW5kbGVycyBhcmUgYXN5bmMuIFJldHVybnMgYSBQcm9taXNlLlxuICAgKlxuICAgKiBUaGUgZGVmYXVsdCBleHBlY3RhdGlvbiBpcyB0aGF0IHRoZSBhcmd1bWVudHMgYXJlIGZyb20gbm9kZSBhbmQgaGF2ZSB0aGUgYXBwbGljYXRpb24gYXMgYXJndlswXVxuICAgKiBhbmQgdGhlIHNjcmlwdCBiZWluZyBydW4gaW4gYXJndlsxXSwgd2l0aCB1c2VyIHBhcmFtZXRlcnMgYWZ0ZXIgdGhhdC5cbiAgICpcbiAgICogQGV4YW1wbGVcbiAgICogYXdhaXQgcHJvZ3JhbS5wYXJzZUFzeW5jKHByb2Nlc3MuYXJndik7XG4gICAqIGF3YWl0IHByb2dyYW0ucGFyc2VBc3luYygpOyAvLyBpbXBsaWNpdGx5IHVzZSBwcm9jZXNzLmFyZ3YgYW5kIGF1dG8tZGV0ZWN0IG5vZGUgdnMgZWxlY3Ryb24gY29udmVudGlvbnNcbiAgICogYXdhaXQgcHJvZ3JhbS5wYXJzZUFzeW5jKG15LWFyZ3MsIHsgZnJvbTogJ3VzZXInIH0pOyAvLyBqdXN0IHVzZXIgc3VwcGxpZWQgYXJndW1lbnRzLCBub3RoaW5nIHNwZWNpYWwgYWJvdXQgYXJndlswXVxuICAgKlxuICAgKiBAcGFyYW0ge3N0cmluZ1tdfSBbYXJndl1cbiAgICogQHBhcmFtIHtPYmplY3R9IFtwYXJzZU9wdGlvbnNdXG4gICAqIEBwYXJhbSB7c3RyaW5nfSBwYXJzZU9wdGlvbnMuZnJvbSAtIHdoZXJlIHRoZSBhcmdzIGFyZSBmcm9tOiAnbm9kZScsICd1c2VyJywgJ2VsZWN0cm9uJ1xuICAgKiBAcmV0dXJuIHtQcm9taXNlfVxuICAgKi9cblxuICBhc3luYyBwYXJzZUFzeW5jKGFyZ3YsIHBhcnNlT3B0aW9ucykge1xuICAgIGNvbnN0IHVzZXJBcmdzID0gdGhpcy5fcHJlcGFyZVVzZXJBcmdzKGFyZ3YsIHBhcnNlT3B0aW9ucyk7XG4gICAgYXdhaXQgdGhpcy5fcGFyc2VDb21tYW5kKFtdLCB1c2VyQXJncyk7XG5cbiAgICByZXR1cm4gdGhpcztcbiAgfVxuXG4gIC8qKlxuICAgKiBFeGVjdXRlIGEgc3ViLWNvbW1hbmQgZXhlY3V0YWJsZS5cbiAgICpcbiAgICogQGFwaSBwcml2YXRlXG4gICAqL1xuXG4gIF9leGVjdXRlU3ViQ29tbWFuZChzdWJjb21tYW5kLCBhcmdzKSB7XG4gICAgYXJncyA9IGFyZ3Muc2xpY2UoKTtcbiAgICBsZXQgbGF1bmNoV2l0aE5vZGUgPSBmYWxzZTsgLy8gVXNlIG5vZGUgZm9yIHNvdXJjZSB0YXJnZXRzIHNvIGRvIG5vdCBuZWVkIHRvIGdldCBwZXJtaXNzaW9ucyBjb3JyZWN0LCBhbmQgb24gV2luZG93cy5cbiAgICBjb25zdCBzb3VyY2VFeHQgPSBbJy5qcycsICcudHMnLCAnLnRzeCcsICcubWpzJywgJy5janMnXTtcblxuICAgIGZ1bmN0aW9uIGZpbmRGaWxlKGJhc2VEaXIsIGJhc2VOYW1lKSB7XG4gICAgICAvLyBMb29rIGZvciBzcGVjaWZpZWQgZmlsZVxuICAgICAgY29uc3QgbG9jYWxCaW4gPSBwYXRoLnJlc29sdmUoYmFzZURpciwgYmFzZU5hbWUpO1xuICAgICAgaWYgKGZzLmV4aXN0c1N5bmMobG9jYWxCaW4pKSByZXR1cm4gbG9jYWxCaW47XG5cbiAgICAgIC8vIFN0b3AgbG9va2luZyBpZiBjYW5kaWRhdGUgYWxyZWFkeSBoYXMgYW4gZXhwZWN0ZWQgZXh0ZW5zaW9uLlxuICAgICAgaWYgKHNvdXJjZUV4dC5pbmNsdWRlcyhwYXRoLmV4dG5hbWUoYmFzZU5hbWUpKSkgcmV0dXJuIHVuZGVmaW5lZDtcblxuICAgICAgLy8gVHJ5IGFsbCB0aGUgZXh0ZW5zaW9ucy5cbiAgICAgIGNvbnN0IGZvdW5kRXh0ID0gc291cmNlRXh0LmZpbmQoZXh0ID0+IGZzLmV4aXN0c1N5bmMoYCR7bG9jYWxCaW59JHtleHR9YCkpO1xuICAgICAgaWYgKGZvdW5kRXh0KSByZXR1cm4gYCR7bG9jYWxCaW59JHtmb3VuZEV4dH1gO1xuXG4gICAgICByZXR1cm4gdW5kZWZpbmVkO1xuICAgIH1cblxuICAgIC8vIE5vdCBjaGVja2luZyBmb3IgaGVscCBmaXJzdC4gVW5saWtlbHkgdG8gaGF2ZSBtYW5kYXRvcnkgYW5kIGV4ZWN1dGFibGUsIGFuZCBjYW4ndCByb2J1c3RseSB0ZXN0IGZvciBoZWxwIGZsYWdzIGluIGV4dGVybmFsIGNvbW1hbmQuXG4gICAgdGhpcy5fY2hlY2tGb3JNaXNzaW5nTWFuZGF0b3J5T3B0aW9ucygpO1xuICAgIHRoaXMuX2NoZWNrRm9yQ29uZmxpY3RpbmdPcHRpb25zKCk7XG5cbiAgICAvLyBleGVjdXRhYmxlRmlsZSBhbmQgZXhlY3V0YWJsZURpciBtaWdodCBiZSBmdWxsIHBhdGgsIG9yIGp1c3QgYSBuYW1lXG4gICAgbGV0IGV4ZWN1dGFibGVGaWxlID0gc3ViY29tbWFuZC5fZXhlY3V0YWJsZUZpbGUgfHwgYCR7dGhpcy5fbmFtZX0tJHtzdWJjb21tYW5kLl9uYW1lfWA7XG4gICAgbGV0IGV4ZWN1dGFibGVEaXIgPSB0aGlzLl9leGVjdXRhYmxlRGlyIHx8ICcnO1xuICAgIGlmICh0aGlzLl9zY3JpcHRQYXRoKSB7XG4gICAgICBsZXQgcmVzb2x2ZWRTY3JpcHRQYXRoOyAvLyByZXNvbHZlIHBvc3NpYmxlIHN5bWxpbmsgZm9yIGluc3RhbGxlZCBucG0gYmluYXJ5XG4gICAgICB0cnkge1xuICAgICAgICByZXNvbHZlZFNjcmlwdFBhdGggPSBmcy5yZWFscGF0aFN5bmModGhpcy5fc2NyaXB0UGF0aCk7XG4gICAgICB9IGNhdGNoIChlcnIpIHtcbiAgICAgICAgcmVzb2x2ZWRTY3JpcHRQYXRoID0gdGhpcy5fc2NyaXB0UGF0aDtcbiAgICAgIH1cbiAgICAgIGV4ZWN1dGFibGVEaXIgPSBwYXRoLnJlc29sdmUocGF0aC5kaXJuYW1lKHJlc29sdmVkU2NyaXB0UGF0aCksIGV4ZWN1dGFibGVEaXIpO1xuICAgIH1cblxuICAgIC8vIExvb2sgZm9yIGEgbG9jYWwgZmlsZSBpbiBwcmVmZXJlbmNlIHRvIGEgY29tbWFuZCBpbiBQQVRILlxuICAgIGlmIChleGVjdXRhYmxlRGlyKSB7XG4gICAgICBsZXQgbG9jYWxGaWxlID0gZmluZEZpbGUoZXhlY3V0YWJsZURpciwgZXhlY3V0YWJsZUZpbGUpO1xuXG4gICAgICAvLyBMZWdhY3kgc2VhcmNoIHVzaW5nIHByZWZpeCBvZiBzY3JpcHQgbmFtZSBpbnN0ZWFkIG9mIGNvbW1hbmQgbmFtZVxuICAgICAgaWYgKCFsb2NhbEZpbGUgJiYgIXN1YmNvbW1hbmQuX2V4ZWN1dGFibGVGaWxlICYmIHRoaXMuX3NjcmlwdFBhdGgpIHtcbiAgICAgICAgY29uc3QgbGVnYWN5TmFtZSA9IHBhdGguYmFzZW5hbWUodGhpcy5fc2NyaXB0UGF0aCwgcGF0aC5leHRuYW1lKHRoaXMuX3NjcmlwdFBhdGgpKTtcbiAgICAgICAgaWYgKGxlZ2FjeU5hbWUgIT09IHRoaXMuX25hbWUpIHtcbiAgICAgICAgICBsb2NhbEZpbGUgPSBmaW5kRmlsZShleGVjdXRhYmxlRGlyLCBgJHtsZWdhY3lOYW1lfS0ke3N1YmNvbW1hbmQuX25hbWV9YCk7XG4gICAgICAgIH1cbiAgICAgIH1cbiAgICAgIGV4ZWN1dGFibGVGaWxlID0gbG9jYWxGaWxlIHx8IGV4ZWN1dGFibGVGaWxlO1xuICAgIH1cblxuICAgIGxhdW5jaFdpdGhOb2RlID0gc291cmNlRXh0LmluY2x1ZGVzKHBhdGguZXh0bmFtZShleGVjdXRhYmxlRmlsZSkpO1xuXG4gICAgbGV0IHByb2M7XG4gICAgaWYgKHByb2Nlc3MucGxhdGZvcm0gIT09ICd3aW4zMicpIHtcbiAgICAgIGlmIChsYXVuY2hXaXRoTm9kZSkge1xuICAgICAgICBhcmdzLnVuc2hpZnQoZXhlY3V0YWJsZUZpbGUpO1xuICAgICAgICAvLyBhZGQgZXhlY3V0YWJsZSBhcmd1bWVudHMgdG8gc3Bhd25cbiAgICAgICAgYXJncyA9IGluY3JlbWVudE5vZGVJbnNwZWN0b3JQb3J0KHByb2Nlc3MuZXhlY0FyZ3YpLmNvbmNhdChhcmdzKTtcblxuICAgICAgICBwcm9jID0gY2hpbGRQcm9jZXNzLnNwYXduKHByb2Nlc3MuYXJndlswXSwgYXJncywgeyBzdGRpbzogJ2luaGVyaXQnIH0pO1xuICAgICAgfSBlbHNlIHtcbiAgICAgICAgcHJvYyA9IGNoaWxkUHJvY2Vzcy5zcGF3bihleGVjdXRhYmxlRmlsZSwgYXJncywgeyBzdGRpbzogJ2luaGVyaXQnIH0pO1xuICAgICAgfVxuICAgIH0gZWxzZSB7XG4gICAgICBhcmdzLnVuc2hpZnQoZXhlY3V0YWJsZUZpbGUpO1xuICAgICAgLy8gYWRkIGV4ZWN1dGFibGUgYXJndW1lbnRzIHRvIHNwYXduXG4gICAgICBhcmdzID0gaW5jcmVtZW50Tm9kZUluc3BlY3RvclBvcnQocHJvY2Vzcy5leGVjQXJndikuY29uY2F0KGFyZ3MpO1xuICAgICAgcHJvYyA9IGNoaWxkUHJvY2Vzcy5zcGF3bihwcm9jZXNzLmV4ZWNQYXRoLCBhcmdzLCB7IHN0ZGlvOiAnaW5oZXJpdCcgfSk7XG4gICAgfVxuXG4gICAgaWYgKCFwcm9jLmtpbGxlZCkgeyAvLyB0ZXN0aW5nIG1haW5seSB0byBhdm9pZCBsZWFrIHdhcm5pbmdzIGR1cmluZyB1bml0IHRlc3RzIHdpdGggbW9ja2VkIHNwYXduXG4gICAgICBjb25zdCBzaWduYWxzID0gWydTSUdVU1IxJywgJ1NJR1VTUjInLCAnU0lHVEVSTScsICdTSUdJTlQnLCAnU0lHSFVQJ107XG4gICAgICBzaWduYWxzLmZvckVhY2goKHNpZ25hbCkgPT4ge1xuICAgICAgICAvLyBAdHMtaWdub3JlXG4gICAgICAgIHByb2Nlc3Mub24oc2lnbmFsLCAoKSA9PiB7XG4gICAgICAgICAgaWYgKHByb2Mua2lsbGVkID09PSBmYWxzZSAmJiBwcm9jLmV4aXRDb2RlID09PSBudWxsKSB7XG4gICAgICAgICAgICBwcm9jLmtpbGwoc2lnbmFsKTtcbiAgICAgICAgICB9XG4gICAgICAgIH0pO1xuICAgICAgfSk7XG4gICAgfVxuXG4gICAgLy8gQnkgZGVmYXVsdCB0ZXJtaW5hdGUgcHJvY2VzcyB3aGVuIHNwYXduZWQgcHJvY2VzcyB0ZXJtaW5hdGVzLlxuICAgIC8vIFN1cHByZXNzaW5nIHRoZSBleGl0IGlmIGV4aXRDYWxsYmFjayBkZWZpbmVkIGlzIGEgYml0IG1lc3N5IGFuZCBvZiBsaW1pdGVkIHVzZSwgYnV0IGRvZXMgYWxsb3cgcHJvY2VzcyB0byBzdGF5IHJ1bm5pbmchXG4gICAgY29uc3QgZXhpdENhbGxiYWNrID0gdGhpcy5fZXhpdENhbGxiYWNrO1xuICAgIGlmICghZXhpdENhbGxiYWNrKSB7XG4gICAgICBwcm9jLm9uKCdjbG9zZScsIHByb2Nlc3MuZXhpdC5iaW5kKHByb2Nlc3MpKTtcbiAgICB9IGVsc2Uge1xuICAgICAgcHJvYy5vbignY2xvc2UnLCAoKSA9PiB7XG4gICAgICAgIGV4aXRDYWxsYmFjayhuZXcgQ29tbWFuZGVyRXJyb3IocHJvY2Vzcy5leGl0Q29kZSB8fCAwLCAnY29tbWFuZGVyLmV4ZWN1dGVTdWJDb21tYW5kQXN5bmMnLCAnKGNsb3NlKScpKTtcbiAgICAgIH0pO1xuICAgIH1cbiAgICBwcm9jLm9uKCdlcnJvcicsIChlcnIpID0+IHtcbiAgICAgIC8vIEB0cy1pZ25vcmVcbiAgICAgIGlmIChlcnIuY29kZSA9PT0gJ0VOT0VOVCcpIHtcbiAgICAgICAgY29uc3QgZXhlY3V0YWJsZURpck1lc3NhZ2UgPSBleGVjdXRhYmxlRGlyXG4gICAgICAgICAgPyBgc2VhcmNoZWQgZm9yIGxvY2FsIHN1YmNvbW1hbmQgcmVsYXRpdmUgdG8gZGlyZWN0b3J5ICcke2V4ZWN1dGFibGVEaXJ9J2BcbiAgICAgICAgICA6ICdubyBkaXJlY3RvcnkgZm9yIHNlYXJjaCBmb3IgbG9jYWwgc3ViY29tbWFuZCwgdXNlIC5leGVjdXRhYmxlRGlyKCkgdG8gc3VwcGx5IGEgY3VzdG9tIGRpcmVjdG9yeSc7XG4gICAgICAgIGNvbnN0IGV4ZWN1dGFibGVNaXNzaW5nID0gYCcke2V4ZWN1dGFibGVGaWxlfScgZG9lcyBub3QgZXhpc3RcbiAtIGlmICcke3N1YmNvbW1hbmQuX25hbWV9JyBpcyBub3QgbWVhbnQgdG8gYmUgYW4gZXhlY3V0YWJsZSBjb21tYW5kLCByZW1vdmUgZGVzY3JpcHRpb24gcGFyYW1ldGVyIGZyb20gJy5jb21tYW5kKCknIGFuZCB1c2UgJy5kZXNjcmlwdGlvbigpJyBpbnN0ZWFkXG4gLSBpZiB0aGUgZGVmYXVsdCBleGVjdXRhYmxlIG5hbWUgaXMgbm90IHN1aXRhYmxlLCB1c2UgdGhlIGV4ZWN1dGFibGVGaWxlIG9wdGlvbiB0byBzdXBwbHkgYSBjdXN0b20gbmFtZSBvciBwYXRoXG4gLSAke2V4ZWN1dGFibGVEaXJNZXNzYWdlfWA7XG4gICAgICAgIHRocm93IG5ldyBFcnJvcihleGVjdXRhYmxlTWlzc2luZyk7XG4gICAgICAvLyBAdHMtaWdub3JlXG4gICAgICB9IGVsc2UgaWYgKGVyci5jb2RlID09PSAnRUFDQ0VTJykge1xuICAgICAgICB0aHJvdyBuZXcgRXJyb3IoYCcke2V4ZWN1dGFibGVGaWxlfScgbm90IGV4ZWN1dGFibGVgKTtcbiAgICAgIH1cbiAgICAgIGlmICghZXhpdENhbGxiYWNrKSB7XG4gICAgICAgIHByb2Nlc3MuZXhpdCgxKTtcbiAgICAgIH0gZWxzZSB7XG4gICAgICAgIGNvbnN0IHdyYXBwZWRFcnJvciA9IG5ldyBDb21tYW5kZXJFcnJvcigxLCAnY29tbWFuZGVyLmV4ZWN1dGVTdWJDb21tYW5kQXN5bmMnLCAnKGVycm9yKScpO1xuICAgICAgICB3cmFwcGVkRXJyb3IubmVzdGVkRXJyb3IgPSBlcnI7XG4gICAgICAgIGV4aXRDYWxsYmFjayh3cmFwcGVkRXJyb3IpO1xuICAgICAgfVxuICAgIH0pO1xuXG4gICAgLy8gU3RvcmUgdGhlIHJlZmVyZW5jZSB0byB0aGUgY2hpbGQgcHJvY2Vzc1xuICAgIHRoaXMucnVubmluZ0NvbW1hbmQgPSBwcm9jO1xuICB9XG5cbiAgLyoqXG4gICAqIEBhcGkgcHJpdmF0ZVxuICAgKi9cblxuICBfZGlzcGF0Y2hTdWJjb21tYW5kKGNvbW1hbmROYW1lLCBvcGVyYW5kcywgdW5rbm93bikge1xuICAgIGNvbnN0IHN1YkNvbW1hbmQgPSB0aGlzLl9maW5kQ29tbWFuZChjb21tYW5kTmFtZSk7XG4gICAgaWYgKCFzdWJDb21tYW5kKSB0aGlzLmhlbHAoeyBlcnJvcjogdHJ1ZSB9KTtcblxuICAgIGxldCBob29rUmVzdWx0O1xuICAgIGhvb2tSZXN1bHQgPSB0aGlzLl9jaGFpbk9yQ2FsbFN1YkNvbW1hbmRIb29rKGhvb2tSZXN1bHQsIHN1YkNvbW1hbmQsICdwcmVTdWJjb21tYW5kJyk7XG4gICAgaG9va1Jlc3VsdCA9IHRoaXMuX2NoYWluT3JDYWxsKGhvb2tSZXN1bHQsICgpID0+IHtcbiAgICAgIGlmIChzdWJDb21tYW5kLl9leGVjdXRhYmxlSGFuZGxlcikge1xuICAgICAgICB0aGlzLl9leGVjdXRlU3ViQ29tbWFuZChzdWJDb21tYW5kLCBvcGVyYW5kcy5jb25jYXQodW5rbm93bikpO1xuICAgICAgfSBlbHNlIHtcbiAgICAgICAgcmV0dXJuIHN1YkNvbW1hbmQuX3BhcnNlQ29tbWFuZChvcGVyYW5kcywgdW5rbm93bik7XG4gICAgICB9XG4gICAgfSk7XG4gICAgcmV0dXJuIGhvb2tSZXN1bHQ7XG4gIH1cblxuICAvKipcbiAgICogQ2hlY2sgdGhpcy5hcmdzIGFnYWluc3QgZXhwZWN0ZWQgdGhpcy5fYXJncy5cbiAgICpcbiAgICogQGFwaSBwcml2YXRlXG4gICAqL1xuXG4gIF9jaGVja051bWJlck9mQXJndW1lbnRzKCkge1xuICAgIC8vIHRvbyBmZXdcbiAgICB0aGlzLl9hcmdzLmZvckVhY2goKGFyZywgaSkgPT4ge1xuICAgICAgaWYgKGFyZy5yZXF1aXJlZCAmJiB0aGlzLmFyZ3NbaV0gPT0gbnVsbCkge1xuICAgICAgICB0aGlzLm1pc3NpbmdBcmd1bWVudChhcmcubmFtZSgpKTtcbiAgICAgIH1cbiAgICB9KTtcbiAgICAvLyB0b28gbWFueVxuICAgIGlmICh0aGlzLl9hcmdzLmxlbmd0aCA+IDAgJiYgdGhpcy5fYXJnc1t0aGlzLl9hcmdzLmxlbmd0aCAtIDFdLnZhcmlhZGljKSB7XG4gICAgICByZXR1cm47XG4gICAgfVxuICAgIGlmICh0aGlzLmFyZ3MubGVuZ3RoID4gdGhpcy5fYXJncy5sZW5ndGgpIHtcbiAgICAgIHRoaXMuX2V4Y2Vzc0FyZ3VtZW50cyh0aGlzLmFyZ3MpO1xuICAgIH1cbiAgfVxuXG4gIC8qKlxuICAgKiBQcm9jZXNzIHRoaXMuYXJncyB1c2luZyB0aGlzLl9hcmdzIGFuZCBzYXZlIGFzIHRoaXMucHJvY2Vzc2VkQXJncyFcbiAgICpcbiAgICogQGFwaSBwcml2YXRlXG4gICAqL1xuXG4gIF9wcm9jZXNzQXJndW1lbnRzKCkge1xuICAgIGNvbnN0IG15UGFyc2VBcmcgPSAoYXJndW1lbnQsIHZhbHVlLCBwcmV2aW91cykgPT4ge1xuICAgICAgLy8gRXh0cmEgcHJvY2Vzc2luZyBmb3IgbmljZSBlcnJvciBtZXNzYWdlIG9uIHBhcnNpbmcgZmFpbHVyZS5cbiAgICAgIGxldCBwYXJzZWRWYWx1ZSA9IHZhbHVlO1xuICAgICAgaWYgKHZhbHVlICE9PSBudWxsICYmIGFyZ3VtZW50LnBhcnNlQXJnKSB7XG4gICAgICAgIHRyeSB7XG4gICAgICAgICAgcGFyc2VkVmFsdWUgPSBhcmd1bWVudC5wYXJzZUFyZyh2YWx1ZSwgcHJldmlvdXMpO1xuICAgICAgICB9IGNhdGNoIChlcnIpIHtcbiAgICAgICAgICBpZiAoZXJyLmNvZGUgPT09ICdjb21tYW5kZXIuaW52YWxpZEFyZ3VtZW50Jykge1xuICAgICAgICAgICAgY29uc3QgbWVzc2FnZSA9IGBlcnJvcjogY29tbWFuZC1hcmd1bWVudCB2YWx1ZSAnJHt2YWx1ZX0nIGlzIGludmFsaWQgZm9yIGFyZ3VtZW50ICcke2FyZ3VtZW50Lm5hbWUoKX0nLiAke2Vyci5tZXNzYWdlfWA7XG4gICAgICAgICAgICB0aGlzLmVycm9yKG1lc3NhZ2UsIHsgZXhpdENvZGU6IGVyci5leGl0Q29kZSwgY29kZTogZXJyLmNvZGUgfSk7XG4gICAgICAgICAgfVxuICAgICAgICAgIHRocm93IGVycjtcbiAgICAgICAgfVxuICAgICAgfVxuICAgICAgcmV0dXJuIHBhcnNlZFZhbHVlO1xuICAgIH07XG5cbiAgICB0aGlzLl9jaGVja051bWJlck9mQXJndW1lbnRzKCk7XG5cbiAgICBjb25zdCBwcm9jZXNzZWRBcmdzID0gW107XG4gICAgdGhpcy5fYXJncy5mb3JFYWNoKChkZWNsYXJlZEFyZywgaW5kZXgpID0+IHtcbiAgICAgIGxldCB2YWx1ZSA9IGRlY2xhcmVkQXJnLmRlZmF1bHRWYWx1ZTtcbiAgICAgIGlmIChkZWNsYXJlZEFyZy52YXJpYWRpYykge1xuICAgICAgICAvLyBDb2xsZWN0IHRvZ2V0aGVyIHJlbWFpbmluZyBhcmd1bWVudHMgZm9yIHBhc3NpbmcgdG9nZXRoZXIgYXMgYW4gYXJyYXkuXG4gICAgICAgIGlmIChpbmRleCA8IHRoaXMuYXJncy5sZW5ndGgpIHtcbiAgICAgICAgICB2YWx1ZSA9IHRoaXMuYXJncy5zbGljZShpbmRleCk7XG4gICAgICAgICAgaWYgKGRlY2xhcmVkQXJnLnBhcnNlQXJnKSB7XG4gICAgICAgICAgICB2YWx1ZSA9IHZhbHVlLnJlZHVjZSgocHJvY2Vzc2VkLCB2KSA9PiB7XG4gICAgICAgICAgICAgIHJldHVybiBteVBhcnNlQXJnKGRlY2xhcmVkQXJnLCB2LCBwcm9jZXNzZWQpO1xuICAgICAgICAgICAgfSwgZGVjbGFyZWRBcmcuZGVmYXVsdFZhbHVlKTtcbiAgICAgICAgICB9XG4gICAgICAgIH0gZWxzZSBpZiAodmFsdWUgPT09IHVuZGVmaW5lZCkge1xuICAgICAgICAgIHZhbHVlID0gW107XG4gICAgICAgIH1cbiAgICAgIH0gZWxzZSBpZiAoaW5kZXggPCB0aGlzLmFyZ3MubGVuZ3RoKSB7XG4gICAgICAgIHZhbHVlID0gdGhpcy5hcmdzW2luZGV4XTtcbiAgICAgICAgaWYgKGRlY2xhcmVkQXJnLnBhcnNlQXJnKSB7XG4gICAgICAgICAgdmFsdWUgPSBteVBhcnNlQXJnKGRlY2xhcmVkQXJnLCB2YWx1ZSwgZGVjbGFyZWRBcmcuZGVmYXVsdFZhbHVlKTtcbiAgICAgICAgfVxuICAgICAgfVxuICAgICAgcHJvY2Vzc2VkQXJnc1tpbmRleF0gPSB2YWx1ZTtcbiAgICB9KTtcbiAgICB0aGlzLnByb2Nlc3NlZEFyZ3MgPSBwcm9jZXNzZWRBcmdzO1xuICB9XG5cbiAgLyoqXG4gICAqIE9uY2Ugd2UgaGF2ZSBhIHByb21pc2Ugd2UgY2hhaW4sIGJ1dCBjYWxsIHN5bmNocm9ub3VzbHkgdW50aWwgdGhlbi5cbiAgICpcbiAgICogQHBhcmFtIHtQcm9taXNlfHVuZGVmaW5lZH0gcHJvbWlzZVxuICAgKiBAcGFyYW0ge0Z1bmN0aW9ufSBmblxuICAgKiBAcmV0dXJuIHtQcm9taXNlfHVuZGVmaW5lZH1cbiAgICogQGFwaSBwcml2YXRlXG4gICAqL1xuXG4gIF9jaGFpbk9yQ2FsbChwcm9taXNlLCBmbikge1xuICAgIC8vIHRoZW5hYmxlXG4gICAgaWYgKHByb21pc2UgJiYgcHJvbWlzZS50aGVuICYmIHR5cGVvZiBwcm9taXNlLnRoZW4gPT09ICdmdW5jdGlvbicpIHtcbiAgICAgIC8vIGFscmVhZHkgaGF2ZSBhIHByb21pc2UsIGNoYWluIGNhbGxiYWNrXG4gICAgICByZXR1cm4gcHJvbWlzZS50aGVuKCgpID0+IGZuKCkpO1xuICAgIH1cbiAgICAvLyBjYWxsYmFjayBtaWdodCByZXR1cm4gYSBwcm9taXNlXG4gICAgcmV0dXJuIGZuKCk7XG4gIH1cblxuICAvKipcbiAgICpcbiAgICogQHBhcmFtIHtQcm9taXNlfHVuZGVmaW5lZH0gcHJvbWlzZVxuICAgKiBAcGFyYW0ge3N0cmluZ30gZXZlbnRcbiAgICogQHJldHVybiB7UHJvbWlzZXx1bmRlZmluZWR9XG4gICAqIEBhcGkgcHJpdmF0ZVxuICAgKi9cblxuICBfY2hhaW5PckNhbGxIb29rcyhwcm9taXNlLCBldmVudCkge1xuICAgIGxldCByZXN1bHQgPSBwcm9taXNlO1xuICAgIGNvbnN0IGhvb2tzID0gW107XG4gICAgZ2V0Q29tbWFuZEFuZFBhcmVudHModGhpcylcbiAgICAgIC5yZXZlcnNlKClcbiAgICAgIC5maWx0ZXIoY21kID0+IGNtZC5fbGlmZUN5Y2xlSG9va3NbZXZlbnRdICE9PSB1bmRlZmluZWQpXG4gICAgICAuZm9yRWFjaChob29rZWRDb21tYW5kID0+IHtcbiAgICAgICAgaG9va2VkQ29tbWFuZC5fbGlmZUN5Y2xlSG9va3NbZXZlbnRdLmZvckVhY2goKGNhbGxiYWNrKSA9PiB7XG4gICAgICAgICAgaG9va3MucHVzaCh7IGhvb2tlZENvbW1hbmQsIGNhbGxiYWNrIH0pO1xuICAgICAgICB9KTtcbiAgICAgIH0pO1xuICAgIGlmIChldmVudCA9PT0gJ3Bvc3RBY3Rpb24nKSB7XG4gICAgICBob29rcy5yZXZlcnNlKCk7XG4gICAgfVxuXG4gICAgaG9va3MuZm9yRWFjaCgoaG9va0RldGFpbCkgPT4ge1xuICAgICAgcmVzdWx0ID0gdGhpcy5fY2hhaW5PckNhbGwocmVzdWx0LCAoKSA9PiB7XG4gICAgICAgIHJldHVybiBob29rRGV0YWlsLmNhbGxiYWNrKGhvb2tEZXRhaWwuaG9va2VkQ29tbWFuZCwgdGhpcyk7XG4gICAgICB9KTtcbiAgICB9KTtcbiAgICByZXR1cm4gcmVzdWx0O1xuICB9XG5cbiAgLyoqXG4gICAqXG4gICAqIEBwYXJhbSB7UHJvbWlzZXx1bmRlZmluZWR9IHByb21pc2VcbiAgICogQHBhcmFtIHtDb21tYW5kfSBzdWJDb21tYW5kXG4gICAqIEBwYXJhbSB7c3RyaW5nfSBldmVudFxuICAgKiBAcmV0dXJuIHtQcm9taXNlfHVuZGVmaW5lZH1cbiAgICogQGFwaSBwcml2YXRlXG4gICAqL1xuXG4gIF9jaGFpbk9yQ2FsbFN1YkNvbW1hbmRIb29rKHByb21pc2UsIHN1YkNvbW1hbmQsIGV2ZW50KSB7XG4gICAgbGV0IHJlc3VsdCA9IHByb21pc2U7XG4gICAgaWYgKHRoaXMuX2xpZmVDeWNsZUhvb2tzW2V2ZW50XSAhPT0gdW5kZWZpbmVkKSB7XG4gICAgICB0aGlzLl9saWZlQ3ljbGVIb29rc1tldmVudF0uZm9yRWFjaCgoaG9vaykgPT4ge1xuICAgICAgICByZXN1bHQgPSB0aGlzLl9jaGFpbk9yQ2FsbChyZXN1bHQsICgpID0+IHtcbiAgICAgICAgICByZXR1cm4gaG9vayh0aGlzLCBzdWJDb21tYW5kKTtcbiAgICAgICAgfSk7XG4gICAgICB9KTtcbiAgICB9XG4gICAgcmV0dXJuIHJlc3VsdDtcbiAgfVxuXG4gIC8qKlxuICAgKiBQcm9jZXNzIGFyZ3VtZW50cyBpbiBjb250ZXh0IG9mIHRoaXMgY29tbWFuZC5cbiAgICogUmV0dXJucyBhY3Rpb24gcmVzdWx0LCBpbiBjYXNlIGl0IGlzIGEgcHJvbWlzZS5cbiAgICpcbiAgICogQGFwaSBwcml2YXRlXG4gICAqL1xuXG4gIF9wYXJzZUNvbW1hbmQob3BlcmFuZHMsIHVua25vd24pIHtcbiAgICBjb25zdCBwYXJzZWQgPSB0aGlzLnBhcnNlT3B0aW9ucyh1bmtub3duKTtcbiAgICB0aGlzLl9wYXJzZU9wdGlvbnNFbnYoKTsgLy8gYWZ0ZXIgY2xpLCBzbyBwYXJzZUFyZyBub3QgY2FsbGVkIG9uIGJvdGggY2xpIGFuZCBlbnZcbiAgICB0aGlzLl9wYXJzZU9wdGlvbnNJbXBsaWVkKCk7XG4gICAgb3BlcmFuZHMgPSBvcGVyYW5kcy5jb25jYXQocGFyc2VkLm9wZXJhbmRzKTtcbiAgICB1bmtub3duID0gcGFyc2VkLnVua25vd247XG4gICAgdGhpcy5hcmdzID0gb3BlcmFuZHMuY29uY2F0KHVua25vd24pO1xuXG4gICAgaWYgKG9wZXJhbmRzICYmIHRoaXMuX2ZpbmRDb21tYW5kKG9wZXJhbmRzWzBdKSkge1xuICAgICAgcmV0dXJuIHRoaXMuX2Rpc3BhdGNoU3ViY29tbWFuZChvcGVyYW5kc1swXSwgb3BlcmFuZHMuc2xpY2UoMSksIHVua25vd24pO1xuICAgIH1cbiAgICBpZiAodGhpcy5faGFzSW1wbGljaXRIZWxwQ29tbWFuZCgpICYmIG9wZXJhbmRzWzBdID09PSB0aGlzLl9oZWxwQ29tbWFuZE5hbWUpIHtcbiAgICAgIGlmIChvcGVyYW5kcy5sZW5ndGggPT09IDEpIHtcbiAgICAgICAgdGhpcy5oZWxwKCk7XG4gICAgICB9XG4gICAgICByZXR1cm4gdGhpcy5fZGlzcGF0Y2hTdWJjb21tYW5kKG9wZXJhbmRzWzFdLCBbXSwgW3RoaXMuX2hlbHBMb25nRmxhZ10pO1xuICAgIH1cbiAgICBpZiAodGhpcy5fZGVmYXVsdENvbW1hbmROYW1lKSB7XG4gICAgICBvdXRwdXRIZWxwSWZSZXF1ZXN0ZWQodGhpcywgdW5rbm93bik7IC8vIFJ1biB0aGUgaGVscCBmb3IgZGVmYXVsdCBjb21tYW5kIGZyb20gcGFyZW50IHJhdGhlciB0aGFuIHBhc3NpbmcgdG8gZGVmYXVsdCBjb21tYW5kXG4gICAgICByZXR1cm4gdGhpcy5fZGlzcGF0Y2hTdWJjb21tYW5kKHRoaXMuX2RlZmF1bHRDb21tYW5kTmFtZSwgb3BlcmFuZHMsIHVua25vd24pO1xuICAgIH1cbiAgICBpZiAodGhpcy5jb21tYW5kcy5sZW5ndGggJiYgdGhpcy5hcmdzLmxlbmd0aCA9PT0gMCAmJiAhdGhpcy5fYWN0aW9uSGFuZGxlciAmJiAhdGhpcy5fZGVmYXVsdENvbW1hbmROYW1lKSB7XG4gICAgICAvLyBwcm9iYWJseSBtaXNzaW5nIHN1YmNvbW1hbmQgYW5kIG5vIGhhbmRsZXIsIHVzZXIgbmVlZHMgaGVscCAoYW5kIGV4aXQpXG4gICAgICB0aGlzLmhlbHAoeyBlcnJvcjogdHJ1ZSB9KTtcbiAgICB9XG5cbiAgICBvdXRwdXRIZWxwSWZSZXF1ZXN0ZWQodGhpcywgcGFyc2VkLnVua25vd24pO1xuICAgIHRoaXMuX2NoZWNrRm9yTWlzc2luZ01hbmRhdG9yeU9wdGlvbnMoKTtcbiAgICB0aGlzLl9jaGVja0ZvckNvbmZsaWN0aW5nT3B0aW9ucygpO1xuXG4gICAgLy8gV2UgZG8gbm90IGFsd2F5cyBjYWxsIHRoaXMgY2hlY2sgdG8gYXZvaWQgbWFza2luZyBhIFwiYmV0dGVyXCIgZXJyb3IsIGxpa2UgdW5rbm93biBjb21tYW5kLlxuICAgIGNvbnN0IGNoZWNrRm9yVW5rbm93bk9wdGlvbnMgPSAoKSA9PiB7XG4gICAgICBpZiAocGFyc2VkLnVua25vd24ubGVuZ3RoID4gMCkge1xuICAgICAgICB0aGlzLnVua25vd25PcHRpb24ocGFyc2VkLnVua25vd25bMF0pO1xuICAgICAgfVxuICAgIH07XG5cbiAgICBjb25zdCBjb21tYW5kRXZlbnQgPSBgY29tbWFuZDoke3RoaXMubmFtZSgpfWA7XG4gICAgaWYgKHRoaXMuX2FjdGlvbkhhbmRsZXIpIHtcbiAgICAgIGNoZWNrRm9yVW5rbm93bk9wdGlvbnMoKTtcbiAgICAgIHRoaXMuX3Byb2Nlc3NBcmd1bWVudHMoKTtcblxuICAgICAgbGV0IGFjdGlvblJlc3VsdDtcbiAgICAgIGFjdGlvblJlc3VsdCA9IHRoaXMuX2NoYWluT3JDYWxsSG9va3MoYWN0aW9uUmVzdWx0LCAncHJlQWN0aW9uJyk7XG4gICAgICBhY3Rpb25SZXN1bHQgPSB0aGlzLl9jaGFpbk9yQ2FsbChhY3Rpb25SZXN1bHQsICgpID0+IHRoaXMuX2FjdGlvbkhhbmRsZXIodGhpcy5wcm9jZXNzZWRBcmdzKSk7XG4gICAgICBpZiAodGhpcy5wYXJlbnQpIHtcbiAgICAgICAgYWN0aW9uUmVzdWx0ID0gdGhpcy5fY2hhaW5PckNhbGwoYWN0aW9uUmVzdWx0LCAoKSA9PiB7XG4gICAgICAgICAgdGhpcy5wYXJlbnQuZW1pdChjb21tYW5kRXZlbnQsIG9wZXJhbmRzLCB1bmtub3duKTsgLy8gbGVnYWN5XG4gICAgICAgIH0pO1xuICAgICAgfVxuICAgICAgYWN0aW9uUmVzdWx0ID0gdGhpcy5fY2hhaW5PckNhbGxIb29rcyhhY3Rpb25SZXN1bHQsICdwb3N0QWN0aW9uJyk7XG4gICAgICByZXR1cm4gYWN0aW9uUmVzdWx0O1xuICAgIH1cbiAgICBpZiAodGhpcy5wYXJlbnQgJiYgdGhpcy5wYXJlbnQubGlzdGVuZXJDb3VudChjb21tYW5kRXZlbnQpKSB7XG4gICAgICBjaGVja0ZvclVua25vd25PcHRpb25zKCk7XG4gICAgICB0aGlzLl9wcm9jZXNzQXJndW1lbnRzKCk7XG4gICAgICB0aGlzLnBhcmVudC5lbWl0KGNvbW1hbmRFdmVudCwgb3BlcmFuZHMsIHVua25vd24pOyAvLyBsZWdhY3lcbiAgICB9IGVsc2UgaWYgKG9wZXJhbmRzLmxlbmd0aCkge1xuICAgICAgaWYgKHRoaXMuX2ZpbmRDb21tYW5kKCcqJykpIHsgLy8gbGVnYWN5IGRlZmF1bHQgY29tbWFuZFxuICAgICAgICByZXR1cm4gdGhpcy5fZGlzcGF0Y2hTdWJjb21tYW5kKCcqJywgb3BlcmFuZHMsIHVua25vd24pO1xuICAgICAgfVxuICAgICAgaWYgKHRoaXMubGlzdGVuZXJDb3VudCgnY29tbWFuZDoqJykpIHtcbiAgICAgICAgLy8gc2tpcCBvcHRpb24gY2hlY2ssIGVtaXQgZXZlbnQgZm9yIHBvc3NpYmxlIG1pc3NwZWxsaW5nIHN1Z2dlc3Rpb25cbiAgICAgICAgdGhpcy5lbWl0KCdjb21tYW5kOionLCBvcGVyYW5kcywgdW5rbm93bik7XG4gICAgICB9IGVsc2UgaWYgKHRoaXMuY29tbWFuZHMubGVuZ3RoKSB7XG4gICAgICAgIHRoaXMudW5rbm93bkNvbW1hbmQoKTtcbiAgICAgIH0gZWxzZSB7XG4gICAgICAgIGNoZWNrRm9yVW5rbm93bk9wdGlvbnMoKTtcbiAgICAgICAgdGhpcy5fcHJvY2Vzc0FyZ3VtZW50cygpO1xuICAgICAgfVxuICAgIH0gZWxzZSBpZiAodGhpcy5jb21tYW5kcy5sZW5ndGgpIHtcbiAgICAgIGNoZWNrRm9yVW5rbm93bk9wdGlvbnMoKTtcbiAgICAgIC8vIFRoaXMgY29tbWFuZCBoYXMgc3ViY29tbWFuZHMgYW5kIG5vdGhpbmcgaG9va2VkIHVwIGF0IHRoaXMgbGV2ZWwsIHNvIGRpc3BsYXkgaGVscCAoYW5kIGV4aXQpLlxuICAgICAgdGhpcy5oZWxwKHsgZXJyb3I6IHRydWUgfSk7XG4gICAgfSBlbHNlIHtcbiAgICAgIGNoZWNrRm9yVW5rbm93bk9wdGlvbnMoKTtcbiAgICAgIHRoaXMuX3Byb2Nlc3NBcmd1bWVudHMoKTtcbiAgICAgIC8vIGZhbGwgdGhyb3VnaCBmb3IgY2FsbGVyIHRvIGhhbmRsZSBhZnRlciBjYWxsaW5nIC5wYXJzZSgpXG4gICAgfVxuICB9XG5cbiAgLyoqXG4gICAqIEZpbmQgbWF0Y2hpbmcgY29tbWFuZC5cbiAgICpcbiAgICogQGFwaSBwcml2YXRlXG4gICAqL1xuICBfZmluZENvbW1hbmQobmFtZSkge1xuICAgIGlmICghbmFtZSkgcmV0dXJuIHVuZGVmaW5lZDtcbiAgICByZXR1cm4gdGhpcy5jb21tYW5kcy5maW5kKGNtZCA9PiBjbWQuX25hbWUgPT09IG5hbWUgfHwgY21kLl9hbGlhc2VzLmluY2x1ZGVzKG5hbWUpKTtcbiAgfVxuXG4gIC8qKlxuICAgKiBSZXR1cm4gYW4gb3B0aW9uIG1hdGNoaW5nIGBhcmdgIGlmIGFueS5cbiAgICpcbiAgICogQHBhcmFtIHtzdHJpbmd9IGFyZ1xuICAgKiBAcmV0dXJuIHtPcHRpb259XG4gICAqIEBhcGkgcHJpdmF0ZVxuICAgKi9cblxuICBfZmluZE9wdGlvbihhcmcpIHtcbiAgICByZXR1cm4gdGhpcy5vcHRpb25zLmZpbmQob3B0aW9uID0+IG9wdGlvbi5pcyhhcmcpKTtcbiAgfVxuXG4gIC8qKlxuICAgKiBEaXNwbGF5IGFuIGVycm9yIG1lc3NhZ2UgaWYgYSBtYW5kYXRvcnkgb3B0aW9uIGRvZXMgbm90IGhhdmUgYSB2YWx1ZS5cbiAgICogQ2FsbGVkIGFmdGVyIGNoZWNraW5nIGZvciBoZWxwIGZsYWdzIGluIGxlYWYgc3ViY29tbWFuZC5cbiAgICpcbiAgICogQGFwaSBwcml2YXRlXG4gICAqL1xuXG4gIF9jaGVja0Zvck1pc3NpbmdNYW5kYXRvcnlPcHRpb25zKCkge1xuICAgIC8vIFdhbGsgdXAgaGllcmFyY2h5IHNvIGNhbiBjYWxsIGluIHN1YmNvbW1hbmQgYWZ0ZXIgY2hlY2tpbmcgZm9yIGRpc3BsYXlpbmcgaGVscC5cbiAgICBmb3IgKGxldCBjbWQgPSB0aGlzOyBjbWQ7IGNtZCA9IGNtZC5wYXJlbnQpIHtcbiAgICAgIGNtZC5vcHRpb25zLmZvckVhY2goKGFuT3B0aW9uKSA9PiB7XG4gICAgICAgIGlmIChhbk9wdGlvbi5tYW5kYXRvcnkgJiYgKGNtZC5nZXRPcHRpb25WYWx1ZShhbk9wdGlvbi5hdHRyaWJ1dGVOYW1lKCkpID09PSB1bmRlZmluZWQpKSB7XG4gICAgICAgICAgY21kLm1pc3NpbmdNYW5kYXRvcnlPcHRpb25WYWx1ZShhbk9wdGlvbik7XG4gICAgICAgIH1cbiAgICAgIH0pO1xuICAgIH1cbiAgfVxuXG4gIC8qKlxuICAgKiBEaXNwbGF5IGFuIGVycm9yIG1lc3NhZ2UgaWYgY29uZmxpY3Rpbmcgb3B0aW9ucyBhcmUgdXNlZCB0b2dldGhlciBpbiB0aGlzLlxuICAgKlxuICAgKiBAYXBpIHByaXZhdGVcbiAgICovXG4gIF9jaGVja0ZvckNvbmZsaWN0aW5nTG9jYWxPcHRpb25zKCkge1xuICAgIGNvbnN0IGRlZmluZWROb25EZWZhdWx0T3B0aW9ucyA9IHRoaXMub3B0aW9ucy5maWx0ZXIoXG4gICAgICAob3B0aW9uKSA9PiB7XG4gICAgICAgIGNvbnN0IG9wdGlvbktleSA9IG9wdGlvbi5hdHRyaWJ1dGVOYW1lKCk7XG4gICAgICAgIGlmICh0aGlzLmdldE9wdGlvblZhbHVlKG9wdGlvbktleSkgPT09IHVuZGVmaW5lZCkge1xuICAgICAgICAgIHJldHVybiBmYWxzZTtcbiAgICAgICAgfVxuICAgICAgICByZXR1cm4gdGhpcy5nZXRPcHRpb25WYWx1ZVNvdXJjZShvcHRpb25LZXkpICE9PSAnZGVmYXVsdCc7XG4gICAgICB9XG4gICAgKTtcblxuICAgIGNvbnN0IG9wdGlvbnNXaXRoQ29uZmxpY3RpbmcgPSBkZWZpbmVkTm9uRGVmYXVsdE9wdGlvbnMuZmlsdGVyKFxuICAgICAgKG9wdGlvbikgPT4gb3B0aW9uLmNvbmZsaWN0c1dpdGgubGVuZ3RoID4gMFxuICAgICk7XG5cbiAgICBvcHRpb25zV2l0aENvbmZsaWN0aW5nLmZvckVhY2goKG9wdGlvbikgPT4ge1xuICAgICAgY29uc3QgY29uZmxpY3RpbmdBbmREZWZpbmVkID0gZGVmaW5lZE5vbkRlZmF1bHRPcHRpb25zLmZpbmQoKGRlZmluZWQpID0+XG4gICAgICAgIG9wdGlvbi5jb25mbGljdHNXaXRoLmluY2x1ZGVzKGRlZmluZWQuYXR0cmlidXRlTmFtZSgpKVxuICAgICAgKTtcbiAgICAgIGlmIChjb25mbGljdGluZ0FuZERlZmluZWQpIHtcbiAgICAgICAgdGhpcy5fY29uZmxpY3RpbmdPcHRpb24ob3B0aW9uLCBjb25mbGljdGluZ0FuZERlZmluZWQpO1xuICAgICAgfVxuICAgIH0pO1xuICB9XG5cbiAgLyoqXG4gICAqIERpc3BsYXkgYW4gZXJyb3IgbWVzc2FnZSBpZiBjb25mbGljdGluZyBvcHRpb25zIGFyZSB1c2VkIHRvZ2V0aGVyLlxuICAgKiBDYWxsZWQgYWZ0ZXIgY2hlY2tpbmcgZm9yIGhlbHAgZmxhZ3MgaW4gbGVhZiBzdWJjb21tYW5kLlxuICAgKlxuICAgKiBAYXBpIHByaXZhdGVcbiAgICovXG4gIF9jaGVja0ZvckNvbmZsaWN0aW5nT3B0aW9ucygpIHtcbiAgICAvLyBXYWxrIHVwIGhpZXJhcmNoeSBzbyBjYW4gY2FsbCBpbiBzdWJjb21tYW5kIGFmdGVyIGNoZWNraW5nIGZvciBkaXNwbGF5aW5nIGhlbHAuXG4gICAgZm9yIChsZXQgY21kID0gdGhpczsgY21kOyBjbWQgPSBjbWQucGFyZW50KSB7XG4gICAgICBjbWQuX2NoZWNrRm9yQ29uZmxpY3RpbmdMb2NhbE9wdGlvbnMoKTtcbiAgICB9XG4gIH1cblxuICAvKipcbiAgICogUGFyc2Ugb3B0aW9ucyBmcm9tIGBhcmd2YCByZW1vdmluZyBrbm93biBvcHRpb25zLFxuICAgKiBhbmQgcmV0dXJuIGFyZ3Ygc3BsaXQgaW50byBvcGVyYW5kcyBhbmQgdW5rbm93biBhcmd1bWVudHMuXG4gICAqXG4gICAqIEV4YW1wbGVzOlxuICAgKlxuICAgKiAgICAgYXJndiA9PiBvcGVyYW5kcywgdW5rbm93blxuICAgKiAgICAgLS1rbm93biBra2sgb3AgPT4gW29wXSwgW11cbiAgICogICAgIG9wIC0ta25vd24ga2trID0+IFtvcF0sIFtdXG4gICAqICAgICBzdWIgLS11bmtub3duIHV1dSBvcCA9PiBbc3ViXSwgWy0tdW5rbm93biB1dXUgb3BdXG4gICAqICAgICBzdWIgLS0gLS11bmtub3duIHV1dSBvcCA9PiBbc3ViIC0tdW5rbm93biB1dXUgb3BdLCBbXVxuICAgKlxuICAgKiBAcGFyYW0ge1N0cmluZ1tdfSBhcmd2XG4gICAqIEByZXR1cm4ge3tvcGVyYW5kczogU3RyaW5nW10sIHVua25vd246IFN0cmluZ1tdfX1cbiAgICovXG5cbiAgcGFyc2VPcHRpb25zKGFyZ3YpIHtcbiAgICBjb25zdCBvcGVyYW5kcyA9IFtdOyAvLyBvcGVyYW5kcywgbm90IG9wdGlvbnMgb3IgdmFsdWVzXG4gICAgY29uc3QgdW5rbm93biA9IFtdOyAvLyBmaXJzdCB1bmtub3duIG9wdGlvbiBhbmQgcmVtYWluaW5nIHVua25vd24gYXJnc1xuICAgIGxldCBkZXN0ID0gb3BlcmFuZHM7XG4gICAgY29uc3QgYXJncyA9IGFyZ3Yuc2xpY2UoKTtcblxuICAgIGZ1bmN0aW9uIG1heWJlT3B0aW9uKGFyZykge1xuICAgICAgcmV0dXJuIGFyZy5sZW5ndGggPiAxICYmIGFyZ1swXSA9PT0gJy0nO1xuICAgIH1cblxuICAgIC8vIHBhcnNlIG9wdGlvbnNcbiAgICBsZXQgYWN0aXZlVmFyaWFkaWNPcHRpb24gPSBudWxsO1xuICAgIHdoaWxlIChhcmdzLmxlbmd0aCkge1xuICAgICAgY29uc3QgYXJnID0gYXJncy5zaGlmdCgpO1xuXG4gICAgICAvLyBsaXRlcmFsXG4gICAgICBpZiAoYXJnID09PSAnLS0nKSB7XG4gICAgICAgIGlmIChkZXN0ID09PSB1bmtub3duKSBkZXN0LnB1c2goYXJnKTtcbiAgICAgICAgZGVzdC5wdXNoKC4uLmFyZ3MpO1xuICAgICAgICBicmVhaztcbiAgICAgIH1cblxuICAgICAgaWYgKGFjdGl2ZVZhcmlhZGljT3B0aW9uICYmICFtYXliZU9wdGlvbihhcmcpKSB7XG4gICAgICAgIHRoaXMuZW1pdChgb3B0aW9uOiR7YWN0aXZlVmFyaWFkaWNPcHRpb24ubmFtZSgpfWAsIGFyZyk7XG4gICAgICAgIGNvbnRpbnVlO1xuICAgICAgfVxuICAgICAgYWN0aXZlVmFyaWFkaWNPcHRpb24gPSBudWxsO1xuXG4gICAgICBpZiAobWF5YmVPcHRpb24oYXJnKSkge1xuICAgICAgICBjb25zdCBvcHRpb24gPSB0aGlzLl9maW5kT3B0aW9uKGFyZyk7XG4gICAgICAgIC8vIHJlY29nbmlzZWQgb3B0aW9uLCBjYWxsIGxpc3RlbmVyIHRvIGFzc2lnbiB2YWx1ZSB3aXRoIHBvc3NpYmxlIGN1c3RvbSBwcm9jZXNzaW5nXG4gICAgICAgIGlmIChvcHRpb24pIHtcbiAgICAgICAgICBpZiAob3B0aW9uLnJlcXVpcmVkKSB7XG4gICAgICAgICAgICBjb25zdCB2YWx1ZSA9IGFyZ3Muc2hpZnQoKTtcbiAgICAgICAgICAgIGlmICh2YWx1ZSA9PT0gdW5kZWZpbmVkKSB0aGlzLm9wdGlvbk1pc3NpbmdBcmd1bWVudChvcHRpb24pO1xuICAgICAgICAgICAgdGhpcy5lbWl0KGBvcHRpb246JHtvcHRpb24ubmFtZSgpfWAsIHZhbHVlKTtcbiAgICAgICAgICB9IGVsc2UgaWYgKG9wdGlvbi5vcHRpb25hbCkge1xuICAgICAgICAgICAgbGV0IHZhbHVlID0gbnVsbDtcbiAgICAgICAgICAgIC8vIGhpc3RvcmljYWwgYmVoYXZpb3VyIGlzIG9wdGlvbmFsIHZhbHVlIGlzIGZvbGxvd2luZyBhcmcgdW5sZXNzIGFuIG9wdGlvblxuICAgICAgICAgICAgaWYgKGFyZ3MubGVuZ3RoID4gMCAmJiAhbWF5YmVPcHRpb24oYXJnc1swXSkpIHtcbiAgICAgICAgICAgICAgdmFsdWUgPSBhcmdzLnNoaWZ0KCk7XG4gICAgICAgICAgICB9XG4gICAgICAgICAgICB0aGlzLmVtaXQoYG9wdGlvbjoke29wdGlvbi5uYW1lKCl9YCwgdmFsdWUpO1xuICAgICAgICAgIH0gZWxzZSB7IC8vIGJvb2xlYW4gZmxhZ1xuICAgICAgICAgICAgdGhpcy5lbWl0KGBvcHRpb246JHtvcHRpb24ubmFtZSgpfWApO1xuICAgICAgICAgIH1cbiAgICAgICAgICBhY3RpdmVWYXJpYWRpY09wdGlvbiA9IG9wdGlvbi52YXJpYWRpYyA/IG9wdGlvbiA6IG51bGw7XG4gICAgICAgICAgY29udGludWU7XG4gICAgICAgIH1cbiAgICAgIH1cblxuICAgICAgLy8gTG9vayBmb3IgY29tYm8gb3B0aW9ucyBmb2xsb3dpbmcgc2luZ2xlIGRhc2gsIGVhdCBmaXJzdCBvbmUgaWYga25vd24uXG4gICAgICBpZiAoYXJnLmxlbmd0aCA+IDIgJiYgYXJnWzBdID09PSAnLScgJiYgYXJnWzFdICE9PSAnLScpIHtcbiAgICAgICAgY29uc3Qgb3B0aW9uID0gdGhpcy5fZmluZE9wdGlvbihgLSR7YXJnWzFdfWApO1xuICAgICAgICBpZiAob3B0aW9uKSB7XG4gICAgICAgICAgaWYgKG9wdGlvbi5yZXF1aXJlZCB8fCAob3B0aW9uLm9wdGlvbmFsICYmIHRoaXMuX2NvbWJpbmVGbGFnQW5kT3B0aW9uYWxWYWx1ZSkpIHtcbiAgICAgICAgICAgIC8vIG9wdGlvbiB3aXRoIHZhbHVlIGZvbGxvd2luZyBpbiBzYW1lIGFyZ3VtZW50XG4gICAgICAgICAgICB0aGlzLmVtaXQoYG9wdGlvbjoke29wdGlvbi5uYW1lKCl9YCwgYXJnLnNsaWNlKDIpKTtcbiAgICAgICAgICB9IGVsc2Uge1xuICAgICAgICAgICAgLy8gYm9vbGVhbiBvcHRpb24sIGVtaXQgYW5kIHB1dCBiYWNrIHJlbWFpbmRlciBvZiBhcmcgZm9yIGZ1cnRoZXIgcHJvY2Vzc2luZ1xuICAgICAgICAgICAgdGhpcy5lbWl0KGBvcHRpb246JHtvcHRpb24ubmFtZSgpfWApO1xuICAgICAgICAgICAgYXJncy51bnNoaWZ0KGAtJHthcmcuc2xpY2UoMil9YCk7XG4gICAgICAgICAgfVxuICAgICAgICAgIGNvbnRpbnVlO1xuICAgICAgICB9XG4gICAgICB9XG5cbiAgICAgIC8vIExvb2sgZm9yIGtub3duIGxvbmcgZmxhZyB3aXRoIHZhbHVlLCBsaWtlIC0tZm9vPWJhclxuICAgICAgaWYgKC9eLS1bXj1dKz0vLnRlc3QoYXJnKSkge1xuICAgICAgICBjb25zdCBpbmRleCA9IGFyZy5pbmRleE9mKCc9Jyk7XG4gICAgICAgIGNvbnN0IG9wdGlvbiA9IHRoaXMuX2ZpbmRPcHRpb24oYXJnLnNsaWNlKDAsIGluZGV4KSk7XG4gICAgICAgIGlmIChvcHRpb24gJiYgKG9wdGlvbi5yZXF1aXJlZCB8fCBvcHRpb24ub3B0aW9uYWwpKSB7XG4gICAgICAgICAgdGhpcy5lbWl0KGBvcHRpb246JHtvcHRpb24ubmFtZSgpfWAsIGFyZy5zbGljZShpbmRleCArIDEpKTtcbiAgICAgICAgICBjb250aW51ZTtcbiAgICAgICAgfVxuICAgICAgfVxuXG4gICAgICAvLyBOb3QgYSByZWNvZ25pc2VkIG9wdGlvbiBieSB0aGlzIGNvbW1hbmQuXG4gICAgICAvLyBNaWdodCBiZSBhIGNvbW1hbmQtYXJndW1lbnQsIG9yIHN1YmNvbW1hbmQgb3B0aW9uLCBvciB1bmtub3duIG9wdGlvbiwgb3IgaGVscCBjb21tYW5kIG9yIG9wdGlvbi5cblxuICAgICAgLy8gQW4gdW5rbm93biBvcHRpb24gbWVhbnMgZnVydGhlciBhcmd1bWVudHMgYWxzbyBjbGFzc2lmaWVkIGFzIHVua25vd24gc28gY2FuIGJlIHJlcHJvY2Vzc2VkIGJ5IHN1YmNvbW1hbmRzLlxuICAgICAgaWYgKG1heWJlT3B0aW9uKGFyZykpIHtcbiAgICAgICAgZGVzdCA9IHVua25vd247XG4gICAgICB9XG5cbiAgICAgIC8vIElmIHVzaW5nIHBvc2l0aW9uYWxPcHRpb25zLCBzdG9wIHByb2Nlc3Npbmcgb3VyIG9wdGlvbnMgYXQgc3ViY29tbWFuZC5cbiAgICAgIGlmICgodGhpcy5fZW5hYmxlUG9zaXRpb25hbE9wdGlvbnMgfHwgdGhpcy5fcGFzc1Rocm91Z2hPcHRpb25zKSAmJiBvcGVyYW5kcy5sZW5ndGggPT09IDAgJiYgdW5rbm93bi5sZW5ndGggPT09IDApIHtcbiAgICAgICAgaWYgKHRoaXMuX2ZpbmRDb21tYW5kKGFyZykpIHtcbiAgICAgICAgICBvcGVyYW5kcy5wdXNoKGFyZyk7XG4gICAgICAgICAgaWYgKGFyZ3MubGVuZ3RoID4gMCkgdW5rbm93bi5wdXNoKC4uLmFyZ3MpO1xuICAgICAgICAgIGJyZWFrO1xuICAgICAgICB9IGVsc2UgaWYgKGFyZyA9PT0gdGhpcy5faGVscENvbW1hbmROYW1lICYmIHRoaXMuX2hhc0ltcGxpY2l0SGVscENvbW1hbmQoKSkge1xuICAgICAgICAgIG9wZXJhbmRzLnB1c2goYXJnKTtcbiAgICAgICAgICBpZiAoYXJncy5sZW5ndGggPiAwKSBvcGVyYW5kcy5wdXNoKC4uLmFyZ3MpO1xuICAgICAgICAgIGJyZWFrO1xuICAgICAgICB9IGVsc2UgaWYgKHRoaXMuX2RlZmF1bHRDb21tYW5kTmFtZSkge1xuICAgICAgICAgIHVua25vd24ucHVzaChhcmcpO1xuICAgICAgICAgIGlmIChhcmdzLmxlbmd0aCA+IDApIHVua25vd24ucHVzaCguLi5hcmdzKTtcbiAgICAgICAgICBicmVhaztcbiAgICAgICAgfVxuICAgICAgfVxuXG4gICAgICAvLyBJZiB1c2luZyBwYXNzVGhyb3VnaE9wdGlvbnMsIHN0b3AgcHJvY2Vzc2luZyBvcHRpb25zIGF0IGZpcnN0IGNvbW1hbmQtYXJndW1lbnQuXG4gICAgICBpZiAodGhpcy5fcGFzc1Rocm91Z2hPcHRpb25zKSB7XG4gICAgICAgIGRlc3QucHVzaChhcmcpO1xuICAgICAgICBpZiAoYXJncy5sZW5ndGggPiAwKSBkZXN0LnB1c2goLi4uYXJncyk7XG4gICAgICAgIGJyZWFrO1xuICAgICAgfVxuXG4gICAgICAvLyBhZGQgYXJnXG4gICAgICBkZXN0LnB1c2goYXJnKTtcbiAgICB9XG5cbiAgICByZXR1cm4geyBvcGVyYW5kcywgdW5rbm93biB9O1xuICB9XG5cbiAgLyoqXG4gICAqIFJldHVybiBhbiBvYmplY3QgY29udGFpbmluZyBsb2NhbCBvcHRpb24gdmFsdWVzIGFzIGtleS12YWx1ZSBwYWlycy5cbiAgICpcbiAgICogQHJldHVybiB7T2JqZWN0fVxuICAgKi9cbiAgb3B0cygpIHtcbiAgICBpZiAodGhpcy5fc3RvcmVPcHRpb25zQXNQcm9wZXJ0aWVzKSB7XG4gICAgICAvLyBQcmVzZXJ2ZSBvcmlnaW5hbCBiZWhhdmlvdXIgc28gYmFja3dhcmRzIGNvbXBhdGlibGUgd2hlbiBzdGlsbCB1c2luZyBwcm9wZXJ0aWVzXG4gICAgICBjb25zdCByZXN1bHQgPSB7fTtcbiAgICAgIGNvbnN0IGxlbiA9IHRoaXMub3B0aW9ucy5sZW5ndGg7XG5cbiAgICAgIGZvciAobGV0IGkgPSAwOyBpIDwgbGVuOyBpKyspIHtcbiAgICAgICAgY29uc3Qga2V5ID0gdGhpcy5vcHRpb25zW2ldLmF0dHJpYnV0ZU5hbWUoKTtcbiAgICAgICAgcmVzdWx0W2tleV0gPSBrZXkgPT09IHRoaXMuX3ZlcnNpb25PcHRpb25OYW1lID8gdGhpcy5fdmVyc2lvbiA6IHRoaXNba2V5XTtcbiAgICAgIH1cbiAgICAgIHJldHVybiByZXN1bHQ7XG4gICAgfVxuXG4gICAgcmV0dXJuIHRoaXMuX29wdGlvblZhbHVlcztcbiAgfVxuXG4gIC8qKlxuICAgKiBSZXR1cm4gYW4gb2JqZWN0IGNvbnRhaW5pbmcgbWVyZ2VkIGxvY2FsIGFuZCBnbG9iYWwgb3B0aW9uIHZhbHVlcyBhcyBrZXktdmFsdWUgcGFpcnMuXG4gICAqXG4gICAqIEByZXR1cm4ge09iamVjdH1cbiAgICovXG4gIG9wdHNXaXRoR2xvYmFscygpIHtcbiAgICAvLyBnbG9iYWxzIG92ZXJ3cml0ZSBsb2NhbHNcbiAgICByZXR1cm4gZ2V0Q29tbWFuZEFuZFBhcmVudHModGhpcykucmVkdWNlKFxuICAgICAgKGNvbWJpbmVkT3B0aW9ucywgY21kKSA9PiBPYmplY3QuYXNzaWduKGNvbWJpbmVkT3B0aW9ucywgY21kLm9wdHMoKSksXG4gICAgICB7fVxuICAgICk7XG4gIH1cblxuICAvKipcbiAgICogRGlzcGxheSBlcnJvciBtZXNzYWdlIGFuZCBleGl0IChvciBjYWxsIGV4aXRPdmVycmlkZSkuXG4gICAqXG4gICAqIEBwYXJhbSB7c3RyaW5nfSBtZXNzYWdlXG4gICAqIEBwYXJhbSB7T2JqZWN0fSBbZXJyb3JPcHRpb25zXVxuICAgKiBAcGFyYW0ge3N0cmluZ30gW2Vycm9yT3B0aW9ucy5jb2RlXSAtIGFuIGlkIHN0cmluZyByZXByZXNlbnRpbmcgdGhlIGVycm9yXG4gICAqIEBwYXJhbSB7bnVtYmVyfSBbZXJyb3JPcHRpb25zLmV4aXRDb2RlXSAtIHVzZWQgd2l0aCBwcm9jZXNzLmV4aXRcbiAgICovXG4gIGVycm9yKG1lc3NhZ2UsIGVycm9yT3B0aW9ucykge1xuICAgIC8vIG91dHB1dCBoYW5kbGluZ1xuICAgIHRoaXMuX291dHB1dENvbmZpZ3VyYXRpb24ub3V0cHV0RXJyb3IoYCR7bWVzc2FnZX1cXG5gLCB0aGlzLl9vdXRwdXRDb25maWd1cmF0aW9uLndyaXRlRXJyKTtcbiAgICBpZiAodHlwZW9mIHRoaXMuX3Nob3dIZWxwQWZ0ZXJFcnJvciA9PT0gJ3N0cmluZycpIHtcbiAgICAgIHRoaXMuX291dHB1dENvbmZpZ3VyYXRpb24ud3JpdGVFcnIoYCR7dGhpcy5fc2hvd0hlbHBBZnRlckVycm9yfVxcbmApO1xuICAgIH0gZWxzZSBpZiAodGhpcy5fc2hvd0hlbHBBZnRlckVycm9yKSB7XG4gICAgICB0aGlzLl9vdXRwdXRDb25maWd1cmF0aW9uLndyaXRlRXJyKCdcXG4nKTtcbiAgICAgIHRoaXMub3V0cHV0SGVscCh7IGVycm9yOiB0cnVlIH0pO1xuICAgIH1cblxuICAgIC8vIGV4aXQgaGFuZGxpbmdcbiAgICBjb25zdCBjb25maWcgPSBlcnJvck9wdGlvbnMgfHwge307XG4gICAgY29uc3QgZXhpdENvZGUgPSBjb25maWcuZXhpdENvZGUgfHwgMTtcbiAgICBjb25zdCBjb2RlID0gY29uZmlnLmNvZGUgfHwgJ2NvbW1hbmRlci5lcnJvcic7XG4gICAgdGhpcy5fZXhpdChleGl0Q29kZSwgY29kZSwgbWVzc2FnZSk7XG4gIH1cblxuICAvKipcbiAgICogQXBwbHkgYW55IG9wdGlvbiByZWxhdGVkIGVudmlyb25tZW50IHZhcmlhYmxlcywgaWYgb3B0aW9uIGRvZXNcbiAgICogbm90IGhhdmUgYSB2YWx1ZSBmcm9tIGNsaSBvciBjbGllbnQgY29kZS5cbiAgICpcbiAgICogQGFwaSBwcml2YXRlXG4gICAqL1xuICBfcGFyc2VPcHRpb25zRW52KCkge1xuICAgIHRoaXMub3B0aW9ucy5mb3JFYWNoKChvcHRpb24pID0+IHtcbiAgICAgIGlmIChvcHRpb24uZW52VmFyICYmIG9wdGlvbi5lbnZWYXIgaW4gcHJvY2Vzcy5lbnYpIHtcbiAgICAgICAgY29uc3Qgb3B0aW9uS2V5ID0gb3B0aW9uLmF0dHJpYnV0ZU5hbWUoKTtcbiAgICAgICAgLy8gUHJpb3JpdHkgY2hlY2suIERvIG5vdCBvdmVyd3JpdGUgY2xpIG9yIG9wdGlvbnMgZnJvbSB1bmtub3duIHNvdXJjZSAoY2xpZW50LWNvZGUpLlxuICAgICAgICBpZiAodGhpcy5nZXRPcHRpb25WYWx1ZShvcHRpb25LZXkpID09PSB1bmRlZmluZWQgfHwgWydkZWZhdWx0JywgJ2NvbmZpZycsICdlbnYnXS5pbmNsdWRlcyh0aGlzLmdldE9wdGlvblZhbHVlU291cmNlKG9wdGlvbktleSkpKSB7XG4gICAgICAgICAgaWYgKG9wdGlvbi5yZXF1aXJlZCB8fCBvcHRpb24ub3B0aW9uYWwpIHsgLy8gb3B0aW9uIGNhbiB0YWtlIGEgdmFsdWVcbiAgICAgICAgICAgIC8vIGtlZXAgdmVyeSBzaW1wbGUsIG9wdGlvbmFsIGFsd2F5cyB0YWtlcyB2YWx1ZVxuICAgICAgICAgICAgdGhpcy5lbWl0KGBvcHRpb25FbnY6JHtvcHRpb24ubmFtZSgpfWAsIHByb2Nlc3MuZW52W29wdGlvbi5lbnZWYXJdKTtcbiAgICAgICAgICB9IGVsc2UgeyAvLyBib29sZWFuXG4gICAgICAgICAgICAvLyBrZWVwIHZlcnkgc2ltcGxlLCBvbmx5IGNhcmUgdGhhdCBlbnZWYXIgZGVmaW5lZCBhbmQgbm90IHRoZSB2YWx1ZVxuICAgICAgICAgICAgdGhpcy5lbWl0KGBvcHRpb25FbnY6JHtvcHRpb24ubmFtZSgpfWApO1xuICAgICAgICAgIH1cbiAgICAgICAgfVxuICAgICAgfVxuICAgIH0pO1xuICB9XG5cbiAgLyoqXG4gICAqIEFwcGx5IGFueSBpbXBsaWVkIG9wdGlvbiB2YWx1ZXMsIGlmIG9wdGlvbiBpcyB1bmRlZmluZWQgb3IgZGVmYXVsdCB2YWx1ZS5cbiAgICpcbiAgICogQGFwaSBwcml2YXRlXG4gICAqL1xuICBfcGFyc2VPcHRpb25zSW1wbGllZCgpIHtcbiAgICBjb25zdCBkdWFsSGVscGVyID0gbmV3IER1YWxPcHRpb25zKHRoaXMub3B0aW9ucyk7XG4gICAgY29uc3QgaGFzQ3VzdG9tT3B0aW9uVmFsdWUgPSAob3B0aW9uS2V5KSA9PiB7XG4gICAgICByZXR1cm4gdGhpcy5nZXRPcHRpb25WYWx1ZShvcHRpb25LZXkpICE9PSB1bmRlZmluZWQgJiYgIVsnZGVmYXVsdCcsICdpbXBsaWVkJ10uaW5jbHVkZXModGhpcy5nZXRPcHRpb25WYWx1ZVNvdXJjZShvcHRpb25LZXkpKTtcbiAgICB9O1xuICAgIHRoaXMub3B0aW9uc1xuICAgICAgLmZpbHRlcihvcHRpb24gPT4gKG9wdGlvbi5pbXBsaWVkICE9PSB1bmRlZmluZWQpICYmXG4gICAgICAgIGhhc0N1c3RvbU9wdGlvblZhbHVlKG9wdGlvbi5hdHRyaWJ1dGVOYW1lKCkpICYmXG4gICAgICAgIGR1YWxIZWxwZXIudmFsdWVGcm9tT3B0aW9uKHRoaXMuZ2V0T3B0aW9uVmFsdWUob3B0aW9uLmF0dHJpYnV0ZU5hbWUoKSksIG9wdGlvbikpXG4gICAgICAuZm9yRWFjaCgob3B0aW9uKSA9PiB7XG4gICAgICAgIE9iamVjdC5rZXlzKG9wdGlvbi5pbXBsaWVkKVxuICAgICAgICAgIC5maWx0ZXIoaW1wbGllZEtleSA9PiAhaGFzQ3VzdG9tT3B0aW9uVmFsdWUoaW1wbGllZEtleSkpXG4gICAgICAgICAgLmZvckVhY2goaW1wbGllZEtleSA9PiB7XG4gICAgICAgICAgICB0aGlzLnNldE9wdGlvblZhbHVlV2l0aFNvdXJjZShpbXBsaWVkS2V5LCBvcHRpb24uaW1wbGllZFtpbXBsaWVkS2V5XSwgJ2ltcGxpZWQnKTtcbiAgICAgICAgICB9KTtcbiAgICAgIH0pO1xuICB9XG5cbiAgLyoqXG4gICAqIEFyZ3VtZW50IGBuYW1lYCBpcyBtaXNzaW5nLlxuICAgKlxuICAgKiBAcGFyYW0ge3N0cmluZ30gbmFtZVxuICAgKiBAYXBpIHByaXZhdGVcbiAgICovXG5cbiAgbWlzc2luZ0FyZ3VtZW50KG5hbWUpIHtcbiAgICBjb25zdCBtZXNzYWdlID0gYGVycm9yOiBtaXNzaW5nIHJlcXVpcmVkIGFyZ3VtZW50ICcke25hbWV9J2A7XG4gICAgdGhpcy5lcnJvcihtZXNzYWdlLCB7IGNvZGU6ICdjb21tYW5kZXIubWlzc2luZ0FyZ3VtZW50JyB9KTtcbiAgfVxuXG4gIC8qKlxuICAgKiBgT3B0aW9uYCBpcyBtaXNzaW5nIGFuIGFyZ3VtZW50LlxuICAgKlxuICAgKiBAcGFyYW0ge09wdGlvbn0gb3B0aW9uXG4gICAqIEBhcGkgcHJpdmF0ZVxuICAgKi9cblxuICBvcHRpb25NaXNzaW5nQXJndW1lbnQob3B0aW9uKSB7XG4gICAgY29uc3QgbWVzc2FnZSA9IGBlcnJvcjogb3B0aW9uICcke29wdGlvbi5mbGFnc30nIGFyZ3VtZW50IG1pc3NpbmdgO1xuICAgIHRoaXMuZXJyb3IobWVzc2FnZSwgeyBjb2RlOiAnY29tbWFuZGVyLm9wdGlvbk1pc3NpbmdBcmd1bWVudCcgfSk7XG4gIH1cblxuICAvKipcbiAgICogYE9wdGlvbmAgZG9lcyBub3QgaGF2ZSBhIHZhbHVlLCBhbmQgaXMgYSBtYW5kYXRvcnkgb3B0aW9uLlxuICAgKlxuICAgKiBAcGFyYW0ge09wdGlvbn0gb3B0aW9uXG4gICAqIEBhcGkgcHJpdmF0ZVxuICAgKi9cblxuICBtaXNzaW5nTWFuZGF0b3J5T3B0aW9uVmFsdWUob3B0aW9uKSB7XG4gICAgY29uc3QgbWVzc2FnZSA9IGBlcnJvcjogcmVxdWlyZWQgb3B0aW9uICcke29wdGlvbi5mbGFnc30nIG5vdCBzcGVjaWZpZWRgO1xuICAgIHRoaXMuZXJyb3IobWVzc2FnZSwgeyBjb2RlOiAnY29tbWFuZGVyLm1pc3NpbmdNYW5kYXRvcnlPcHRpb25WYWx1ZScgfSk7XG4gIH1cblxuICAvKipcbiAgICogYE9wdGlvbmAgY29uZmxpY3RzIHdpdGggYW5vdGhlciBvcHRpb24uXG4gICAqXG4gICAqIEBwYXJhbSB7T3B0aW9ufSBvcHRpb25cbiAgICogQHBhcmFtIHtPcHRpb259IGNvbmZsaWN0aW5nT3B0aW9uXG4gICAqIEBhcGkgcHJpdmF0ZVxuICAgKi9cbiAgX2NvbmZsaWN0aW5nT3B0aW9uKG9wdGlvbiwgY29uZmxpY3RpbmdPcHRpb24pIHtcbiAgICAvLyBUaGUgY2FsbGluZyBjb2RlIGRvZXMgbm90IGtub3cgd2hldGhlciBhIG5lZ2F0ZWQgb3B0aW9uIGlzIHRoZSBzb3VyY2Ugb2YgdGhlXG4gICAgLy8gdmFsdWUsIHNvIGRvIHNvbWUgd29yayB0byB0YWtlIGFuIGVkdWNhdGVkIGd1ZXNzLlxuICAgIGNvbnN0IGZpbmRCZXN0T3B0aW9uRnJvbVZhbHVlID0gKG9wdGlvbikgPT4ge1xuICAgICAgY29uc3Qgb3B0aW9uS2V5ID0gb3B0aW9uLmF0dHJpYnV0ZU5hbWUoKTtcbiAgICAgIGNvbnN0IG9wdGlvblZhbHVlID0gdGhpcy5nZXRPcHRpb25WYWx1ZShvcHRpb25LZXkpO1xuICAgICAgY29uc3QgbmVnYXRpdmVPcHRpb24gPSB0aGlzLm9wdGlvbnMuZmluZCh0YXJnZXQgPT4gdGFyZ2V0Lm5lZ2F0ZSAmJiBvcHRpb25LZXkgPT09IHRhcmdldC5hdHRyaWJ1dGVOYW1lKCkpO1xuICAgICAgY29uc3QgcG9zaXRpdmVPcHRpb24gPSB0aGlzLm9wdGlvbnMuZmluZCh0YXJnZXQgPT4gIXRhcmdldC5uZWdhdGUgJiYgb3B0aW9uS2V5ID09PSB0YXJnZXQuYXR0cmlidXRlTmFtZSgpKTtcbiAgICAgIGlmIChuZWdhdGl2ZU9wdGlvbiAmJiAoXG4gICAgICAgIChuZWdhdGl2ZU9wdGlvbi5wcmVzZXRBcmcgPT09IHVuZGVmaW5lZCAmJiBvcHRpb25WYWx1ZSA9PT0gZmFsc2UpIHx8XG4gICAgICAgIChuZWdhdGl2ZU9wdGlvbi5wcmVzZXRBcmcgIT09IHVuZGVmaW5lZCAmJiBvcHRpb25WYWx1ZSA9PT0gbmVnYXRpdmVPcHRpb24ucHJlc2V0QXJnKVxuICAgICAgKSkge1xuICAgICAgICByZXR1cm4gbmVnYXRpdmVPcHRpb247XG4gICAgICB9XG4gICAgICByZXR1cm4gcG9zaXRpdmVPcHRpb24gfHwgb3B0aW9uO1xuICAgIH07XG5cbiAgICBjb25zdCBnZXRFcnJvck1lc3NhZ2UgPSAob3B0aW9uKSA9PiB7XG4gICAgICBjb25zdCBiZXN0T3B0aW9uID0gZmluZEJlc3RPcHRpb25Gcm9tVmFsdWUob3B0aW9uKTtcbiAgICAgIGNvbnN0IG9wdGlvbktleSA9IGJlc3RPcHRpb24uYXR0cmlidXRlTmFtZSgpO1xuICAgICAgY29uc3Qgc291cmNlID0gdGhpcy5nZXRPcHRpb25WYWx1ZVNvdXJjZShvcHRpb25LZXkpO1xuICAgICAgaWYgKHNvdXJjZSA9PT0gJ2VudicpIHtcbiAgICAgICAgcmV0dXJuIGBlbnZpcm9ubWVudCB2YXJpYWJsZSAnJHtiZXN0T3B0aW9uLmVudlZhcn0nYDtcbiAgICAgIH1cbiAgICAgIHJldHVybiBgb3B0aW9uICcke2Jlc3RPcHRpb24uZmxhZ3N9J2A7XG4gICAgfTtcblxuICAgIGNvbnN0IG1lc3NhZ2UgPSBgZXJyb3I6ICR7Z2V0RXJyb3JNZXNzYWdlKG9wdGlvbil9IGNhbm5vdCBiZSB1c2VkIHdpdGggJHtnZXRFcnJvck1lc3NhZ2UoY29uZmxpY3RpbmdPcHRpb24pfWA7XG4gICAgdGhpcy5lcnJvcihtZXNzYWdlLCB7IGNvZGU6ICdjb21tYW5kZXIuY29uZmxpY3RpbmdPcHRpb24nIH0pO1xuICB9XG5cbiAgLyoqXG4gICAqIFVua25vd24gb3B0aW9uIGBmbGFnYC5cbiAgICpcbiAgICogQHBhcmFtIHtzdHJpbmd9IGZsYWdcbiAgICogQGFwaSBwcml2YXRlXG4gICAqL1xuXG4gIHVua25vd25PcHRpb24oZmxhZykge1xuICAgIGlmICh0aGlzLl9hbGxvd1Vua25vd25PcHRpb24pIHJldHVybjtcbiAgICBsZXQgc3VnZ2VzdGlvbiA9ICcnO1xuXG4gICAgaWYgKGZsYWcuc3RhcnRzV2l0aCgnLS0nKSAmJiB0aGlzLl9zaG93U3VnZ2VzdGlvbkFmdGVyRXJyb3IpIHtcbiAgICAgIC8vIExvb3BpbmcgdG8gcGljayB1cCB0aGUgZ2xvYmFsIG9wdGlvbnMgdG9vXG4gICAgICBsZXQgY2FuZGlkYXRlRmxhZ3MgPSBbXTtcbiAgICAgIGxldCBjb21tYW5kID0gdGhpcztcbiAgICAgIGRvIHtcbiAgICAgICAgY29uc3QgbW9yZUZsYWdzID0gY29tbWFuZC5jcmVhdGVIZWxwKCkudmlzaWJsZU9wdGlvbnMoY29tbWFuZClcbiAgICAgICAgICAuZmlsdGVyKG9wdGlvbiA9PiBvcHRpb24ubG9uZylcbiAgICAgICAgICAubWFwKG9wdGlvbiA9PiBvcHRpb24ubG9uZyk7XG4gICAgICAgIGNhbmRpZGF0ZUZsYWdzID0gY2FuZGlkYXRlRmxhZ3MuY29uY2F0KG1vcmVGbGFncyk7XG4gICAgICAgIGNvbW1hbmQgPSBjb21tYW5kLnBhcmVudDtcbiAgICAgIH0gd2hpbGUgKGNvbW1hbmQgJiYgIWNvbW1hbmQuX2VuYWJsZVBvc2l0aW9uYWxPcHRpb25zKTtcbiAgICAgIHN1Z2dlc3Rpb24gPSBzdWdnZXN0U2ltaWxhcihmbGFnLCBjYW5kaWRhdGVGbGFncyk7XG4gICAgfVxuXG4gICAgY29uc3QgbWVzc2FnZSA9IGBlcnJvcjogdW5rbm93biBvcHRpb24gJyR7ZmxhZ30nJHtzdWdnZXN0aW9ufWA7XG4gICAgdGhpcy5lcnJvcihtZXNzYWdlLCB7IGNvZGU6ICdjb21tYW5kZXIudW5rbm93bk9wdGlvbicgfSk7XG4gIH1cblxuICAvKipcbiAgICogRXhjZXNzIGFyZ3VtZW50cywgbW9yZSB0aGFuIGV4cGVjdGVkLlxuICAgKlxuICAgKiBAcGFyYW0ge3N0cmluZ1tdfSByZWNlaXZlZEFyZ3NcbiAgICogQGFwaSBwcml2YXRlXG4gICAqL1xuXG4gIF9leGNlc3NBcmd1bWVudHMocmVjZWl2ZWRBcmdzKSB7XG4gICAgaWYgKHRoaXMuX2FsbG93RXhjZXNzQXJndW1lbnRzKSByZXR1cm47XG5cbiAgICBjb25zdCBleHBlY3RlZCA9IHRoaXMuX2FyZ3MubGVuZ3RoO1xuICAgIGNvbnN0IHMgPSAoZXhwZWN0ZWQgPT09IDEpID8gJycgOiAncyc7XG4gICAgY29uc3QgZm9yU3ViY29tbWFuZCA9IHRoaXMucGFyZW50ID8gYCBmb3IgJyR7dGhpcy5uYW1lKCl9J2AgOiAnJztcbiAgICBjb25zdCBtZXNzYWdlID0gYGVycm9yOiB0b28gbWFueSBhcmd1bWVudHMke2ZvclN1YmNvbW1hbmR9LiBFeHBlY3RlZCAke2V4cGVjdGVkfSBhcmd1bWVudCR7c30gYnV0IGdvdCAke3JlY2VpdmVkQXJncy5sZW5ndGh9LmA7XG4gICAgdGhpcy5lcnJvcihtZXNzYWdlLCB7IGNvZGU6ICdjb21tYW5kZXIuZXhjZXNzQXJndW1lbnRzJyB9KTtcbiAgfVxuXG4gIC8qKlxuICAgKiBVbmtub3duIGNvbW1hbmQuXG4gICAqXG4gICAqIEBhcGkgcHJpdmF0ZVxuICAgKi9cblxuICB1bmtub3duQ29tbWFuZCgpIHtcbiAgICBjb25zdCB1bmtub3duTmFtZSA9IHRoaXMuYXJnc1swXTtcbiAgICBsZXQgc3VnZ2VzdGlvbiA9ICcnO1xuXG4gICAgaWYgKHRoaXMuX3Nob3dTdWdnZXN0aW9uQWZ0ZXJFcnJvcikge1xuICAgICAgY29uc3QgY2FuZGlkYXRlTmFtZXMgPSBbXTtcbiAgICAgIHRoaXMuY3JlYXRlSGVscCgpLnZpc2libGVDb21tYW5kcyh0aGlzKS5mb3JFYWNoKChjb21tYW5kKSA9PiB7XG4gICAgICAgIGNhbmRpZGF0ZU5hbWVzLnB1c2goY29tbWFuZC5uYW1lKCkpO1xuICAgICAgICAvLyBqdXN0IHZpc2libGUgYWxpYXNcbiAgICAgICAgaWYgKGNvbW1hbmQuYWxpYXMoKSkgY2FuZGlkYXRlTmFtZXMucHVzaChjb21tYW5kLmFsaWFzKCkpO1xuICAgICAgfSk7XG4gICAgICBzdWdnZXN0aW9uID0gc3VnZ2VzdFNpbWlsYXIodW5rbm93bk5hbWUsIGNhbmRpZGF0ZU5hbWVzKTtcbiAgICB9XG5cbiAgICBjb25zdCBtZXNzYWdlID0gYGVycm9yOiB1bmtub3duIGNvbW1hbmQgJyR7dW5rbm93bk5hbWV9JyR7c3VnZ2VzdGlvbn1gO1xuICAgIHRoaXMuZXJyb3IobWVzc2FnZSwgeyBjb2RlOiAnY29tbWFuZGVyLnVua25vd25Db21tYW5kJyB9KTtcbiAgfVxuXG4gIC8qKlxuICAgKiBTZXQgdGhlIHByb2dyYW0gdmVyc2lvbiB0byBgc3RyYC5cbiAgICpcbiAgICogVGhpcyBtZXRob2QgYXV0by1yZWdpc3RlcnMgdGhlIFwiLVYsIC0tdmVyc2lvblwiIGZsYWdcbiAgICogd2hpY2ggd2lsbCBwcmludCB0aGUgdmVyc2lvbiBudW1iZXIgd2hlbiBwYXNzZWQuXG4gICAqXG4gICAqIFlvdSBjYW4gb3B0aW9uYWxseSBzdXBwbHkgdGhlICBmbGFncyBhbmQgZGVzY3JpcHRpb24gdG8gb3ZlcnJpZGUgdGhlIGRlZmF1bHRzLlxuICAgKlxuICAgKiBAcGFyYW0ge3N0cmluZ30gc3RyXG4gICAqIEBwYXJhbSB7c3RyaW5nfSBbZmxhZ3NdXG4gICAqIEBwYXJhbSB7c3RyaW5nfSBbZGVzY3JpcHRpb25dXG4gICAqIEByZXR1cm4ge3RoaXMgfCBzdHJpbmd9IGB0aGlzYCBjb21tYW5kIGZvciBjaGFpbmluZywgb3IgdmVyc2lvbiBzdHJpbmcgaWYgbm8gYXJndW1lbnRzXG4gICAqL1xuXG4gIHZlcnNpb24oc3RyLCBmbGFncywgZGVzY3JpcHRpb24pIHtcbiAgICBpZiAoc3RyID09PSB1bmRlZmluZWQpIHJldHVybiB0aGlzLl92ZXJzaW9uO1xuICAgIHRoaXMuX3ZlcnNpb24gPSBzdHI7XG4gICAgZmxhZ3MgPSBmbGFncyB8fCAnLVYsIC0tdmVyc2lvbic7XG4gICAgZGVzY3JpcHRpb24gPSBkZXNjcmlwdGlvbiB8fCAnb3V0cHV0IHRoZSB2ZXJzaW9uIG51bWJlcic7XG4gICAgY29uc3QgdmVyc2lvbk9wdGlvbiA9IHRoaXMuY3JlYXRlT3B0aW9uKGZsYWdzLCBkZXNjcmlwdGlvbik7XG4gICAgdGhpcy5fdmVyc2lvbk9wdGlvbk5hbWUgPSB2ZXJzaW9uT3B0aW9uLmF0dHJpYnV0ZU5hbWUoKTtcbiAgICB0aGlzLm9wdGlvbnMucHVzaCh2ZXJzaW9uT3B0aW9uKTtcbiAgICB0aGlzLm9uKCdvcHRpb246JyArIHZlcnNpb25PcHRpb24ubmFtZSgpLCAoKSA9PiB7XG4gICAgICB0aGlzLl9vdXRwdXRDb25maWd1cmF0aW9uLndyaXRlT3V0KGAke3N0cn1cXG5gKTtcbiAgICAgIHRoaXMuX2V4aXQoMCwgJ2NvbW1hbmRlci52ZXJzaW9uJywgc3RyKTtcbiAgICB9KTtcbiAgICByZXR1cm4gdGhpcztcbiAgfVxuXG4gIC8qKlxuICAgKiBTZXQgdGhlIGRlc2NyaXB0aW9uLlxuICAgKlxuICAgKiBAcGFyYW0ge3N0cmluZ30gW3N0cl1cbiAgICogQHBhcmFtIHtPYmplY3R9IFthcmdzRGVzY3JpcHRpb25dXG4gICAqIEByZXR1cm4ge3N0cmluZ3xDb21tYW5kfVxuICAgKi9cbiAgZGVzY3JpcHRpb24oc3RyLCBhcmdzRGVzY3JpcHRpb24pIHtcbiAgICBpZiAoc3RyID09PSB1bmRlZmluZWQgJiYgYXJnc0Rlc2NyaXB0aW9uID09PSB1bmRlZmluZWQpIHJldHVybiB0aGlzLl9kZXNjcmlwdGlvbjtcbiAgICB0aGlzLl9kZXNjcmlwdGlvbiA9IHN0cjtcbiAgICBpZiAoYXJnc0Rlc2NyaXB0aW9uKSB7XG4gICAgICB0aGlzLl9hcmdzRGVzY3JpcHRpb24gPSBhcmdzRGVzY3JpcHRpb247XG4gICAgfVxuICAgIHJldHVybiB0aGlzO1xuICB9XG5cbiAgLyoqXG4gICAqIFNldCB0aGUgc3VtbWFyeS4gVXNlZCB3aGVuIGxpc3RlZCBhcyBzdWJjb21tYW5kIG9mIHBhcmVudC5cbiAgICpcbiAgICogQHBhcmFtIHtzdHJpbmd9IFtzdHJdXG4gICAqIEByZXR1cm4ge3N0cmluZ3xDb21tYW5kfVxuICAgKi9cbiAgc3VtbWFyeShzdHIpIHtcbiAgICBpZiAoc3RyID09PSB1bmRlZmluZWQpIHJldHVybiB0aGlzLl9zdW1tYXJ5O1xuICAgIHRoaXMuX3N1bW1hcnkgPSBzdHI7XG4gICAgcmV0dXJuIHRoaXM7XG4gIH1cblxuICAvKipcbiAgICogU2V0IGFuIGFsaWFzIGZvciB0aGUgY29tbWFuZC5cbiAgICpcbiAgICogWW91IG1heSBjYWxsIG1vcmUgdGhhbiBvbmNlIHRvIGFkZCBtdWx0aXBsZSBhbGlhc2VzLiBPbmx5IHRoZSBmaXJzdCBhbGlhcyBpcyBzaG93biBpbiB0aGUgYXV0by1nZW5lcmF0ZWQgaGVscC5cbiAgICpcbiAgICogQHBhcmFtIHtzdHJpbmd9IFthbGlhc11cbiAgICogQHJldHVybiB7c3RyaW5nfENvbW1hbmR9XG4gICAqL1xuXG4gIGFsaWFzKGFsaWFzKSB7XG4gICAgaWYgKGFsaWFzID09PSB1bmRlZmluZWQpIHJldHVybiB0aGlzLl9hbGlhc2VzWzBdOyAvLyBqdXN0IHJldHVybiBmaXJzdCwgZm9yIGJhY2t3YXJkcyBjb21wYXRpYmlsaXR5XG5cbiAgICAvKiogQHR5cGUge0NvbW1hbmR9ICovXG4gICAgbGV0IGNvbW1hbmQgPSB0aGlzO1xuICAgIGlmICh0aGlzLmNvbW1hbmRzLmxlbmd0aCAhPT0gMCAmJiB0aGlzLmNvbW1hbmRzW3RoaXMuY29tbWFuZHMubGVuZ3RoIC0gMV0uX2V4ZWN1dGFibGVIYW5kbGVyKSB7XG4gICAgICAvLyBhc3N1bWUgYWRkaW5nIGFsaWFzIGZvciBsYXN0IGFkZGVkIGV4ZWN1dGFibGUgc3ViY29tbWFuZCwgcmF0aGVyIHRoYW4gdGhpc1xuICAgICAgY29tbWFuZCA9IHRoaXMuY29tbWFuZHNbdGhpcy5jb21tYW5kcy5sZW5ndGggLSAxXTtcbiAgICB9XG5cbiAgICBpZiAoYWxpYXMgPT09IGNvbW1hbmQuX25hbWUpIHRocm93IG5ldyBFcnJvcignQ29tbWFuZCBhbGlhcyBjYW5cXCd0IGJlIHRoZSBzYW1lIGFzIGl0cyBuYW1lJyk7XG5cbiAgICBjb21tYW5kLl9hbGlhc2VzLnB1c2goYWxpYXMpO1xuICAgIHJldHVybiB0aGlzO1xuICB9XG5cbiAgLyoqXG4gICAqIFNldCBhbGlhc2VzIGZvciB0aGUgY29tbWFuZC5cbiAgICpcbiAgICogT25seSB0aGUgZmlyc3QgYWxpYXMgaXMgc2hvd24gaW4gdGhlIGF1dG8tZ2VuZXJhdGVkIGhlbHAuXG4gICAqXG4gICAqIEBwYXJhbSB7c3RyaW5nW119IFthbGlhc2VzXVxuICAgKiBAcmV0dXJuIHtzdHJpbmdbXXxDb21tYW5kfVxuICAgKi9cblxuICBhbGlhc2VzKGFsaWFzZXMpIHtcbiAgICAvLyBHZXR0ZXIgZm9yIHRoZSBhcnJheSBvZiBhbGlhc2VzIGlzIHRoZSBtYWluIHJlYXNvbiBmb3IgaGF2aW5nIGFsaWFzZXMoKSBpbiBhZGRpdGlvbiB0byBhbGlhcygpLlxuICAgIGlmIChhbGlhc2VzID09PSB1bmRlZmluZWQpIHJldHVybiB0aGlzLl9hbGlhc2VzO1xuXG4gICAgYWxpYXNlcy5mb3JFYWNoKChhbGlhcykgPT4gdGhpcy5hbGlhcyhhbGlhcykpO1xuICAgIHJldHVybiB0aGlzO1xuICB9XG5cbiAgLyoqXG4gICAqIFNldCAvIGdldCB0aGUgY29tbWFuZCB1c2FnZSBgc3RyYC5cbiAgICpcbiAgICogQHBhcmFtIHtzdHJpbmd9IFtzdHJdXG4gICAqIEByZXR1cm4ge1N0cmluZ3xDb21tYW5kfVxuICAgKi9cblxuICB1c2FnZShzdHIpIHtcbiAgICBpZiAoc3RyID09PSB1bmRlZmluZWQpIHtcbiAgICAgIGlmICh0aGlzLl91c2FnZSkgcmV0dXJuIHRoaXMuX3VzYWdlO1xuXG4gICAgICBjb25zdCBhcmdzID0gdGhpcy5fYXJncy5tYXAoKGFyZykgPT4ge1xuICAgICAgICByZXR1cm4gaHVtYW5SZWFkYWJsZUFyZ05hbWUoYXJnKTtcbiAgICAgIH0pO1xuICAgICAgcmV0dXJuIFtdLmNvbmNhdChcbiAgICAgICAgKHRoaXMub3B0aW9ucy5sZW5ndGggfHwgdGhpcy5faGFzSGVscE9wdGlvbiA/ICdbb3B0aW9uc10nIDogW10pLFxuICAgICAgICAodGhpcy5jb21tYW5kcy5sZW5ndGggPyAnW2NvbW1hbmRdJyA6IFtdKSxcbiAgICAgICAgKHRoaXMuX2FyZ3MubGVuZ3RoID8gYXJncyA6IFtdKVxuICAgICAgKS5qb2luKCcgJyk7XG4gICAgfVxuXG4gICAgdGhpcy5fdXNhZ2UgPSBzdHI7XG4gICAgcmV0dXJuIHRoaXM7XG4gIH1cblxuICAvKipcbiAgICogR2V0IG9yIHNldCB0aGUgbmFtZSBvZiB0aGUgY29tbWFuZC5cbiAgICpcbiAgICogQHBhcmFtIHtzdHJpbmd9IFtzdHJdXG4gICAqIEByZXR1cm4ge3N0cmluZ3xDb21tYW5kfVxuICAgKi9cblxuICBuYW1lKHN0cikge1xuICAgIGlmIChzdHIgPT09IHVuZGVmaW5lZCkgcmV0dXJuIHRoaXMuX25hbWU7XG4gICAgdGhpcy5fbmFtZSA9IHN0cjtcbiAgICByZXR1cm4gdGhpcztcbiAgfVxuXG4gIC8qKlxuICAgKiBTZXQgdGhlIG5hbWUgb2YgdGhlIGNvbW1hbmQgZnJvbSBzY3JpcHQgZmlsZW5hbWUsIHN1Y2ggYXMgcHJvY2Vzcy5hcmd2WzFdLFxuICAgKiBvciByZXF1aXJlLm1haW4uZmlsZW5hbWUsIG9yIF9fZmlsZW5hbWUuXG4gICAqXG4gICAqIChVc2VkIGludGVybmFsbHkgYW5kIHB1YmxpYyBhbHRob3VnaCBub3QgZG9jdW1lbnRlZCBpbiBSRUFETUUuKVxuICAgKlxuICAgKiBAZXhhbXBsZVxuICAgKiBwcm9ncmFtLm5hbWVGcm9tRmlsZW5hbWUocmVxdWlyZS5tYWluLmZpbGVuYW1lKTtcbiAgICpcbiAgICogQHBhcmFtIHtzdHJpbmd9IGZpbGVuYW1lXG4gICAqIEByZXR1cm4ge0NvbW1hbmR9XG4gICAqL1xuXG4gIG5hbWVGcm9tRmlsZW5hbWUoZmlsZW5hbWUpIHtcbiAgICB0aGlzLl9uYW1lID0gcGF0aC5iYXNlbmFtZShmaWxlbmFtZSwgcGF0aC5leHRuYW1lKGZpbGVuYW1lKSk7XG5cbiAgICByZXR1cm4gdGhpcztcbiAgfVxuXG4gIC8qKlxuICAgKiBHZXQgb3Igc2V0IHRoZSBkaXJlY3RvcnkgZm9yIHNlYXJjaGluZyBmb3IgZXhlY3V0YWJsZSBzdWJjb21tYW5kcyBvZiB0aGlzIGNvbW1hbmQuXG4gICAqXG4gICAqIEBleGFtcGxlXG4gICAqIHByb2dyYW0uZXhlY3V0YWJsZURpcihfX2Rpcm5hbWUpO1xuICAgKiAvLyBvclxuICAgKiBwcm9ncmFtLmV4ZWN1dGFibGVEaXIoJ3N1YmNvbW1hbmRzJyk7XG4gICAqXG4gICAqIEBwYXJhbSB7c3RyaW5nfSBbcGF0aF1cbiAgICogQHJldHVybiB7c3RyaW5nfENvbW1hbmR9XG4gICAqL1xuXG4gIGV4ZWN1dGFibGVEaXIocGF0aCkge1xuICAgIGlmIChwYXRoID09PSB1bmRlZmluZWQpIHJldHVybiB0aGlzLl9leGVjdXRhYmxlRGlyO1xuICAgIHRoaXMuX2V4ZWN1dGFibGVEaXIgPSBwYXRoO1xuICAgIHJldHVybiB0aGlzO1xuICB9XG5cbiAgLyoqXG4gICAqIFJldHVybiBwcm9ncmFtIGhlbHAgZG9jdW1lbnRhdGlvbi5cbiAgICpcbiAgICogQHBhcmFtIHt7IGVycm9yOiBib29sZWFuIH19IFtjb250ZXh0T3B0aW9uc10gLSBwYXNzIHtlcnJvcjp0cnVlfSB0byB3cmFwIGZvciBzdGRlcnIgaW5zdGVhZCBvZiBzdGRvdXRcbiAgICogQHJldHVybiB7c3RyaW5nfVxuICAgKi9cblxuICBoZWxwSW5mb3JtYXRpb24oY29udGV4dE9wdGlvbnMpIHtcbiAgICBjb25zdCBoZWxwZXIgPSB0aGlzLmNyZWF0ZUhlbHAoKTtcbiAgICBpZiAoaGVscGVyLmhlbHBXaWR0aCA9PT0gdW5kZWZpbmVkKSB7XG4gICAgICBoZWxwZXIuaGVscFdpZHRoID0gKGNvbnRleHRPcHRpb25zICYmIGNvbnRleHRPcHRpb25zLmVycm9yKSA/IHRoaXMuX291dHB1dENvbmZpZ3VyYXRpb24uZ2V0RXJySGVscFdpZHRoKCkgOiB0aGlzLl9vdXRwdXRDb25maWd1cmF0aW9uLmdldE91dEhlbHBXaWR0aCgpO1xuICAgIH1cbiAgICByZXR1cm4gaGVscGVyLmZvcm1hdEhlbHAodGhpcywgaGVscGVyKTtcbiAgfVxuXG4gIC8qKlxuICAgKiBAYXBpIHByaXZhdGVcbiAgICovXG5cbiAgX2dldEhlbHBDb250ZXh0KGNvbnRleHRPcHRpb25zKSB7XG4gICAgY29udGV4dE9wdGlvbnMgPSBjb250ZXh0T3B0aW9ucyB8fCB7fTtcbiAgICBjb25zdCBjb250ZXh0ID0geyBlcnJvcjogISFjb250ZXh0T3B0aW9ucy5lcnJvciB9O1xuICAgIGxldCB3cml0ZTtcbiAgICBpZiAoY29udGV4dC5lcnJvcikge1xuICAgICAgd3JpdGUgPSAoYXJnKSA9PiB0aGlzLl9vdXRwdXRDb25maWd1cmF0aW9uLndyaXRlRXJyKGFyZyk7XG4gICAgfSBlbHNlIHtcbiAgICAgIHdyaXRlID0gKGFyZykgPT4gdGhpcy5fb3V0cHV0Q29uZmlndXJhdGlvbi53cml0ZU91dChhcmcpO1xuICAgIH1cbiAgICBjb250ZXh0LndyaXRlID0gY29udGV4dE9wdGlvbnMud3JpdGUgfHwgd3JpdGU7XG4gICAgY29udGV4dC5jb21tYW5kID0gdGhpcztcbiAgICByZXR1cm4gY29udGV4dDtcbiAgfVxuXG4gIC8qKlxuICAgKiBPdXRwdXQgaGVscCBpbmZvcm1hdGlvbiBmb3IgdGhpcyBjb21tYW5kLlxuICAgKlxuICAgKiBPdXRwdXRzIGJ1aWx0LWluIGhlbHAsIGFuZCBjdXN0b20gdGV4dCBhZGRlZCB1c2luZyBgLmFkZEhlbHBUZXh0KClgLlxuICAgKlxuICAgKiBAcGFyYW0ge3sgZXJyb3I6IGJvb2xlYW4gfSB8IEZ1bmN0aW9ufSBbY29udGV4dE9wdGlvbnNdIC0gcGFzcyB7ZXJyb3I6dHJ1ZX0gdG8gd3JpdGUgdG8gc3RkZXJyIGluc3RlYWQgb2Ygc3Rkb3V0XG4gICAqL1xuXG4gIG91dHB1dEhlbHAoY29udGV4dE9wdGlvbnMpIHtcbiAgICBsZXQgZGVwcmVjYXRlZENhbGxiYWNrO1xuICAgIGlmICh0eXBlb2YgY29udGV4dE9wdGlvbnMgPT09ICdmdW5jdGlvbicpIHtcbiAgICAgIGRlcHJlY2F0ZWRDYWxsYmFjayA9IGNvbnRleHRPcHRpb25zO1xuICAgICAgY29udGV4dE9wdGlvbnMgPSB1bmRlZmluZWQ7XG4gICAgfVxuICAgIGNvbnN0IGNvbnRleHQgPSB0aGlzLl9nZXRIZWxwQ29udGV4dChjb250ZXh0T3B0aW9ucyk7XG5cbiAgICBnZXRDb21tYW5kQW5kUGFyZW50cyh0aGlzKS5yZXZlcnNlKCkuZm9yRWFjaChjb21tYW5kID0+IGNvbW1hbmQuZW1pdCgnYmVmb3JlQWxsSGVscCcsIGNvbnRleHQpKTtcbiAgICB0aGlzLmVtaXQoJ2JlZm9yZUhlbHAnLCBjb250ZXh0KTtcblxuICAgIGxldCBoZWxwSW5mb3JtYXRpb24gPSB0aGlzLmhlbHBJbmZvcm1hdGlvbihjb250ZXh0KTtcbiAgICBpZiAoZGVwcmVjYXRlZENhbGxiYWNrKSB7XG4gICAgICBoZWxwSW5mb3JtYXRpb24gPSBkZXByZWNhdGVkQ2FsbGJhY2soaGVscEluZm9ybWF0aW9uKTtcbiAgICAgIGlmICh0eXBlb2YgaGVscEluZm9ybWF0aW9uICE9PSAnc3RyaW5nJyAmJiAhQnVmZmVyLmlzQnVmZmVyKGhlbHBJbmZvcm1hdGlvbikpIHtcbiAgICAgICAgdGhyb3cgbmV3IEVycm9yKCdvdXRwdXRIZWxwIGNhbGxiYWNrIG11c3QgcmV0dXJuIGEgc3RyaW5nIG9yIGEgQnVmZmVyJyk7XG4gICAgICB9XG4gICAgfVxuICAgIGNvbnRleHQud3JpdGUoaGVscEluZm9ybWF0aW9uKTtcblxuICAgIHRoaXMuZW1pdCh0aGlzLl9oZWxwTG9uZ0ZsYWcpOyAvLyBkZXByZWNhdGVkXG4gICAgdGhpcy5lbWl0KCdhZnRlckhlbHAnLCBjb250ZXh0KTtcbiAgICBnZXRDb21tYW5kQW5kUGFyZW50cyh0aGlzKS5mb3JFYWNoKGNvbW1hbmQgPT4gY29tbWFuZC5lbWl0KCdhZnRlckFsbEhlbHAnLCBjb250ZXh0KSk7XG4gIH1cblxuICAvKipcbiAgICogWW91IGNhbiBwYXNzIGluIGZsYWdzIGFuZCBhIGRlc2NyaXB0aW9uIHRvIG92ZXJyaWRlIHRoZSBoZWxwXG4gICAqIGZsYWdzIGFuZCBoZWxwIGRlc2NyaXB0aW9uIGZvciB5b3VyIGNvbW1hbmQuIFBhc3MgaW4gZmFsc2UgdG9cbiAgICogZGlzYWJsZSB0aGUgYnVpbHQtaW4gaGVscCBvcHRpb24uXG4gICAqXG4gICAqIEBwYXJhbSB7c3RyaW5nIHwgYm9vbGVhbn0gW2ZsYWdzXVxuICAgKiBAcGFyYW0ge3N0cmluZ30gW2Rlc2NyaXB0aW9uXVxuICAgKiBAcmV0dXJuIHtDb21tYW5kfSBgdGhpc2AgY29tbWFuZCBmb3IgY2hhaW5pbmdcbiAgICovXG5cbiAgaGVscE9wdGlvbihmbGFncywgZGVzY3JpcHRpb24pIHtcbiAgICBpZiAodHlwZW9mIGZsYWdzID09PSAnYm9vbGVhbicpIHtcbiAgICAgIHRoaXMuX2hhc0hlbHBPcHRpb24gPSBmbGFncztcbiAgICAgIHJldHVybiB0aGlzO1xuICAgIH1cbiAgICB0aGlzLl9oZWxwRmxhZ3MgPSBmbGFncyB8fCB0aGlzLl9oZWxwRmxhZ3M7XG4gICAgdGhpcy5faGVscERlc2NyaXB0aW9uID0gZGVzY3JpcHRpb24gfHwgdGhpcy5faGVscERlc2NyaXB0aW9uO1xuXG4gICAgY29uc3QgaGVscEZsYWdzID0gc3BsaXRPcHRpb25GbGFncyh0aGlzLl9oZWxwRmxhZ3MpO1xuICAgIHRoaXMuX2hlbHBTaG9ydEZsYWcgPSBoZWxwRmxhZ3Muc2hvcnRGbGFnO1xuICAgIHRoaXMuX2hlbHBMb25nRmxhZyA9IGhlbHBGbGFncy5sb25nRmxhZztcblxuICAgIHJldHVybiB0aGlzO1xuICB9XG5cbiAgLyoqXG4gICAqIE91dHB1dCBoZWxwIGluZm9ybWF0aW9uIGFuZCBleGl0LlxuICAgKlxuICAgKiBPdXRwdXRzIGJ1aWx0LWluIGhlbHAsIGFuZCBjdXN0b20gdGV4dCBhZGRlZCB1c2luZyBgLmFkZEhlbHBUZXh0KClgLlxuICAgKlxuICAgKiBAcGFyYW0ge3sgZXJyb3I6IGJvb2xlYW4gfX0gW2NvbnRleHRPcHRpb25zXSAtIHBhc3Mge2Vycm9yOnRydWV9IHRvIHdyaXRlIHRvIHN0ZGVyciBpbnN0ZWFkIG9mIHN0ZG91dFxuICAgKi9cblxuICBoZWxwKGNvbnRleHRPcHRpb25zKSB7XG4gICAgdGhpcy5vdXRwdXRIZWxwKGNvbnRleHRPcHRpb25zKTtcbiAgICBsZXQgZXhpdENvZGUgPSBwcm9jZXNzLmV4aXRDb2RlIHx8IDA7XG4gICAgaWYgKGV4aXRDb2RlID09PSAwICYmIGNvbnRleHRPcHRpb25zICYmIHR5cGVvZiBjb250ZXh0T3B0aW9ucyAhPT0gJ2Z1bmN0aW9uJyAmJiBjb250ZXh0T3B0aW9ucy5lcnJvcikge1xuICAgICAgZXhpdENvZGUgPSAxO1xuICAgIH1cbiAgICAvLyBtZXNzYWdlOiBkbyBub3QgaGF2ZSBhbGwgZGlzcGxheWVkIHRleHQgYXZhaWxhYmxlIHNvIG9ubHkgcGFzc2luZyBwbGFjZWhvbGRlci5cbiAgICB0aGlzLl9leGl0KGV4aXRDb2RlLCAnY29tbWFuZGVyLmhlbHAnLCAnKG91dHB1dEhlbHApJyk7XG4gIH1cblxuICAvKipcbiAgICogQWRkIGFkZGl0aW9uYWwgdGV4dCB0byBiZSBkaXNwbGF5ZWQgd2l0aCB0aGUgYnVpbHQtaW4gaGVscC5cbiAgICpcbiAgICogUG9zaXRpb24gaXMgJ2JlZm9yZScgb3IgJ2FmdGVyJyB0byBhZmZlY3QganVzdCB0aGlzIGNvbW1hbmQsXG4gICAqIGFuZCAnYmVmb3JlQWxsJyBvciAnYWZ0ZXJBbGwnIHRvIGFmZmVjdCB0aGlzIGNvbW1hbmQgYW5kIGFsbCBpdHMgc3ViY29tbWFuZHMuXG4gICAqXG4gICAqIEBwYXJhbSB7c3RyaW5nfSBwb3NpdGlvbiAtIGJlZm9yZSBvciBhZnRlciBidWlsdC1pbiBoZWxwXG4gICAqIEBwYXJhbSB7c3RyaW5nIHwgRnVuY3Rpb259IHRleHQgLSBzdHJpbmcgdG8gYWRkLCBvciBhIGZ1bmN0aW9uIHJldHVybmluZyBhIHN0cmluZ1xuICAgKiBAcmV0dXJuIHtDb21tYW5kfSBgdGhpc2AgY29tbWFuZCBmb3IgY2hhaW5pbmdcbiAgICovXG4gIGFkZEhlbHBUZXh0KHBvc2l0aW9uLCB0ZXh0KSB7XG4gICAgY29uc3QgYWxsb3dlZFZhbHVlcyA9IFsnYmVmb3JlQWxsJywgJ2JlZm9yZScsICdhZnRlcicsICdhZnRlckFsbCddO1xuICAgIGlmICghYWxsb3dlZFZhbHVlcy5pbmNsdWRlcyhwb3NpdGlvbikpIHtcbiAgICAgIHRocm93IG5ldyBFcnJvcihgVW5leHBlY3RlZCB2YWx1ZSBmb3IgcG9zaXRpb24gdG8gYWRkSGVscFRleHQuXG5FeHBlY3Rpbmcgb25lIG9mICcke2FsbG93ZWRWYWx1ZXMuam9pbihcIicsICdcIil9J2ApO1xuICAgIH1cbiAgICBjb25zdCBoZWxwRXZlbnQgPSBgJHtwb3NpdGlvbn1IZWxwYDtcbiAgICB0aGlzLm9uKGhlbHBFdmVudCwgKGNvbnRleHQpID0+IHtcbiAgICAgIGxldCBoZWxwU3RyO1xuICAgICAgaWYgKHR5cGVvZiB0ZXh0ID09PSAnZnVuY3Rpb24nKSB7XG4gICAgICAgIGhlbHBTdHIgPSB0ZXh0KHsgZXJyb3I6IGNvbnRleHQuZXJyb3IsIGNvbW1hbmQ6IGNvbnRleHQuY29tbWFuZCB9KTtcbiAgICAgIH0gZWxzZSB7XG4gICAgICAgIGhlbHBTdHIgPSB0ZXh0O1xuICAgICAgfVxuICAgICAgLy8gSWdub3JlIGZhbHN5IHZhbHVlIHdoZW4gbm90aGluZyB0byBvdXRwdXQuXG4gICAgICBpZiAoaGVscFN0cikge1xuICAgICAgICBjb250ZXh0LndyaXRlKGAke2hlbHBTdHJ9XFxuYCk7XG4gICAgICB9XG4gICAgfSk7XG4gICAgcmV0dXJuIHRoaXM7XG4gIH1cbn1cblxuLyoqXG4gKiBPdXRwdXQgaGVscCBpbmZvcm1hdGlvbiBpZiBoZWxwIGZsYWdzIHNwZWNpZmllZFxuICpcbiAqIEBwYXJhbSB7Q29tbWFuZH0gY21kIC0gY29tbWFuZCB0byBvdXRwdXQgaGVscCBmb3JcbiAqIEBwYXJhbSB7QXJyYXl9IGFyZ3MgLSBhcnJheSBvZiBvcHRpb25zIHRvIHNlYXJjaCBmb3IgaGVscCBmbGFnc1xuICogQGFwaSBwcml2YXRlXG4gKi9cblxuZnVuY3Rpb24gb3V0cHV0SGVscElmUmVxdWVzdGVkKGNtZCwgYXJncykge1xuICBjb25zdCBoZWxwT3B0aW9uID0gY21kLl9oYXNIZWxwT3B0aW9uICYmIGFyZ3MuZmluZChhcmcgPT4gYXJnID09PSBjbWQuX2hlbHBMb25nRmxhZyB8fCBhcmcgPT09IGNtZC5faGVscFNob3J0RmxhZyk7XG4gIGlmIChoZWxwT3B0aW9uKSB7XG4gICAgY21kLm91dHB1dEhlbHAoKTtcbiAgICAvLyAoRG8gbm90IGhhdmUgYWxsIGRpc3BsYXllZCB0ZXh0IGF2YWlsYWJsZSBzbyBvbmx5IHBhc3NpbmcgcGxhY2Vob2xkZXIuKVxuICAgIGNtZC5fZXhpdCgwLCAnY29tbWFuZGVyLmhlbHBEaXNwbGF5ZWQnLCAnKG91dHB1dEhlbHApJyk7XG4gIH1cbn1cblxuLyoqXG4gKiBTY2FuIGFyZ3VtZW50cyBhbmQgaW5jcmVtZW50IHBvcnQgbnVtYmVyIGZvciBpbnNwZWN0IGNhbGxzICh0byBhdm9pZCBjb25mbGljdHMgd2hlbiBzcGF3bmluZyBuZXcgY29tbWFuZCkuXG4gKlxuICogQHBhcmFtIHtzdHJpbmdbXX0gYXJncyAtIGFycmF5IG9mIGFyZ3VtZW50cyBmcm9tIG5vZGUuZXhlY0FyZ3ZcbiAqIEByZXR1cm5zIHtzdHJpbmdbXX1cbiAqIEBhcGkgcHJpdmF0ZVxuICovXG5cbmZ1bmN0aW9uIGluY3JlbWVudE5vZGVJbnNwZWN0b3JQb3J0KGFyZ3MpIHtcbiAgLy8gVGVzdGluZyBmb3IgdGhlc2Ugb3B0aW9uczpcbiAgLy8gIC0taW5zcGVjdFs9W2hvc3Q6XXBvcnRdXG4gIC8vICAtLWluc3BlY3QtYnJrWz1baG9zdDpdcG9ydF1cbiAgLy8gIC0taW5zcGVjdC1wb3J0PVtob3N0Ol1wb3J0XG4gIHJldHVybiBhcmdzLm1hcCgoYXJnKSA9PiB7XG4gICAgaWYgKCFhcmcuc3RhcnRzV2l0aCgnLS1pbnNwZWN0JykpIHtcbiAgICAgIHJldHVybiBhcmc7XG4gICAgfVxuICAgIGxldCBkZWJ1Z09wdGlvbjtcbiAgICBsZXQgZGVidWdIb3N0ID0gJzEyNy4wLjAuMSc7XG4gICAgbGV0IGRlYnVnUG9ydCA9ICc5MjI5JztcbiAgICBsZXQgbWF0Y2g7XG4gICAgaWYgKChtYXRjaCA9IGFyZy5tYXRjaCgvXigtLWluc3BlY3QoLWJyayk/KSQvKSkgIT09IG51bGwpIHtcbiAgICAgIC8vIGUuZy4gLS1pbnNwZWN0XG4gICAgICBkZWJ1Z09wdGlvbiA9IG1hdGNoWzFdO1xuICAgIH0gZWxzZSBpZiAoKG1hdGNoID0gYXJnLm1hdGNoKC9eKC0taW5zcGVjdCgtYnJrfC1wb3J0KT8pPShbXjpdKykkLykpICE9PSBudWxsKSB7XG4gICAgICBkZWJ1Z09wdGlvbiA9IG1hdGNoWzFdO1xuICAgICAgaWYgKC9eXFxkKyQvLnRlc3QobWF0Y2hbM10pKSB7XG4gICAgICAgIC8vIGUuZy4gLS1pbnNwZWN0PTEyMzRcbiAgICAgICAgZGVidWdQb3J0ID0gbWF0Y2hbM107XG4gICAgICB9IGVsc2Uge1xuICAgICAgICAvLyBlLmcuIC0taW5zcGVjdD1sb2NhbGhvc3RcbiAgICAgICAgZGVidWdIb3N0ID0gbWF0Y2hbM107XG4gICAgICB9XG4gICAgfSBlbHNlIGlmICgobWF0Y2ggPSBhcmcubWF0Y2goL14oLS1pbnNwZWN0KC1icmt8LXBvcnQpPyk9KFteOl0rKTooXFxkKykkLykpICE9PSBudWxsKSB7XG4gICAgICAvLyBlLmcuIC0taW5zcGVjdD1sb2NhbGhvc3Q6MTIzNFxuICAgICAgZGVidWdPcHRpb24gPSBtYXRjaFsxXTtcbiAgICAgIGRlYnVnSG9zdCA9IG1hdGNoWzNdO1xuICAgICAgZGVidWdQb3J0ID0gbWF0Y2hbNF07XG4gICAgfVxuXG4gICAgaWYgKGRlYnVnT3B0aW9uICYmIGRlYnVnUG9ydCAhPT0gJzAnKSB7XG4gICAgICByZXR1cm4gYCR7ZGVidWdPcHRpb259PSR7ZGVidWdIb3N0fToke3BhcnNlSW50KGRlYnVnUG9ydCkgKyAxfWA7XG4gICAgfVxuICAgIHJldHVybiBhcmc7XG4gIH0pO1xufVxuXG4vKipcbiAqIEBwYXJhbSB7Q29tbWFuZH0gc3RhcnRDb21tYW5kXG4gKiBAcmV0dXJucyB7Q29tbWFuZFtdfVxuICogQGFwaSBwcml2YXRlXG4gKi9cblxuZnVuY3Rpb24gZ2V0Q29tbWFuZEFuZFBhcmVudHMoc3RhcnRDb21tYW5kKSB7XG4gIGNvbnN0IHJlc3VsdCA9IFtdO1xuICBmb3IgKGxldCBjb21tYW5kID0gc3RhcnRDb21tYW5kOyBjb21tYW5kOyBjb21tYW5kID0gY29tbWFuZC5wYXJlbnQpIHtcbiAgICByZXN1bHQucHVzaChjb21tYW5kKTtcbiAgfVxuICByZXR1cm4gcmVzdWx0O1xufVxuXG5leHBvcnRzLkNvbW1hbmQgPSBDb21tYW5kO1xuIiwiLy8gQHRzLWNoZWNrXG5cbi8qKlxuICogQ29tbWFuZGVyRXJyb3IgY2xhc3NcbiAqIEBjbGFzc1xuICovXG5jbGFzcyBDb21tYW5kZXJFcnJvciBleHRlbmRzIEVycm9yIHtcbiAgLyoqXG4gICAqIENvbnN0cnVjdHMgdGhlIENvbW1hbmRlckVycm9yIGNsYXNzXG4gICAqIEBwYXJhbSB7bnVtYmVyfSBleGl0Q29kZSBzdWdnZXN0ZWQgZXhpdCBjb2RlIHdoaWNoIGNvdWxkIGJlIHVzZWQgd2l0aCBwcm9jZXNzLmV4aXRcbiAgICogQHBhcmFtIHtzdHJpbmd9IGNvZGUgYW4gaWQgc3RyaW5nIHJlcHJlc2VudGluZyB0aGUgZXJyb3JcbiAgICogQHBhcmFtIHtzdHJpbmd9IG1lc3NhZ2UgaHVtYW4tcmVhZGFibGUgZGVzY3JpcHRpb24gb2YgdGhlIGVycm9yXG4gICAqIEBjb25zdHJ1Y3RvclxuICAgKi9cbiAgY29uc3RydWN0b3IoZXhpdENvZGUsIGNvZGUsIG1lc3NhZ2UpIHtcbiAgICBzdXBlcihtZXNzYWdlKTtcbiAgICAvLyBwcm9wZXJseSBjYXB0dXJlIHN0YWNrIHRyYWNlIGluIE5vZGUuanNcbiAgICBFcnJvci5jYXB0dXJlU3RhY2tUcmFjZSh0aGlzLCB0aGlzLmNvbnN0cnVjdG9yKTtcbiAgICB0aGlzLm5hbWUgPSB0aGlzLmNvbnN0cnVjdG9yLm5hbWU7XG4gICAgdGhpcy5jb2RlID0gY29kZTtcbiAgICB0aGlzLmV4aXRDb2RlID0gZXhpdENvZGU7XG4gICAgdGhpcy5uZXN0ZWRFcnJvciA9IHVuZGVmaW5lZDtcbiAgfVxufVxuXG4vKipcbiAqIEludmFsaWRBcmd1bWVudEVycm9yIGNsYXNzXG4gKiBAY2xhc3NcbiAqL1xuY2xhc3MgSW52YWxpZEFyZ3VtZW50RXJyb3IgZXh0ZW5kcyBDb21tYW5kZXJFcnJvciB7XG4gIC8qKlxuICAgKiBDb25zdHJ1Y3RzIHRoZSBJbnZhbGlkQXJndW1lbnRFcnJvciBjbGFzc1xuICAgKiBAcGFyYW0ge3N0cmluZ30gW21lc3NhZ2VdIGV4cGxhbmF0aW9uIG9mIHdoeSBhcmd1bWVudCBpcyBpbnZhbGlkXG4gICAqIEBjb25zdHJ1Y3RvclxuICAgKi9cbiAgY29uc3RydWN0b3IobWVzc2FnZSkge1xuICAgIHN1cGVyKDEsICdjb21tYW5kZXIuaW52YWxpZEFyZ3VtZW50JywgbWVzc2FnZSk7XG4gICAgLy8gcHJvcGVybHkgY2FwdHVyZSBzdGFjayB0cmFjZSBpbiBOb2RlLmpzXG4gICAgRXJyb3IuY2FwdHVyZVN0YWNrVHJhY2UodGhpcywgdGhpcy5jb25zdHJ1Y3Rvcik7XG4gICAgdGhpcy5uYW1lID0gdGhpcy5jb25zdHJ1Y3Rvci5uYW1lO1xuICB9XG59XG5cbmV4cG9ydHMuQ29tbWFuZGVyRXJyb3IgPSBDb21tYW5kZXJFcnJvcjtcbmV4cG9ydHMuSW52YWxpZEFyZ3VtZW50RXJyb3IgPSBJbnZhbGlkQXJndW1lbnRFcnJvcjtcbiIsImNvbnN0IHsgaHVtYW5SZWFkYWJsZUFyZ05hbWUgfSA9IHJlcXVpcmUoJy4vYXJndW1lbnQuanMnKTtcblxuLyoqXG4gKiBUeXBlU2NyaXB0IGltcG9ydCB0eXBlcyBmb3IgSlNEb2MsIHVzZWQgYnkgVmlzdWFsIFN0dWRpbyBDb2RlIEludGVsbGlTZW5zZSBhbmQgYG5wbSBydW4gdHlwZXNjcmlwdC1jaGVja0pTYFxuICogaHR0cHM6Ly93d3cudHlwZXNjcmlwdGxhbmcub3JnL2RvY3MvaGFuZGJvb2svanNkb2Mtc3VwcG9ydGVkLXR5cGVzLmh0bWwjaW1wb3J0LXR5cGVzXG4gKiBAdHlwZWRlZiB7IGltcG9ydChcIi4vYXJndW1lbnQuanNcIikuQXJndW1lbnQgfSBBcmd1bWVudFxuICogQHR5cGVkZWYgeyBpbXBvcnQoXCIuL2NvbW1hbmQuanNcIikuQ29tbWFuZCB9IENvbW1hbmRcbiAqIEB0eXBlZGVmIHsgaW1wb3J0KFwiLi9vcHRpb24uanNcIikuT3B0aW9uIH0gT3B0aW9uXG4gKi9cblxuLy8gQHRzLWNoZWNrXG5cbi8vIEFsdGhvdWdoIHRoaXMgaXMgYSBjbGFzcywgbWV0aG9kcyBhcmUgc3RhdGljIGluIHN0eWxlIHRvIGFsbG93IG92ZXJyaWRlIHVzaW5nIHN1YmNsYXNzIG9yIGp1c3QgZnVuY3Rpb25zLlxuY2xhc3MgSGVscCB7XG4gIGNvbnN0cnVjdG9yKCkge1xuICAgIHRoaXMuaGVscFdpZHRoID0gdW5kZWZpbmVkO1xuICAgIHRoaXMuc29ydFN1YmNvbW1hbmRzID0gZmFsc2U7XG4gICAgdGhpcy5zb3J0T3B0aW9ucyA9IGZhbHNlO1xuICAgIHRoaXMuc2hvd0dsb2JhbE9wdGlvbnMgPSBmYWxzZTtcbiAgfVxuXG4gIC8qKlxuICAgKiBHZXQgYW4gYXJyYXkgb2YgdGhlIHZpc2libGUgc3ViY29tbWFuZHMuIEluY2x1ZGVzIGEgcGxhY2Vob2xkZXIgZm9yIHRoZSBpbXBsaWNpdCBoZWxwIGNvbW1hbmQsIGlmIHRoZXJlIGlzIG9uZS5cbiAgICpcbiAgICogQHBhcmFtIHtDb21tYW5kfSBjbWRcbiAgICogQHJldHVybnMge0NvbW1hbmRbXX1cbiAgICovXG5cbiAgdmlzaWJsZUNvbW1hbmRzKGNtZCkge1xuICAgIGNvbnN0IHZpc2libGVDb21tYW5kcyA9IGNtZC5jb21tYW5kcy5maWx0ZXIoY21kID0+ICFjbWQuX2hpZGRlbik7XG4gICAgaWYgKGNtZC5faGFzSW1wbGljaXRIZWxwQ29tbWFuZCgpKSB7XG4gICAgICAvLyBDcmVhdGUgYSBjb21tYW5kIG1hdGNoaW5nIHRoZSBpbXBsaWNpdCBoZWxwIGNvbW1hbmQuXG4gICAgICBjb25zdCBbLCBoZWxwTmFtZSwgaGVscEFyZ3NdID0gY21kLl9oZWxwQ29tbWFuZG5hbWVBbmRBcmdzLm1hdGNoKC8oW14gXSspICooLiopLyk7XG4gICAgICBjb25zdCBoZWxwQ29tbWFuZCA9IGNtZC5jcmVhdGVDb21tYW5kKGhlbHBOYW1lKVxuICAgICAgICAuaGVscE9wdGlvbihmYWxzZSk7XG4gICAgICBoZWxwQ29tbWFuZC5kZXNjcmlwdGlvbihjbWQuX2hlbHBDb21tYW5kRGVzY3JpcHRpb24pO1xuICAgICAgaWYgKGhlbHBBcmdzKSBoZWxwQ29tbWFuZC5hcmd1bWVudHMoaGVscEFyZ3MpO1xuICAgICAgdmlzaWJsZUNvbW1hbmRzLnB1c2goaGVscENvbW1hbmQpO1xuICAgIH1cbiAgICBpZiAodGhpcy5zb3J0U3ViY29tbWFuZHMpIHtcbiAgICAgIHZpc2libGVDb21tYW5kcy5zb3J0KChhLCBiKSA9PiB7XG4gICAgICAgIC8vIEB0cy1pZ25vcmU6IG92ZXJsb2FkZWQgcmV0dXJuIHR5cGVcbiAgICAgICAgcmV0dXJuIGEubmFtZSgpLmxvY2FsZUNvbXBhcmUoYi5uYW1lKCkpO1xuICAgICAgfSk7XG4gICAgfVxuICAgIHJldHVybiB2aXNpYmxlQ29tbWFuZHM7XG4gIH1cblxuICAvKipcbiAgICogQ29tcGFyZSBvcHRpb25zIGZvciBzb3J0LlxuICAgKlxuICAgKiBAcGFyYW0ge09wdGlvbn0gYVxuICAgKiBAcGFyYW0ge09wdGlvbn0gYlxuICAgKiBAcmV0dXJucyBudW1iZXJcbiAgICovXG4gIGNvbXBhcmVPcHRpb25zKGEsIGIpIHtcbiAgICBjb25zdCBnZXRTb3J0S2V5ID0gKG9wdGlvbikgPT4ge1xuICAgICAgLy8gV1lTSVdZRyBmb3Igb3JkZXIgZGlzcGxheWVkIGluIGhlbHAuIFNob3J0IHVzZWQgZm9yIGNvbXBhcmlzb24gaWYgcHJlc2VudC4gTm8gc3BlY2lhbCBoYW5kbGluZyBmb3IgbmVnYXRlZC5cbiAgICAgIHJldHVybiBvcHRpb24uc2hvcnQgPyBvcHRpb24uc2hvcnQucmVwbGFjZSgvXi0vLCAnJykgOiBvcHRpb24ubG9uZy5yZXBsYWNlKC9eLS0vLCAnJyk7XG4gICAgfTtcbiAgICByZXR1cm4gZ2V0U29ydEtleShhKS5sb2NhbGVDb21wYXJlKGdldFNvcnRLZXkoYikpO1xuICB9XG5cbiAgLyoqXG4gICAqIEdldCBhbiBhcnJheSBvZiB0aGUgdmlzaWJsZSBvcHRpb25zLiBJbmNsdWRlcyBhIHBsYWNlaG9sZGVyIGZvciB0aGUgaW1wbGljaXQgaGVscCBvcHRpb24sIGlmIHRoZXJlIGlzIG9uZS5cbiAgICpcbiAgICogQHBhcmFtIHtDb21tYW5kfSBjbWRcbiAgICogQHJldHVybnMge09wdGlvbltdfVxuICAgKi9cblxuICB2aXNpYmxlT3B0aW9ucyhjbWQpIHtcbiAgICBjb25zdCB2aXNpYmxlT3B0aW9ucyA9IGNtZC5vcHRpb25zLmZpbHRlcigob3B0aW9uKSA9PiAhb3B0aW9uLmhpZGRlbik7XG4gICAgLy8gSW1wbGljaXQgaGVscFxuICAgIGNvbnN0IHNob3dTaG9ydEhlbHBGbGFnID0gY21kLl9oYXNIZWxwT3B0aW9uICYmIGNtZC5faGVscFNob3J0RmxhZyAmJiAhY21kLl9maW5kT3B0aW9uKGNtZC5faGVscFNob3J0RmxhZyk7XG4gICAgY29uc3Qgc2hvd0xvbmdIZWxwRmxhZyA9IGNtZC5faGFzSGVscE9wdGlvbiAmJiAhY21kLl9maW5kT3B0aW9uKGNtZC5faGVscExvbmdGbGFnKTtcbiAgICBpZiAoc2hvd1Nob3J0SGVscEZsYWcgfHwgc2hvd0xvbmdIZWxwRmxhZykge1xuICAgICAgbGV0IGhlbHBPcHRpb247XG4gICAgICBpZiAoIXNob3dTaG9ydEhlbHBGbGFnKSB7XG4gICAgICAgIGhlbHBPcHRpb24gPSBjbWQuY3JlYXRlT3B0aW9uKGNtZC5faGVscExvbmdGbGFnLCBjbWQuX2hlbHBEZXNjcmlwdGlvbik7XG4gICAgICB9IGVsc2UgaWYgKCFzaG93TG9uZ0hlbHBGbGFnKSB7XG4gICAgICAgIGhlbHBPcHRpb24gPSBjbWQuY3JlYXRlT3B0aW9uKGNtZC5faGVscFNob3J0RmxhZywgY21kLl9oZWxwRGVzY3JpcHRpb24pO1xuICAgICAgfSBlbHNlIHtcbiAgICAgICAgaGVscE9wdGlvbiA9IGNtZC5jcmVhdGVPcHRpb24oY21kLl9oZWxwRmxhZ3MsIGNtZC5faGVscERlc2NyaXB0aW9uKTtcbiAgICAgIH1cbiAgICAgIHZpc2libGVPcHRpb25zLnB1c2goaGVscE9wdGlvbik7XG4gICAgfVxuICAgIGlmICh0aGlzLnNvcnRPcHRpb25zKSB7XG4gICAgICB2aXNpYmxlT3B0aW9ucy5zb3J0KHRoaXMuY29tcGFyZU9wdGlvbnMpO1xuICAgIH1cbiAgICByZXR1cm4gdmlzaWJsZU9wdGlvbnM7XG4gIH1cblxuICAvKipcbiAgICogR2V0IGFuIGFycmF5IG9mIHRoZSB2aXNpYmxlIGdsb2JhbCBvcHRpb25zLiAoTm90IGluY2x1ZGluZyBoZWxwLilcbiAgICpcbiAgICogQHBhcmFtIHtDb21tYW5kfSBjbWRcbiAgICogQHJldHVybnMge09wdGlvbltdfVxuICAgKi9cblxuICB2aXNpYmxlR2xvYmFsT3B0aW9ucyhjbWQpIHtcbiAgICBpZiAoIXRoaXMuc2hvd0dsb2JhbE9wdGlvbnMpIHJldHVybiBbXTtcblxuICAgIGNvbnN0IGdsb2JhbE9wdGlvbnMgPSBbXTtcbiAgICBmb3IgKGxldCBwYXJlbnRDbWQgPSBjbWQucGFyZW50OyBwYXJlbnRDbWQ7IHBhcmVudENtZCA9IHBhcmVudENtZC5wYXJlbnQpIHtcbiAgICAgIGNvbnN0IHZpc2libGVPcHRpb25zID0gcGFyZW50Q21kLm9wdGlvbnMuZmlsdGVyKChvcHRpb24pID0+ICFvcHRpb24uaGlkZGVuKTtcbiAgICAgIGdsb2JhbE9wdGlvbnMucHVzaCguLi52aXNpYmxlT3B0aW9ucyk7XG4gICAgfVxuICAgIGlmICh0aGlzLnNvcnRPcHRpb25zKSB7XG4gICAgICBnbG9iYWxPcHRpb25zLnNvcnQodGhpcy5jb21wYXJlT3B0aW9ucyk7XG4gICAgfVxuICAgIHJldHVybiBnbG9iYWxPcHRpb25zO1xuICB9XG5cbiAgLyoqXG4gICAqIEdldCBhbiBhcnJheSBvZiB0aGUgYXJndW1lbnRzIGlmIGFueSBoYXZlIGEgZGVzY3JpcHRpb24uXG4gICAqXG4gICAqIEBwYXJhbSB7Q29tbWFuZH0gY21kXG4gICAqIEByZXR1cm5zIHtBcmd1bWVudFtdfVxuICAgKi9cblxuICB2aXNpYmxlQXJndW1lbnRzKGNtZCkge1xuICAgIC8vIFNpZGUgZWZmZWN0ISBBcHBseSB0aGUgbGVnYWN5IGRlc2NyaXB0aW9ucyBiZWZvcmUgdGhlIGFyZ3VtZW50cyBhcmUgZGlzcGxheWVkLlxuICAgIGlmIChjbWQuX2FyZ3NEZXNjcmlwdGlvbikge1xuICAgICAgY21kLl9hcmdzLmZvckVhY2goYXJndW1lbnQgPT4ge1xuICAgICAgICBhcmd1bWVudC5kZXNjcmlwdGlvbiA9IGFyZ3VtZW50LmRlc2NyaXB0aW9uIHx8IGNtZC5fYXJnc0Rlc2NyaXB0aW9uW2FyZ3VtZW50Lm5hbWUoKV0gfHwgJyc7XG4gICAgICB9KTtcbiAgICB9XG5cbiAgICAvLyBJZiB0aGVyZSBhcmUgYW55IGFyZ3VtZW50cyB3aXRoIGEgZGVzY3JpcHRpb24gdGhlbiByZXR1cm4gYWxsIHRoZSBhcmd1bWVudHMuXG4gICAgaWYgKGNtZC5fYXJncy5maW5kKGFyZ3VtZW50ID0+IGFyZ3VtZW50LmRlc2NyaXB0aW9uKSkge1xuICAgICAgcmV0dXJuIGNtZC5fYXJncztcbiAgICB9XG4gICAgcmV0dXJuIFtdO1xuICB9XG5cbiAgLyoqXG4gICAqIEdldCB0aGUgY29tbWFuZCB0ZXJtIHRvIHNob3cgaW4gdGhlIGxpc3Qgb2Ygc3ViY29tbWFuZHMuXG4gICAqXG4gICAqIEBwYXJhbSB7Q29tbWFuZH0gY21kXG4gICAqIEByZXR1cm5zIHtzdHJpbmd9XG4gICAqL1xuXG4gIHN1YmNvbW1hbmRUZXJtKGNtZCkge1xuICAgIC8vIExlZ2FjeS4gSWdub3JlcyBjdXN0b20gdXNhZ2Ugc3RyaW5nLCBhbmQgbmVzdGVkIGNvbW1hbmRzLlxuICAgIGNvbnN0IGFyZ3MgPSBjbWQuX2FyZ3MubWFwKGFyZyA9PiBodW1hblJlYWRhYmxlQXJnTmFtZShhcmcpKS5qb2luKCcgJyk7XG4gICAgcmV0dXJuIGNtZC5fbmFtZSArXG4gICAgICAoY21kLl9hbGlhc2VzWzBdID8gJ3wnICsgY21kLl9hbGlhc2VzWzBdIDogJycpICtcbiAgICAgIChjbWQub3B0aW9ucy5sZW5ndGggPyAnIFtvcHRpb25zXScgOiAnJykgKyAvLyBzaW1wbGlzdGljIGNoZWNrIGZvciBub24taGVscCBvcHRpb25cbiAgICAgIChhcmdzID8gJyAnICsgYXJncyA6ICcnKTtcbiAgfVxuXG4gIC8qKlxuICAgKiBHZXQgdGhlIG9wdGlvbiB0ZXJtIHRvIHNob3cgaW4gdGhlIGxpc3Qgb2Ygb3B0aW9ucy5cbiAgICpcbiAgICogQHBhcmFtIHtPcHRpb259IG9wdGlvblxuICAgKiBAcmV0dXJucyB7c3RyaW5nfVxuICAgKi9cblxuICBvcHRpb25UZXJtKG9wdGlvbikge1xuICAgIHJldHVybiBvcHRpb24uZmxhZ3M7XG4gIH1cblxuICAvKipcbiAgICogR2V0IHRoZSBhcmd1bWVudCB0ZXJtIHRvIHNob3cgaW4gdGhlIGxpc3Qgb2YgYXJndW1lbnRzLlxuICAgKlxuICAgKiBAcGFyYW0ge0FyZ3VtZW50fSBhcmd1bWVudFxuICAgKiBAcmV0dXJucyB7c3RyaW5nfVxuICAgKi9cblxuICBhcmd1bWVudFRlcm0oYXJndW1lbnQpIHtcbiAgICByZXR1cm4gYXJndW1lbnQubmFtZSgpO1xuICB9XG5cbiAgLyoqXG4gICAqIEdldCB0aGUgbG9uZ2VzdCBjb21tYW5kIHRlcm0gbGVuZ3RoLlxuICAgKlxuICAgKiBAcGFyYW0ge0NvbW1hbmR9IGNtZFxuICAgKiBAcGFyYW0ge0hlbHB9IGhlbHBlclxuICAgKiBAcmV0dXJucyB7bnVtYmVyfVxuICAgKi9cblxuICBsb25nZXN0U3ViY29tbWFuZFRlcm1MZW5ndGgoY21kLCBoZWxwZXIpIHtcbiAgICByZXR1cm4gaGVscGVyLnZpc2libGVDb21tYW5kcyhjbWQpLnJlZHVjZSgobWF4LCBjb21tYW5kKSA9PiB7XG4gICAgICByZXR1cm4gTWF0aC5tYXgobWF4LCBoZWxwZXIuc3ViY29tbWFuZFRlcm0oY29tbWFuZCkubGVuZ3RoKTtcbiAgICB9LCAwKTtcbiAgfVxuXG4gIC8qKlxuICAgKiBHZXQgdGhlIGxvbmdlc3Qgb3B0aW9uIHRlcm0gbGVuZ3RoLlxuICAgKlxuICAgKiBAcGFyYW0ge0NvbW1hbmR9IGNtZFxuICAgKiBAcGFyYW0ge0hlbHB9IGhlbHBlclxuICAgKiBAcmV0dXJucyB7bnVtYmVyfVxuICAgKi9cblxuICBsb25nZXN0T3B0aW9uVGVybUxlbmd0aChjbWQsIGhlbHBlcikge1xuICAgIHJldHVybiBoZWxwZXIudmlzaWJsZU9wdGlvbnMoY21kKS5yZWR1Y2UoKG1heCwgb3B0aW9uKSA9PiB7XG4gICAgICByZXR1cm4gTWF0aC5tYXgobWF4LCBoZWxwZXIub3B0aW9uVGVybShvcHRpb24pLmxlbmd0aCk7XG4gICAgfSwgMCk7XG4gIH1cblxuICAvKipcbiAgICogR2V0IHRoZSBsb25nZXN0IGdsb2JhbCBvcHRpb24gdGVybSBsZW5ndGguXG4gICAqXG4gICAqIEBwYXJhbSB7Q29tbWFuZH0gY21kXG4gICAqIEBwYXJhbSB7SGVscH0gaGVscGVyXG4gICAqIEByZXR1cm5zIHtudW1iZXJ9XG4gICAqL1xuXG4gIGxvbmdlc3RHbG9iYWxPcHRpb25UZXJtTGVuZ3RoKGNtZCwgaGVscGVyKSB7XG4gICAgcmV0dXJuIGhlbHBlci52aXNpYmxlR2xvYmFsT3B0aW9ucyhjbWQpLnJlZHVjZSgobWF4LCBvcHRpb24pID0+IHtcbiAgICAgIHJldHVybiBNYXRoLm1heChtYXgsIGhlbHBlci5vcHRpb25UZXJtKG9wdGlvbikubGVuZ3RoKTtcbiAgICB9LCAwKTtcbiAgfVxuXG4gIC8qKlxuICAgKiBHZXQgdGhlIGxvbmdlc3QgYXJndW1lbnQgdGVybSBsZW5ndGguXG4gICAqXG4gICAqIEBwYXJhbSB7Q29tbWFuZH0gY21kXG4gICAqIEBwYXJhbSB7SGVscH0gaGVscGVyXG4gICAqIEByZXR1cm5zIHtudW1iZXJ9XG4gICAqL1xuXG4gIGxvbmdlc3RBcmd1bWVudFRlcm1MZW5ndGgoY21kLCBoZWxwZXIpIHtcbiAgICByZXR1cm4gaGVscGVyLnZpc2libGVBcmd1bWVudHMoY21kKS5yZWR1Y2UoKG1heCwgYXJndW1lbnQpID0+IHtcbiAgICAgIHJldHVybiBNYXRoLm1heChtYXgsIGhlbHBlci5hcmd1bWVudFRlcm0oYXJndW1lbnQpLmxlbmd0aCk7XG4gICAgfSwgMCk7XG4gIH1cblxuICAvKipcbiAgICogR2V0IHRoZSBjb21tYW5kIHVzYWdlIHRvIGJlIGRpc3BsYXllZCBhdCB0aGUgdG9wIG9mIHRoZSBidWlsdC1pbiBoZWxwLlxuICAgKlxuICAgKiBAcGFyYW0ge0NvbW1hbmR9IGNtZFxuICAgKiBAcmV0dXJucyB7c3RyaW5nfVxuICAgKi9cblxuICBjb21tYW5kVXNhZ2UoY21kKSB7XG4gICAgLy8gVXNhZ2VcbiAgICBsZXQgY21kTmFtZSA9IGNtZC5fbmFtZTtcbiAgICBpZiAoY21kLl9hbGlhc2VzWzBdKSB7XG4gICAgICBjbWROYW1lID0gY21kTmFtZSArICd8JyArIGNtZC5fYWxpYXNlc1swXTtcbiAgICB9XG4gICAgbGV0IHBhcmVudENtZE5hbWVzID0gJyc7XG4gICAgZm9yIChsZXQgcGFyZW50Q21kID0gY21kLnBhcmVudDsgcGFyZW50Q21kOyBwYXJlbnRDbWQgPSBwYXJlbnRDbWQucGFyZW50KSB7XG4gICAgICBwYXJlbnRDbWROYW1lcyA9IHBhcmVudENtZC5uYW1lKCkgKyAnICcgKyBwYXJlbnRDbWROYW1lcztcbiAgICB9XG4gICAgcmV0dXJuIHBhcmVudENtZE5hbWVzICsgY21kTmFtZSArICcgJyArIGNtZC51c2FnZSgpO1xuICB9XG5cbiAgLyoqXG4gICAqIEdldCB0aGUgZGVzY3JpcHRpb24gZm9yIHRoZSBjb21tYW5kLlxuICAgKlxuICAgKiBAcGFyYW0ge0NvbW1hbmR9IGNtZFxuICAgKiBAcmV0dXJucyB7c3RyaW5nfVxuICAgKi9cblxuICBjb21tYW5kRGVzY3JpcHRpb24oY21kKSB7XG4gICAgLy8gQHRzLWlnbm9yZTogb3ZlcmxvYWRlZCByZXR1cm4gdHlwZVxuICAgIHJldHVybiBjbWQuZGVzY3JpcHRpb24oKTtcbiAgfVxuXG4gIC8qKlxuICAgKiBHZXQgdGhlIHN1YmNvbW1hbmQgc3VtbWFyeSB0byBzaG93IGluIHRoZSBsaXN0IG9mIHN1YmNvbW1hbmRzLlxuICAgKiAoRmFsbGJhY2sgdG8gZGVzY3JpcHRpb24gZm9yIGJhY2t3YXJkcyBjb21wYXRpYmlsaXR5LilcbiAgICpcbiAgICogQHBhcmFtIHtDb21tYW5kfSBjbWRcbiAgICogQHJldHVybnMge3N0cmluZ31cbiAgICovXG5cbiAgc3ViY29tbWFuZERlc2NyaXB0aW9uKGNtZCkge1xuICAgIC8vIEB0cy1pZ25vcmU6IG92ZXJsb2FkZWQgcmV0dXJuIHR5cGVcbiAgICByZXR1cm4gY21kLnN1bW1hcnkoKSB8fCBjbWQuZGVzY3JpcHRpb24oKTtcbiAgfVxuXG4gIC8qKlxuICAgKiBHZXQgdGhlIG9wdGlvbiBkZXNjcmlwdGlvbiB0byBzaG93IGluIHRoZSBsaXN0IG9mIG9wdGlvbnMuXG4gICAqXG4gICAqIEBwYXJhbSB7T3B0aW9ufSBvcHRpb25cbiAgICogQHJldHVybiB7c3RyaW5nfVxuICAgKi9cblxuICBvcHRpb25EZXNjcmlwdGlvbihvcHRpb24pIHtcbiAgICBjb25zdCBleHRyYUluZm8gPSBbXTtcblxuICAgIGlmIChvcHRpb24uYXJnQ2hvaWNlcykge1xuICAgICAgZXh0cmFJbmZvLnB1c2goXG4gICAgICAgIC8vIHVzZSBzdHJpbmdpZnkgdG8gbWF0Y2ggdGhlIGRpc3BsYXkgb2YgdGhlIGRlZmF1bHQgdmFsdWVcbiAgICAgICAgYGNob2ljZXM6ICR7b3B0aW9uLmFyZ0Nob2ljZXMubWFwKChjaG9pY2UpID0+IEpTT04uc3RyaW5naWZ5KGNob2ljZSkpLmpvaW4oJywgJyl9YCk7XG4gICAgfVxuICAgIGlmIChvcHRpb24uZGVmYXVsdFZhbHVlICE9PSB1bmRlZmluZWQpIHtcbiAgICAgIC8vIGRlZmF1bHQgZm9yIGJvb2xlYW4gYW5kIG5lZ2F0ZWQgbW9yZSBmb3IgcHJvZ3JhbW1lciB0aGFuIGVuZCB1c2VyLFxuICAgICAgLy8gYnV0IHNob3cgdHJ1ZS9mYWxzZSBmb3IgYm9vbGVhbiBvcHRpb24gYXMgbWF5IGJlIGZvciBoYW5kLXJvbGxlZCBlbnYgb3IgY29uZmlnIHByb2Nlc3NpbmcuXG4gICAgICBjb25zdCBzaG93RGVmYXVsdCA9IG9wdGlvbi5yZXF1aXJlZCB8fCBvcHRpb24ub3B0aW9uYWwgfHxcbiAgICAgICAgKG9wdGlvbi5pc0Jvb2xlYW4oKSAmJiB0eXBlb2Ygb3B0aW9uLmRlZmF1bHRWYWx1ZSA9PT0gJ2Jvb2xlYW4nKTtcbiAgICAgIGlmIChzaG93RGVmYXVsdCkge1xuICAgICAgICBleHRyYUluZm8ucHVzaChgZGVmYXVsdDogJHtvcHRpb24uZGVmYXVsdFZhbHVlRGVzY3JpcHRpb24gfHwgSlNPTi5zdHJpbmdpZnkob3B0aW9uLmRlZmF1bHRWYWx1ZSl9YCk7XG4gICAgICB9XG4gICAgfVxuICAgIC8vIHByZXNldCBmb3IgYm9vbGVhbiBhbmQgbmVnYXRlZCBhcmUgbW9yZSBmb3IgcHJvZ3JhbW1lciB0aGFuIGVuZCB1c2VyXG4gICAgaWYgKG9wdGlvbi5wcmVzZXRBcmcgIT09IHVuZGVmaW5lZCAmJiBvcHRpb24ub3B0aW9uYWwpIHtcbiAgICAgIGV4dHJhSW5mby5wdXNoKGBwcmVzZXQ6ICR7SlNPTi5zdHJpbmdpZnkob3B0aW9uLnByZXNldEFyZyl9YCk7XG4gICAgfVxuICAgIGlmIChvcHRpb24uZW52VmFyICE9PSB1bmRlZmluZWQpIHtcbiAgICAgIGV4dHJhSW5mby5wdXNoKGBlbnY6ICR7b3B0aW9uLmVudlZhcn1gKTtcbiAgICB9XG4gICAgaWYgKGV4dHJhSW5mby5sZW5ndGggPiAwKSB7XG4gICAgICByZXR1cm4gYCR7b3B0aW9uLmRlc2NyaXB0aW9ufSAoJHtleHRyYUluZm8uam9pbignLCAnKX0pYDtcbiAgICB9XG5cbiAgICByZXR1cm4gb3B0aW9uLmRlc2NyaXB0aW9uO1xuICB9XG5cbiAgLyoqXG4gICAqIEdldCB0aGUgYXJndW1lbnQgZGVzY3JpcHRpb24gdG8gc2hvdyBpbiB0aGUgbGlzdCBvZiBhcmd1bWVudHMuXG4gICAqXG4gICAqIEBwYXJhbSB7QXJndW1lbnR9IGFyZ3VtZW50XG4gICAqIEByZXR1cm4ge3N0cmluZ31cbiAgICovXG5cbiAgYXJndW1lbnREZXNjcmlwdGlvbihhcmd1bWVudCkge1xuICAgIGNvbnN0IGV4dHJhSW5mbyA9IFtdO1xuICAgIGlmIChhcmd1bWVudC5hcmdDaG9pY2VzKSB7XG4gICAgICBleHRyYUluZm8ucHVzaChcbiAgICAgICAgLy8gdXNlIHN0cmluZ2lmeSB0byBtYXRjaCB0aGUgZGlzcGxheSBvZiB0aGUgZGVmYXVsdCB2YWx1ZVxuICAgICAgICBgY2hvaWNlczogJHthcmd1bWVudC5hcmdDaG9pY2VzLm1hcCgoY2hvaWNlKSA9PiBKU09OLnN0cmluZ2lmeShjaG9pY2UpKS5qb2luKCcsICcpfWApO1xuICAgIH1cbiAgICBpZiAoYXJndW1lbnQuZGVmYXVsdFZhbHVlICE9PSB1bmRlZmluZWQpIHtcbiAgICAgIGV4dHJhSW5mby5wdXNoKGBkZWZhdWx0OiAke2FyZ3VtZW50LmRlZmF1bHRWYWx1ZURlc2NyaXB0aW9uIHx8IEpTT04uc3RyaW5naWZ5KGFyZ3VtZW50LmRlZmF1bHRWYWx1ZSl9YCk7XG4gICAgfVxuICAgIGlmIChleHRyYUluZm8ubGVuZ3RoID4gMCkge1xuICAgICAgY29uc3QgZXh0cmFEZXNjcmlwdG9uID0gYCgke2V4dHJhSW5mby5qb2luKCcsICcpfSlgO1xuICAgICAgaWYgKGFyZ3VtZW50LmRlc2NyaXB0aW9uKSB7XG4gICAgICAgIHJldHVybiBgJHthcmd1bWVudC5kZXNjcmlwdGlvbn0gJHtleHRyYURlc2NyaXB0b259YDtcbiAgICAgIH1cbiAgICAgIHJldHVybiBleHRyYURlc2NyaXB0b247XG4gICAgfVxuICAgIHJldHVybiBhcmd1bWVudC5kZXNjcmlwdGlvbjtcbiAgfVxuXG4gIC8qKlxuICAgKiBHZW5lcmF0ZSB0aGUgYnVpbHQtaW4gaGVscCB0ZXh0LlxuICAgKlxuICAgKiBAcGFyYW0ge0NvbW1hbmR9IGNtZFxuICAgKiBAcGFyYW0ge0hlbHB9IGhlbHBlclxuICAgKiBAcmV0dXJucyB7c3RyaW5nfVxuICAgKi9cblxuICBmb3JtYXRIZWxwKGNtZCwgaGVscGVyKSB7XG4gICAgY29uc3QgdGVybVdpZHRoID0gaGVscGVyLnBhZFdpZHRoKGNtZCwgaGVscGVyKTtcbiAgICBjb25zdCBoZWxwV2lkdGggPSBoZWxwZXIuaGVscFdpZHRoIHx8IDgwO1xuICAgIGNvbnN0IGl0ZW1JbmRlbnRXaWR0aCA9IDI7XG4gICAgY29uc3QgaXRlbVNlcGFyYXRvcldpZHRoID0gMjsgLy8gYmV0d2VlbiB0ZXJtIGFuZCBkZXNjcmlwdGlvblxuICAgIGZ1bmN0aW9uIGZvcm1hdEl0ZW0odGVybSwgZGVzY3JpcHRpb24pIHtcbiAgICAgIGlmIChkZXNjcmlwdGlvbikge1xuICAgICAgICBjb25zdCBmdWxsVGV4dCA9IGAke3Rlcm0ucGFkRW5kKHRlcm1XaWR0aCArIGl0ZW1TZXBhcmF0b3JXaWR0aCl9JHtkZXNjcmlwdGlvbn1gO1xuICAgICAgICByZXR1cm4gaGVscGVyLndyYXAoZnVsbFRleHQsIGhlbHBXaWR0aCAtIGl0ZW1JbmRlbnRXaWR0aCwgdGVybVdpZHRoICsgaXRlbVNlcGFyYXRvcldpZHRoKTtcbiAgICAgIH1cbiAgICAgIHJldHVybiB0ZXJtO1xuICAgIH1cbiAgICBmdW5jdGlvbiBmb3JtYXRMaXN0KHRleHRBcnJheSkge1xuICAgICAgcmV0dXJuIHRleHRBcnJheS5qb2luKCdcXG4nKS5yZXBsYWNlKC9eL2dtLCAnICcucmVwZWF0KGl0ZW1JbmRlbnRXaWR0aCkpO1xuICAgIH1cblxuICAgIC8vIFVzYWdlXG4gICAgbGV0IG91dHB1dCA9IFtgVXNhZ2U6ICR7aGVscGVyLmNvbW1hbmRVc2FnZShjbWQpfWAsICcnXTtcblxuICAgIC8vIERlc2NyaXB0aW9uXG4gICAgY29uc3QgY29tbWFuZERlc2NyaXB0aW9uID0gaGVscGVyLmNvbW1hbmREZXNjcmlwdGlvbihjbWQpO1xuICAgIGlmIChjb21tYW5kRGVzY3JpcHRpb24ubGVuZ3RoID4gMCkge1xuICAgICAgb3V0cHV0ID0gb3V0cHV0LmNvbmNhdChbaGVscGVyLndyYXAoY29tbWFuZERlc2NyaXB0aW9uLCBoZWxwV2lkdGgsIDApLCAnJ10pO1xuICAgIH1cblxuICAgIC8vIEFyZ3VtZW50c1xuICAgIGNvbnN0IGFyZ3VtZW50TGlzdCA9IGhlbHBlci52aXNpYmxlQXJndW1lbnRzKGNtZCkubWFwKChhcmd1bWVudCkgPT4ge1xuICAgICAgcmV0dXJuIGZvcm1hdEl0ZW0oaGVscGVyLmFyZ3VtZW50VGVybShhcmd1bWVudCksIGhlbHBlci5hcmd1bWVudERlc2NyaXB0aW9uKGFyZ3VtZW50KSk7XG4gICAgfSk7XG4gICAgaWYgKGFyZ3VtZW50TGlzdC5sZW5ndGggPiAwKSB7XG4gICAgICBvdXRwdXQgPSBvdXRwdXQuY29uY2F0KFsnQXJndW1lbnRzOicsIGZvcm1hdExpc3QoYXJndW1lbnRMaXN0KSwgJyddKTtcbiAgICB9XG5cbiAgICAvLyBPcHRpb25zXG4gICAgY29uc3Qgb3B0aW9uTGlzdCA9IGhlbHBlci52aXNpYmxlT3B0aW9ucyhjbWQpLm1hcCgob3B0aW9uKSA9PiB7XG4gICAgICByZXR1cm4gZm9ybWF0SXRlbShoZWxwZXIub3B0aW9uVGVybShvcHRpb24pLCBoZWxwZXIub3B0aW9uRGVzY3JpcHRpb24ob3B0aW9uKSk7XG4gICAgfSk7XG4gICAgaWYgKG9wdGlvbkxpc3QubGVuZ3RoID4gMCkge1xuICAgICAgb3V0cHV0ID0gb3V0cHV0LmNvbmNhdChbJ09wdGlvbnM6JywgZm9ybWF0TGlzdChvcHRpb25MaXN0KSwgJyddKTtcbiAgICB9XG5cbiAgICBpZiAodGhpcy5zaG93R2xvYmFsT3B0aW9ucykge1xuICAgICAgY29uc3QgZ2xvYmFsT3B0aW9uTGlzdCA9IGhlbHBlci52aXNpYmxlR2xvYmFsT3B0aW9ucyhjbWQpLm1hcCgob3B0aW9uKSA9PiB7XG4gICAgICAgIHJldHVybiBmb3JtYXRJdGVtKGhlbHBlci5vcHRpb25UZXJtKG9wdGlvbiksIGhlbHBlci5vcHRpb25EZXNjcmlwdGlvbihvcHRpb24pKTtcbiAgICAgIH0pO1xuICAgICAgaWYgKGdsb2JhbE9wdGlvbkxpc3QubGVuZ3RoID4gMCkge1xuICAgICAgICBvdXRwdXQgPSBvdXRwdXQuY29uY2F0KFsnR2xvYmFsIE9wdGlvbnM6JywgZm9ybWF0TGlzdChnbG9iYWxPcHRpb25MaXN0KSwgJyddKTtcbiAgICAgIH1cbiAgICB9XG5cbiAgICAvLyBDb21tYW5kc1xuICAgIGNvbnN0IGNvbW1hbmRMaXN0ID0gaGVscGVyLnZpc2libGVDb21tYW5kcyhjbWQpLm1hcCgoY21kKSA9PiB7XG4gICAgICByZXR1cm4gZm9ybWF0SXRlbShoZWxwZXIuc3ViY29tbWFuZFRlcm0oY21kKSwgaGVscGVyLnN1YmNvbW1hbmREZXNjcmlwdGlvbihjbWQpKTtcbiAgICB9KTtcbiAgICBpZiAoY29tbWFuZExpc3QubGVuZ3RoID4gMCkge1xuICAgICAgb3V0cHV0ID0gb3V0cHV0LmNvbmNhdChbJ0NvbW1hbmRzOicsIGZvcm1hdExpc3QoY29tbWFuZExpc3QpLCAnJ10pO1xuICAgIH1cblxuICAgIHJldHVybiBvdXRwdXQuam9pbignXFxuJyk7XG4gIH1cblxuICAvKipcbiAgICogQ2FsY3VsYXRlIHRoZSBwYWQgd2lkdGggZnJvbSB0aGUgbWF4aW11bSB0ZXJtIGxlbmd0aC5cbiAgICpcbiAgICogQHBhcmFtIHtDb21tYW5kfSBjbWRcbiAgICogQHBhcmFtIHtIZWxwfSBoZWxwZXJcbiAgICogQHJldHVybnMge251bWJlcn1cbiAgICovXG5cbiAgcGFkV2lkdGgoY21kLCBoZWxwZXIpIHtcbiAgICByZXR1cm4gTWF0aC5tYXgoXG4gICAgICBoZWxwZXIubG9uZ2VzdE9wdGlvblRlcm1MZW5ndGgoY21kLCBoZWxwZXIpLFxuICAgICAgaGVscGVyLmxvbmdlc3RHbG9iYWxPcHRpb25UZXJtTGVuZ3RoKGNtZCwgaGVscGVyKSxcbiAgICAgIGhlbHBlci5sb25nZXN0U3ViY29tbWFuZFRlcm1MZW5ndGgoY21kLCBoZWxwZXIpLFxuICAgICAgaGVscGVyLmxvbmdlc3RBcmd1bWVudFRlcm1MZW5ndGgoY21kLCBoZWxwZXIpXG4gICAgKTtcbiAgfVxuXG4gIC8qKlxuICAgKiBXcmFwIHRoZSBnaXZlbiBzdHJpbmcgdG8gd2lkdGggY2hhcmFjdGVycyBwZXIgbGluZSwgd2l0aCBsaW5lcyBhZnRlciB0aGUgZmlyc3QgaW5kZW50ZWQuXG4gICAqIERvIG5vdCB3cmFwIGlmIGluc3VmZmljaWVudCByb29tIGZvciB3cmFwcGluZyAobWluQ29sdW1uV2lkdGgpLCBvciBzdHJpbmcgaXMgbWFudWFsbHkgZm9ybWF0dGVkLlxuICAgKlxuICAgKiBAcGFyYW0ge3N0cmluZ30gc3RyXG4gICAqIEBwYXJhbSB7bnVtYmVyfSB3aWR0aFxuICAgKiBAcGFyYW0ge251bWJlcn0gaW5kZW50XG4gICAqIEBwYXJhbSB7bnVtYmVyfSBbbWluQ29sdW1uV2lkdGg9NDBdXG4gICAqIEByZXR1cm4ge3N0cmluZ31cbiAgICpcbiAgICovXG5cbiAgd3JhcChzdHIsIHdpZHRoLCBpbmRlbnQsIG1pbkNvbHVtbldpZHRoID0gNDApIHtcbiAgICAvLyBGdWxsIFxccyBjaGFyYWN0ZXJzLCBtaW51cyB0aGUgbGluZWZlZWRzLlxuICAgIGNvbnN0IGluZGVudHMgPSAnIFxcXFxmXFxcXHRcXFxcdlxcdTAwYTBcXHUxNjgwXFx1MjAwMC1cXHUyMDBhXFx1MjAyZlxcdTIwNWZcXHUzMDAwXFx1ZmVmZic7XG4gICAgLy8gRGV0ZWN0IG1hbnVhbGx5IHdyYXBwZWQgYW5kIGluZGVudGVkIHN0cmluZ3MgYnkgc2VhcmNoaW5nIGZvciBsaW5lIGJyZWFrIGZvbGxvd2VkIGJ5IHNwYWNlcy5cbiAgICBjb25zdCBtYW51YWxJbmRlbnQgPSBuZXcgUmVnRXhwKGBbXFxcXG5dWyR7aW5kZW50c31dK2ApO1xuICAgIGlmIChzdHIubWF0Y2gobWFudWFsSW5kZW50KSkgcmV0dXJuIHN0cjtcbiAgICAvLyBEbyBub3Qgd3JhcCBpZiBub3QgZW5vdWdoIHJvb20gZm9yIGEgd3JhcHBlZCBjb2x1bW4gb2YgdGV4dCAoYXMgY291bGQgZW5kIHVwIHdpdGggYSB3b3JkIHBlciBsaW5lKS5cbiAgICBjb25zdCBjb2x1bW5XaWR0aCA9IHdpZHRoIC0gaW5kZW50O1xuICAgIGlmIChjb2x1bW5XaWR0aCA8IG1pbkNvbHVtbldpZHRoKSByZXR1cm4gc3RyO1xuXG4gICAgY29uc3QgbGVhZGluZ1N0ciA9IHN0ci5zbGljZSgwLCBpbmRlbnQpO1xuICAgIGNvbnN0IGNvbHVtblRleHQgPSBzdHIuc2xpY2UoaW5kZW50KS5yZXBsYWNlKCdcXHJcXG4nLCAnXFxuJyk7XG4gICAgY29uc3QgaW5kZW50U3RyaW5nID0gJyAnLnJlcGVhdChpbmRlbnQpO1xuICAgIGNvbnN0IHplcm9XaWR0aFNwYWNlID0gJ1xcdTIwMEInO1xuICAgIGNvbnN0IGJyZWFrcyA9IGBcXFxccyR7emVyb1dpZHRoU3BhY2V9YDtcbiAgICAvLyBNYXRjaCBsaW5lIGVuZCAoc28gZW1wdHkgbGluZXMgZG9uJ3QgY29sbGFwc2UpLFxuICAgIC8vIG9yIGFzIG11Y2ggdGV4dCBhcyB3aWxsIGZpdCBpbiBjb2x1bW4sIG9yIGV4Y2VzcyB0ZXh0IHVwIHRvIGZpcnN0IGJyZWFrLlxuICAgIGNvbnN0IHJlZ2V4ID0gbmV3IFJlZ0V4cChgXFxufC57MSwke2NvbHVtbldpZHRoIC0gMX19KFske2JyZWFrc31dfCQpfFteJHticmVha3N9XSs/KFske2JyZWFrc31dfCQpYCwgJ2cnKTtcbiAgICBjb25zdCBsaW5lcyA9IGNvbHVtblRleHQubWF0Y2gocmVnZXgpIHx8IFtdO1xuICAgIHJldHVybiBsZWFkaW5nU3RyICsgbGluZXMubWFwKChsaW5lLCBpKSA9PiB7XG4gICAgICBpZiAobGluZSA9PT0gJ1xcbicpIHJldHVybiAnJzsgLy8gcHJlc2VydmUgZW1wdHkgbGluZXNcbiAgICAgIHJldHVybiAoKGkgPiAwKSA/IGluZGVudFN0cmluZyA6ICcnKSArIGxpbmUudHJpbUVuZCgpO1xuICAgIH0pLmpvaW4oJ1xcbicpO1xuICB9XG59XG5cbmV4cG9ydHMuSGVscCA9IEhlbHA7XG4iLCJjb25zdCB7IEludmFsaWRBcmd1bWVudEVycm9yIH0gPSByZXF1aXJlKCcuL2Vycm9yLmpzJyk7XG5cbi8vIEB0cy1jaGVja1xuXG5jbGFzcyBPcHRpb24ge1xuICAvKipcbiAgICogSW5pdGlhbGl6ZSBhIG5ldyBgT3B0aW9uYCB3aXRoIHRoZSBnaXZlbiBgZmxhZ3NgIGFuZCBgZGVzY3JpcHRpb25gLlxuICAgKlxuICAgKiBAcGFyYW0ge3N0cmluZ30gZmxhZ3NcbiAgICogQHBhcmFtIHtzdHJpbmd9IFtkZXNjcmlwdGlvbl1cbiAgICovXG5cbiAgY29uc3RydWN0b3IoZmxhZ3MsIGRlc2NyaXB0aW9uKSB7XG4gICAgdGhpcy5mbGFncyA9IGZsYWdzO1xuICAgIHRoaXMuZGVzY3JpcHRpb24gPSBkZXNjcmlwdGlvbiB8fCAnJztcblxuICAgIHRoaXMucmVxdWlyZWQgPSBmbGFncy5pbmNsdWRlcygnPCcpOyAvLyBBIHZhbHVlIG11c3QgYmUgc3VwcGxpZWQgd2hlbiB0aGUgb3B0aW9uIGlzIHNwZWNpZmllZC5cbiAgICB0aGlzLm9wdGlvbmFsID0gZmxhZ3MuaW5jbHVkZXMoJ1snKTsgLy8gQSB2YWx1ZSBpcyBvcHRpb25hbCB3aGVuIHRoZSBvcHRpb24gaXMgc3BlY2lmaWVkLlxuICAgIC8vIHZhcmlhZGljIHRlc3QgaWdub3JlcyA8dmFsdWUsLi4uPiBldCBhbCB3aGljaCBtaWdodCBiZSB1c2VkIHRvIGRlc2NyaWJlIGN1c3RvbSBzcGxpdHRpbmcgb2Ygc2luZ2xlIGFyZ3VtZW50XG4gICAgdGhpcy52YXJpYWRpYyA9IC9cXHdcXC5cXC5cXC5bPlxcXV0kLy50ZXN0KGZsYWdzKTsgLy8gVGhlIG9wdGlvbiBjYW4gdGFrZSBtdWx0aXBsZSB2YWx1ZXMuXG4gICAgdGhpcy5tYW5kYXRvcnkgPSBmYWxzZTsgLy8gVGhlIG9wdGlvbiBtdXN0IGhhdmUgYSB2YWx1ZSBhZnRlciBwYXJzaW5nLCB3aGljaCB1c3VhbGx5IG1lYW5zIGl0IG11c3QgYmUgc3BlY2lmaWVkIG9uIGNvbW1hbmQgbGluZS5cbiAgICBjb25zdCBvcHRpb25GbGFncyA9IHNwbGl0T3B0aW9uRmxhZ3MoZmxhZ3MpO1xuICAgIHRoaXMuc2hvcnQgPSBvcHRpb25GbGFncy5zaG9ydEZsYWc7XG4gICAgdGhpcy5sb25nID0gb3B0aW9uRmxhZ3MubG9uZ0ZsYWc7XG4gICAgdGhpcy5uZWdhdGUgPSBmYWxzZTtcbiAgICBpZiAodGhpcy5sb25nKSB7XG4gICAgICB0aGlzLm5lZ2F0ZSA9IHRoaXMubG9uZy5zdGFydHNXaXRoKCctLW5vLScpO1xuICAgIH1cbiAgICB0aGlzLmRlZmF1bHRWYWx1ZSA9IHVuZGVmaW5lZDtcbiAgICB0aGlzLmRlZmF1bHRWYWx1ZURlc2NyaXB0aW9uID0gdW5kZWZpbmVkO1xuICAgIHRoaXMucHJlc2V0QXJnID0gdW5kZWZpbmVkO1xuICAgIHRoaXMuZW52VmFyID0gdW5kZWZpbmVkO1xuICAgIHRoaXMucGFyc2VBcmcgPSB1bmRlZmluZWQ7XG4gICAgdGhpcy5oaWRkZW4gPSBmYWxzZTtcbiAgICB0aGlzLmFyZ0Nob2ljZXMgPSB1bmRlZmluZWQ7XG4gICAgdGhpcy5jb25mbGljdHNXaXRoID0gW107XG4gICAgdGhpcy5pbXBsaWVkID0gdW5kZWZpbmVkO1xuICB9XG5cbiAgLyoqXG4gICAqIFNldCB0aGUgZGVmYXVsdCB2YWx1ZSwgYW5kIG9wdGlvbmFsbHkgc3VwcGx5IHRoZSBkZXNjcmlwdGlvbiB0byBiZSBkaXNwbGF5ZWQgaW4gdGhlIGhlbHAuXG4gICAqXG4gICAqIEBwYXJhbSB7YW55fSB2YWx1ZVxuICAgKiBAcGFyYW0ge3N0cmluZ30gW2Rlc2NyaXB0aW9uXVxuICAgKiBAcmV0dXJuIHtPcHRpb259XG4gICAqL1xuXG4gIGRlZmF1bHQodmFsdWUsIGRlc2NyaXB0aW9uKSB7XG4gICAgdGhpcy5kZWZhdWx0VmFsdWUgPSB2YWx1ZTtcbiAgICB0aGlzLmRlZmF1bHRWYWx1ZURlc2NyaXB0aW9uID0gZGVzY3JpcHRpb247XG4gICAgcmV0dXJuIHRoaXM7XG4gIH1cblxuICAvKipcbiAgICogUHJlc2V0IHRvIHVzZSB3aGVuIG9wdGlvbiB1c2VkIHdpdGhvdXQgb3B0aW9uLWFyZ3VtZW50LCBlc3BlY2lhbGx5IG9wdGlvbmFsIGJ1dCBhbHNvIGJvb2xlYW4gYW5kIG5lZ2F0ZWQuXG4gICAqIFRoZSBjdXN0b20gcHJvY2Vzc2luZyAocGFyc2VBcmcpIGlzIGNhbGxlZC5cbiAgICpcbiAgICogQGV4YW1wbGVcbiAgICogbmV3IE9wdGlvbignLS1jb2xvcicpLmRlZmF1bHQoJ0dSRVlTQ0FMRScpLnByZXNldCgnUkdCJyk7XG4gICAqIG5ldyBPcHRpb24oJy0tZG9uYXRlIFthbW91bnRdJykucHJlc2V0KCcyMCcpLmFyZ1BhcnNlcihwYXJzZUZsb2F0KTtcbiAgICpcbiAgICogQHBhcmFtIHthbnl9IGFyZ1xuICAgKiBAcmV0dXJuIHtPcHRpb259XG4gICAqL1xuXG4gIHByZXNldChhcmcpIHtcbiAgICB0aGlzLnByZXNldEFyZyA9IGFyZztcbiAgICByZXR1cm4gdGhpcztcbiAgfVxuXG4gIC8qKlxuICAgKiBBZGQgb3B0aW9uIG5hbWUocykgdGhhdCBjb25mbGljdCB3aXRoIHRoaXMgb3B0aW9uLlxuICAgKiBBbiBlcnJvciB3aWxsIGJlIGRpc3BsYXllZCBpZiBjb25mbGljdGluZyBvcHRpb25zIGFyZSBmb3VuZCBkdXJpbmcgcGFyc2luZy5cbiAgICpcbiAgICogQGV4YW1wbGVcbiAgICogbmV3IE9wdGlvbignLS1yZ2InKS5jb25mbGljdHMoJ2NteWsnKTtcbiAgICogbmV3IE9wdGlvbignLS1qcycpLmNvbmZsaWN0cyhbJ3RzJywgJ2pzeCddKTtcbiAgICpcbiAgICogQHBhcmFtIHtzdHJpbmcgfCBzdHJpbmdbXX0gbmFtZXNcbiAgICogQHJldHVybiB7T3B0aW9ufVxuICAgKi9cblxuICBjb25mbGljdHMobmFtZXMpIHtcbiAgICB0aGlzLmNvbmZsaWN0c1dpdGggPSB0aGlzLmNvbmZsaWN0c1dpdGguY29uY2F0KG5hbWVzKTtcbiAgICByZXR1cm4gdGhpcztcbiAgfVxuXG4gIC8qKlxuICAgKiBTcGVjaWZ5IGltcGxpZWQgb3B0aW9uIHZhbHVlcyBmb3Igd2hlbiB0aGlzIG9wdGlvbiBpcyBzZXQgYW5kIHRoZSBpbXBsaWVkIG9wdGlvbnMgYXJlIG5vdC5cbiAgICpcbiAgICogVGhlIGN1c3RvbSBwcm9jZXNzaW5nIChwYXJzZUFyZykgaXMgbm90IGNhbGxlZCBvbiB0aGUgaW1wbGllZCB2YWx1ZXMuXG4gICAqXG4gICAqIEBleGFtcGxlXG4gICAqIHByb2dyYW1cbiAgICogICAuYWRkT3B0aW9uKG5ldyBPcHRpb24oJy0tbG9nJywgJ3dyaXRlIGxvZ2dpbmcgaW5mb3JtYXRpb24gdG8gZmlsZScpKVxuICAgKiAgIC5hZGRPcHRpb24obmV3IE9wdGlvbignLS10cmFjZScsICdsb2cgZXh0cmEgZGV0YWlscycpLmltcGxpZXMoeyBsb2c6ICd0cmFjZS50eHQnIH0pKTtcbiAgICpcbiAgICogQHBhcmFtIHtPYmplY3R9IGltcGxpZWRPcHRpb25WYWx1ZXNcbiAgICogQHJldHVybiB7T3B0aW9ufVxuICAgKi9cbiAgaW1wbGllcyhpbXBsaWVkT3B0aW9uVmFsdWVzKSB7XG4gICAgbGV0IG5ld0ltcGxpZWQgPSBpbXBsaWVkT3B0aW9uVmFsdWVzO1xuICAgIGlmICh0eXBlb2YgaW1wbGllZE9wdGlvblZhbHVlcyA9PT0gJ3N0cmluZycpIHtcbiAgICAgIC8vIHN0cmluZyBpcyBub3QgZG9jdW1lbnRlZCwgYnV0IGVhc3kgbWlzdGFrZSBhbmQgd2UgY2FuIGRvIHdoYXQgdXNlciBwcm9iYWJseSBpbnRlbmRlZC5cbiAgICAgIG5ld0ltcGxpZWQgPSB7IFtpbXBsaWVkT3B0aW9uVmFsdWVzXTogdHJ1ZSB9O1xuICAgIH1cbiAgICB0aGlzLmltcGxpZWQgPSBPYmplY3QuYXNzaWduKHRoaXMuaW1wbGllZCB8fCB7fSwgbmV3SW1wbGllZCk7XG4gICAgcmV0dXJuIHRoaXM7XG4gIH1cblxuICAvKipcbiAgICogU2V0IGVudmlyb25tZW50IHZhcmlhYmxlIHRvIGNoZWNrIGZvciBvcHRpb24gdmFsdWUuXG4gICAqXG4gICAqIEFuIGVudmlyb25tZW50IHZhcmlhYmxlIGlzIG9ubHkgdXNlZCBpZiB3aGVuIHByb2Nlc3NlZCB0aGUgY3VycmVudCBvcHRpb24gdmFsdWUgaXNcbiAgICogdW5kZWZpbmVkLCBvciB0aGUgc291cmNlIG9mIHRoZSBjdXJyZW50IHZhbHVlIGlzICdkZWZhdWx0JyBvciAnY29uZmlnJyBvciAnZW52Jy5cbiAgICpcbiAgICogQHBhcmFtIHtzdHJpbmd9IG5hbWVcbiAgICogQHJldHVybiB7T3B0aW9ufVxuICAgKi9cblxuICBlbnYobmFtZSkge1xuICAgIHRoaXMuZW52VmFyID0gbmFtZTtcbiAgICByZXR1cm4gdGhpcztcbiAgfVxuXG4gIC8qKlxuICAgKiBTZXQgdGhlIGN1c3RvbSBoYW5kbGVyIGZvciBwcm9jZXNzaW5nIENMSSBvcHRpb24gYXJndW1lbnRzIGludG8gb3B0aW9uIHZhbHVlcy5cbiAgICpcbiAgICogQHBhcmFtIHtGdW5jdGlvbn0gW2ZuXVxuICAgKiBAcmV0dXJuIHtPcHRpb259XG4gICAqL1xuXG4gIGFyZ1BhcnNlcihmbikge1xuICAgIHRoaXMucGFyc2VBcmcgPSBmbjtcbiAgICByZXR1cm4gdGhpcztcbiAgfVxuXG4gIC8qKlxuICAgKiBXaGV0aGVyIHRoZSBvcHRpb24gaXMgbWFuZGF0b3J5IGFuZCBtdXN0IGhhdmUgYSB2YWx1ZSBhZnRlciBwYXJzaW5nLlxuICAgKlxuICAgKiBAcGFyYW0ge2Jvb2xlYW59IFttYW5kYXRvcnk9dHJ1ZV1cbiAgICogQHJldHVybiB7T3B0aW9ufVxuICAgKi9cblxuICBtYWtlT3B0aW9uTWFuZGF0b3J5KG1hbmRhdG9yeSA9IHRydWUpIHtcbiAgICB0aGlzLm1hbmRhdG9yeSA9ICEhbWFuZGF0b3J5O1xuICAgIHJldHVybiB0aGlzO1xuICB9XG5cbiAgLyoqXG4gICAqIEhpZGUgb3B0aW9uIGluIGhlbHAuXG4gICAqXG4gICAqIEBwYXJhbSB7Ym9vbGVhbn0gW2hpZGU9dHJ1ZV1cbiAgICogQHJldHVybiB7T3B0aW9ufVxuICAgKi9cblxuICBoaWRlSGVscChoaWRlID0gdHJ1ZSkge1xuICAgIHRoaXMuaGlkZGVuID0gISFoaWRlO1xuICAgIHJldHVybiB0aGlzO1xuICB9XG5cbiAgLyoqXG4gICAqIEBhcGkgcHJpdmF0ZVxuICAgKi9cblxuICBfY29uY2F0VmFsdWUodmFsdWUsIHByZXZpb3VzKSB7XG4gICAgaWYgKHByZXZpb3VzID09PSB0aGlzLmRlZmF1bHRWYWx1ZSB8fCAhQXJyYXkuaXNBcnJheShwcmV2aW91cykpIHtcbiAgICAgIHJldHVybiBbdmFsdWVdO1xuICAgIH1cblxuICAgIHJldHVybiBwcmV2aW91cy5jb25jYXQodmFsdWUpO1xuICB9XG5cbiAgLyoqXG4gICAqIE9ubHkgYWxsb3cgb3B0aW9uIHZhbHVlIHRvIGJlIG9uZSBvZiBjaG9pY2VzLlxuICAgKlxuICAgKiBAcGFyYW0ge3N0cmluZ1tdfSB2YWx1ZXNcbiAgICogQHJldHVybiB7T3B0aW9ufVxuICAgKi9cblxuICBjaG9pY2VzKHZhbHVlcykge1xuICAgIHRoaXMuYXJnQ2hvaWNlcyA9IHZhbHVlcy5zbGljZSgpO1xuICAgIHRoaXMucGFyc2VBcmcgPSAoYXJnLCBwcmV2aW91cykgPT4ge1xuICAgICAgaWYgKCF0aGlzLmFyZ0Nob2ljZXMuaW5jbHVkZXMoYXJnKSkge1xuICAgICAgICB0aHJvdyBuZXcgSW52YWxpZEFyZ3VtZW50RXJyb3IoYEFsbG93ZWQgY2hvaWNlcyBhcmUgJHt0aGlzLmFyZ0Nob2ljZXMuam9pbignLCAnKX0uYCk7XG4gICAgICB9XG4gICAgICBpZiAodGhpcy52YXJpYWRpYykge1xuICAgICAgICByZXR1cm4gdGhpcy5fY29uY2F0VmFsdWUoYXJnLCBwcmV2aW91cyk7XG4gICAgICB9XG4gICAgICByZXR1cm4gYXJnO1xuICAgIH07XG4gICAgcmV0dXJuIHRoaXM7XG4gIH1cblxuICAvKipcbiAgICogUmV0dXJuIG9wdGlvbiBuYW1lLlxuICAgKlxuICAgKiBAcmV0dXJuIHtzdHJpbmd9XG4gICAqL1xuXG4gIG5hbWUoKSB7XG4gICAgaWYgKHRoaXMubG9uZykge1xuICAgICAgcmV0dXJuIHRoaXMubG9uZy5yZXBsYWNlKC9eLS0vLCAnJyk7XG4gICAgfVxuICAgIHJldHVybiB0aGlzLnNob3J0LnJlcGxhY2UoL14tLywgJycpO1xuICB9XG5cbiAgLyoqXG4gICAqIFJldHVybiBvcHRpb24gbmFtZSwgaW4gYSBjYW1lbGNhc2UgZm9ybWF0IHRoYXQgY2FuIGJlIHVzZWRcbiAgICogYXMgYSBvYmplY3QgYXR0cmlidXRlIGtleS5cbiAgICpcbiAgICogQHJldHVybiB7c3RyaW5nfVxuICAgKiBAYXBpIHByaXZhdGVcbiAgICovXG5cbiAgYXR0cmlidXRlTmFtZSgpIHtcbiAgICByZXR1cm4gY2FtZWxjYXNlKHRoaXMubmFtZSgpLnJlcGxhY2UoL15uby0vLCAnJykpO1xuICB9XG5cbiAgLyoqXG4gICAqIENoZWNrIGlmIGBhcmdgIG1hdGNoZXMgdGhlIHNob3J0IG9yIGxvbmcgZmxhZy5cbiAgICpcbiAgICogQHBhcmFtIHtzdHJpbmd9IGFyZ1xuICAgKiBAcmV0dXJuIHtib29sZWFufVxuICAgKiBAYXBpIHByaXZhdGVcbiAgICovXG5cbiAgaXMoYXJnKSB7XG4gICAgcmV0dXJuIHRoaXMuc2hvcnQgPT09IGFyZyB8fCB0aGlzLmxvbmcgPT09IGFyZztcbiAgfVxuXG4gIC8qKlxuICAgKiBSZXR1cm4gd2hldGhlciBhIGJvb2xlYW4gb3B0aW9uLlxuICAgKlxuICAgKiBPcHRpb25zIGFyZSBvbmUgb2YgYm9vbGVhbiwgbmVnYXRlZCwgcmVxdWlyZWQgYXJndW1lbnQsIG9yIG9wdGlvbmFsIGFyZ3VtZW50LlxuICAgKlxuICAgKiBAcmV0dXJuIHtib29sZWFufVxuICAgKiBAYXBpIHByaXZhdGVcbiAgICovXG5cbiAgaXNCb29sZWFuKCkge1xuICAgIHJldHVybiAhdGhpcy5yZXF1aXJlZCAmJiAhdGhpcy5vcHRpb25hbCAmJiAhdGhpcy5uZWdhdGU7XG4gIH1cbn1cblxuLyoqXG4gKiBUaGlzIGNsYXNzIGlzIHRvIG1ha2UgaXQgZWFzaWVyIHRvIHdvcmsgd2l0aCBkdWFsIG9wdGlvbnMsIHdpdGhvdXQgY2hhbmdpbmcgdGhlIGV4aXN0aW5nXG4gKiBpbXBsZW1lbnRhdGlvbi4gV2Ugc3VwcG9ydCBzZXBhcmF0ZSBkdWFsIG9wdGlvbnMgZm9yIHNlcGFyYXRlIHBvc2l0aXZlIGFuZCBuZWdhdGl2ZSBvcHRpb25zLFxuICogbGlrZSBgLS1idWlsZGAgYW5kIGAtLW5vLWJ1aWxkYCwgd2hpY2ggc2hhcmUgYSBzaW5nbGUgb3B0aW9uIHZhbHVlLiBUaGlzIHdvcmtzIG5pY2VseSBmb3Igc29tZVxuICogdXNlIGNhc2VzLCBidXQgaXMgdHJpY2t5IGZvciBvdGhlcnMgd2hlcmUgd2Ugd2FudCBzZXBhcmF0ZSBiZWhhdmlvdXJzIGRlc3BpdGVcbiAqIHRoZSBzaW5nbGUgc2hhcmVkIG9wdGlvbiB2YWx1ZS5cbiAqL1xuY2xhc3MgRHVhbE9wdGlvbnMge1xuICAvKipcbiAgICogQHBhcmFtIHtPcHRpb25bXX0gb3B0aW9uc1xuICAgKi9cbiAgY29uc3RydWN0b3Iob3B0aW9ucykge1xuICAgIHRoaXMucG9zaXRpdmVPcHRpb25zID0gbmV3IE1hcCgpO1xuICAgIHRoaXMubmVnYXRpdmVPcHRpb25zID0gbmV3IE1hcCgpO1xuICAgIHRoaXMuZHVhbE9wdGlvbnMgPSBuZXcgU2V0KCk7XG4gICAgb3B0aW9ucy5mb3JFYWNoKG9wdGlvbiA9PiB7XG4gICAgICBpZiAob3B0aW9uLm5lZ2F0ZSkge1xuICAgICAgICB0aGlzLm5lZ2F0aXZlT3B0aW9ucy5zZXQob3B0aW9uLmF0dHJpYnV0ZU5hbWUoKSwgb3B0aW9uKTtcbiAgICAgIH0gZWxzZSB7XG4gICAgICAgIHRoaXMucG9zaXRpdmVPcHRpb25zLnNldChvcHRpb24uYXR0cmlidXRlTmFtZSgpLCBvcHRpb24pO1xuICAgICAgfVxuICAgIH0pO1xuICAgIHRoaXMubmVnYXRpdmVPcHRpb25zLmZvckVhY2goKHZhbHVlLCBrZXkpID0+IHtcbiAgICAgIGlmICh0aGlzLnBvc2l0aXZlT3B0aW9ucy5oYXMoa2V5KSkge1xuICAgICAgICB0aGlzLmR1YWxPcHRpb25zLmFkZChrZXkpO1xuICAgICAgfVxuICAgIH0pO1xuICB9XG5cbiAgLyoqXG4gICAqIERpZCB0aGUgdmFsdWUgY29tZSBmcm9tIHRoZSBvcHRpb24sIGFuZCBub3QgZnJvbSBwb3NzaWJsZSBtYXRjaGluZyBkdWFsIG9wdGlvbj9cbiAgICpcbiAgICogQHBhcmFtIHthbnl9IHZhbHVlXG4gICAqIEBwYXJhbSB7T3B0aW9ufSBvcHRpb25cbiAgICogQHJldHVybnMge2Jvb2xlYW59XG4gICAqL1xuICB2YWx1ZUZyb21PcHRpb24odmFsdWUsIG9wdGlvbikge1xuICAgIGNvbnN0IG9wdGlvbktleSA9IG9wdGlvbi5hdHRyaWJ1dGVOYW1lKCk7XG4gICAgaWYgKCF0aGlzLmR1YWxPcHRpb25zLmhhcyhvcHRpb25LZXkpKSByZXR1cm4gdHJ1ZTtcblxuICAgIC8vIFVzZSB0aGUgdmFsdWUgdG8gZGVkdWNlIGlmIChwcm9iYWJseSkgY2FtZSBmcm9tIHRoZSBvcHRpb24uXG4gICAgY29uc3QgcHJlc2V0ID0gdGhpcy5uZWdhdGl2ZU9wdGlvbnMuZ2V0KG9wdGlvbktleSkucHJlc2V0QXJnO1xuICAgIGNvbnN0IG5lZ2F0aXZlVmFsdWUgPSAocHJlc2V0ICE9PSB1bmRlZmluZWQpID8gcHJlc2V0IDogZmFsc2U7XG4gICAgcmV0dXJuIG9wdGlvbi5uZWdhdGUgPT09IChuZWdhdGl2ZVZhbHVlID09PSB2YWx1ZSk7XG4gIH1cbn1cblxuLyoqXG4gKiBDb252ZXJ0IHN0cmluZyBmcm9tIGtlYmFiLWNhc2UgdG8gY2FtZWxDYXNlLlxuICpcbiAqIEBwYXJhbSB7c3RyaW5nfSBzdHJcbiAqIEByZXR1cm4ge3N0cmluZ31cbiAqIEBhcGkgcHJpdmF0ZVxuICovXG5cbmZ1bmN0aW9uIGNhbWVsY2FzZShzdHIpIHtcbiAgcmV0dXJuIHN0ci5zcGxpdCgnLScpLnJlZHVjZSgoc3RyLCB3b3JkKSA9PiB7XG4gICAgcmV0dXJuIHN0ciArIHdvcmRbMF0udG9VcHBlckNhc2UoKSArIHdvcmQuc2xpY2UoMSk7XG4gIH0pO1xufVxuXG4vKipcbiAqIFNwbGl0IHRoZSBzaG9ydCBhbmQgbG9uZyBmbGFnIG91dCBvZiBzb21ldGhpbmcgbGlrZSAnLW0sLS1taXhlZCA8dmFsdWU+J1xuICpcbiAqIEBhcGkgcHJpdmF0ZVxuICovXG5cbmZ1bmN0aW9uIHNwbGl0T3B0aW9uRmxhZ3MoZmxhZ3MpIHtcbiAgbGV0IHNob3J0RmxhZztcbiAgbGV0IGxvbmdGbGFnO1xuICAvLyBVc2Ugb3JpZ2luYWwgdmVyeSBsb29zZSBwYXJzaW5nIHRvIG1haW50YWluIGJhY2t3YXJkcyBjb21wYXRpYmlsaXR5IGZvciBub3csXG4gIC8vIHdoaWNoIGFsbG93ZWQgZm9yIGV4YW1wbGUgdW5pbnRlbmRlZCBgLXN3LCAtLXNob3J0LXdvcmRgIFtzaWNdLlxuICBjb25zdCBmbGFnUGFydHMgPSBmbGFncy5zcGxpdCgvWyB8LF0rLyk7XG4gIGlmIChmbGFnUGFydHMubGVuZ3RoID4gMSAmJiAhL15bWzxdLy50ZXN0KGZsYWdQYXJ0c1sxXSkpIHNob3J0RmxhZyA9IGZsYWdQYXJ0cy5zaGlmdCgpO1xuICBsb25nRmxhZyA9IGZsYWdQYXJ0cy5zaGlmdCgpO1xuICAvLyBBZGQgc3VwcG9ydCBmb3IgbG9uZSBzaG9ydCBmbGFnIHdpdGhvdXQgc2lnbmlmaWNhbnRseSBjaGFuZ2luZyBwYXJzaW5nIVxuICBpZiAoIXNob3J0RmxhZyAmJiAvXi1bXi1dJC8udGVzdChsb25nRmxhZykpIHtcbiAgICBzaG9ydEZsYWcgPSBsb25nRmxhZztcbiAgICBsb25nRmxhZyA9IHVuZGVmaW5lZDtcbiAgfVxuICByZXR1cm4geyBzaG9ydEZsYWcsIGxvbmdGbGFnIH07XG59XG5cbmV4cG9ydHMuT3B0aW9uID0gT3B0aW9uO1xuZXhwb3J0cy5zcGxpdE9wdGlvbkZsYWdzID0gc3BsaXRPcHRpb25GbGFncztcbmV4cG9ydHMuRHVhbE9wdGlvbnMgPSBEdWFsT3B0aW9ucztcbiIsImNvbnN0IG1heERpc3RhbmNlID0gMztcblxuZnVuY3Rpb24gZWRpdERpc3RhbmNlKGEsIGIpIHtcbiAgLy8gaHR0cHM6Ly9lbi53aWtpcGVkaWEub3JnL3dpa2kvRGFtZXJhdeKAk0xldmVuc2h0ZWluX2Rpc3RhbmNlXG4gIC8vIENhbGN1bGF0aW5nIG9wdGltYWwgc3RyaW5nIGFsaWdubWVudCBkaXN0YW5jZSwgbm8gc3Vic3RyaW5nIGlzIGVkaXRlZCBtb3JlIHRoYW4gb25jZS5cbiAgLy8gKFNpbXBsZSBpbXBsZW1lbnRhdGlvbi4pXG5cbiAgLy8gUXVpY2sgZWFybHkgZXhpdCwgcmV0dXJuIHdvcnN0IGNhc2UuXG4gIGlmIChNYXRoLmFicyhhLmxlbmd0aCAtIGIubGVuZ3RoKSA+IG1heERpc3RhbmNlKSByZXR1cm4gTWF0aC5tYXgoYS5sZW5ndGgsIGIubGVuZ3RoKTtcblxuICAvLyBkaXN0YW5jZSBiZXR3ZWVuIHByZWZpeCBzdWJzdHJpbmdzIG9mIGEgYW5kIGJcbiAgY29uc3QgZCA9IFtdO1xuXG4gIC8vIHB1cmUgZGVsZXRpb25zIHR1cm4gYSBpbnRvIGVtcHR5IHN0cmluZ1xuICBmb3IgKGxldCBpID0gMDsgaSA8PSBhLmxlbmd0aDsgaSsrKSB7XG4gICAgZFtpXSA9IFtpXTtcbiAgfVxuICAvLyBwdXJlIGluc2VydGlvbnMgdHVybiBlbXB0eSBzdHJpbmcgaW50byBiXG4gIGZvciAobGV0IGogPSAwOyBqIDw9IGIubGVuZ3RoOyBqKyspIHtcbiAgICBkWzBdW2pdID0gajtcbiAgfVxuXG4gIC8vIGZpbGwgbWF0cml4XG4gIGZvciAobGV0IGogPSAxOyBqIDw9IGIubGVuZ3RoOyBqKyspIHtcbiAgICBmb3IgKGxldCBpID0gMTsgaSA8PSBhLmxlbmd0aDsgaSsrKSB7XG4gICAgICBsZXQgY29zdCA9IDE7XG4gICAgICBpZiAoYVtpIC0gMV0gPT09IGJbaiAtIDFdKSB7XG4gICAgICAgIGNvc3QgPSAwO1xuICAgICAgfSBlbHNlIHtcbiAgICAgICAgY29zdCA9IDE7XG4gICAgICB9XG4gICAgICBkW2ldW2pdID0gTWF0aC5taW4oXG4gICAgICAgIGRbaSAtIDFdW2pdICsgMSwgLy8gZGVsZXRpb25cbiAgICAgICAgZFtpXVtqIC0gMV0gKyAxLCAvLyBpbnNlcnRpb25cbiAgICAgICAgZFtpIC0gMV1baiAtIDFdICsgY29zdCAvLyBzdWJzdGl0dXRpb25cbiAgICAgICk7XG4gICAgICAvLyB0cmFuc3Bvc2l0aW9uXG4gICAgICBpZiAoaSA+IDEgJiYgaiA+IDEgJiYgYVtpIC0gMV0gPT09IGJbaiAtIDJdICYmIGFbaSAtIDJdID09PSBiW2ogLSAxXSkge1xuICAgICAgICBkW2ldW2pdID0gTWF0aC5taW4oZFtpXVtqXSwgZFtpIC0gMl1baiAtIDJdICsgMSk7XG4gICAgICB9XG4gICAgfVxuICB9XG5cbiAgcmV0dXJuIGRbYS5sZW5ndGhdW2IubGVuZ3RoXTtcbn1cblxuLyoqXG4gKiBGaW5kIGNsb3NlIG1hdGNoZXMsIHJlc3RyaWN0ZWQgdG8gc2FtZSBudW1iZXIgb2YgZWRpdHMuXG4gKlxuICogQHBhcmFtIHtzdHJpbmd9IHdvcmRcbiAqIEBwYXJhbSB7c3RyaW5nW119IGNhbmRpZGF0ZXNcbiAqIEByZXR1cm5zIHtzdHJpbmd9XG4gKi9cblxuZnVuY3Rpb24gc3VnZ2VzdFNpbWlsYXIod29yZCwgY2FuZGlkYXRlcykge1xuICBpZiAoIWNhbmRpZGF0ZXMgfHwgY2FuZGlkYXRlcy5sZW5ndGggPT09IDApIHJldHVybiAnJztcbiAgLy8gcmVtb3ZlIHBvc3NpYmxlIGR1cGxpY2F0ZXNcbiAgY2FuZGlkYXRlcyA9IEFycmF5LmZyb20obmV3IFNldChjYW5kaWRhdGVzKSk7XG5cbiAgY29uc3Qgc2VhcmNoaW5nT3B0aW9ucyA9IHdvcmQuc3RhcnRzV2l0aCgnLS0nKTtcbiAgaWYgKHNlYXJjaGluZ09wdGlvbnMpIHtcbiAgICB3b3JkID0gd29yZC5zbGljZSgyKTtcbiAgICBjYW5kaWRhdGVzID0gY2FuZGlkYXRlcy5tYXAoY2FuZGlkYXRlID0+IGNhbmRpZGF0ZS5zbGljZSgyKSk7XG4gIH1cblxuICBsZXQgc2ltaWxhciA9IFtdO1xuICBsZXQgYmVzdERpc3RhbmNlID0gbWF4RGlzdGFuY2U7XG4gIGNvbnN0IG1pblNpbWlsYXJpdHkgPSAwLjQ7XG4gIGNhbmRpZGF0ZXMuZm9yRWFjaCgoY2FuZGlkYXRlKSA9PiB7XG4gICAgaWYgKGNhbmRpZGF0ZS5sZW5ndGggPD0gMSkgcmV0dXJuOyAvLyBubyBvbmUgY2hhcmFjdGVyIGd1ZXNzZXNcblxuICAgIGNvbnN0IGRpc3RhbmNlID0gZWRpdERpc3RhbmNlKHdvcmQsIGNhbmRpZGF0ZSk7XG4gICAgY29uc3QgbGVuZ3RoID0gTWF0aC5tYXgod29yZC5sZW5ndGgsIGNhbmRpZGF0ZS5sZW5ndGgpO1xuICAgIGNvbnN0IHNpbWlsYXJpdHkgPSAobGVuZ3RoIC0gZGlzdGFuY2UpIC8gbGVuZ3RoO1xuICAgIGlmIChzaW1pbGFyaXR5ID4gbWluU2ltaWxhcml0eSkge1xuICAgICAgaWYgKGRpc3RhbmNlIDwgYmVzdERpc3RhbmNlKSB7XG4gICAgICAgIC8vIGJldHRlciBlZGl0IGRpc3RhbmNlLCB0aHJvdyBhd2F5IHByZXZpb3VzIHdvcnNlIG1hdGNoZXNcbiAgICAgICAgYmVzdERpc3RhbmNlID0gZGlzdGFuY2U7XG4gICAgICAgIHNpbWlsYXIgPSBbY2FuZGlkYXRlXTtcbiAgICAgIH0gZWxzZSBpZiAoZGlzdGFuY2UgPT09IGJlc3REaXN0YW5jZSkge1xuICAgICAgICBzaW1pbGFyLnB1c2goY2FuZGlkYXRlKTtcbiAgICAgIH1cbiAgICB9XG4gIH0pO1xuXG4gIHNpbWlsYXIuc29ydCgoYSwgYikgPT4gYS5sb2NhbGVDb21wYXJlKGIpKTtcbiAgaWYgKHNlYXJjaGluZ09wdGlvbnMpIHtcbiAgICBzaW1pbGFyID0gc2ltaWxhci5tYXAoY2FuZGlkYXRlID0+IGAtLSR7Y2FuZGlkYXRlfWApO1xuICB9XG5cbiAgaWYgKHNpbWlsYXIubGVuZ3RoID4gMSkge1xuICAgIHJldHVybiBgXFxuKERpZCB5b3UgbWVhbiBvbmUgb2YgJHtzaW1pbGFyLmpvaW4oJywgJyl9PylgO1xuICB9XG4gIGlmIChzaW1pbGFyLmxlbmd0aCA9PT0gMSkge1xuICAgIHJldHVybiBgXFxuKERpZCB5b3UgbWVhbiAke3NpbWlsYXJbMF19PylgO1xuICB9XG4gIHJldHVybiAnJztcbn1cblxuZXhwb3J0cy5zdWdnZXN0U2ltaWxhciA9IHN1Z2dlc3RTaW1pbGFyO1xuIiwiXCJ1c2Ugc3RyaWN0XCI7XG5PYmplY3QuZGVmaW5lUHJvcGVydHkoZXhwb3J0cywgXCJfX2VzTW9kdWxlXCIsIHsgdmFsdWU6IHRydWUgfSk7XG5leHBvcnRzLmFzc2VydFZhbGlkUGF0dGVybiA9IHZvaWQgMDtcbmNvbnN0IE1BWF9QQVRURVJOX0xFTkdUSCA9IDEwMjQgKiA2NDtcbmNvbnN0IGFzc2VydFZhbGlkUGF0dGVybiA9IChwYXR0ZXJuKSA9PiB7XG4gICAgaWYgKHR5cGVvZiBwYXR0ZXJuICE9PSAnc3RyaW5nJykge1xuICAgICAgICB0aHJvdyBuZXcgVHlwZUVycm9yKCdpbnZhbGlkIHBhdHRlcm4nKTtcbiAgICB9XG4gICAgaWYgKHBhdHRlcm4ubGVuZ3RoID4gTUFYX1BBVFRFUk5fTEVOR1RIKSB7XG4gICAgICAgIHRocm93IG5ldyBUeXBlRXJyb3IoJ3BhdHRlcm4gaXMgdG9vIGxvbmcnKTtcbiAgICB9XG59O1xuZXhwb3J0cy5hc3NlcnRWYWxpZFBhdHRlcm4gPSBhc3NlcnRWYWxpZFBhdHRlcm47XG4vLyMgc291cmNlTWFwcGluZ1VSTD1hc3NlcnQtdmFsaWQtcGF0dGVybi5qcy5tYXAiLCJcInVzZSBzdHJpY3RcIjtcbi8vIHBhcnNlIGEgc2luZ2xlIHBhdGggcG9ydGlvblxuT2JqZWN0LmRlZmluZVByb3BlcnR5KGV4cG9ydHMsIFwiX19lc01vZHVsZVwiLCB7IHZhbHVlOiB0cnVlIH0pO1xuZXhwb3J0cy5BU1QgPSB2b2lkIDA7XG5jb25zdCBicmFjZV9leHByZXNzaW9uc19qc18xID0gcmVxdWlyZShcIi4vYnJhY2UtZXhwcmVzc2lvbnMuanNcIik7XG5jb25zdCB1bmVzY2FwZV9qc18xID0gcmVxdWlyZShcIi4vdW5lc2NhcGUuanNcIik7XG5jb25zdCB0eXBlcyA9IG5ldyBTZXQoWychJywgJz8nLCAnKycsICcqJywgJ0AnXSk7XG5jb25zdCBpc0V4dGdsb2JUeXBlID0gKGMpID0+IHR5cGVzLmhhcyhjKTtcbi8vIFBhdHRlcm5zIHRoYXQgZ2V0IHByZXBlbmRlZCB0byBiaW5kIHRvIHRoZSBzdGFydCBvZiBlaXRoZXIgdGhlXG4vLyBlbnRpcmUgc3RyaW5nLCBvciBqdXN0IGEgc2luZ2xlIHBhdGggcG9ydGlvbiwgdG8gcHJldmVudCBkb3RzXG4vLyBhbmQvb3IgdHJhdmVyc2FsIHBhdHRlcm5zLCB3aGVuIG5lZWRlZC5cbi8vIEV4dHMgZG9uJ3QgbmVlZCB0aGUgXiBvciAvIGJpdCwgYmVjYXVzZSB0aGUgcm9vdCBiaW5kcyB0aGF0IGFscmVhZHkuXG5jb25zdCBzdGFydE5vVHJhdmVyc2FsID0gJyg/ISg/Ol58LylcXFxcLlxcXFwuPyg/OiR8LykpJztcbmNvbnN0IHN0YXJ0Tm9Eb3QgPSAnKD8hXFxcXC4pJztcbi8vIGNoYXJhY3RlcnMgdGhhdCBpbmRpY2F0ZSBhIHN0YXJ0IG9mIHBhdHRlcm4gbmVlZHMgdGhlIFwibm8gZG90c1wiIGJpdCxcbi8vIGJlY2F1c2UgYSBkb3QgKm1pZ2h0KiBiZSBtYXRjaGVkLiAoIGlzIG5vdCBpbiB0aGUgbGlzdCwgYmVjYXVzZSBpblxuLy8gdGhlIGNhc2Ugb2YgYSBjaGlsZCBleHRnbG9iLCBpdCB3aWxsIGhhbmRsZSB0aGUgcHJldmVudGlvbiBpdHNlbGYuXG5jb25zdCBhZGRQYXR0ZXJuU3RhcnQgPSBuZXcgU2V0KFsnWycsICcuJ10pO1xuLy8gY2FzZXMgd2hlcmUgdHJhdmVyc2FsIGlzIEEtT0ssIG5vIGRvdCBwcmV2ZW50aW9uIG5lZWRlZFxuY29uc3QganVzdERvdHMgPSBuZXcgU2V0KFsnLi4nLCAnLiddKTtcbmNvbnN0IHJlU3BlY2lhbHMgPSBuZXcgU2V0KCcoKS4qe30rP1tdXiRcXFxcIScpO1xuY29uc3QgcmVnRXhwRXNjYXBlID0gKHMpID0+IHMucmVwbGFjZSgvWy1bXFxde30oKSorPy4sXFxcXF4kfCNcXHNdL2csICdcXFxcJCYnKTtcbi8vIGFueSBzaW5nbGUgdGhpbmcgb3RoZXIgdGhhbiAvXG5jb25zdCBxbWFyayA9ICdbXi9dJztcbi8vICogPT4gYW55IG51bWJlciBvZiBjaGFyYWN0ZXJzXG5jb25zdCBzdGFyID0gcW1hcmsgKyAnKj8nO1xuLy8gdXNlICsgd2hlbiB3ZSBuZWVkIHRvIGVuc3VyZSB0aGF0ICpzb21ldGhpbmcqIG1hdGNoZXMsIGJlY2F1c2UgdGhlICogaXNcbi8vIHRoZSBvbmx5IHRoaW5nIGluIHRoZSBwYXRoIHBvcnRpb24uXG5jb25zdCBzdGFyTm9FbXB0eSA9IHFtYXJrICsgJys/Jztcbi8vIHJlbW92ZSB0aGUgXFwgY2hhcnMgdGhhdCB3ZSBhZGRlZCBpZiB3ZSBlbmQgdXAgZG9pbmcgYSBub25tYWdpYyBjb21wYXJlXG4vLyBjb25zdCBkZXNsYXNoID0gKHM6IHN0cmluZykgPT4gcy5yZXBsYWNlKC9cXFxcKC4pL2csICckMScpXG5jbGFzcyBBU1Qge1xuICAgIHR5cGU7XG4gICAgI3Jvb3Q7XG4gICAgI2hhc01hZ2ljO1xuICAgICN1ZmxhZyA9IGZhbHNlO1xuICAgICNwYXJ0cyA9IFtdO1xuICAgICNwYXJlbnQ7XG4gICAgI3BhcmVudEluZGV4O1xuICAgICNuZWdzO1xuICAgICNmaWxsZWROZWdzID0gZmFsc2U7XG4gICAgI29wdGlvbnM7XG4gICAgI3RvU3RyaW5nO1xuICAgIC8vIHNldCB0byB0cnVlIGlmIGl0J3MgYW4gZXh0Z2xvYiB3aXRoIG5vIGNoaWxkcmVuXG4gICAgLy8gKHdoaWNoIHJlYWxseSBtZWFucyBvbmUgY2hpbGQgb2YgJycpXG4gICAgI2VtcHR5RXh0ID0gZmFsc2U7XG4gICAgY29uc3RydWN0b3IodHlwZSwgcGFyZW50LCBvcHRpb25zID0ge30pIHtcbiAgICAgICAgdGhpcy50eXBlID0gdHlwZTtcbiAgICAgICAgLy8gZXh0Z2xvYnMgYXJlIGluaGVyZW50bHkgbWFnaWNhbFxuICAgICAgICBpZiAodHlwZSlcbiAgICAgICAgICAgIHRoaXMuI2hhc01hZ2ljID0gdHJ1ZTtcbiAgICAgICAgdGhpcy4jcGFyZW50ID0gcGFyZW50O1xuICAgICAgICB0aGlzLiNyb290ID0gdGhpcy4jcGFyZW50ID8gdGhpcy4jcGFyZW50LiNyb290IDogdGhpcztcbiAgICAgICAgdGhpcy4jb3B0aW9ucyA9IHRoaXMuI3Jvb3QgPT09IHRoaXMgPyBvcHRpb25zIDogdGhpcy4jcm9vdC4jb3B0aW9ucztcbiAgICAgICAgdGhpcy4jbmVncyA9IHRoaXMuI3Jvb3QgPT09IHRoaXMgPyBbXSA6IHRoaXMuI3Jvb3QuI25lZ3M7XG4gICAgICAgIGlmICh0eXBlID09PSAnIScgJiYgIXRoaXMuI3Jvb3QuI2ZpbGxlZE5lZ3MpXG4gICAgICAgICAgICB0aGlzLiNuZWdzLnB1c2godGhpcyk7XG4gICAgICAgIHRoaXMuI3BhcmVudEluZGV4ID0gdGhpcy4jcGFyZW50ID8gdGhpcy4jcGFyZW50LiNwYXJ0cy5sZW5ndGggOiAwO1xuICAgIH1cbiAgICBnZXQgaGFzTWFnaWMoKSB7XG4gICAgICAgIC8qIGM4IGlnbm9yZSBzdGFydCAqL1xuICAgICAgICBpZiAodGhpcy4jaGFzTWFnaWMgIT09IHVuZGVmaW5lZClcbiAgICAgICAgICAgIHJldHVybiB0aGlzLiNoYXNNYWdpYztcbiAgICAgICAgLyogYzggaWdub3JlIHN0b3AgKi9cbiAgICAgICAgZm9yIChjb25zdCBwIG9mIHRoaXMuI3BhcnRzKSB7XG4gICAgICAgICAgICBpZiAodHlwZW9mIHAgPT09ICdzdHJpbmcnKVxuICAgICAgICAgICAgICAgIGNvbnRpbnVlO1xuICAgICAgICAgICAgaWYgKHAudHlwZSB8fCBwLmhhc01hZ2ljKVxuICAgICAgICAgICAgICAgIHJldHVybiAodGhpcy4jaGFzTWFnaWMgPSB0cnVlKTtcbiAgICAgICAgfVxuICAgICAgICAvLyBub3RlOiB3aWxsIGJlIHVuZGVmaW5lZCB1bnRpbCB3ZSBnZW5lcmF0ZSB0aGUgcmVnZXhwIHNyYyBhbmQgZmluZCBvdXRcbiAgICAgICAgcmV0dXJuIHRoaXMuI2hhc01hZ2ljO1xuICAgIH1cbiAgICAvLyByZWNvbnN0cnVjdHMgdGhlIHBhdHRlcm5cbiAgICB0b1N0cmluZygpIHtcbiAgICAgICAgaWYgKHRoaXMuI3RvU3RyaW5nICE9PSB1bmRlZmluZWQpXG4gICAgICAgICAgICByZXR1cm4gdGhpcy4jdG9TdHJpbmc7XG4gICAgICAgIGlmICghdGhpcy50eXBlKSB7XG4gICAgICAgICAgICByZXR1cm4gKHRoaXMuI3RvU3RyaW5nID0gdGhpcy4jcGFydHMubWFwKHAgPT4gU3RyaW5nKHApKS5qb2luKCcnKSk7XG4gICAgICAgIH1cbiAgICAgICAgZWxzZSB7XG4gICAgICAgICAgICByZXR1cm4gKHRoaXMuI3RvU3RyaW5nID1cbiAgICAgICAgICAgICAgICB0aGlzLnR5cGUgKyAnKCcgKyB0aGlzLiNwYXJ0cy5tYXAocCA9PiBTdHJpbmcocCkpLmpvaW4oJ3wnKSArICcpJyk7XG4gICAgICAgIH1cbiAgICB9XG4gICAgI2ZpbGxOZWdzKCkge1xuICAgICAgICAvKiBjOCBpZ25vcmUgc3RhcnQgKi9cbiAgICAgICAgaWYgKHRoaXMgIT09IHRoaXMuI3Jvb3QpXG4gICAgICAgICAgICB0aHJvdyBuZXcgRXJyb3IoJ3Nob3VsZCBvbmx5IGNhbGwgb24gcm9vdCcpO1xuICAgICAgICBpZiAodGhpcy4jZmlsbGVkTmVncylcbiAgICAgICAgICAgIHJldHVybiB0aGlzO1xuICAgICAgICAvKiBjOCBpZ25vcmUgc3RvcCAqL1xuICAgICAgICAvLyBjYWxsIHRvU3RyaW5nKCkgb25jZSB0byBmaWxsIHRoaXMgb3V0XG4gICAgICAgIHRoaXMudG9TdHJpbmcoKTtcbiAgICAgICAgdGhpcy4jZmlsbGVkTmVncyA9IHRydWU7XG4gICAgICAgIGxldCBuO1xuICAgICAgICB3aGlsZSAoKG4gPSB0aGlzLiNuZWdzLnBvcCgpKSkge1xuICAgICAgICAgICAgaWYgKG4udHlwZSAhPT0gJyEnKVxuICAgICAgICAgICAgICAgIGNvbnRpbnVlO1xuICAgICAgICAgICAgLy8gd2FsayB1cCB0aGUgdHJlZSwgYXBwZW5kaW5nIGV2ZXJ0aGluZyB0aGF0IGNvbWVzIEFGVEVSIHBhcmVudEluZGV4XG4gICAgICAgICAgICBsZXQgcCA9IG47XG4gICAgICAgICAgICBsZXQgcHAgPSBwLiNwYXJlbnQ7XG4gICAgICAgICAgICB3aGlsZSAocHApIHtcbiAgICAgICAgICAgICAgICBmb3IgKGxldCBpID0gcC4jcGFyZW50SW5kZXggKyAxOyAhcHAudHlwZSAmJiBpIDwgcHAuI3BhcnRzLmxlbmd0aDsgaSsrKSB7XG4gICAgICAgICAgICAgICAgICAgIGZvciAoY29uc3QgcGFydCBvZiBuLiNwYXJ0cykge1xuICAgICAgICAgICAgICAgICAgICAgICAgLyogYzggaWdub3JlIHN0YXJ0ICovXG4gICAgICAgICAgICAgICAgICAgICAgICBpZiAodHlwZW9mIHBhcnQgPT09ICdzdHJpbmcnKSB7XG4gICAgICAgICAgICAgICAgICAgICAgICAgICAgdGhyb3cgbmV3IEVycm9yKCdzdHJpbmcgcGFydCBpbiBleHRnbG9iIEFTVD8/Jyk7XG4gICAgICAgICAgICAgICAgICAgICAgICB9XG4gICAgICAgICAgICAgICAgICAgICAgICAvKiBjOCBpZ25vcmUgc3RvcCAqL1xuICAgICAgICAgICAgICAgICAgICAgICAgcGFydC5jb3B5SW4ocHAuI3BhcnRzW2ldKTtcbiAgICAgICAgICAgICAgICAgICAgfVxuICAgICAgICAgICAgICAgIH1cbiAgICAgICAgICAgICAgICBwID0gcHA7XG4gICAgICAgICAgICAgICAgcHAgPSBwLiNwYXJlbnQ7XG4gICAgICAgICAgICB9XG4gICAgICAgIH1cbiAgICAgICAgcmV0dXJuIHRoaXM7XG4gICAgfVxuICAgIHB1c2goLi4ucGFydHMpIHtcbiAgICAgICAgZm9yIChjb25zdCBwIG9mIHBhcnRzKSB7XG4gICAgICAgICAgICBpZiAocCA9PT0gJycpXG4gICAgICAgICAgICAgICAgY29udGludWU7XG4gICAgICAgICAgICAvKiBjOCBpZ25vcmUgc3RhcnQgKi9cbiAgICAgICAgICAgIGlmICh0eXBlb2YgcCAhPT0gJ3N0cmluZycgJiYgIShwIGluc3RhbmNlb2YgQVNUICYmIHAuI3BhcmVudCA9PT0gdGhpcykpIHtcbiAgICAgICAgICAgICAgICB0aHJvdyBuZXcgRXJyb3IoJ2ludmFsaWQgcGFydDogJyArIHApO1xuICAgICAgICAgICAgfVxuICAgICAgICAgICAgLyogYzggaWdub3JlIHN0b3AgKi9cbiAgICAgICAgICAgIHRoaXMuI3BhcnRzLnB1c2gocCk7XG4gICAgICAgIH1cbiAgICB9XG4gICAgdG9KU09OKCkge1xuICAgICAgICBjb25zdCByZXQgPSB0aGlzLnR5cGUgPT09IG51bGxcbiAgICAgICAgICAgID8gdGhpcy4jcGFydHMuc2xpY2UoKS5tYXAocCA9PiAodHlwZW9mIHAgPT09ICdzdHJpbmcnID8gcCA6IHAudG9KU09OKCkpKVxuICAgICAgICAgICAgOiBbdGhpcy50eXBlLCAuLi50aGlzLiNwYXJ0cy5tYXAocCA9PiBwLnRvSlNPTigpKV07XG4gICAgICAgIGlmICh0aGlzLmlzU3RhcnQoKSAmJiAhdGhpcy50eXBlKVxuICAgICAgICAgICAgcmV0LnVuc2hpZnQoW10pO1xuICAgICAgICBpZiAodGhpcy5pc0VuZCgpICYmXG4gICAgICAgICAgICAodGhpcyA9PT0gdGhpcy4jcm9vdCB8fFxuICAgICAgICAgICAgICAgICh0aGlzLiNyb290LiNmaWxsZWROZWdzICYmIHRoaXMuI3BhcmVudD8udHlwZSA9PT0gJyEnKSkpIHtcbiAgICAgICAgICAgIHJldC5wdXNoKHt9KTtcbiAgICAgICAgfVxuICAgICAgICByZXR1cm4gcmV0O1xuICAgIH1cbiAgICBpc1N0YXJ0KCkge1xuICAgICAgICBpZiAodGhpcy4jcm9vdCA9PT0gdGhpcylcbiAgICAgICAgICAgIHJldHVybiB0cnVlO1xuICAgICAgICAvLyBpZiAodGhpcy50eXBlKSByZXR1cm4gISF0aGlzLiNwYXJlbnQ/LmlzU3RhcnQoKVxuICAgICAgICBpZiAoIXRoaXMuI3BhcmVudD8uaXNTdGFydCgpKVxuICAgICAgICAgICAgcmV0dXJuIGZhbHNlO1xuICAgICAgICBpZiAodGhpcy4jcGFyZW50SW5kZXggPT09IDApXG4gICAgICAgICAgICByZXR1cm4gdHJ1ZTtcbiAgICAgICAgLy8gaWYgZXZlcnl0aGluZyBBSEVBRCBvZiB0aGlzIGlzIGEgbmVnYXRpb24sIHRoZW4gaXQncyBzdGlsbCB0aGUgXCJzdGFydFwiXG4gICAgICAgIGNvbnN0IHAgPSB0aGlzLiNwYXJlbnQ7XG4gICAgICAgIGZvciAobGV0IGkgPSAwOyBpIDwgdGhpcy4jcGFyZW50SW5kZXg7IGkrKykge1xuICAgICAgICAgICAgY29uc3QgcHAgPSBwLiNwYXJ0c1tpXTtcbiAgICAgICAgICAgIGlmICghKHBwIGluc3RhbmNlb2YgQVNUICYmIHBwLnR5cGUgPT09ICchJykpIHtcbiAgICAgICAgICAgICAgICByZXR1cm4gZmFsc2U7XG4gICAgICAgICAgICB9XG4gICAgICAgIH1cbiAgICAgICAgcmV0dXJuIHRydWU7XG4gICAgfVxuICAgIGlzRW5kKCkge1xuICAgICAgICBpZiAodGhpcy4jcm9vdCA9PT0gdGhpcylcbiAgICAgICAgICAgIHJldHVybiB0cnVlO1xuICAgICAgICBpZiAodGhpcy4jcGFyZW50Py50eXBlID09PSAnIScpXG4gICAgICAgICAgICByZXR1cm4gdHJ1ZTtcbiAgICAgICAgaWYgKCF0aGlzLiNwYXJlbnQ/LmlzRW5kKCkpXG4gICAgICAgICAgICByZXR1cm4gZmFsc2U7XG4gICAgICAgIGlmICghdGhpcy50eXBlKVxuICAgICAgICAgICAgcmV0dXJuIHRoaXMuI3BhcmVudD8uaXNFbmQoKTtcbiAgICAgICAgLy8gaWYgbm90IHJvb3QsIGl0J2xsIGFsd2F5cyBoYXZlIGEgcGFyZW50XG4gICAgICAgIC8qIGM4IGlnbm9yZSBzdGFydCAqL1xuICAgICAgICBjb25zdCBwbCA9IHRoaXMuI3BhcmVudCA/IHRoaXMuI3BhcmVudC4jcGFydHMubGVuZ3RoIDogMDtcbiAgICAgICAgLyogYzggaWdub3JlIHN0b3AgKi9cbiAgICAgICAgcmV0dXJuIHRoaXMuI3BhcmVudEluZGV4ID09PSBwbCAtIDE7XG4gICAgfVxuICAgIGNvcHlJbihwYXJ0KSB7XG4gICAgICAgIGlmICh0eXBlb2YgcGFydCA9PT0gJ3N0cmluZycpXG4gICAgICAgICAgICB0aGlzLnB1c2gocGFydCk7XG4gICAgICAgIGVsc2VcbiAgICAgICAgICAgIHRoaXMucHVzaChwYXJ0LmNsb25lKHRoaXMpKTtcbiAgICB9XG4gICAgY2xvbmUocGFyZW50KSB7XG4gICAgICAgIGNvbnN0IGMgPSBuZXcgQVNUKHRoaXMudHlwZSwgcGFyZW50KTtcbiAgICAgICAgZm9yIChjb25zdCBwIG9mIHRoaXMuI3BhcnRzKSB7XG4gICAgICAgICAgICBjLmNvcHlJbihwKTtcbiAgICAgICAgfVxuICAgICAgICByZXR1cm4gYztcbiAgICB9XG4gICAgc3RhdGljICNwYXJzZUFTVChzdHIsIGFzdCwgcG9zLCBvcHQpIHtcbiAgICAgICAgbGV0IGVzY2FwaW5nID0gZmFsc2U7XG4gICAgICAgIGxldCBpbkJyYWNlID0gZmFsc2U7XG4gICAgICAgIGxldCBicmFjZVN0YXJ0ID0gLTE7XG4gICAgICAgIGxldCBicmFjZU5lZyA9IGZhbHNlO1xuICAgICAgICBpZiAoYXN0LnR5cGUgPT09IG51bGwpIHtcbiAgICAgICAgICAgIC8vIG91dHNpZGUgb2YgYSBleHRnbG9iLCBhcHBlbmQgdW50aWwgd2UgZmluZCBhIHN0YXJ0XG4gICAgICAgICAgICBsZXQgaSA9IHBvcztcbiAgICAgICAgICAgIGxldCBhY2MgPSAnJztcbiAgICAgICAgICAgIHdoaWxlIChpIDwgc3RyLmxlbmd0aCkge1xuICAgICAgICAgICAgICAgIGNvbnN0IGMgPSBzdHIuY2hhckF0KGkrKyk7XG4gICAgICAgICAgICAgICAgLy8gc3RpbGwgYWNjdW11bGF0ZSBlc2NhcGVzIGF0IHRoaXMgcG9pbnQsIGJ1dCB3ZSBkbyBpZ25vcmVcbiAgICAgICAgICAgICAgICAvLyBzdGFydHMgdGhhdCBhcmUgZXNjYXBlZFxuICAgICAgICAgICAgICAgIGlmIChlc2NhcGluZyB8fCBjID09PSAnXFxcXCcpIHtcbiAgICAgICAgICAgICAgICAgICAgZXNjYXBpbmcgPSAhZXNjYXBpbmc7XG4gICAgICAgICAgICAgICAgICAgIGFjYyArPSBjO1xuICAgICAgICAgICAgICAgICAgICBjb250aW51ZTtcbiAgICAgICAgICAgICAgICB9XG4gICAgICAgICAgICAgICAgaWYgKGluQnJhY2UpIHtcbiAgICAgICAgICAgICAgICAgICAgaWYgKGkgPT09IGJyYWNlU3RhcnQgKyAxKSB7XG4gICAgICAgICAgICAgICAgICAgICAgICBpZiAoYyA9PT0gJ14nIHx8IGMgPT09ICchJykge1xuICAgICAgICAgICAgICAgICAgICAgICAgICAgIGJyYWNlTmVnID0gdHJ1ZTtcbiAgICAgICAgICAgICAgICAgICAgICAgIH1cbiAgICAgICAgICAgICAgICAgICAgfVxuICAgICAgICAgICAgICAgICAgICBlbHNlIGlmIChjID09PSAnXScgJiYgIShpID09PSBicmFjZVN0YXJ0ICsgMiAmJiBicmFjZU5lZykpIHtcbiAgICAgICAgICAgICAgICAgICAgICAgIGluQnJhY2UgPSBmYWxzZTtcbiAgICAgICAgICAgICAgICAgICAgfVxuICAgICAgICAgICAgICAgICAgICBhY2MgKz0gYztcbiAgICAgICAgICAgICAgICAgICAgY29udGludWU7XG4gICAgICAgICAgICAgICAgfVxuICAgICAgICAgICAgICAgIGVsc2UgaWYgKGMgPT09ICdbJykge1xuICAgICAgICAgICAgICAgICAgICBpbkJyYWNlID0gdHJ1ZTtcbiAgICAgICAgICAgICAgICAgICAgYnJhY2VTdGFydCA9IGk7XG4gICAgICAgICAgICAgICAgICAgIGJyYWNlTmVnID0gZmFsc2U7XG4gICAgICAgICAgICAgICAgICAgIGFjYyArPSBjO1xuICAgICAgICAgICAgICAgICAgICBjb250aW51ZTtcbiAgICAgICAgICAgICAgICB9XG4gICAgICAgICAgICAgICAgaWYgKCFvcHQubm9leHQgJiYgaXNFeHRnbG9iVHlwZShjKSAmJiBzdHIuY2hhckF0KGkpID09PSAnKCcpIHtcbiAgICAgICAgICAgICAgICAgICAgYXN0LnB1c2goYWNjKTtcbiAgICAgICAgICAgICAgICAgICAgYWNjID0gJyc7XG4gICAgICAgICAgICAgICAgICAgIGNvbnN0IGV4dCA9IG5ldyBBU1QoYywgYXN0KTtcbiAgICAgICAgICAgICAgICAgICAgaSA9IEFTVC4jcGFyc2VBU1Qoc3RyLCBleHQsIGksIG9wdCk7XG4gICAgICAgICAgICAgICAgICAgIGFzdC5wdXNoKGV4dCk7XG4gICAgICAgICAgICAgICAgICAgIGNvbnRpbnVlO1xuICAgICAgICAgICAgICAgIH1cbiAgICAgICAgICAgICAgICBhY2MgKz0gYztcbiAgICAgICAgICAgIH1cbiAgICAgICAgICAgIGFzdC5wdXNoKGFjYyk7XG4gICAgICAgICAgICByZXR1cm4gaTtcbiAgICAgICAgfVxuICAgICAgICAvLyBzb21lIGtpbmQgb2YgZXh0Z2xvYiwgcG9zIGlzIGF0IHRoZSAoXG4gICAgICAgIC8vIGZpbmQgdGhlIG5leHQgfCBvciApXG4gICAgICAgIGxldCBpID0gcG9zICsgMTtcbiAgICAgICAgbGV0IHBhcnQgPSBuZXcgQVNUKG51bGwsIGFzdCk7XG4gICAgICAgIGNvbnN0IHBhcnRzID0gW107XG4gICAgICAgIGxldCBhY2MgPSAnJztcbiAgICAgICAgd2hpbGUgKGkgPCBzdHIubGVuZ3RoKSB7XG4gICAgICAgICAgICBjb25zdCBjID0gc3RyLmNoYXJBdChpKyspO1xuICAgICAgICAgICAgLy8gc3RpbGwgYWNjdW11bGF0ZSBlc2NhcGVzIGF0IHRoaXMgcG9pbnQsIGJ1dCB3ZSBkbyBpZ25vcmVcbiAgICAgICAgICAgIC8vIHN0YXJ0cyB0aGF0IGFyZSBlc2NhcGVkXG4gICAgICAgICAgICBpZiAoZXNjYXBpbmcgfHwgYyA9PT0gJ1xcXFwnKSB7XG4gICAgICAgICAgICAgICAgZXNjYXBpbmcgPSAhZXNjYXBpbmc7XG4gICAgICAgICAgICAgICAgYWNjICs9IGM7XG4gICAgICAgICAgICAgICAgY29udGludWU7XG4gICAgICAgICAgICB9XG4gICAgICAgICAgICBpZiAoaW5CcmFjZSkge1xuICAgICAgICAgICAgICAgIGlmIChpID09PSBicmFjZVN0YXJ0ICsgMSkge1xuICAgICAgICAgICAgICAgICAgICBpZiAoYyA9PT0gJ14nIHx8IGMgPT09ICchJykge1xuICAgICAgICAgICAgICAgICAgICAgICAgYnJhY2VOZWcgPSB0cnVlO1xuICAgICAgICAgICAgICAgICAgICB9XG4gICAgICAgICAgICAgICAgfVxuICAgICAgICAgICAgICAgIGVsc2UgaWYgKGMgPT09ICddJyAmJiAhKGkgPT09IGJyYWNlU3RhcnQgKyAyICYmIGJyYWNlTmVnKSkge1xuICAgICAgICAgICAgICAgICAgICBpbkJyYWNlID0gZmFsc2U7XG4gICAgICAgICAgICAgICAgfVxuICAgICAgICAgICAgICAgIGFjYyArPSBjO1xuICAgICAgICAgICAgICAgIGNvbnRpbnVlO1xuICAgICAgICAgICAgfVxuICAgICAgICAgICAgZWxzZSBpZiAoYyA9PT0gJ1snKSB7XG4gICAgICAgICAgICAgICAgaW5CcmFjZSA9IHRydWU7XG4gICAgICAgICAgICAgICAgYnJhY2VTdGFydCA9IGk7XG4gICAgICAgICAgICAgICAgYnJhY2VOZWcgPSBmYWxzZTtcbiAgICAgICAgICAgICAgICBhY2MgKz0gYztcbiAgICAgICAgICAgICAgICBjb250aW51ZTtcbiAgICAgICAgICAgIH1cbiAgICAgICAgICAgIGlmIChpc0V4dGdsb2JUeXBlKGMpICYmIHN0ci5jaGFyQXQoaSkgPT09ICcoJykge1xuICAgICAgICAgICAgICAgIHBhcnQucHVzaChhY2MpO1xuICAgICAgICAgICAgICAgIGFjYyA9ICcnO1xuICAgICAgICAgICAgICAgIGNvbnN0IGV4dCA9IG5ldyBBU1QoYywgcGFydCk7XG4gICAgICAgICAgICAgICAgcGFydC5wdXNoKGV4dCk7XG4gICAgICAgICAgICAgICAgaSA9IEFTVC4jcGFyc2VBU1Qoc3RyLCBleHQsIGksIG9wdCk7XG4gICAgICAgICAgICAgICAgY29udGludWU7XG4gICAgICAgICAgICB9XG4gICAgICAgICAgICBpZiAoYyA9PT0gJ3wnKSB7XG4gICAgICAgICAgICAgICAgcGFydC5wdXNoKGFjYyk7XG4gICAgICAgICAgICAgICAgYWNjID0gJyc7XG4gICAgICAgICAgICAgICAgcGFydHMucHVzaChwYXJ0KTtcbiAgICAgICAgICAgICAgICBwYXJ0ID0gbmV3IEFTVChudWxsLCBhc3QpO1xuICAgICAgICAgICAgICAgIGNvbnRpbnVlO1xuICAgICAgICAgICAgfVxuICAgICAgICAgICAgaWYgKGMgPT09ICcpJykge1xuICAgICAgICAgICAgICAgIGlmIChhY2MgPT09ICcnICYmIGFzdC4jcGFydHMubGVuZ3RoID09PSAwKSB7XG4gICAgICAgICAgICAgICAgICAgIGFzdC4jZW1wdHlFeHQgPSB0cnVlO1xuICAgICAgICAgICAgICAgIH1cbiAgICAgICAgICAgICAgICBwYXJ0LnB1c2goYWNjKTtcbiAgICAgICAgICAgICAgICBhY2MgPSAnJztcbiAgICAgICAgICAgICAgICBhc3QucHVzaCguLi5wYXJ0cywgcGFydCk7XG4gICAgICAgICAgICAgICAgcmV0dXJuIGk7XG4gICAgICAgICAgICB9XG4gICAgICAgICAgICBhY2MgKz0gYztcbiAgICAgICAgfVxuICAgICAgICAvLyB1bmZpbmlzaGVkIGV4dGdsb2JcbiAgICAgICAgLy8gaWYgd2UgZ290IGhlcmUsIGl0IHdhcyBhIG1hbGZvcm1lZCBleHRnbG9iISBub3QgYW4gZXh0Z2xvYiwgYnV0XG4gICAgICAgIC8vIG1heWJlIHNvbWV0aGluZyBlbHNlIGluIHRoZXJlLlxuICAgICAgICBhc3QudHlwZSA9IG51bGw7XG4gICAgICAgIGFzdC4jaGFzTWFnaWMgPSB1bmRlZmluZWQ7XG4gICAgICAgIGFzdC4jcGFydHMgPSBbc3RyLnN1YnN0cmluZyhwb3MgLSAxKV07XG4gICAgICAgIHJldHVybiBpO1xuICAgIH1cbiAgICBzdGF0aWMgZnJvbUdsb2IocGF0dGVybiwgb3B0aW9ucyA9IHt9KSB7XG4gICAgICAgIGNvbnN0IGFzdCA9IG5ldyBBU1QobnVsbCwgdW5kZWZpbmVkLCBvcHRpb25zKTtcbiAgICAgICAgQVNULiNwYXJzZUFTVChwYXR0ZXJuLCBhc3QsIDAsIG9wdGlvbnMpO1xuICAgICAgICByZXR1cm4gYXN0O1xuICAgIH1cbiAgICAvLyByZXR1cm5zIHRoZSByZWd1bGFyIGV4cHJlc3Npb24gaWYgdGhlcmUncyBtYWdpYywgb3IgdGhlIHVuZXNjYXBlZFxuICAgIC8vIHN0cmluZyBpZiBub3QuXG4gICAgdG9NTVBhdHRlcm4oKSB7XG4gICAgICAgIC8vIHNob3VsZCBvbmx5IGJlIGNhbGxlZCBvbiByb290XG4gICAgICAgIC8qIGM4IGlnbm9yZSBzdGFydCAqL1xuICAgICAgICBpZiAodGhpcyAhPT0gdGhpcy4jcm9vdClcbiAgICAgICAgICAgIHJldHVybiB0aGlzLiNyb290LnRvTU1QYXR0ZXJuKCk7XG4gICAgICAgIC8qIGM4IGlnbm9yZSBzdG9wICovXG4gICAgICAgIGNvbnN0IGdsb2IgPSB0aGlzLnRvU3RyaW5nKCk7XG4gICAgICAgIGNvbnN0IFtyZSwgYm9keSwgaGFzTWFnaWMsIHVmbGFnXSA9IHRoaXMudG9SZWdFeHBTb3VyY2UoKTtcbiAgICAgICAgLy8gaWYgd2UncmUgaW4gbm9jYXNlIG1vZGUsIGFuZCBub3Qgbm9jYXNlTWFnaWNPbmx5LCB0aGVuIHdlIGRvXG4gICAgICAgIC8vIHN0aWxsIG5lZWQgYSByZWd1bGFyIGV4cHJlc3Npb24gaWYgd2UgaGF2ZSB0byBjYXNlLWluc2Vuc2l0aXZlbHlcbiAgICAgICAgLy8gbWF0Y2ggY2FwaXRhbC9sb3dlcmNhc2UgY2hhcmFjdGVycy5cbiAgICAgICAgY29uc3QgYW55TWFnaWMgPSBoYXNNYWdpYyB8fFxuICAgICAgICAgICAgdGhpcy4jaGFzTWFnaWMgfHxcbiAgICAgICAgICAgICh0aGlzLiNvcHRpb25zLm5vY2FzZSAmJlxuICAgICAgICAgICAgICAgICF0aGlzLiNvcHRpb25zLm5vY2FzZU1hZ2ljT25seSAmJlxuICAgICAgICAgICAgICAgIGdsb2IudG9VcHBlckNhc2UoKSAhPT0gZ2xvYi50b0xvd2VyQ2FzZSgpKTtcbiAgICAgICAgaWYgKCFhbnlNYWdpYykge1xuICAgICAgICAgICAgcmV0dXJuIGJvZHk7XG4gICAgICAgIH1cbiAgICAgICAgY29uc3QgZmxhZ3MgPSAodGhpcy4jb3B0aW9ucy5ub2Nhc2UgPyAnaScgOiAnJykgKyAodWZsYWcgPyAndScgOiAnJyk7XG4gICAgICAgIHJldHVybiBPYmplY3QuYXNzaWduKG5ldyBSZWdFeHAoYF4ke3JlfSRgLCBmbGFncyksIHtcbiAgICAgICAgICAgIF9zcmM6IHJlLFxuICAgICAgICAgICAgX2dsb2I6IGdsb2IsXG4gICAgICAgIH0pO1xuICAgIH1cbiAgICBnZXQgb3B0aW9ucygpIHtcbiAgICAgICAgcmV0dXJuIHRoaXMuI29wdGlvbnM7XG4gICAgfVxuICAgIC8vIHJldHVybnMgdGhlIHN0cmluZyBtYXRjaCwgdGhlIHJlZ2V4cCBzb3VyY2UsIHdoZXRoZXIgdGhlcmUncyBtYWdpY1xuICAgIC8vIGluIHRoZSByZWdleHAgKHNvIGEgcmVndWxhciBleHByZXNzaW9uIGlzIHJlcXVpcmVkKSBhbmQgd2hldGhlciBvclxuICAgIC8vIG5vdCB0aGUgdWZsYWcgaXMgbmVlZGVkIGZvciB0aGUgcmVndWxhciBleHByZXNzaW9uIChmb3IgcG9zaXggY2xhc3NlcylcbiAgICAvLyBUT0RPOiBpbnN0ZWFkIG9mIGluamVjdGluZyB0aGUgc3RhcnQvZW5kIGF0IHRoaXMgcG9pbnQsIGp1c3QgcmV0dXJuXG4gICAgLy8gdGhlIEJPRFkgb2YgdGhlIHJlZ2V4cCwgYWxvbmcgd2l0aCB0aGUgc3RhcnQvZW5kIHBvcnRpb25zIHN1aXRhYmxlXG4gICAgLy8gZm9yIGJpbmRpbmcgdGhlIHN0YXJ0L2VuZCBpbiBlaXRoZXIgYSBqb2luZWQgZnVsbC1wYXRoIG1ha2VSZSBjb250ZXh0XG4gICAgLy8gKHdoZXJlIHdlIGJpbmQgdG8gKF58LyksIG9yIGEgc3RhbmRhbG9uZSBtYXRjaFBhcnQgY29udGV4dCAod2hlcmVcbiAgICAvLyB3ZSBiaW5kIHRvIF4sIGFuZCBub3QgLykuICBPdGhlcndpc2Ugc2xhc2hlcyBnZXQgZHVwZWQhXG4gICAgLy9cbiAgICAvLyBJbiBwYXJ0LW1hdGNoaW5nIG1vZGUsIHRoZSBzdGFydCBpczpcbiAgICAvLyAtIGlmIG5vdCBpc1N0YXJ0OiBub3RoaW5nXG4gICAgLy8gLSBpZiB0cmF2ZXJzYWwgcG9zc2libGUsIGJ1dCBub3QgYWxsb3dlZDogXig/IVxcLlxcLj8kKVxuICAgIC8vIC0gaWYgZG90cyBhbGxvd2VkIG9yIG5vdCBwb3NzaWJsZTogXlxuICAgIC8vIC0gaWYgZG90cyBwb3NzaWJsZSBhbmQgbm90IGFsbG93ZWQ6IF4oPyFcXC4pXG4gICAgLy8gZW5kIGlzOlxuICAgIC8vIC0gaWYgbm90IGlzRW5kKCk6IG5vdGhpbmdcbiAgICAvLyAtIGVsc2U6ICRcbiAgICAvL1xuICAgIC8vIEluIGZ1bGwtcGF0aCBtYXRjaGluZyBtb2RlLCB3ZSBwdXQgdGhlIHNsYXNoIGF0IHRoZSBTVEFSVCBvZiB0aGVcbiAgICAvLyBwYXR0ZXJuLCBzbyBzdGFydCBpczpcbiAgICAvLyAtIGlmIGZpcnN0IHBhdHRlcm46IHNhbWUgYXMgcGFydC1tYXRjaGluZyBtb2RlXG4gICAgLy8gLSBpZiBub3QgaXNTdGFydCgpOiBub3RoaW5nXG4gICAgLy8gLSBpZiB0cmF2ZXJzYWwgcG9zc2libGUsIGJ1dCBub3QgYWxsb3dlZDogLyg/IVxcLlxcLj8oPzokfC8pKVxuICAgIC8vIC0gaWYgZG90cyBhbGxvd2VkIG9yIG5vdCBwb3NzaWJsZTogL1xuICAgIC8vIC0gaWYgZG90cyBwb3NzaWJsZSBhbmQgbm90IGFsbG93ZWQ6IC8oPyFcXC4pXG4gICAgLy8gZW5kIGlzOlxuICAgIC8vIC0gaWYgbGFzdCBwYXR0ZXJuLCBzYW1lIGFzIHBhcnQtbWF0Y2hpbmcgbW9kZVxuICAgIC8vIC0gZWxzZSBub3RoaW5nXG4gICAgLy9cbiAgICAvLyBBbHdheXMgcHV0IHRoZSAoPzokfC8pIG9uIG5lZ2F0ZWQgdGFpbHMsIHRob3VnaCwgYmVjYXVzZSB0aGF0IGhhcyB0byBiZVxuICAgIC8vIHRoZXJlIHRvIGJpbmQgdGhlIGVuZCBvZiB0aGUgbmVnYXRlZCBwYXR0ZXJuIHBvcnRpb24sIGFuZCBpdCdzIGVhc2llciB0b1xuICAgIC8vIGp1c3Qgc3RpY2sgaXQgaW4gbm93IHJhdGhlciB0aGFuIHRyeSB0byBpbmplY3QgaXQgbGF0ZXIgaW4gdGhlIG1pZGRsZSBvZlxuICAgIC8vIHRoZSBwYXR0ZXJuLlxuICAgIC8vXG4gICAgLy8gV2UgY2FuIGp1c3QgYWx3YXlzIHJldHVybiB0aGUgc2FtZSBlbmQsIGFuZCBsZWF2ZSBpdCB1cCB0byB0aGUgY2FsbGVyXG4gICAgLy8gdG8ga25vdyB3aGV0aGVyIGl0J3MgZ29pbmcgdG8gYmUgdXNlZCBqb2luZWQgb3IgaW4gcGFydHMuXG4gICAgLy8gQW5kLCBpZiB0aGUgc3RhcnQgaXMgYWRqdXN0ZWQgc2xpZ2h0bHksIGNhbiBkbyB0aGUgc2FtZSB0aGVyZTpcbiAgICAvLyAtIGlmIG5vdCBpc1N0YXJ0OiBub3RoaW5nXG4gICAgLy8gLSBpZiB0cmF2ZXJzYWwgcG9zc2libGUsIGJ1dCBub3QgYWxsb3dlZDogKD86L3xeKSg/IVxcLlxcLj8kKVxuICAgIC8vIC0gaWYgZG90cyBhbGxvd2VkIG9yIG5vdCBwb3NzaWJsZTogKD86L3xeKVxuICAgIC8vIC0gaWYgZG90cyBwb3NzaWJsZSBhbmQgbm90IGFsbG93ZWQ6ICg/Oi98XikoPyFcXC4pXG4gICAgLy9cbiAgICAvLyBCdXQgaXQncyBiZXR0ZXIgdG8gaGF2ZSBhIHNpbXBsZXIgYmluZGluZyB3aXRob3V0IGEgY29uZGl0aW9uYWwsIGZvclxuICAgIC8vIHBlcmZvcm1hbmNlLCBzbyBwcm9iYWJseSBiZXR0ZXIgdG8gcmV0dXJuIGJvdGggc3RhcnQgb3B0aW9ucy5cbiAgICAvL1xuICAgIC8vIFRoZW4gdGhlIGNhbGxlciBqdXN0IGlnbm9yZXMgdGhlIGVuZCBpZiBpdCdzIG5vdCB0aGUgZmlyc3QgcGF0dGVybixcbiAgICAvLyBhbmQgdGhlIHN0YXJ0IGFsd2F5cyBnZXRzIGFwcGxpZWQuXG4gICAgLy9cbiAgICAvLyBCdXQgdGhhdCdzIGFsd2F5cyBnb2luZyB0byBiZSAkIGlmIGl0J3MgdGhlIGVuZGluZyBwYXR0ZXJuLCBvciBub3RoaW5nLFxuICAgIC8vIHNvIHRoZSBjYWxsZXIgY2FuIGp1c3QgYXR0YWNoICQgYXQgdGhlIGVuZCBvZiB0aGUgcGF0dGVybiB3aGVuIGJ1aWxkaW5nLlxuICAgIC8vXG4gICAgLy8gU28gdGhlIHRvZG8gaXM6XG4gICAgLy8gLSBiZXR0ZXIgZGV0ZWN0IHdoYXQga2luZCBvZiBzdGFydCBpcyBuZWVkZWRcbiAgICAvLyAtIHJldHVybiBib3RoIGZsYXZvcnMgb2Ygc3RhcnRpbmcgcGF0dGVyblxuICAgIC8vIC0gYXR0YWNoICQgYXQgdGhlIGVuZCBvZiB0aGUgcGF0dGVybiB3aGVuIGNyZWF0aW5nIHRoZSBhY3R1YWwgUmVnRXhwXG4gICAgLy9cbiAgICAvLyBBaCwgYnV0IHdhaXQsIG5vLCB0aGF0IGFsbCBvbmx5IGFwcGxpZXMgdG8gdGhlIHJvb3Qgd2hlbiB0aGUgZmlyc3QgcGF0dGVyblxuICAgIC8vIGlzIG5vdCBhbiBleHRnbG9iLiBJZiB0aGUgZmlyc3QgcGF0dGVybiBJUyBhbiBleHRnbG9iLCB0aGVuIHdlIG5lZWQgYWxsXG4gICAgLy8gdGhhdCBkb3QgcHJldmVudGlvbiBiaXogdG8gbGl2ZSBpbiB0aGUgZXh0Z2xvYiBwb3J0aW9ucywgYmVjYXVzZSBlZ1xuICAgIC8vICsoKnwueCopIGNhbiBtYXRjaCAueHkgYnV0IG5vdCAueXguXG4gICAgLy9cbiAgICAvLyBTbywgcmV0dXJuIHRoZSB0d28gZmxhdm9ycyBpZiBpdCdzICNyb290IGFuZCB0aGUgZmlyc3QgY2hpbGQgaXMgbm90IGFuXG4gICAgLy8gQVNULCBvdGhlcndpc2UgbGVhdmUgaXQgdG8gdGhlIGNoaWxkIEFTVCB0byBoYW5kbGUgaXQsIGFuZCB0aGVyZSxcbiAgICAvLyB1c2UgdGhlICg/Ol58Lykgc3R5bGUgb2Ygc3RhcnQgYmluZGluZy5cbiAgICAvL1xuICAgIC8vIEV2ZW4gc2ltcGxpZmllZCBmdXJ0aGVyOlxuICAgIC8vIC0gU2luY2UgdGhlIHN0YXJ0IGZvciBhIGpvaW4gaXMgZWcgLyg/IVxcLikgYW5kIHRoZSBzdGFydCBmb3IgYSBwYXJ0XG4gICAgLy8gaXMgXig/IVxcLiksIHdlIGNhbiBqdXN0IHByZXBlbmQgKD8hXFwuKSB0byB0aGUgcGF0dGVybiAoZWl0aGVyIHJvb3RcbiAgICAvLyBvciBzdGFydCBvciB3aGF0ZXZlcikgYW5kIHByZXBlbmQgXiBvciAvIGF0IHRoZSBSZWdleHAgY29uc3RydWN0aW9uLlxuICAgIHRvUmVnRXhwU291cmNlKGFsbG93RG90KSB7XG4gICAgICAgIGNvbnN0IGRvdCA9IGFsbG93RG90ID8/ICEhdGhpcy4jb3B0aW9ucy5kb3Q7XG4gICAgICAgIGlmICh0aGlzLiNyb290ID09PSB0aGlzKVxuICAgICAgICAgICAgdGhpcy4jZmlsbE5lZ3MoKTtcbiAgICAgICAgaWYgKCF0aGlzLnR5cGUpIHtcbiAgICAgICAgICAgIGNvbnN0IG5vRW1wdHkgPSB0aGlzLmlzU3RhcnQoKSAmJiB0aGlzLmlzRW5kKCk7XG4gICAgICAgICAgICBjb25zdCBzcmMgPSB0aGlzLiNwYXJ0c1xuICAgICAgICAgICAgICAgIC5tYXAocCA9PiB7XG4gICAgICAgICAgICAgICAgY29uc3QgW3JlLCBfLCBoYXNNYWdpYywgdWZsYWddID0gdHlwZW9mIHAgPT09ICdzdHJpbmcnXG4gICAgICAgICAgICAgICAgICAgID8gQVNULiNwYXJzZUdsb2IocCwgdGhpcy4jaGFzTWFnaWMsIG5vRW1wdHkpXG4gICAgICAgICAgICAgICAgICAgIDogcC50b1JlZ0V4cFNvdXJjZShhbGxvd0RvdCk7XG4gICAgICAgICAgICAgICAgdGhpcy4jaGFzTWFnaWMgPSB0aGlzLiNoYXNNYWdpYyB8fCBoYXNNYWdpYztcbiAgICAgICAgICAgICAgICB0aGlzLiN1ZmxhZyA9IHRoaXMuI3VmbGFnIHx8IHVmbGFnO1xuICAgICAgICAgICAgICAgIHJldHVybiByZTtcbiAgICAgICAgICAgIH0pXG4gICAgICAgICAgICAgICAgLmpvaW4oJycpO1xuICAgICAgICAgICAgbGV0IHN0YXJ0ID0gJyc7XG4gICAgICAgICAgICBpZiAodGhpcy5pc1N0YXJ0KCkpIHtcbiAgICAgICAgICAgICAgICBpZiAodHlwZW9mIHRoaXMuI3BhcnRzWzBdID09PSAnc3RyaW5nJykge1xuICAgICAgICAgICAgICAgICAgICAvLyB0aGlzIGlzIHRoZSBzdHJpbmcgdGhhdCB3aWxsIG1hdGNoIHRoZSBzdGFydCBvZiB0aGUgcGF0dGVybixcbiAgICAgICAgICAgICAgICAgICAgLy8gc28gd2UgbmVlZCB0byBwcm90ZWN0IGFnYWluc3QgZG90cyBhbmQgc3VjaC5cbiAgICAgICAgICAgICAgICAgICAgLy8gJy4nIGFuZCAnLi4nIGNhbm5vdCBtYXRjaCB1bmxlc3MgdGhlIHBhdHRlcm4gaXMgdGhhdCBleGFjdGx5LFxuICAgICAgICAgICAgICAgICAgICAvLyBldmVuIGlmIGl0IHN0YXJ0cyB3aXRoIC4gb3IgZG90OnRydWUgaXMgc2V0LlxuICAgICAgICAgICAgICAgICAgICBjb25zdCBkb3RUcmF2QWxsb3dlZCA9IHRoaXMuI3BhcnRzLmxlbmd0aCA9PT0gMSAmJiBqdXN0RG90cy5oYXModGhpcy4jcGFydHNbMF0pO1xuICAgICAgICAgICAgICAgICAgICBpZiAoIWRvdFRyYXZBbGxvd2VkKSB7XG4gICAgICAgICAgICAgICAgICAgICAgICBjb25zdCBhcHMgPSBhZGRQYXR0ZXJuU3RhcnQ7XG4gICAgICAgICAgICAgICAgICAgICAgICAvLyBjaGVjayBpZiB3ZSBoYXZlIGEgcG9zc2liaWxpdHkgb2YgbWF0Y2hpbmcgLiBvciAuLixcbiAgICAgICAgICAgICAgICAgICAgICAgIC8vIGFuZCBwcmV2ZW50IHRoYXQuXG4gICAgICAgICAgICAgICAgICAgICAgICBjb25zdCBuZWVkTm9UcmF2ID0gXG4gICAgICAgICAgICAgICAgICAgICAgICAvLyBkb3RzIGFyZSBhbGxvd2VkLCBhbmQgdGhlIHBhdHRlcm4gc3RhcnRzIHdpdGggWyBvciAuXG4gICAgICAgICAgICAgICAgICAgICAgICAoZG90ICYmIGFwcy5oYXMoc3JjLmNoYXJBdCgwKSkpIHx8XG4gICAgICAgICAgICAgICAgICAgICAgICAgICAgLy8gdGhlIHBhdHRlcm4gc3RhcnRzIHdpdGggXFwuLCBhbmQgdGhlbiBbIG9yIC5cbiAgICAgICAgICAgICAgICAgICAgICAgICAgICAoc3JjLnN0YXJ0c1dpdGgoJ1xcXFwuJykgJiYgYXBzLmhhcyhzcmMuY2hhckF0KDIpKSkgfHxcbiAgICAgICAgICAgICAgICAgICAgICAgICAgICAvLyB0aGUgcGF0dGVybiBzdGFydHMgd2l0aCBcXC5cXC4sIGFuZCB0aGVuIFsgb3IgLlxuICAgICAgICAgICAgICAgICAgICAgICAgICAgIChzcmMuc3RhcnRzV2l0aCgnXFxcXC5cXFxcLicpICYmIGFwcy5oYXMoc3JjLmNoYXJBdCg0KSkpO1xuICAgICAgICAgICAgICAgICAgICAgICAgLy8gbm8gbmVlZCB0byBwcmV2ZW50IGRvdHMgaWYgaXQgY2FuJ3QgbWF0Y2ggYSBkb3QsIG9yIGlmIGFcbiAgICAgICAgICAgICAgICAgICAgICAgIC8vIHN1Yi1wYXR0ZXJuIHdpbGwgYmUgcHJldmVudGluZyBpdCBhbnl3YXkuXG4gICAgICAgICAgICAgICAgICAgICAgICBjb25zdCBuZWVkTm9Eb3QgPSAhZG90ICYmICFhbGxvd0RvdCAmJiBhcHMuaGFzKHNyYy5jaGFyQXQoMCkpO1xuICAgICAgICAgICAgICAgICAgICAgICAgc3RhcnQgPSBuZWVkTm9UcmF2ID8gc3RhcnROb1RyYXZlcnNhbCA6IG5lZWROb0RvdCA/IHN0YXJ0Tm9Eb3QgOiAnJztcbiAgICAgICAgICAgICAgICAgICAgfVxuICAgICAgICAgICAgICAgIH1cbiAgICAgICAgICAgIH1cbiAgICAgICAgICAgIC8vIGFwcGVuZCB0aGUgXCJlbmQgb2YgcGF0aCBwb3J0aW9uXCIgcGF0dGVybiB0byBuZWdhdGlvbiB0YWlsc1xuICAgICAgICAgICAgbGV0IGVuZCA9ICcnO1xuICAgICAgICAgICAgaWYgKHRoaXMuaXNFbmQoKSAmJlxuICAgICAgICAgICAgICAgIHRoaXMuI3Jvb3QuI2ZpbGxlZE5lZ3MgJiZcbiAgICAgICAgICAgICAgICB0aGlzLiNwYXJlbnQ/LnR5cGUgPT09ICchJykge1xuICAgICAgICAgICAgICAgIGVuZCA9ICcoPzokfFxcXFwvKSc7XG4gICAgICAgICAgICB9XG4gICAgICAgICAgICBjb25zdCBmaW5hbCA9IHN0YXJ0ICsgc3JjICsgZW5kO1xuICAgICAgICAgICAgcmV0dXJuIFtcbiAgICAgICAgICAgICAgICBmaW5hbCxcbiAgICAgICAgICAgICAgICAoMCwgdW5lc2NhcGVfanNfMS51bmVzY2FwZSkoc3JjKSxcbiAgICAgICAgICAgICAgICAodGhpcy4jaGFzTWFnaWMgPSAhIXRoaXMuI2hhc01hZ2ljKSxcbiAgICAgICAgICAgICAgICB0aGlzLiN1ZmxhZyxcbiAgICAgICAgICAgIF07XG4gICAgICAgIH1cbiAgICAgICAgLy8gV2UgbmVlZCB0byBjYWxjdWxhdGUgdGhlIGJvZHkgKnR3aWNlKiBpZiBpdCdzIGEgcmVwZWF0IHBhdHRlcm5cbiAgICAgICAgLy8gYXQgdGhlIHN0YXJ0LCBvbmNlIGluIG5vZG90IG1vZGUsIHRoZW4gYWdhaW4gaW4gZG90IG1vZGUsIHNvIGFcbiAgICAgICAgLy8gcGF0dGVybiBsaWtlICooPykgY2FuIG1hdGNoICd4LnknXG4gICAgICAgIGNvbnN0IHJlcGVhdGVkID0gdGhpcy50eXBlID09PSAnKicgfHwgdGhpcy50eXBlID09PSAnKyc7XG4gICAgICAgIC8vIHNvbWUga2luZCBvZiBleHRnbG9iXG4gICAgICAgIGNvbnN0IHN0YXJ0ID0gdGhpcy50eXBlID09PSAnIScgPyAnKD86KD8hKD86JyA6ICcoPzonO1xuICAgICAgICBsZXQgYm9keSA9IHRoaXMuI3BhcnRzVG9SZWdFeHAoZG90KTtcbiAgICAgICAgaWYgKHRoaXMuaXNTdGFydCgpICYmIHRoaXMuaXNFbmQoKSAmJiAhYm9keSAmJiB0aGlzLnR5cGUgIT09ICchJykge1xuICAgICAgICAgICAgLy8gaW52YWxpZCBleHRnbG9iLCBoYXMgdG8gYXQgbGVhc3QgYmUgKnNvbWV0aGluZyogcHJlc2VudCwgaWYgaXQnc1xuICAgICAgICAgICAgLy8gdGhlIGVudGlyZSBwYXRoIHBvcnRpb24uXG4gICAgICAgICAgICBjb25zdCBzID0gdGhpcy50b1N0cmluZygpO1xuICAgICAgICAgICAgdGhpcy4jcGFydHMgPSBbc107XG4gICAgICAgICAgICB0aGlzLnR5cGUgPSBudWxsO1xuICAgICAgICAgICAgdGhpcy4jaGFzTWFnaWMgPSB1bmRlZmluZWQ7XG4gICAgICAgICAgICByZXR1cm4gW3MsICgwLCB1bmVzY2FwZV9qc18xLnVuZXNjYXBlKSh0aGlzLnRvU3RyaW5nKCkpLCBmYWxzZSwgZmFsc2VdO1xuICAgICAgICB9XG4gICAgICAgIC8vIFhYWCBhYnN0cmFjdCBvdXQgdGhpcyBtYXAgbWV0aG9kXG4gICAgICAgIGxldCBib2R5RG90QWxsb3dlZCA9ICFyZXBlYXRlZCB8fCBhbGxvd0RvdCB8fCBkb3QgfHwgIXN0YXJ0Tm9Eb3RcbiAgICAgICAgICAgID8gJydcbiAgICAgICAgICAgIDogdGhpcy4jcGFydHNUb1JlZ0V4cCh0cnVlKTtcbiAgICAgICAgaWYgKGJvZHlEb3RBbGxvd2VkID09PSBib2R5KSB7XG4gICAgICAgICAgICBib2R5RG90QWxsb3dlZCA9ICcnO1xuICAgICAgICB9XG4gICAgICAgIGlmIChib2R5RG90QWxsb3dlZCkge1xuICAgICAgICAgICAgYm9keSA9IGAoPzoke2JvZHl9KSg/OiR7Ym9keURvdEFsbG93ZWR9KSo/YDtcbiAgICAgICAgfVxuICAgICAgICAvLyBhbiBlbXB0eSAhKCkgaXMgZXhhY3RseSBlcXVpdmFsZW50IHRvIGEgc3Rhck5vRW1wdHlcbiAgICAgICAgbGV0IGZpbmFsID0gJyc7XG4gICAgICAgIGlmICh0aGlzLnR5cGUgPT09ICchJyAmJiB0aGlzLiNlbXB0eUV4dCkge1xuICAgICAgICAgICAgZmluYWwgPSAodGhpcy5pc1N0YXJ0KCkgJiYgIWRvdCA/IHN0YXJ0Tm9Eb3QgOiAnJykgKyBzdGFyTm9FbXB0eTtcbiAgICAgICAgfVxuICAgICAgICBlbHNlIHtcbiAgICAgICAgICAgIGNvbnN0IGNsb3NlID0gdGhpcy50eXBlID09PSAnISdcbiAgICAgICAgICAgICAgICA/IC8vICEoKSBtdXN0IG1hdGNoIHNvbWV0aGluZyxidXQgISh4KSBjYW4gbWF0Y2ggJydcbiAgICAgICAgICAgICAgICAgICAgJykpJyArXG4gICAgICAgICAgICAgICAgICAgICAgICAodGhpcy5pc1N0YXJ0KCkgJiYgIWRvdCAmJiAhYWxsb3dEb3QgPyBzdGFydE5vRG90IDogJycpICtcbiAgICAgICAgICAgICAgICAgICAgICAgIHN0YXIgK1xuICAgICAgICAgICAgICAgICAgICAgICAgJyknXG4gICAgICAgICAgICAgICAgOiB0aGlzLnR5cGUgPT09ICdAJ1xuICAgICAgICAgICAgICAgICAgICA/ICcpJ1xuICAgICAgICAgICAgICAgICAgICA6IHRoaXMudHlwZSA9PT0gJz8nXG4gICAgICAgICAgICAgICAgICAgICAgICA/ICcpPydcbiAgICAgICAgICAgICAgICAgICAgICAgIDogdGhpcy50eXBlID09PSAnKycgJiYgYm9keURvdEFsbG93ZWRcbiAgICAgICAgICAgICAgICAgICAgICAgICAgICA/ICcpJ1xuICAgICAgICAgICAgICAgICAgICAgICAgICAgIDogdGhpcy50eXBlID09PSAnKicgJiYgYm9keURvdEFsbG93ZWRcbiAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgPyBgKT9gXG4gICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgIDogYCkke3RoaXMudHlwZX1gO1xuICAgICAgICAgICAgZmluYWwgPSBzdGFydCArIGJvZHkgKyBjbG9zZTtcbiAgICAgICAgfVxuICAgICAgICByZXR1cm4gW1xuICAgICAgICAgICAgZmluYWwsXG4gICAgICAgICAgICAoMCwgdW5lc2NhcGVfanNfMS51bmVzY2FwZSkoYm9keSksXG4gICAgICAgICAgICAodGhpcy4jaGFzTWFnaWMgPSAhIXRoaXMuI2hhc01hZ2ljKSxcbiAgICAgICAgICAgIHRoaXMuI3VmbGFnLFxuICAgICAgICBdO1xuICAgIH1cbiAgICAjcGFydHNUb1JlZ0V4cChkb3QpIHtcbiAgICAgICAgcmV0dXJuIHRoaXMuI3BhcnRzXG4gICAgICAgICAgICAubWFwKHAgPT4ge1xuICAgICAgICAgICAgLy8gZXh0Z2xvYiBBU1RzIHNob3VsZCBvbmx5IGNvbnRhaW4gcGFyZW50IEFTVHNcbiAgICAgICAgICAgIC8qIGM4IGlnbm9yZSBzdGFydCAqL1xuICAgICAgICAgICAgaWYgKHR5cGVvZiBwID09PSAnc3RyaW5nJykge1xuICAgICAgICAgICAgICAgIHRocm93IG5ldyBFcnJvcignc3RyaW5nIHR5cGUgaW4gZXh0Z2xvYiBhc3Q/PycpO1xuICAgICAgICAgICAgfVxuICAgICAgICAgICAgLyogYzggaWdub3JlIHN0b3AgKi9cbiAgICAgICAgICAgIC8vIGNhbiBpZ25vcmUgaGFzTWFnaWMsIGJlY2F1c2UgZXh0Z2xvYnMgYXJlIGFscmVhZHkgYWx3YXlzIG1hZ2ljXG4gICAgICAgICAgICBjb25zdCBbcmUsIF8sIF9oYXNNYWdpYywgdWZsYWddID0gcC50b1JlZ0V4cFNvdXJjZShkb3QpO1xuICAgICAgICAgICAgdGhpcy4jdWZsYWcgPSB0aGlzLiN1ZmxhZyB8fCB1ZmxhZztcbiAgICAgICAgICAgIHJldHVybiByZTtcbiAgICAgICAgfSlcbiAgICAgICAgICAgIC5maWx0ZXIocCA9PiAhKHRoaXMuaXNTdGFydCgpICYmIHRoaXMuaXNFbmQoKSkgfHwgISFwKVxuICAgICAgICAgICAgLmpvaW4oJ3wnKTtcbiAgICB9XG4gICAgc3RhdGljICNwYXJzZUdsb2IoZ2xvYiwgaGFzTWFnaWMsIG5vRW1wdHkgPSBmYWxzZSkge1xuICAgICAgICBsZXQgZXNjYXBpbmcgPSBmYWxzZTtcbiAgICAgICAgbGV0IHJlID0gJyc7XG4gICAgICAgIGxldCB1ZmxhZyA9IGZhbHNlO1xuICAgICAgICBmb3IgKGxldCBpID0gMDsgaSA8IGdsb2IubGVuZ3RoOyBpKyspIHtcbiAgICAgICAgICAgIGNvbnN0IGMgPSBnbG9iLmNoYXJBdChpKTtcbiAgICAgICAgICAgIGlmIChlc2NhcGluZykge1xuICAgICAgICAgICAgICAgIGVzY2FwaW5nID0gZmFsc2U7XG4gICAgICAgICAgICAgICAgcmUgKz0gKHJlU3BlY2lhbHMuaGFzKGMpID8gJ1xcXFwnIDogJycpICsgYztcbiAgICAgICAgICAgICAgICBjb250aW51ZTtcbiAgICAgICAgICAgIH1cbiAgICAgICAgICAgIGlmIChjID09PSAnXFxcXCcpIHtcbiAgICAgICAgICAgICAgICBpZiAoaSA9PT0gZ2xvYi5sZW5ndGggLSAxKSB7XG4gICAgICAgICAgICAgICAgICAgIHJlICs9ICdcXFxcXFxcXCc7XG4gICAgICAgICAgICAgICAgfVxuICAgICAgICAgICAgICAgIGVsc2Uge1xuICAgICAgICAgICAgICAgICAgICBlc2NhcGluZyA9IHRydWU7XG4gICAgICAgICAgICAgICAgfVxuICAgICAgICAgICAgICAgIGNvbnRpbnVlO1xuICAgICAgICAgICAgfVxuICAgICAgICAgICAgaWYgKGMgPT09ICdbJykge1xuICAgICAgICAgICAgICAgIGNvbnN0IFtzcmMsIG5lZWRVZmxhZywgY29uc3VtZWQsIG1hZ2ljXSA9ICgwLCBicmFjZV9leHByZXNzaW9uc19qc18xLnBhcnNlQ2xhc3MpKGdsb2IsIGkpO1xuICAgICAgICAgICAgICAgIGlmIChjb25zdW1lZCkge1xuICAgICAgICAgICAgICAgICAgICByZSArPSBzcmM7XG4gICAgICAgICAgICAgICAgICAgIHVmbGFnID0gdWZsYWcgfHwgbmVlZFVmbGFnO1xuICAgICAgICAgICAgICAgICAgICBpICs9IGNvbnN1bWVkIC0gMTtcbiAgICAgICAgICAgICAgICAgICAgaGFzTWFnaWMgPSBoYXNNYWdpYyB8fCBtYWdpYztcbiAgICAgICAgICAgICAgICAgICAgY29udGludWU7XG4gICAgICAgICAgICAgICAgfVxuICAgICAgICAgICAgfVxuICAgICAgICAgICAgaWYgKGMgPT09ICcqJykge1xuICAgICAgICAgICAgICAgIGlmIChub0VtcHR5ICYmIGdsb2IgPT09ICcqJylcbiAgICAgICAgICAgICAgICAgICAgcmUgKz0gc3Rhck5vRW1wdHk7XG4gICAgICAgICAgICAgICAgZWxzZVxuICAgICAgICAgICAgICAgICAgICByZSArPSBzdGFyO1xuICAgICAgICAgICAgICAgIGhhc01hZ2ljID0gdHJ1ZTtcbiAgICAgICAgICAgICAgICBjb250aW51ZTtcbiAgICAgICAgICAgIH1cbiAgICAgICAgICAgIGlmIChjID09PSAnPycpIHtcbiAgICAgICAgICAgICAgICByZSArPSBxbWFyaztcbiAgICAgICAgICAgICAgICBoYXNNYWdpYyA9IHRydWU7XG4gICAgICAgICAgICAgICAgY29udGludWU7XG4gICAgICAgICAgICB9XG4gICAgICAgICAgICByZSArPSByZWdFeHBFc2NhcGUoYyk7XG4gICAgICAgIH1cbiAgICAgICAgcmV0dXJuIFtyZSwgKDAsIHVuZXNjYXBlX2pzXzEudW5lc2NhcGUpKGdsb2IpLCAhIWhhc01hZ2ljLCB1ZmxhZ107XG4gICAgfVxufVxuZXhwb3J0cy5BU1QgPSBBU1Q7XG4vLyMgc291cmNlTWFwcGluZ1VSTD1hc3QuanMubWFwIiwiXCJ1c2Ugc3RyaWN0XCI7XG4vLyB0cmFuc2xhdGUgdGhlIHZhcmlvdXMgcG9zaXggY2hhcmFjdGVyIGNsYXNzZXMgaW50byB1bmljb2RlIHByb3BlcnRpZXNcbi8vIHRoaXMgd29ya3MgYWNyb3NzIGFsbCB1bmljb2RlIGxvY2FsZXNcbk9iamVjdC5kZWZpbmVQcm9wZXJ0eShleHBvcnRzLCBcIl9fZXNNb2R1bGVcIiwgeyB2YWx1ZTogdHJ1ZSB9KTtcbmV4cG9ydHMucGFyc2VDbGFzcyA9IHZvaWQgMDtcbi8vIHsgPHBvc2l4IGNsYXNzPjogWzx0cmFuc2xhdGlvbj4sIC91IGZsYWcgcmVxdWlyZWQsIG5lZ2F0ZWRdXG5jb25zdCBwb3NpeENsYXNzZXMgPSB7XG4gICAgJ1s6YWxudW06XSc6IFsnXFxcXHB7TH1cXFxccHtObH1cXFxccHtOZH0nLCB0cnVlXSxcbiAgICAnWzphbHBoYTpdJzogWydcXFxccHtMfVxcXFxwe05sfScsIHRydWVdLFxuICAgICdbOmFzY2lpOl0nOiBbJ1xcXFx4JyArICcwMC1cXFxceCcgKyAnN2YnLCBmYWxzZV0sXG4gICAgJ1s6Ymxhbms6XSc6IFsnXFxcXHB7WnN9XFxcXHQnLCB0cnVlXSxcbiAgICAnWzpjbnRybDpdJzogWydcXFxccHtDY30nLCB0cnVlXSxcbiAgICAnWzpkaWdpdDpdJzogWydcXFxccHtOZH0nLCB0cnVlXSxcbiAgICAnWzpncmFwaDpdJzogWydcXFxccHtafVxcXFxwe0N9JywgdHJ1ZSwgdHJ1ZV0sXG4gICAgJ1s6bG93ZXI6XSc6IFsnXFxcXHB7TGx9JywgdHJ1ZV0sXG4gICAgJ1s6cHJpbnQ6XSc6IFsnXFxcXHB7Q30nLCB0cnVlXSxcbiAgICAnWzpwdW5jdDpdJzogWydcXFxccHtQfScsIHRydWVdLFxuICAgICdbOnNwYWNlOl0nOiBbJ1xcXFxwe1p9XFxcXHRcXFxcclxcXFxuXFxcXHZcXFxcZicsIHRydWVdLFxuICAgICdbOnVwcGVyOl0nOiBbJ1xcXFxwe0x1fScsIHRydWVdLFxuICAgICdbOndvcmQ6XSc6IFsnXFxcXHB7TH1cXFxccHtObH1cXFxccHtOZH1cXFxccHtQY30nLCB0cnVlXSxcbiAgICAnWzp4ZGlnaXQ6XSc6IFsnQS1GYS1mMC05JywgZmFsc2VdLFxufTtcbi8vIG9ubHkgbmVlZCB0byBlc2NhcGUgYSBmZXcgdGhpbmdzIGluc2lkZSBvZiBicmFjZSBleHByZXNzaW9uc1xuLy8gZXNjYXBlczogWyBcXCBdIC1cbmNvbnN0IGJyYWNlRXNjYXBlID0gKHMpID0+IHMucmVwbGFjZSgvW1tcXF1cXFxcLV0vZywgJ1xcXFwkJicpO1xuLy8gZXNjYXBlIGFsbCByZWdleHAgbWFnaWMgY2hhcmFjdGVyc1xuY29uc3QgcmVnZXhwRXNjYXBlID0gKHMpID0+IHMucmVwbGFjZSgvWy1bXFxde30oKSorPy4sXFxcXF4kfCNcXHNdL2csICdcXFxcJCYnKTtcbi8vIGV2ZXJ5dGhpbmcgaGFzIGFscmVhZHkgYmVlbiBlc2NhcGVkLCB3ZSBqdXN0IGhhdmUgdG8gam9pblxuY29uc3QgcmFuZ2VzVG9TdHJpbmcgPSAocmFuZ2VzKSA9PiByYW5nZXMuam9pbignJyk7XG4vLyB0YWtlcyBhIGdsb2Igc3RyaW5nIGF0IGEgcG9zaXggYnJhY2UgZXhwcmVzc2lvbiwgYW5kIHJldHVybnNcbi8vIGFuIGVxdWl2YWxlbnQgcmVndWxhciBleHByZXNzaW9uIHNvdXJjZSwgYW5kIGJvb2xlYW4gaW5kaWNhdGluZ1xuLy8gd2hldGhlciB0aGUgL3UgZmxhZyBuZWVkcyB0byBiZSBhcHBsaWVkLCBhbmQgdGhlIG51bWJlciBvZiBjaGFyc1xuLy8gY29uc3VtZWQgdG8gcGFyc2UgdGhlIGNoYXJhY3RlciBjbGFzcy5cbi8vIFRoaXMgYWxzbyByZW1vdmVzIG91dCBvZiBvcmRlciByYW5nZXMsIGFuZCByZXR1cm5zICgkLikgaWYgdGhlXG4vLyBlbnRpcmUgY2xhc3MganVzdCBubyBnb29kLlxuY29uc3QgcGFyc2VDbGFzcyA9IChnbG9iLCBwb3NpdGlvbikgPT4ge1xuICAgIGNvbnN0IHBvcyA9IHBvc2l0aW9uO1xuICAgIC8qIGM4IGlnbm9yZSBzdGFydCAqL1xuICAgIGlmIChnbG9iLmNoYXJBdChwb3MpICE9PSAnWycpIHtcbiAgICAgICAgdGhyb3cgbmV3IEVycm9yKCdub3QgaW4gYSBicmFjZSBleHByZXNzaW9uJyk7XG4gICAgfVxuICAgIC8qIGM4IGlnbm9yZSBzdG9wICovXG4gICAgY29uc3QgcmFuZ2VzID0gW107XG4gICAgY29uc3QgbmVncyA9IFtdO1xuICAgIGxldCBpID0gcG9zICsgMTtcbiAgICBsZXQgc2F3U3RhcnQgPSBmYWxzZTtcbiAgICBsZXQgdWZsYWcgPSBmYWxzZTtcbiAgICBsZXQgZXNjYXBpbmcgPSBmYWxzZTtcbiAgICBsZXQgbmVnYXRlID0gZmFsc2U7XG4gICAgbGV0IGVuZFBvcyA9IHBvcztcbiAgICBsZXQgcmFuZ2VTdGFydCA9ICcnO1xuICAgIFdISUxFOiB3aGlsZSAoaSA8IGdsb2IubGVuZ3RoKSB7XG4gICAgICAgIGNvbnN0IGMgPSBnbG9iLmNoYXJBdChpKTtcbiAgICAgICAgaWYgKChjID09PSAnIScgfHwgYyA9PT0gJ14nKSAmJiBpID09PSBwb3MgKyAxKSB7XG4gICAgICAgICAgICBuZWdhdGUgPSB0cnVlO1xuICAgICAgICAgICAgaSsrO1xuICAgICAgICAgICAgY29udGludWU7XG4gICAgICAgIH1cbiAgICAgICAgaWYgKGMgPT09ICddJyAmJiBzYXdTdGFydCAmJiAhZXNjYXBpbmcpIHtcbiAgICAgICAgICAgIGVuZFBvcyA9IGkgKyAxO1xuICAgICAgICAgICAgYnJlYWs7XG4gICAgICAgIH1cbiAgICAgICAgc2F3U3RhcnQgPSB0cnVlO1xuICAgICAgICBpZiAoYyA9PT0gJ1xcXFwnKSB7XG4gICAgICAgICAgICBpZiAoIWVzY2FwaW5nKSB7XG4gICAgICAgICAgICAgICAgZXNjYXBpbmcgPSB0cnVlO1xuICAgICAgICAgICAgICAgIGkrKztcbiAgICAgICAgICAgICAgICBjb250aW51ZTtcbiAgICAgICAgICAgIH1cbiAgICAgICAgICAgIC8vIGVzY2FwZWQgXFwgY2hhciwgZmFsbCB0aHJvdWdoIGFuZCB0cmVhdCBsaWtlIG5vcm1hbCBjaGFyXG4gICAgICAgIH1cbiAgICAgICAgaWYgKGMgPT09ICdbJyAmJiAhZXNjYXBpbmcpIHtcbiAgICAgICAgICAgIC8vIGVpdGhlciBhIHBvc2l4IGNsYXNzLCBhIGNvbGxhdGlvbiBlcXVpdmFsZW50LCBvciBqdXN0IGEgW1xuICAgICAgICAgICAgZm9yIChjb25zdCBbY2xzLCBbdW5pcCwgdSwgbmVnXV0gb2YgT2JqZWN0LmVudHJpZXMocG9zaXhDbGFzc2VzKSkge1xuICAgICAgICAgICAgICAgIGlmIChnbG9iLnN0YXJ0c1dpdGgoY2xzLCBpKSkge1xuICAgICAgICAgICAgICAgICAgICAvLyBpbnZhbGlkLCBbYS1bXSBpcyBmaW5lLCBidXQgbm90IFthLVs6YWxwaGFdXVxuICAgICAgICAgICAgICAgICAgICBpZiAocmFuZ2VTdGFydCkge1xuICAgICAgICAgICAgICAgICAgICAgICAgcmV0dXJuIFsnJC4nLCBmYWxzZSwgZ2xvYi5sZW5ndGggLSBwb3MsIHRydWVdO1xuICAgICAgICAgICAgICAgICAgICB9XG4gICAgICAgICAgICAgICAgICAgIGkgKz0gY2xzLmxlbmd0aDtcbiAgICAgICAgICAgICAgICAgICAgaWYgKG5lZylcbiAgICAgICAgICAgICAgICAgICAgICAgIG5lZ3MucHVzaCh1bmlwKTtcbiAgICAgICAgICAgICAgICAgICAgZWxzZVxuICAgICAgICAgICAgICAgICAgICAgICAgcmFuZ2VzLnB1c2godW5pcCk7XG4gICAgICAgICAgICAgICAgICAgIHVmbGFnID0gdWZsYWcgfHwgdTtcbiAgICAgICAgICAgICAgICAgICAgY29udGludWUgV0hJTEU7XG4gICAgICAgICAgICAgICAgfVxuICAgICAgICAgICAgfVxuICAgICAgICB9XG4gICAgICAgIC8vIG5vdyBpdCdzIGp1c3QgYSBub3JtYWwgY2hhcmFjdGVyLCBlZmZlY3RpdmVseVxuICAgICAgICBlc2NhcGluZyA9IGZhbHNlO1xuICAgICAgICBpZiAocmFuZ2VTdGFydCkge1xuICAgICAgICAgICAgLy8gdGhyb3cgdGhpcyByYW5nZSBhd2F5IGlmIGl0J3Mgbm90IHZhbGlkLCBidXQgb3RoZXJzXG4gICAgICAgICAgICAvLyBjYW4gc3RpbGwgbWF0Y2guXG4gICAgICAgICAgICBpZiAoYyA+IHJhbmdlU3RhcnQpIHtcbiAgICAgICAgICAgICAgICByYW5nZXMucHVzaChicmFjZUVzY2FwZShyYW5nZVN0YXJ0KSArICctJyArIGJyYWNlRXNjYXBlKGMpKTtcbiAgICAgICAgICAgIH1cbiAgICAgICAgICAgIGVsc2UgaWYgKGMgPT09IHJhbmdlU3RhcnQpIHtcbiAgICAgICAgICAgICAgICByYW5nZXMucHVzaChicmFjZUVzY2FwZShjKSk7XG4gICAgICAgICAgICB9XG4gICAgICAgICAgICByYW5nZVN0YXJ0ID0gJyc7XG4gICAgICAgICAgICBpKys7XG4gICAgICAgICAgICBjb250aW51ZTtcbiAgICAgICAgfVxuICAgICAgICAvLyBub3cgbWlnaHQgYmUgdGhlIHN0YXJ0IG9mIGEgcmFuZ2UuXG4gICAgICAgIC8vIGNhbiBiZSBlaXRoZXIgYy1kIG9yIGMtXSBvciBjPG1vcmUuLi4+XSBvciBjXSBhdCB0aGlzIHBvaW50XG4gICAgICAgIGlmIChnbG9iLnN0YXJ0c1dpdGgoJy1dJywgaSArIDEpKSB7XG4gICAgICAgICAgICByYW5nZXMucHVzaChicmFjZUVzY2FwZShjICsgJy0nKSk7XG4gICAgICAgICAgICBpICs9IDI7XG4gICAgICAgICAgICBjb250aW51ZTtcbiAgICAgICAgfVxuICAgICAgICBpZiAoZ2xvYi5zdGFydHNXaXRoKCctJywgaSArIDEpKSB7XG4gICAgICAgICAgICByYW5nZVN0YXJ0ID0gYztcbiAgICAgICAgICAgIGkgKz0gMjtcbiAgICAgICAgICAgIGNvbnRpbnVlO1xuICAgICAgICB9XG4gICAgICAgIC8vIG5vdCB0aGUgc3RhcnQgb2YgYSByYW5nZSwganVzdCBhIHNpbmdsZSBjaGFyYWN0ZXJcbiAgICAgICAgcmFuZ2VzLnB1c2goYnJhY2VFc2NhcGUoYykpO1xuICAgICAgICBpKys7XG4gICAgfVxuICAgIGlmIChlbmRQb3MgPCBpKSB7XG4gICAgICAgIC8vIGRpZG4ndCBzZWUgdGhlIGVuZCBvZiB0aGUgY2xhc3MsIG5vdCBhIHZhbGlkIGNsYXNzLFxuICAgICAgICAvLyBidXQgbWlnaHQgc3RpbGwgYmUgdmFsaWQgYXMgYSBsaXRlcmFsIG1hdGNoLlxuICAgICAgICByZXR1cm4gWycnLCBmYWxzZSwgMCwgZmFsc2VdO1xuICAgIH1cbiAgICAvLyBpZiB3ZSBnb3Qgbm8gcmFuZ2VzIGFuZCBubyBuZWdhdGVzLCB0aGVuIHdlIGhhdmUgYSByYW5nZSB0aGF0XG4gICAgLy8gY2Fubm90IHBvc3NpYmx5IG1hdGNoIGFueXRoaW5nLCBhbmQgdGhhdCBwb2lzb25zIHRoZSB3aG9sZSBnbG9iXG4gICAgaWYgKCFyYW5nZXMubGVuZ3RoICYmICFuZWdzLmxlbmd0aCkge1xuICAgICAgICByZXR1cm4gWyckLicsIGZhbHNlLCBnbG9iLmxlbmd0aCAtIHBvcywgdHJ1ZV07XG4gICAgfVxuICAgIC8vIGlmIHdlIGdvdCBvbmUgcG9zaXRpdmUgcmFuZ2UsIGFuZCBpdCdzIGEgc2luZ2xlIGNoYXJhY3RlciwgdGhlbiB0aGF0J3NcbiAgICAvLyBub3QgYWN0dWFsbHkgYSBtYWdpYyBwYXR0ZXJuLCBpdCdzIGp1c3QgdGhhdCBvbmUgbGl0ZXJhbCBjaGFyYWN0ZXIuXG4gICAgLy8gd2Ugc2hvdWxkIG5vdCB0cmVhdCB0aGF0IGFzIFwibWFnaWNcIiwgd2Ugc2hvdWxkIGp1c3QgcmV0dXJuIHRoZSBsaXRlcmFsXG4gICAgLy8gY2hhcmFjdGVyLiBbX10gaXMgYSBwZXJmZWN0bHkgdmFsaWQgd2F5IHRvIGVzY2FwZSBnbG9iIG1hZ2ljIGNoYXJzLlxuICAgIGlmIChuZWdzLmxlbmd0aCA9PT0gMCAmJlxuICAgICAgICByYW5nZXMubGVuZ3RoID09PSAxICYmXG4gICAgICAgIC9eXFxcXD8uJC8udGVzdChyYW5nZXNbMF0pICYmXG4gICAgICAgICFuZWdhdGUpIHtcbiAgICAgICAgY29uc3QgciA9IHJhbmdlc1swXS5sZW5ndGggPT09IDIgPyByYW5nZXNbMF0uc2xpY2UoLTEpIDogcmFuZ2VzWzBdO1xuICAgICAgICByZXR1cm4gW3JlZ2V4cEVzY2FwZShyKSwgZmFsc2UsIGVuZFBvcyAtIHBvcywgZmFsc2VdO1xuICAgIH1cbiAgICBjb25zdCBzcmFuZ2VzID0gJ1snICsgKG5lZ2F0ZSA/ICdeJyA6ICcnKSArIHJhbmdlc1RvU3RyaW5nKHJhbmdlcykgKyAnXSc7XG4gICAgY29uc3Qgc25lZ3MgPSAnWycgKyAobmVnYXRlID8gJycgOiAnXicpICsgcmFuZ2VzVG9TdHJpbmcobmVncykgKyAnXSc7XG4gICAgY29uc3QgY29tYiA9IHJhbmdlcy5sZW5ndGggJiYgbmVncy5sZW5ndGhcbiAgICAgICAgPyAnKCcgKyBzcmFuZ2VzICsgJ3wnICsgc25lZ3MgKyAnKSdcbiAgICAgICAgOiByYW5nZXMubGVuZ3RoXG4gICAgICAgICAgICA/IHNyYW5nZXNcbiAgICAgICAgICAgIDogc25lZ3M7XG4gICAgcmV0dXJuIFtjb21iLCB1ZmxhZywgZW5kUG9zIC0gcG9zLCB0cnVlXTtcbn07XG5leHBvcnRzLnBhcnNlQ2xhc3MgPSBwYXJzZUNsYXNzO1xuLy8jIHNvdXJjZU1hcHBpbmdVUkw9YnJhY2UtZXhwcmVzc2lvbnMuanMubWFwIiwiXCJ1c2Ugc3RyaWN0XCI7XG5PYmplY3QuZGVmaW5lUHJvcGVydHkoZXhwb3J0cywgXCJfX2VzTW9kdWxlXCIsIHsgdmFsdWU6IHRydWUgfSk7XG5leHBvcnRzLmVzY2FwZSA9IHZvaWQgMDtcbi8qKlxuICogRXNjYXBlIGFsbCBtYWdpYyBjaGFyYWN0ZXJzIGluIGEgZ2xvYiBwYXR0ZXJuLlxuICpcbiAqIElmIHRoZSB7QGxpbmsgd2luZG93c1BhdGhzTm9Fc2NhcGUgfCBHbG9iT3B0aW9ucy53aW5kb3dzUGF0aHNOb0VzY2FwZX1cbiAqIG9wdGlvbiBpcyB1c2VkLCB0aGVuIGNoYXJhY3RlcnMgYXJlIGVzY2FwZWQgYnkgd3JhcHBpbmcgaW4gYFtdYCwgYmVjYXVzZVxuICogYSBtYWdpYyBjaGFyYWN0ZXIgd3JhcHBlZCBpbiBhIGNoYXJhY3RlciBjbGFzcyBjYW4gb25seSBiZSBzYXRpc2ZpZWQgYnlcbiAqIHRoYXQgZXhhY3QgY2hhcmFjdGVyLiAgSW4gdGhpcyBtb2RlLCBgXFxgIGlzIF9ub3RfIGVzY2FwZWQsIGJlY2F1c2UgaXQgaXNcbiAqIG5vdCBpbnRlcnByZXRlZCBhcyBhIG1hZ2ljIGNoYXJhY3RlciwgYnV0IGluc3RlYWQgYXMgYSBwYXRoIHNlcGFyYXRvci5cbiAqL1xuY29uc3QgZXNjYXBlID0gKHMsIHsgd2luZG93c1BhdGhzTm9Fc2NhcGUgPSBmYWxzZSwgfSA9IHt9KSA9PiB7XG4gICAgLy8gZG9uJ3QgbmVlZCB0byBlc2NhcGUgK0AhIGJlY2F1c2Ugd2UgZXNjYXBlIHRoZSBwYXJlbnNcbiAgICAvLyB0aGF0IG1ha2UgdGhvc2UgbWFnaWMsIGFuZCBlc2NhcGluZyAhIGFzIFshXSBpc24ndCB2YWxpZCxcbiAgICAvLyBiZWNhdXNlIFshXV0gaXMgYSB2YWxpZCBnbG9iIGNsYXNzIG1lYW5pbmcgbm90ICddJy5cbiAgICByZXR1cm4gd2luZG93c1BhdGhzTm9Fc2NhcGVcbiAgICAgICAgPyBzLnJlcGxhY2UoL1s/KigpW1xcXV0vZywgJ1skJl0nKVxuICAgICAgICA6IHMucmVwbGFjZSgvWz8qKClbXFxdXFxcXF0vZywgJ1xcXFwkJicpO1xufTtcbmV4cG9ydHMuZXNjYXBlID0gZXNjYXBlO1xuLy8jIHNvdXJjZU1hcHBpbmdVUkw9ZXNjYXBlLmpzLm1hcCIsIlwidXNlIHN0cmljdFwiO1xudmFyIF9faW1wb3J0RGVmYXVsdCA9ICh0aGlzICYmIHRoaXMuX19pbXBvcnREZWZhdWx0KSB8fCBmdW5jdGlvbiAobW9kKSB7XG4gICAgcmV0dXJuIChtb2QgJiYgbW9kLl9fZXNNb2R1bGUpID8gbW9kIDogeyBcImRlZmF1bHRcIjogbW9kIH07XG59O1xuT2JqZWN0LmRlZmluZVByb3BlcnR5KGV4cG9ydHMsIFwiX19lc01vZHVsZVwiLCB7IHZhbHVlOiB0cnVlIH0pO1xuZXhwb3J0cy51bmVzY2FwZSA9IGV4cG9ydHMuZXNjYXBlID0gZXhwb3J0cy5BU1QgPSBleHBvcnRzLk1pbmltYXRjaCA9IGV4cG9ydHMubWF0Y2ggPSBleHBvcnRzLm1ha2VSZSA9IGV4cG9ydHMuYnJhY2VFeHBhbmQgPSBleHBvcnRzLmRlZmF1bHRzID0gZXhwb3J0cy5maWx0ZXIgPSBleHBvcnRzLkdMT0JTVEFSID0gZXhwb3J0cy5zZXAgPSBleHBvcnRzLm1pbmltYXRjaCA9IHZvaWQgMDtcbmNvbnN0IGJyYWNlX2V4cGFuc2lvbl8xID0gX19pbXBvcnREZWZhdWx0KHJlcXVpcmUoXCJicmFjZS1leHBhbnNpb25cIikpO1xuY29uc3QgYXNzZXJ0X3ZhbGlkX3BhdHRlcm5fanNfMSA9IHJlcXVpcmUoXCIuL2Fzc2VydC12YWxpZC1wYXR0ZXJuLmpzXCIpO1xuY29uc3QgYXN0X2pzXzEgPSByZXF1aXJlKFwiLi9hc3QuanNcIik7XG5jb25zdCBlc2NhcGVfanNfMSA9IHJlcXVpcmUoXCIuL2VzY2FwZS5qc1wiKTtcbmNvbnN0IHVuZXNjYXBlX2pzXzEgPSByZXF1aXJlKFwiLi91bmVzY2FwZS5qc1wiKTtcbmNvbnN0IG1pbmltYXRjaCA9IChwLCBwYXR0ZXJuLCBvcHRpb25zID0ge30pID0+IHtcbiAgICAoMCwgYXNzZXJ0X3ZhbGlkX3BhdHRlcm5fanNfMS5hc3NlcnRWYWxpZFBhdHRlcm4pKHBhdHRlcm4pO1xuICAgIC8vIHNob3J0Y3V0OiBjb21tZW50cyBtYXRjaCBub3RoaW5nLlxuICAgIGlmICghb3B0aW9ucy5ub2NvbW1lbnQgJiYgcGF0dGVybi5jaGFyQXQoMCkgPT09ICcjJykge1xuICAgICAgICByZXR1cm4gZmFsc2U7XG4gICAgfVxuICAgIHJldHVybiBuZXcgTWluaW1hdGNoKHBhdHRlcm4sIG9wdGlvbnMpLm1hdGNoKHApO1xufTtcbmV4cG9ydHMubWluaW1hdGNoID0gbWluaW1hdGNoO1xuLy8gT3B0aW1pemVkIGNoZWNraW5nIGZvciB0aGUgbW9zdCBjb21tb24gZ2xvYiBwYXR0ZXJucy5cbmNvbnN0IHN0YXJEb3RFeHRSRSA9IC9eXFwqKyhbXitAIT9cXCpcXFtcXChdKikkLztcbmNvbnN0IHN0YXJEb3RFeHRUZXN0ID0gKGV4dCkgPT4gKGYpID0+ICFmLnN0YXJ0c1dpdGgoJy4nKSAmJiBmLmVuZHNXaXRoKGV4dCk7XG5jb25zdCBzdGFyRG90RXh0VGVzdERvdCA9IChleHQpID0+IChmKSA9PiBmLmVuZHNXaXRoKGV4dCk7XG5jb25zdCBzdGFyRG90RXh0VGVzdE5vY2FzZSA9IChleHQpID0+IHtcbiAgICBleHQgPSBleHQudG9Mb3dlckNhc2UoKTtcbiAgICByZXR1cm4gKGYpID0+ICFmLnN0YXJ0c1dpdGgoJy4nKSAmJiBmLnRvTG93ZXJDYXNlKCkuZW5kc1dpdGgoZXh0KTtcbn07XG5jb25zdCBzdGFyRG90RXh0VGVzdE5vY2FzZURvdCA9IChleHQpID0+IHtcbiAgICBleHQgPSBleHQudG9Mb3dlckNhc2UoKTtcbiAgICByZXR1cm4gKGYpID0+IGYudG9Mb3dlckNhc2UoKS5lbmRzV2l0aChleHQpO1xufTtcbmNvbnN0IHN0YXJEb3RTdGFyUkUgPSAvXlxcKitcXC5cXCorJC87XG5jb25zdCBzdGFyRG90U3RhclRlc3QgPSAoZikgPT4gIWYuc3RhcnRzV2l0aCgnLicpICYmIGYuaW5jbHVkZXMoJy4nKTtcbmNvbnN0IHN0YXJEb3RTdGFyVGVzdERvdCA9IChmKSA9PiBmICE9PSAnLicgJiYgZiAhPT0gJy4uJyAmJiBmLmluY2x1ZGVzKCcuJyk7XG5jb25zdCBkb3RTdGFyUkUgPSAvXlxcLlxcKiskLztcbmNvbnN0IGRvdFN0YXJUZXN0ID0gKGYpID0+IGYgIT09ICcuJyAmJiBmICE9PSAnLi4nICYmIGYuc3RhcnRzV2l0aCgnLicpO1xuY29uc3Qgc3RhclJFID0gL15cXCorJC87XG5jb25zdCBzdGFyVGVzdCA9IChmKSA9PiBmLmxlbmd0aCAhPT0gMCAmJiAhZi5zdGFydHNXaXRoKCcuJyk7XG5jb25zdCBzdGFyVGVzdERvdCA9IChmKSA9PiBmLmxlbmd0aCAhPT0gMCAmJiBmICE9PSAnLicgJiYgZiAhPT0gJy4uJztcbmNvbnN0IHFtYXJrc1JFID0gL15cXD8rKFteK0AhP1xcKlxcW1xcKF0qKT8kLztcbmNvbnN0IHFtYXJrc1Rlc3ROb2Nhc2UgPSAoWyQwLCBleHQgPSAnJ10pID0+IHtcbiAgICBjb25zdCBub2V4dCA9IHFtYXJrc1Rlc3ROb0V4dChbJDBdKTtcbiAgICBpZiAoIWV4dClcbiAgICAgICAgcmV0dXJuIG5vZXh0O1xuICAgIGV4dCA9IGV4dC50b0xvd2VyQ2FzZSgpO1xuICAgIHJldHVybiAoZikgPT4gbm9leHQoZikgJiYgZi50b0xvd2VyQ2FzZSgpLmVuZHNXaXRoKGV4dCk7XG59O1xuY29uc3QgcW1hcmtzVGVzdE5vY2FzZURvdCA9IChbJDAsIGV4dCA9ICcnXSkgPT4ge1xuICAgIGNvbnN0IG5vZXh0ID0gcW1hcmtzVGVzdE5vRXh0RG90KFskMF0pO1xuICAgIGlmICghZXh0KVxuICAgICAgICByZXR1cm4gbm9leHQ7XG4gICAgZXh0ID0gZXh0LnRvTG93ZXJDYXNlKCk7XG4gICAgcmV0dXJuIChmKSA9PiBub2V4dChmKSAmJiBmLnRvTG93ZXJDYXNlKCkuZW5kc1dpdGgoZXh0KTtcbn07XG5jb25zdCBxbWFya3NUZXN0RG90ID0gKFskMCwgZXh0ID0gJyddKSA9PiB7XG4gICAgY29uc3Qgbm9leHQgPSBxbWFya3NUZXN0Tm9FeHREb3QoWyQwXSk7XG4gICAgcmV0dXJuICFleHQgPyBub2V4dCA6IChmKSA9PiBub2V4dChmKSAmJiBmLmVuZHNXaXRoKGV4dCk7XG59O1xuY29uc3QgcW1hcmtzVGVzdCA9IChbJDAsIGV4dCA9ICcnXSkgPT4ge1xuICAgIGNvbnN0IG5vZXh0ID0gcW1hcmtzVGVzdE5vRXh0KFskMF0pO1xuICAgIHJldHVybiAhZXh0ID8gbm9leHQgOiAoZikgPT4gbm9leHQoZikgJiYgZi5lbmRzV2l0aChleHQpO1xufTtcbmNvbnN0IHFtYXJrc1Rlc3ROb0V4dCA9IChbJDBdKSA9PiB7XG4gICAgY29uc3QgbGVuID0gJDAubGVuZ3RoO1xuICAgIHJldHVybiAoZikgPT4gZi5sZW5ndGggPT09IGxlbiAmJiAhZi5zdGFydHNXaXRoKCcuJyk7XG59O1xuY29uc3QgcW1hcmtzVGVzdE5vRXh0RG90ID0gKFskMF0pID0+IHtcbiAgICBjb25zdCBsZW4gPSAkMC5sZW5ndGg7XG4gICAgcmV0dXJuIChmKSA9PiBmLmxlbmd0aCA9PT0gbGVuICYmIGYgIT09ICcuJyAmJiBmICE9PSAnLi4nO1xufTtcbi8qIGM4IGlnbm9yZSBzdGFydCAqL1xuY29uc3QgZGVmYXVsdFBsYXRmb3JtID0gKHR5cGVvZiBwcm9jZXNzID09PSAnb2JqZWN0JyAmJiBwcm9jZXNzXG4gICAgPyAodHlwZW9mIHByb2Nlc3MuZW52ID09PSAnb2JqZWN0JyAmJlxuICAgICAgICBwcm9jZXNzLmVudiAmJlxuICAgICAgICBwcm9jZXNzLmVudi5fX01JTklNQVRDSF9URVNUSU5HX1BMQVRGT1JNX18pIHx8XG4gICAgICAgIHByb2Nlc3MucGxhdGZvcm1cbiAgICA6ICdwb3NpeCcpO1xuY29uc3QgcGF0aCA9IHtcbiAgICB3aW4zMjogeyBzZXA6ICdcXFxcJyB9LFxuICAgIHBvc2l4OiB7IHNlcDogJy8nIH0sXG59O1xuLyogYzggaWdub3JlIHN0b3AgKi9cbmV4cG9ydHMuc2VwID0gZGVmYXVsdFBsYXRmb3JtID09PSAnd2luMzInID8gcGF0aC53aW4zMi5zZXAgOiBwYXRoLnBvc2l4LnNlcDtcbmV4cG9ydHMubWluaW1hdGNoLnNlcCA9IGV4cG9ydHMuc2VwO1xuZXhwb3J0cy5HTE9CU1RBUiA9IFN5bWJvbCgnZ2xvYnN0YXIgKionKTtcbmV4cG9ydHMubWluaW1hdGNoLkdMT0JTVEFSID0gZXhwb3J0cy5HTE9CU1RBUjtcbi8vIGFueSBzaW5nbGUgdGhpbmcgb3RoZXIgdGhhbiAvXG4vLyBkb24ndCBuZWVkIHRvIGVzY2FwZSAvIHdoZW4gdXNpbmcgbmV3IFJlZ0V4cCgpXG5jb25zdCBxbWFyayA9ICdbXi9dJztcbi8vICogPT4gYW55IG51bWJlciBvZiBjaGFyYWN0ZXJzXG5jb25zdCBzdGFyID0gcW1hcmsgKyAnKj8nO1xuLy8gKiogd2hlbiBkb3RzIGFyZSBhbGxvd2VkLiAgQW55dGhpbmcgZ29lcywgZXhjZXB0IC4uIGFuZCAuXG4vLyBub3QgKF4gb3IgLyBmb2xsb3dlZCBieSBvbmUgb3IgdHdvIGRvdHMgZm9sbG93ZWQgYnkgJCBvciAvKSxcbi8vIGZvbGxvd2VkIGJ5IGFueXRoaW5nLCBhbnkgbnVtYmVyIG9mIHRpbWVzLlxuY29uc3QgdHdvU3RhckRvdCA9ICcoPzooPyEoPzpcXFxcL3xeKSg/OlxcXFwuezEsMn0pKCR8XFxcXC8pKS4pKj8nO1xuLy8gbm90IGEgXiBvciAvIGZvbGxvd2VkIGJ5IGEgZG90LFxuLy8gZm9sbG93ZWQgYnkgYW55dGhpbmcsIGFueSBudW1iZXIgb2YgdGltZXMuXG5jb25zdCB0d29TdGFyTm9Eb3QgPSAnKD86KD8hKD86XFxcXC98XilcXFxcLikuKSo/JztcbmNvbnN0IGZpbHRlciA9IChwYXR0ZXJuLCBvcHRpb25zID0ge30pID0+IChwKSA9PiAoMCwgZXhwb3J0cy5taW5pbWF0Y2gpKHAsIHBhdHRlcm4sIG9wdGlvbnMpO1xuZXhwb3J0cy5maWx0ZXIgPSBmaWx0ZXI7XG5leHBvcnRzLm1pbmltYXRjaC5maWx0ZXIgPSBleHBvcnRzLmZpbHRlcjtcbmNvbnN0IGV4dCA9IChhLCBiID0ge30pID0+IE9iamVjdC5hc3NpZ24oe30sIGEsIGIpO1xuY29uc3QgZGVmYXVsdHMgPSAoZGVmKSA9PiB7XG4gICAgaWYgKCFkZWYgfHwgdHlwZW9mIGRlZiAhPT0gJ29iamVjdCcgfHwgIU9iamVjdC5rZXlzKGRlZikubGVuZ3RoKSB7XG4gICAgICAgIHJldHVybiBleHBvcnRzLm1pbmltYXRjaDtcbiAgICB9XG4gICAgY29uc3Qgb3JpZyA9IGV4cG9ydHMubWluaW1hdGNoO1xuICAgIGNvbnN0IG0gPSAocCwgcGF0dGVybiwgb3B0aW9ucyA9IHt9KSA9PiBvcmlnKHAsIHBhdHRlcm4sIGV4dChkZWYsIG9wdGlvbnMpKTtcbiAgICByZXR1cm4gT2JqZWN0LmFzc2lnbihtLCB7XG4gICAgICAgIE1pbmltYXRjaDogY2xhc3MgTWluaW1hdGNoIGV4dGVuZHMgb3JpZy5NaW5pbWF0Y2gge1xuICAgICAgICAgICAgY29uc3RydWN0b3IocGF0dGVybiwgb3B0aW9ucyA9IHt9KSB7XG4gICAgICAgICAgICAgICAgc3VwZXIocGF0dGVybiwgZXh0KGRlZiwgb3B0aW9ucykpO1xuICAgICAgICAgICAgfVxuICAgICAgICAgICAgc3RhdGljIGRlZmF1bHRzKG9wdGlvbnMpIHtcbiAgICAgICAgICAgICAgICByZXR1cm4gb3JpZy5kZWZhdWx0cyhleHQoZGVmLCBvcHRpb25zKSkuTWluaW1hdGNoO1xuICAgICAgICAgICAgfVxuICAgICAgICB9LFxuICAgICAgICBBU1Q6IGNsYXNzIEFTVCBleHRlbmRzIG9yaWcuQVNUIHtcbiAgICAgICAgICAgIC8qIGM4IGlnbm9yZSBzdGFydCAqL1xuICAgICAgICAgICAgY29uc3RydWN0b3IodHlwZSwgcGFyZW50LCBvcHRpb25zID0ge30pIHtcbiAgICAgICAgICAgICAgICBzdXBlcih0eXBlLCBwYXJlbnQsIGV4dChkZWYsIG9wdGlvbnMpKTtcbiAgICAgICAgICAgIH1cbiAgICAgICAgICAgIC8qIGM4IGlnbm9yZSBzdG9wICovXG4gICAgICAgICAgICBzdGF0aWMgZnJvbUdsb2IocGF0dGVybiwgb3B0aW9ucyA9IHt9KSB7XG4gICAgICAgICAgICAgICAgcmV0dXJuIG9yaWcuQVNULmZyb21HbG9iKHBhdHRlcm4sIGV4dChkZWYsIG9wdGlvbnMpKTtcbiAgICAgICAgICAgIH1cbiAgICAgICAgfSxcbiAgICAgICAgdW5lc2NhcGU6IChzLCBvcHRpb25zID0ge30pID0+IG9yaWcudW5lc2NhcGUocywgZXh0KGRlZiwgb3B0aW9ucykpLFxuICAgICAgICBlc2NhcGU6IChzLCBvcHRpb25zID0ge30pID0+IG9yaWcuZXNjYXBlKHMsIGV4dChkZWYsIG9wdGlvbnMpKSxcbiAgICAgICAgZmlsdGVyOiAocGF0dGVybiwgb3B0aW9ucyA9IHt9KSA9PiBvcmlnLmZpbHRlcihwYXR0ZXJuLCBleHQoZGVmLCBvcHRpb25zKSksXG4gICAgICAgIGRlZmF1bHRzOiAob3B0aW9ucykgPT4gb3JpZy5kZWZhdWx0cyhleHQoZGVmLCBvcHRpb25zKSksXG4gICAgICAgIG1ha2VSZTogKHBhdHRlcm4sIG9wdGlvbnMgPSB7fSkgPT4gb3JpZy5tYWtlUmUocGF0dGVybiwgZXh0KGRlZiwgb3B0aW9ucykpLFxuICAgICAgICBicmFjZUV4cGFuZDogKHBhdHRlcm4sIG9wdGlvbnMgPSB7fSkgPT4gb3JpZy5icmFjZUV4cGFuZChwYXR0ZXJuLCBleHQoZGVmLCBvcHRpb25zKSksXG4gICAgICAgIG1hdGNoOiAobGlzdCwgcGF0dGVybiwgb3B0aW9ucyA9IHt9KSA9PiBvcmlnLm1hdGNoKGxpc3QsIHBhdHRlcm4sIGV4dChkZWYsIG9wdGlvbnMpKSxcbiAgICAgICAgc2VwOiBvcmlnLnNlcCxcbiAgICAgICAgR0xPQlNUQVI6IGV4cG9ydHMuR0xPQlNUQVIsXG4gICAgfSk7XG59O1xuZXhwb3J0cy5kZWZhdWx0cyA9IGRlZmF1bHRzO1xuZXhwb3J0cy5taW5pbWF0Y2guZGVmYXVsdHMgPSBleHBvcnRzLmRlZmF1bHRzO1xuLy8gQnJhY2UgZXhwYW5zaW9uOlxuLy8gYXtiLGN9ZCAtPiBhYmQgYWNkXG4vLyBhe2IsfWMgLT4gYWJjIGFjXG4vLyBhezAuLjN9ZCAtPiBhMGQgYTFkIGEyZCBhM2Rcbi8vIGF7Yixje2QsZX1mfWcgLT4gYWJnIGFjZGZnIGFjZWZnXG4vLyBhe2IsY31ke2UsZn1nIC0+IGFiZGVnIGFjZGVnIGFiZGVnIGFiZGZnXG4vL1xuLy8gSW52YWxpZCBzZXRzIGFyZSBub3QgZXhwYW5kZWQuXG4vLyBhezIuLn1iIC0+IGF7Mi4ufWJcbi8vIGF7Yn1jIC0+IGF7Yn1jXG5jb25zdCBicmFjZUV4cGFuZCA9IChwYXR0ZXJuLCBvcHRpb25zID0ge30pID0+IHtcbiAgICAoMCwgYXNzZXJ0X3ZhbGlkX3BhdHRlcm5fanNfMS5hc3NlcnRWYWxpZFBhdHRlcm4pKHBhdHRlcm4pO1xuICAgIC8vIFRoYW5rcyB0byBZZXRpbmcgTGkgPGh0dHBzOi8vZ2l0aHViLmNvbS95ZXRpbmdsaT4gZm9yXG4gICAgLy8gaW1wcm92aW5nIHRoaXMgcmVnZXhwIHRvIGF2b2lkIGEgUmVET1MgdnVsbmVyYWJpbGl0eS5cbiAgICBpZiAob3B0aW9ucy5ub2JyYWNlIHx8ICEvXFx7KD86KD8hXFx7KS4pKlxcfS8udGVzdChwYXR0ZXJuKSkge1xuICAgICAgICAvLyBzaG9ydGN1dC4gbm8gbmVlZCB0byBleHBhbmQuXG4gICAgICAgIHJldHVybiBbcGF0dGVybl07XG4gICAgfVxuICAgIHJldHVybiAoMCwgYnJhY2VfZXhwYW5zaW9uXzEuZGVmYXVsdCkocGF0dGVybik7XG59O1xuZXhwb3J0cy5icmFjZUV4cGFuZCA9IGJyYWNlRXhwYW5kO1xuZXhwb3J0cy5taW5pbWF0Y2guYnJhY2VFeHBhbmQgPSBleHBvcnRzLmJyYWNlRXhwYW5kO1xuLy8gcGFyc2UgYSBjb21wb25lbnQgb2YgdGhlIGV4cGFuZGVkIHNldC5cbi8vIEF0IHRoaXMgcG9pbnQsIG5vIHBhdHRlcm4gbWF5IGNvbnRhaW4gXCIvXCIgaW4gaXRcbi8vIHNvIHdlJ3JlIGdvaW5nIHRvIHJldHVybiBhIDJkIGFycmF5LCB3aGVyZSBlYWNoIGVudHJ5IGlzIHRoZSBmdWxsXG4vLyBwYXR0ZXJuLCBzcGxpdCBvbiAnLycsIGFuZCB0aGVuIHR1cm5lZCBpbnRvIGEgcmVndWxhciBleHByZXNzaW9uLlxuLy8gQSByZWdleHAgaXMgbWFkZSBhdCB0aGUgZW5kIHdoaWNoIGpvaW5zIGVhY2ggYXJyYXkgd2l0aCBhblxuLy8gZXNjYXBlZCAvLCBhbmQgYW5vdGhlciBmdWxsIG9uZSB3aGljaCBqb2lucyBlYWNoIHJlZ2V4cCB3aXRoIHwuXG4vL1xuLy8gRm9sbG93aW5nIHRoZSBsZWFkIG9mIEJhc2ggNC4xLCBub3RlIHRoYXQgXCIqKlwiIG9ubHkgaGFzIHNwZWNpYWwgbWVhbmluZ1xuLy8gd2hlbiBpdCBpcyB0aGUgKm9ubHkqIHRoaW5nIGluIGEgcGF0aCBwb3J0aW9uLiAgT3RoZXJ3aXNlLCBhbnkgc2VyaWVzXG4vLyBvZiAqIGlzIGVxdWl2YWxlbnQgdG8gYSBzaW5nbGUgKi4gIEdsb2JzdGFyIGJlaGF2aW9yIGlzIGVuYWJsZWQgYnlcbi8vIGRlZmF1bHQsIGFuZCBjYW4gYmUgZGlzYWJsZWQgYnkgc2V0dGluZyBvcHRpb25zLm5vZ2xvYnN0YXIuXG5jb25zdCBtYWtlUmUgPSAocGF0dGVybiwgb3B0aW9ucyA9IHt9KSA9PiBuZXcgTWluaW1hdGNoKHBhdHRlcm4sIG9wdGlvbnMpLm1ha2VSZSgpO1xuZXhwb3J0cy5tYWtlUmUgPSBtYWtlUmU7XG5leHBvcnRzLm1pbmltYXRjaC5tYWtlUmUgPSBleHBvcnRzLm1ha2VSZTtcbmNvbnN0IG1hdGNoID0gKGxpc3QsIHBhdHRlcm4sIG9wdGlvbnMgPSB7fSkgPT4ge1xuICAgIGNvbnN0IG1tID0gbmV3IE1pbmltYXRjaChwYXR0ZXJuLCBvcHRpb25zKTtcbiAgICBsaXN0ID0gbGlzdC5maWx0ZXIoZiA9PiBtbS5tYXRjaChmKSk7XG4gICAgaWYgKG1tLm9wdGlvbnMubm9udWxsICYmICFsaXN0Lmxlbmd0aCkge1xuICAgICAgICBsaXN0LnB1c2gocGF0dGVybik7XG4gICAgfVxuICAgIHJldHVybiBsaXN0O1xufTtcbmV4cG9ydHMubWF0Y2ggPSBtYXRjaDtcbmV4cG9ydHMubWluaW1hdGNoLm1hdGNoID0gZXhwb3J0cy5tYXRjaDtcbi8vIHJlcGxhY2Ugc3R1ZmYgbGlrZSBcXCogd2l0aCAqXG5jb25zdCBnbG9iTWFnaWMgPSAvWz8qXXxbK0AhXVxcKC4qP1xcKXxcXFt8XFxdLztcbmNvbnN0IHJlZ0V4cEVzY2FwZSA9IChzKSA9PiBzLnJlcGxhY2UoL1stW1xcXXt9KCkqKz8uLFxcXFxeJHwjXFxzXS9nLCAnXFxcXCQmJyk7XG5jbGFzcyBNaW5pbWF0Y2gge1xuICAgIG9wdGlvbnM7XG4gICAgc2V0O1xuICAgIHBhdHRlcm47XG4gICAgd2luZG93c1BhdGhzTm9Fc2NhcGU7XG4gICAgbm9uZWdhdGU7XG4gICAgbmVnYXRlO1xuICAgIGNvbW1lbnQ7XG4gICAgZW1wdHk7XG4gICAgcHJlc2VydmVNdWx0aXBsZVNsYXNoZXM7XG4gICAgcGFydGlhbDtcbiAgICBnbG9iU2V0O1xuICAgIGdsb2JQYXJ0cztcbiAgICBub2Nhc2U7XG4gICAgaXNXaW5kb3dzO1xuICAgIHBsYXRmb3JtO1xuICAgIHdpbmRvd3NOb01hZ2ljUm9vdDtcbiAgICByZWdleHA7XG4gICAgY29uc3RydWN0b3IocGF0dGVybiwgb3B0aW9ucyA9IHt9KSB7XG4gICAgICAgICgwLCBhc3NlcnRfdmFsaWRfcGF0dGVybl9qc18xLmFzc2VydFZhbGlkUGF0dGVybikocGF0dGVybik7XG4gICAgICAgIG9wdGlvbnMgPSBvcHRpb25zIHx8IHt9O1xuICAgICAgICB0aGlzLm9wdGlvbnMgPSBvcHRpb25zO1xuICAgICAgICB0aGlzLnBhdHRlcm4gPSBwYXR0ZXJuO1xuICAgICAgICB0aGlzLnBsYXRmb3JtID0gb3B0aW9ucy5wbGF0Zm9ybSB8fCBkZWZhdWx0UGxhdGZvcm07XG4gICAgICAgIHRoaXMuaXNXaW5kb3dzID0gdGhpcy5wbGF0Zm9ybSA9PT0gJ3dpbjMyJztcbiAgICAgICAgdGhpcy53aW5kb3dzUGF0aHNOb0VzY2FwZSA9XG4gICAgICAgICAgICAhIW9wdGlvbnMud2luZG93c1BhdGhzTm9Fc2NhcGUgfHwgb3B0aW9ucy5hbGxvd1dpbmRvd3NFc2NhcGUgPT09IGZhbHNlO1xuICAgICAgICBpZiAodGhpcy53aW5kb3dzUGF0aHNOb0VzY2FwZSkge1xuICAgICAgICAgICAgdGhpcy5wYXR0ZXJuID0gdGhpcy5wYXR0ZXJuLnJlcGxhY2UoL1xcXFwvZywgJy8nKTtcbiAgICAgICAgfVxuICAgICAgICB0aGlzLnByZXNlcnZlTXVsdGlwbGVTbGFzaGVzID0gISFvcHRpb25zLnByZXNlcnZlTXVsdGlwbGVTbGFzaGVzO1xuICAgICAgICB0aGlzLnJlZ2V4cCA9IG51bGw7XG4gICAgICAgIHRoaXMubmVnYXRlID0gZmFsc2U7XG4gICAgICAgIHRoaXMubm9uZWdhdGUgPSAhIW9wdGlvbnMubm9uZWdhdGU7XG4gICAgICAgIHRoaXMuY29tbWVudCA9IGZhbHNlO1xuICAgICAgICB0aGlzLmVtcHR5ID0gZmFsc2U7XG4gICAgICAgIHRoaXMucGFydGlhbCA9ICEhb3B0aW9ucy5wYXJ0aWFsO1xuICAgICAgICB0aGlzLm5vY2FzZSA9ICEhdGhpcy5vcHRpb25zLm5vY2FzZTtcbiAgICAgICAgdGhpcy53aW5kb3dzTm9NYWdpY1Jvb3QgPVxuICAgICAgICAgICAgb3B0aW9ucy53aW5kb3dzTm9NYWdpY1Jvb3QgIT09IHVuZGVmaW5lZFxuICAgICAgICAgICAgICAgID8gb3B0aW9ucy53aW5kb3dzTm9NYWdpY1Jvb3RcbiAgICAgICAgICAgICAgICA6ICEhKHRoaXMuaXNXaW5kb3dzICYmIHRoaXMubm9jYXNlKTtcbiAgICAgICAgdGhpcy5nbG9iU2V0ID0gW107XG4gICAgICAgIHRoaXMuZ2xvYlBhcnRzID0gW107XG4gICAgICAgIHRoaXMuc2V0ID0gW107XG4gICAgICAgIC8vIG1ha2UgdGhlIHNldCBvZiByZWdleHBzIGV0Yy5cbiAgICAgICAgdGhpcy5tYWtlKCk7XG4gICAgfVxuICAgIGhhc01hZ2ljKCkge1xuICAgICAgICBpZiAodGhpcy5vcHRpb25zLm1hZ2ljYWxCcmFjZXMgJiYgdGhpcy5zZXQubGVuZ3RoID4gMSkge1xuICAgICAgICAgICAgcmV0dXJuIHRydWU7XG4gICAgICAgIH1cbiAgICAgICAgZm9yIChjb25zdCBwYXR0ZXJuIG9mIHRoaXMuc2V0KSB7XG4gICAgICAgICAgICBmb3IgKGNvbnN0IHBhcnQgb2YgcGF0dGVybikge1xuICAgICAgICAgICAgICAgIGlmICh0eXBlb2YgcGFydCAhPT0gJ3N0cmluZycpXG4gICAgICAgICAgICAgICAgICAgIHJldHVybiB0cnVlO1xuICAgICAgICAgICAgfVxuICAgICAgICB9XG4gICAgICAgIHJldHVybiBmYWxzZTtcbiAgICB9XG4gICAgZGVidWcoLi4uXykgeyB9XG4gICAgbWFrZSgpIHtcbiAgICAgICAgY29uc3QgcGF0dGVybiA9IHRoaXMucGF0dGVybjtcbiAgICAgICAgY29uc3Qgb3B0aW9ucyA9IHRoaXMub3B0aW9ucztcbiAgICAgICAgLy8gZW1wdHkgcGF0dGVybnMgYW5kIGNvbW1lbnRzIG1hdGNoIG5vdGhpbmcuXG4gICAgICAgIGlmICghb3B0aW9ucy5ub2NvbW1lbnQgJiYgcGF0dGVybi5jaGFyQXQoMCkgPT09ICcjJykge1xuICAgICAgICAgICAgdGhpcy5jb21tZW50ID0gdHJ1ZTtcbiAgICAgICAgICAgIHJldHVybjtcbiAgICAgICAgfVxuICAgICAgICBpZiAoIXBhdHRlcm4pIHtcbiAgICAgICAgICAgIHRoaXMuZW1wdHkgPSB0cnVlO1xuICAgICAgICAgICAgcmV0dXJuO1xuICAgICAgICB9XG4gICAgICAgIC8vIHN0ZXAgMTogZmlndXJlIG91dCBuZWdhdGlvbiwgZXRjLlxuICAgICAgICB0aGlzLnBhcnNlTmVnYXRlKCk7XG4gICAgICAgIC8vIHN0ZXAgMjogZXhwYW5kIGJyYWNlc1xuICAgICAgICB0aGlzLmdsb2JTZXQgPSBbLi4ubmV3IFNldCh0aGlzLmJyYWNlRXhwYW5kKCkpXTtcbiAgICAgICAgaWYgKG9wdGlvbnMuZGVidWcpIHtcbiAgICAgICAgICAgIHRoaXMuZGVidWcgPSAoLi4uYXJncykgPT4gY29uc29sZS5lcnJvciguLi5hcmdzKTtcbiAgICAgICAgfVxuICAgICAgICB0aGlzLmRlYnVnKHRoaXMucGF0dGVybiwgdGhpcy5nbG9iU2V0KTtcbiAgICAgICAgLy8gc3RlcCAzOiBub3cgd2UgaGF2ZSBhIHNldCwgc28gdHVybiBlYWNoIG9uZSBpbnRvIGEgc2VyaWVzIG9mXG4gICAgICAgIC8vIHBhdGgtcG9ydGlvbiBtYXRjaGluZyBwYXR0ZXJucy5cbiAgICAgICAgLy8gVGhlc2Ugd2lsbCBiZSByZWdleHBzLCBleGNlcHQgaW4gdGhlIGNhc2Ugb2YgXCIqKlwiLCB3aGljaCBpc1xuICAgICAgICAvLyBzZXQgdG8gdGhlIEdMT0JTVEFSIG9iamVjdCBmb3IgZ2xvYnN0YXIgYmVoYXZpb3IsXG4gICAgICAgIC8vIGFuZCB3aWxsIG5vdCBjb250YWluIGFueSAvIGNoYXJhY3RlcnNcbiAgICAgICAgLy9cbiAgICAgICAgLy8gRmlyc3QsIHdlIHByZXByb2Nlc3MgdG8gbWFrZSB0aGUgZ2xvYiBwYXR0ZXJuIHNldHMgYSBiaXQgc2ltcGxlclxuICAgICAgICAvLyBhbmQgZGVkdXBlZC4gIFRoZXJlIGFyZSBzb21lIHBlcmYta2lsbGluZyBwYXR0ZXJucyB0aGF0IGNhbiBjYXVzZVxuICAgICAgICAvLyBwcm9ibGVtcyB3aXRoIGEgZ2xvYiB3YWxrLCBidXQgd2UgY2FuIHNpbXBsaWZ5IHRoZW0gZG93biBhIGJpdC5cbiAgICAgICAgY29uc3QgcmF3R2xvYlBhcnRzID0gdGhpcy5nbG9iU2V0Lm1hcChzID0+IHRoaXMuc2xhc2hTcGxpdChzKSk7XG4gICAgICAgIHRoaXMuZ2xvYlBhcnRzID0gdGhpcy5wcmVwcm9jZXNzKHJhd0dsb2JQYXJ0cyk7XG4gICAgICAgIHRoaXMuZGVidWcodGhpcy5wYXR0ZXJuLCB0aGlzLmdsb2JQYXJ0cyk7XG4gICAgICAgIC8vIGdsb2IgLS0+IHJlZ2V4cHNcbiAgICAgICAgbGV0IHNldCA9IHRoaXMuZ2xvYlBhcnRzLm1hcCgocywgXywgX18pID0+IHtcbiAgICAgICAgICAgIGlmICh0aGlzLmlzV2luZG93cyAmJiB0aGlzLndpbmRvd3NOb01hZ2ljUm9vdCkge1xuICAgICAgICAgICAgICAgIC8vIGNoZWNrIGlmIGl0J3MgYSBkcml2ZSBvciB1bmMgcGF0aC5cbiAgICAgICAgICAgICAgICBjb25zdCBpc1VOQyA9IHNbMF0gPT09ICcnICYmXG4gICAgICAgICAgICAgICAgICAgIHNbMV0gPT09ICcnICYmXG4gICAgICAgICAgICAgICAgICAgIChzWzJdID09PSAnPycgfHwgIWdsb2JNYWdpYy50ZXN0KHNbMl0pKSAmJlxuICAgICAgICAgICAgICAgICAgICAhZ2xvYk1hZ2ljLnRlc3Qoc1szXSk7XG4gICAgICAgICAgICAgICAgY29uc3QgaXNEcml2ZSA9IC9eW2Etel06L2kudGVzdChzWzBdKTtcbiAgICAgICAgICAgICAgICBpZiAoaXNVTkMpIHtcbiAgICAgICAgICAgICAgICAgICAgcmV0dXJuIFsuLi5zLnNsaWNlKDAsIDQpLCAuLi5zLnNsaWNlKDQpLm1hcChzcyA9PiB0aGlzLnBhcnNlKHNzKSldO1xuICAgICAgICAgICAgICAgIH1cbiAgICAgICAgICAgICAgICBlbHNlIGlmIChpc0RyaXZlKSB7XG4gICAgICAgICAgICAgICAgICAgIHJldHVybiBbc1swXSwgLi4ucy5zbGljZSgxKS5tYXAoc3MgPT4gdGhpcy5wYXJzZShzcykpXTtcbiAgICAgICAgICAgICAgICB9XG4gICAgICAgICAgICB9XG4gICAgICAgICAgICByZXR1cm4gcy5tYXAoc3MgPT4gdGhpcy5wYXJzZShzcykpO1xuICAgICAgICB9KTtcbiAgICAgICAgdGhpcy5kZWJ1Zyh0aGlzLnBhdHRlcm4sIHNldCk7XG4gICAgICAgIC8vIGZpbHRlciBvdXQgZXZlcnl0aGluZyB0aGF0IGRpZG4ndCBjb21waWxlIHByb3Blcmx5LlxuICAgICAgICB0aGlzLnNldCA9IHNldC5maWx0ZXIocyA9PiBzLmluZGV4T2YoZmFsc2UpID09PSAtMSk7XG4gICAgICAgIC8vIGRvIG5vdCB0cmVhdCB0aGUgPyBpbiBVTkMgcGF0aHMgYXMgbWFnaWNcbiAgICAgICAgaWYgKHRoaXMuaXNXaW5kb3dzKSB7XG4gICAgICAgICAgICBmb3IgKGxldCBpID0gMDsgaSA8IHRoaXMuc2V0Lmxlbmd0aDsgaSsrKSB7XG4gICAgICAgICAgICAgICAgY29uc3QgcCA9IHRoaXMuc2V0W2ldO1xuICAgICAgICAgICAgICAgIGlmIChwWzBdID09PSAnJyAmJlxuICAgICAgICAgICAgICAgICAgICBwWzFdID09PSAnJyAmJlxuICAgICAgICAgICAgICAgICAgICB0aGlzLmdsb2JQYXJ0c1tpXVsyXSA9PT0gJz8nICYmXG4gICAgICAgICAgICAgICAgICAgIHR5cGVvZiBwWzNdID09PSAnc3RyaW5nJyAmJlxuICAgICAgICAgICAgICAgICAgICAvXlthLXpdOiQvaS50ZXN0KHBbM10pKSB7XG4gICAgICAgICAgICAgICAgICAgIHBbMl0gPSAnPyc7XG4gICAgICAgICAgICAgICAgfVxuICAgICAgICAgICAgfVxuICAgICAgICB9XG4gICAgICAgIHRoaXMuZGVidWcodGhpcy5wYXR0ZXJuLCB0aGlzLnNldCk7XG4gICAgfVxuICAgIC8vIHZhcmlvdXMgdHJhbnNmb3JtcyB0byBlcXVpdmFsZW50IHBhdHRlcm4gc2V0cyB0aGF0IGFyZVxuICAgIC8vIGZhc3RlciB0byBwcm9jZXNzIGluIGEgZmlsZXN5c3RlbSB3YWxrLiAgVGhlIGdvYWwgaXMgdG9cbiAgICAvLyBlbGltaW5hdGUgd2hhdCB3ZSBjYW4sIGFuZCBwdXNoIGFsbCAqKiBwYXR0ZXJucyBhcyBmYXJcbiAgICAvLyB0byB0aGUgcmlnaHQgYXMgcG9zc2libGUsIGV2ZW4gaWYgaXQgaW5jcmVhc2VzIHRoZSBudW1iZXJcbiAgICAvLyBvZiBwYXR0ZXJucyB0aGF0IHdlIGhhdmUgdG8gcHJvY2Vzcy5cbiAgICBwcmVwcm9jZXNzKGdsb2JQYXJ0cykge1xuICAgICAgICAvLyBpZiB3ZSdyZSBub3QgaW4gZ2xvYnN0YXIgbW9kZSwgdGhlbiB0dXJuIGFsbCAqKiBpbnRvICpcbiAgICAgICAgaWYgKHRoaXMub3B0aW9ucy5ub2dsb2JzdGFyKSB7XG4gICAgICAgICAgICBmb3IgKGxldCBpID0gMDsgaSA8IGdsb2JQYXJ0cy5sZW5ndGg7IGkrKykge1xuICAgICAgICAgICAgICAgIGZvciAobGV0IGogPSAwOyBqIDwgZ2xvYlBhcnRzW2ldLmxlbmd0aDsgaisrKSB7XG4gICAgICAgICAgICAgICAgICAgIGlmIChnbG9iUGFydHNbaV1bal0gPT09ICcqKicpIHtcbiAgICAgICAgICAgICAgICAgICAgICAgIGdsb2JQYXJ0c1tpXVtqXSA9ICcqJztcbiAgICAgICAgICAgICAgICAgICAgfVxuICAgICAgICAgICAgICAgIH1cbiAgICAgICAgICAgIH1cbiAgICAgICAgfVxuICAgICAgICBjb25zdCB7IG9wdGltaXphdGlvbkxldmVsID0gMSB9ID0gdGhpcy5vcHRpb25zO1xuICAgICAgICBpZiAob3B0aW1pemF0aW9uTGV2ZWwgPj0gMikge1xuICAgICAgICAgICAgLy8gYWdncmVzc2l2ZSBvcHRpbWl6YXRpb24gZm9yIHRoZSBwdXJwb3NlIG9mIGZzIHdhbGtpbmdcbiAgICAgICAgICAgIGdsb2JQYXJ0cyA9IHRoaXMuZmlyc3RQaGFzZVByZVByb2Nlc3MoZ2xvYlBhcnRzKTtcbiAgICAgICAgICAgIGdsb2JQYXJ0cyA9IHRoaXMuc2Vjb25kUGhhc2VQcmVQcm9jZXNzKGdsb2JQYXJ0cyk7XG4gICAgICAgIH1cbiAgICAgICAgZWxzZSBpZiAob3B0aW1pemF0aW9uTGV2ZWwgPj0gMSkge1xuICAgICAgICAgICAgLy8ganVzdCBiYXNpYyBvcHRpbWl6YXRpb25zIHRvIHJlbW92ZSBzb21lIC4uIHBhcnRzXG4gICAgICAgICAgICBnbG9iUGFydHMgPSB0aGlzLmxldmVsT25lT3B0aW1pemUoZ2xvYlBhcnRzKTtcbiAgICAgICAgfVxuICAgICAgICBlbHNlIHtcbiAgICAgICAgICAgIC8vIGp1c3QgY29sbGFwc2UgbXVsdGlwbGUgKiogcG9ydGlvbnMgaW50byBvbmVcbiAgICAgICAgICAgIGdsb2JQYXJ0cyA9IHRoaXMuYWRqYXNjZW50R2xvYnN0YXJPcHRpbWl6ZShnbG9iUGFydHMpO1xuICAgICAgICB9XG4gICAgICAgIHJldHVybiBnbG9iUGFydHM7XG4gICAgfVxuICAgIC8vIGp1c3QgZ2V0IHJpZCBvZiBhZGphc2NlbnQgKiogcG9ydGlvbnNcbiAgICBhZGphc2NlbnRHbG9ic3Rhck9wdGltaXplKGdsb2JQYXJ0cykge1xuICAgICAgICByZXR1cm4gZ2xvYlBhcnRzLm1hcChwYXJ0cyA9PiB7XG4gICAgICAgICAgICBsZXQgZ3MgPSAtMTtcbiAgICAgICAgICAgIHdoaWxlICgtMSAhPT0gKGdzID0gcGFydHMuaW5kZXhPZignKionLCBncyArIDEpKSkge1xuICAgICAgICAgICAgICAgIGxldCBpID0gZ3M7XG4gICAgICAgICAgICAgICAgd2hpbGUgKHBhcnRzW2kgKyAxXSA9PT0gJyoqJykge1xuICAgICAgICAgICAgICAgICAgICBpKys7XG4gICAgICAgICAgICAgICAgfVxuICAgICAgICAgICAgICAgIGlmIChpICE9PSBncykge1xuICAgICAgICAgICAgICAgICAgICBwYXJ0cy5zcGxpY2UoZ3MsIGkgLSBncyk7XG4gICAgICAgICAgICAgICAgfVxuICAgICAgICAgICAgfVxuICAgICAgICAgICAgcmV0dXJuIHBhcnRzO1xuICAgICAgICB9KTtcbiAgICB9XG4gICAgLy8gZ2V0IHJpZCBvZiBhZGphc2NlbnQgKiogYW5kIHJlc29sdmUgLi4gcG9ydGlvbnNcbiAgICBsZXZlbE9uZU9wdGltaXplKGdsb2JQYXJ0cykge1xuICAgICAgICByZXR1cm4gZ2xvYlBhcnRzLm1hcChwYXJ0cyA9PiB7XG4gICAgICAgICAgICBwYXJ0cyA9IHBhcnRzLnJlZHVjZSgoc2V0LCBwYXJ0KSA9PiB7XG4gICAgICAgICAgICAgICAgY29uc3QgcHJldiA9IHNldFtzZXQubGVuZ3RoIC0gMV07XG4gICAgICAgICAgICAgICAgaWYgKHBhcnQgPT09ICcqKicgJiYgcHJldiA9PT0gJyoqJykge1xuICAgICAgICAgICAgICAgICAgICByZXR1cm4gc2V0O1xuICAgICAgICAgICAgICAgIH1cbiAgICAgICAgICAgICAgICBpZiAocGFydCA9PT0gJy4uJykge1xuICAgICAgICAgICAgICAgICAgICBpZiAocHJldiAmJiBwcmV2ICE9PSAnLi4nICYmIHByZXYgIT09ICcuJyAmJiBwcmV2ICE9PSAnKionKSB7XG4gICAgICAgICAgICAgICAgICAgICAgICBzZXQucG9wKCk7XG4gICAgICAgICAgICAgICAgICAgICAgICByZXR1cm4gc2V0O1xuICAgICAgICAgICAgICAgICAgICB9XG4gICAgICAgICAgICAgICAgfVxuICAgICAgICAgICAgICAgIHNldC5wdXNoKHBhcnQpO1xuICAgICAgICAgICAgICAgIHJldHVybiBzZXQ7XG4gICAgICAgICAgICB9LCBbXSk7XG4gICAgICAgICAgICByZXR1cm4gcGFydHMubGVuZ3RoID09PSAwID8gWycnXSA6IHBhcnRzO1xuICAgICAgICB9KTtcbiAgICB9XG4gICAgbGV2ZWxUd29GaWxlT3B0aW1pemUocGFydHMpIHtcbiAgICAgICAgaWYgKCFBcnJheS5pc0FycmF5KHBhcnRzKSkge1xuICAgICAgICAgICAgcGFydHMgPSB0aGlzLnNsYXNoU3BsaXQocGFydHMpO1xuICAgICAgICB9XG4gICAgICAgIGxldCBkaWRTb21ldGhpbmcgPSBmYWxzZTtcbiAgICAgICAgZG8ge1xuICAgICAgICAgICAgZGlkU29tZXRoaW5nID0gZmFsc2U7XG4gICAgICAgICAgICAvLyA8cHJlPi88ZT4vPHJlc3Q+IC0+IDxwcmU+LzxyZXN0PlxuICAgICAgICAgICAgaWYgKCF0aGlzLnByZXNlcnZlTXVsdGlwbGVTbGFzaGVzKSB7XG4gICAgICAgICAgICAgICAgZm9yIChsZXQgaSA9IDE7IGkgPCBwYXJ0cy5sZW5ndGggLSAxOyBpKyspIHtcbiAgICAgICAgICAgICAgICAgICAgY29uc3QgcCA9IHBhcnRzW2ldO1xuICAgICAgICAgICAgICAgICAgICAvLyBkb24ndCBzcXVlZXplIG91dCBVTkMgcGF0dGVybnNcbiAgICAgICAgICAgICAgICAgICAgaWYgKGkgPT09IDEgJiYgcCA9PT0gJycgJiYgcGFydHNbMF0gPT09ICcnKVxuICAgICAgICAgICAgICAgICAgICAgICAgY29udGludWU7XG4gICAgICAgICAgICAgICAgICAgIGlmIChwID09PSAnLicgfHwgcCA9PT0gJycpIHtcbiAgICAgICAgICAgICAgICAgICAgICAgIGRpZFNvbWV0aGluZyA9IHRydWU7XG4gICAgICAgICAgICAgICAgICAgICAgICBwYXJ0cy5zcGxpY2UoaSwgMSk7XG4gICAgICAgICAgICAgICAgICAgICAgICBpLS07XG4gICAgICAgICAgICAgICAgICAgIH1cbiAgICAgICAgICAgICAgICB9XG4gICAgICAgICAgICAgICAgaWYgKHBhcnRzWzBdID09PSAnLicgJiZcbiAgICAgICAgICAgICAgICAgICAgcGFydHMubGVuZ3RoID09PSAyICYmXG4gICAgICAgICAgICAgICAgICAgIChwYXJ0c1sxXSA9PT0gJy4nIHx8IHBhcnRzWzFdID09PSAnJykpIHtcbiAgICAgICAgICAgICAgICAgICAgZGlkU29tZXRoaW5nID0gdHJ1ZTtcbiAgICAgICAgICAgICAgICAgICAgcGFydHMucG9wKCk7XG4gICAgICAgICAgICAgICAgfVxuICAgICAgICAgICAgfVxuICAgICAgICAgICAgLy8gPHByZT4vPHA+Ly4uLzxyZXN0PiAtPiA8cHJlPi88cmVzdD5cbiAgICAgICAgICAgIGxldCBkZCA9IDA7XG4gICAgICAgICAgICB3aGlsZSAoLTEgIT09IChkZCA9IHBhcnRzLmluZGV4T2YoJy4uJywgZGQgKyAxKSkpIHtcbiAgICAgICAgICAgICAgICBjb25zdCBwID0gcGFydHNbZGQgLSAxXTtcbiAgICAgICAgICAgICAgICBpZiAocCAmJiBwICE9PSAnLicgJiYgcCAhPT0gJy4uJyAmJiBwICE9PSAnKionKSB7XG4gICAgICAgICAgICAgICAgICAgIGRpZFNvbWV0aGluZyA9IHRydWU7XG4gICAgICAgICAgICAgICAgICAgIHBhcnRzLnNwbGljZShkZCAtIDEsIDIpO1xuICAgICAgICAgICAgICAgICAgICBkZCAtPSAyO1xuICAgICAgICAgICAgICAgIH1cbiAgICAgICAgICAgIH1cbiAgICAgICAgfSB3aGlsZSAoZGlkU29tZXRoaW5nKTtcbiAgICAgICAgcmV0dXJuIHBhcnRzLmxlbmd0aCA9PT0gMCA/IFsnJ10gOiBwYXJ0cztcbiAgICB9XG4gICAgLy8gRmlyc3QgcGhhc2U6IHNpbmdsZS1wYXR0ZXJuIHByb2Nlc3NpbmdcbiAgICAvLyA8cHJlPiBpcyAxIG9yIG1vcmUgcG9ydGlvbnNcbiAgICAvLyA8cmVzdD4gaXMgMSBvciBtb3JlIHBvcnRpb25zXG4gICAgLy8gPHA+IGlzIGFueSBwb3J0aW9uIG90aGVyIHRoYW4gLiwgLi4sICcnLCBvciAqKlxuICAgIC8vIDxlPiBpcyAuIG9yICcnXG4gICAgLy9cbiAgICAvLyAqKi8uLiBpcyAqYnJ1dGFsKiBmb3IgZmlsZXN5c3RlbSB3YWxraW5nIHBlcmZvcm1hbmNlLCBiZWNhdXNlXG4gICAgLy8gaXQgZWZmZWN0aXZlbHkgcmVzZXRzIHRoZSByZWN1cnNpdmUgd2FsayBlYWNoIHRpbWUgaXQgb2NjdXJzLFxuICAgIC8vIGFuZCAqKiBjYW5ub3QgYmUgcmVkdWNlZCBvdXQgYnkgYSAuLiBwYXR0ZXJuIHBhcnQgbGlrZSBhIHJlZ2V4cFxuICAgIC8vIG9yIG1vc3Qgc3RyaW5ncyAob3RoZXIgdGhhbiAuLiwgLiwgYW5kICcnKSBjYW4gYmUuXG4gICAgLy9cbiAgICAvLyA8cHJlPi8qKi8uLi88cD4vPHA+LzxyZXN0PiAtPiB7PHByZT4vLi4vPHA+LzxwPi88cmVzdD4sPHByZT4vKiovPHA+LzxwPi88cmVzdD59XG4gICAgLy8gPHByZT4vPGU+LzxyZXN0PiAtPiA8cHJlPi88cmVzdD5cbiAgICAvLyA8cHJlPi88cD4vLi4vPHJlc3Q+IC0+IDxwcmU+LzxyZXN0PlxuICAgIC8vICoqLyoqLzxyZXN0PiAtPiAqKi88cmVzdD5cbiAgICAvL1xuICAgIC8vICoqLyovPHJlc3Q+IC0+ICovKiovPHJlc3Q+IDw9PSBub3QgdmFsaWQgYmVjYXVzZSAqKiBkb2Vzbid0IGZvbGxvd1xuICAgIC8vIHRoaXMgV09VTEQgYmUgYWxsb3dlZCBpZiAqKiBkaWQgZm9sbG93IHN5bWxpbmtzLCBvciAqIGRpZG4ndFxuICAgIGZpcnN0UGhhc2VQcmVQcm9jZXNzKGdsb2JQYXJ0cykge1xuICAgICAgICBsZXQgZGlkU29tZXRoaW5nID0gZmFsc2U7XG4gICAgICAgIGRvIHtcbiAgICAgICAgICAgIGRpZFNvbWV0aGluZyA9IGZhbHNlO1xuICAgICAgICAgICAgLy8gPHByZT4vKiovLi4vPHA+LzxwPi88cmVzdD4gLT4gezxwcmU+Ly4uLzxwPi88cD4vPHJlc3Q+LDxwcmU+LyoqLzxwPi88cD4vPHJlc3Q+fVxuICAgICAgICAgICAgZm9yIChsZXQgcGFydHMgb2YgZ2xvYlBhcnRzKSB7XG4gICAgICAgICAgICAgICAgbGV0IGdzID0gLTE7XG4gICAgICAgICAgICAgICAgd2hpbGUgKC0xICE9PSAoZ3MgPSBwYXJ0cy5pbmRleE9mKCcqKicsIGdzICsgMSkpKSB7XG4gICAgICAgICAgICAgICAgICAgIGxldCBnc3MgPSBncztcbiAgICAgICAgICAgICAgICAgICAgd2hpbGUgKHBhcnRzW2dzcyArIDFdID09PSAnKionKSB7XG4gICAgICAgICAgICAgICAgICAgICAgICAvLyA8cHJlPi8qKi8qKi88cmVzdD4gLT4gPHByZT4vKiovPHJlc3Q+XG4gICAgICAgICAgICAgICAgICAgICAgICBnc3MrKztcbiAgICAgICAgICAgICAgICAgICAgfVxuICAgICAgICAgICAgICAgICAgICAvLyBlZywgaWYgZ3MgaXMgMiBhbmQgZ3NzIGlzIDQsIHRoYXQgbWVhbnMgd2UgaGF2ZSAzICoqXG4gICAgICAgICAgICAgICAgICAgIC8vIHBhcnRzLCBhbmQgY2FuIHJlbW92ZSAyIG9mIHRoZW0uXG4gICAgICAgICAgICAgICAgICAgIGlmIChnc3MgPiBncykge1xuICAgICAgICAgICAgICAgICAgICAgICAgcGFydHMuc3BsaWNlKGdzICsgMSwgZ3NzIC0gZ3MpO1xuICAgICAgICAgICAgICAgICAgICB9XG4gICAgICAgICAgICAgICAgICAgIGxldCBuZXh0ID0gcGFydHNbZ3MgKyAxXTtcbiAgICAgICAgICAgICAgICAgICAgY29uc3QgcCA9IHBhcnRzW2dzICsgMl07XG4gICAgICAgICAgICAgICAgICAgIGNvbnN0IHAyID0gcGFydHNbZ3MgKyAzXTtcbiAgICAgICAgICAgICAgICAgICAgaWYgKG5leHQgIT09ICcuLicpXG4gICAgICAgICAgICAgICAgICAgICAgICBjb250aW51ZTtcbiAgICAgICAgICAgICAgICAgICAgaWYgKCFwIHx8XG4gICAgICAgICAgICAgICAgICAgICAgICBwID09PSAnLicgfHxcbiAgICAgICAgICAgICAgICAgICAgICAgIHAgPT09ICcuLicgfHxcbiAgICAgICAgICAgICAgICAgICAgICAgICFwMiB8fFxuICAgICAgICAgICAgICAgICAgICAgICAgcDIgPT09ICcuJyB8fFxuICAgICAgICAgICAgICAgICAgICAgICAgcDIgPT09ICcuLicpIHtcbiAgICAgICAgICAgICAgICAgICAgICAgIGNvbnRpbnVlO1xuICAgICAgICAgICAgICAgICAgICB9XG4gICAgICAgICAgICAgICAgICAgIGRpZFNvbWV0aGluZyA9IHRydWU7XG4gICAgICAgICAgICAgICAgICAgIC8vIGVkaXQgcGFydHMgaW4gcGxhY2UsIGFuZCBwdXNoIHRoZSBuZXcgb25lXG4gICAgICAgICAgICAgICAgICAgIHBhcnRzLnNwbGljZShncywgMSk7XG4gICAgICAgICAgICAgICAgICAgIGNvbnN0IG90aGVyID0gcGFydHMuc2xpY2UoMCk7XG4gICAgICAgICAgICAgICAgICAgIG90aGVyW2dzXSA9ICcqKic7XG4gICAgICAgICAgICAgICAgICAgIGdsb2JQYXJ0cy5wdXNoKG90aGVyKTtcbiAgICAgICAgICAgICAgICAgICAgZ3MtLTtcbiAgICAgICAgICAgICAgICB9XG4gICAgICAgICAgICAgICAgLy8gPHByZT4vPGU+LzxyZXN0PiAtPiA8cHJlPi88cmVzdD5cbiAgICAgICAgICAgICAgICBpZiAoIXRoaXMucHJlc2VydmVNdWx0aXBsZVNsYXNoZXMpIHtcbiAgICAgICAgICAgICAgICAgICAgZm9yIChsZXQgaSA9IDE7IGkgPCBwYXJ0cy5sZW5ndGggLSAxOyBpKyspIHtcbiAgICAgICAgICAgICAgICAgICAgICAgIGNvbnN0IHAgPSBwYXJ0c1tpXTtcbiAgICAgICAgICAgICAgICAgICAgICAgIC8vIGRvbid0IHNxdWVlemUgb3V0IFVOQyBwYXR0ZXJuc1xuICAgICAgICAgICAgICAgICAgICAgICAgaWYgKGkgPT09IDEgJiYgcCA9PT0gJycgJiYgcGFydHNbMF0gPT09ICcnKVxuICAgICAgICAgICAgICAgICAgICAgICAgICAgIGNvbnRpbnVlO1xuICAgICAgICAgICAgICAgICAgICAgICAgaWYgKHAgPT09ICcuJyB8fCBwID09PSAnJykge1xuICAgICAgICAgICAgICAgICAgICAgICAgICAgIGRpZFNvbWV0aGluZyA9IHRydWU7XG4gICAgICAgICAgICAgICAgICAgICAgICAgICAgcGFydHMuc3BsaWNlKGksIDEpO1xuICAgICAgICAgICAgICAgICAgICAgICAgICAgIGktLTtcbiAgICAgICAgICAgICAgICAgICAgICAgIH1cbiAgICAgICAgICAgICAgICAgICAgfVxuICAgICAgICAgICAgICAgICAgICBpZiAocGFydHNbMF0gPT09ICcuJyAmJlxuICAgICAgICAgICAgICAgICAgICAgICAgcGFydHMubGVuZ3RoID09PSAyICYmXG4gICAgICAgICAgICAgICAgICAgICAgICAocGFydHNbMV0gPT09ICcuJyB8fCBwYXJ0c1sxXSA9PT0gJycpKSB7XG4gICAgICAgICAgICAgICAgICAgICAgICBkaWRTb21ldGhpbmcgPSB0cnVlO1xuICAgICAgICAgICAgICAgICAgICAgICAgcGFydHMucG9wKCk7XG4gICAgICAgICAgICAgICAgICAgIH1cbiAgICAgICAgICAgICAgICB9XG4gICAgICAgICAgICAgICAgLy8gPHByZT4vPHA+Ly4uLzxyZXN0PiAtPiA8cHJlPi88cmVzdD5cbiAgICAgICAgICAgICAgICBsZXQgZGQgPSAwO1xuICAgICAgICAgICAgICAgIHdoaWxlICgtMSAhPT0gKGRkID0gcGFydHMuaW5kZXhPZignLi4nLCBkZCArIDEpKSkge1xuICAgICAgICAgICAgICAgICAgICBjb25zdCBwID0gcGFydHNbZGQgLSAxXTtcbiAgICAgICAgICAgICAgICAgICAgaWYgKHAgJiYgcCAhPT0gJy4nICYmIHAgIT09ICcuLicgJiYgcCAhPT0gJyoqJykge1xuICAgICAgICAgICAgICAgICAgICAgICAgZGlkU29tZXRoaW5nID0gdHJ1ZTtcbiAgICAgICAgICAgICAgICAgICAgICAgIGNvbnN0IG5lZWREb3QgPSBkZCA9PT0gMSAmJiBwYXJ0c1tkZCArIDFdID09PSAnKionO1xuICAgICAgICAgICAgICAgICAgICAgICAgY29uc3Qgc3BsaW4gPSBuZWVkRG90ID8gWycuJ10gOiBbXTtcbiAgICAgICAgICAgICAgICAgICAgICAgIHBhcnRzLnNwbGljZShkZCAtIDEsIDIsIC4uLnNwbGluKTtcbiAgICAgICAgICAgICAgICAgICAgICAgIGlmIChwYXJ0cy5sZW5ndGggPT09IDApXG4gICAgICAgICAgICAgICAgICAgICAgICAgICAgcGFydHMucHVzaCgnJyk7XG4gICAgICAgICAgICAgICAgICAgICAgICBkZCAtPSAyO1xuICAgICAgICAgICAgICAgICAgICB9XG4gICAgICAgICAgICAgICAgfVxuICAgICAgICAgICAgfVxuICAgICAgICB9IHdoaWxlIChkaWRTb21ldGhpbmcpO1xuICAgICAgICByZXR1cm4gZ2xvYlBhcnRzO1xuICAgIH1cbiAgICAvLyBzZWNvbmQgcGhhc2U6IG11bHRpLXBhdHRlcm4gZGVkdXBlc1xuICAgIC8vIHs8cHJlPi8qLzxyZXN0Piw8cHJlPi88cD4vPHJlc3Q+fSAtPiA8cHJlPi8qLzxyZXN0PlxuICAgIC8vIHs8cHJlPi88cmVzdD4sPHByZT4vPHJlc3Q+fSAtPiA8cHJlPi88cmVzdD5cbiAgICAvLyB7PHByZT4vKiovPHJlc3Q+LDxwcmU+LzxyZXN0Pn0gLT4gPHByZT4vKiovPHJlc3Q+XG4gICAgLy9cbiAgICAvLyB7PHByZT4vKiovPHJlc3Q+LDxwcmU+LyoqLzxwPi88cmVzdD59IC0+IDxwcmU+LyoqLzxyZXN0PlxuICAgIC8vIF4tLSBub3QgdmFsaWQgYmVjYXVzZSAqKiBkb2Vucyd0IGZvbGxvdyBzeW1saW5rc1xuICAgIHNlY29uZFBoYXNlUHJlUHJvY2VzcyhnbG9iUGFydHMpIHtcbiAgICAgICAgZm9yIChsZXQgaSA9IDA7IGkgPCBnbG9iUGFydHMubGVuZ3RoIC0gMTsgaSsrKSB7XG4gICAgICAgICAgICBmb3IgKGxldCBqID0gaSArIDE7IGogPCBnbG9iUGFydHMubGVuZ3RoOyBqKyspIHtcbiAgICAgICAgICAgICAgICBjb25zdCBtYXRjaGVkID0gdGhpcy5wYXJ0c01hdGNoKGdsb2JQYXJ0c1tpXSwgZ2xvYlBhcnRzW2pdLCAhdGhpcy5wcmVzZXJ2ZU11bHRpcGxlU2xhc2hlcyk7XG4gICAgICAgICAgICAgICAgaWYgKG1hdGNoZWQpIHtcbiAgICAgICAgICAgICAgICAgICAgZ2xvYlBhcnRzW2ldID0gW107XG4gICAgICAgICAgICAgICAgICAgIGdsb2JQYXJ0c1tqXSA9IG1hdGNoZWQ7XG4gICAgICAgICAgICAgICAgICAgIGJyZWFrO1xuICAgICAgICAgICAgICAgIH1cbiAgICAgICAgICAgIH1cbiAgICAgICAgfVxuICAgICAgICByZXR1cm4gZ2xvYlBhcnRzLmZpbHRlcihncyA9PiBncy5sZW5ndGgpO1xuICAgIH1cbiAgICBwYXJ0c01hdGNoKGEsIGIsIGVtcHR5R1NNYXRjaCA9IGZhbHNlKSB7XG4gICAgICAgIGxldCBhaSA9IDA7XG4gICAgICAgIGxldCBiaSA9IDA7XG4gICAgICAgIGxldCByZXN1bHQgPSBbXTtcbiAgICAgICAgbGV0IHdoaWNoID0gJyc7XG4gICAgICAgIHdoaWxlIChhaSA8IGEubGVuZ3RoICYmIGJpIDwgYi5sZW5ndGgpIHtcbiAgICAgICAgICAgIGlmIChhW2FpXSA9PT0gYltiaV0pIHtcbiAgICAgICAgICAgICAgICByZXN1bHQucHVzaCh3aGljaCA9PT0gJ2InID8gYltiaV0gOiBhW2FpXSk7XG4gICAgICAgICAgICAgICAgYWkrKztcbiAgICAgICAgICAgICAgICBiaSsrO1xuICAgICAgICAgICAgfVxuICAgICAgICAgICAgZWxzZSBpZiAoZW1wdHlHU01hdGNoICYmIGFbYWldID09PSAnKionICYmIGJbYmldID09PSBhW2FpICsgMV0pIHtcbiAgICAgICAgICAgICAgICByZXN1bHQucHVzaChhW2FpXSk7XG4gICAgICAgICAgICAgICAgYWkrKztcbiAgICAgICAgICAgIH1cbiAgICAgICAgICAgIGVsc2UgaWYgKGVtcHR5R1NNYXRjaCAmJiBiW2JpXSA9PT0gJyoqJyAmJiBhW2FpXSA9PT0gYltiaSArIDFdKSB7XG4gICAgICAgICAgICAgICAgcmVzdWx0LnB1c2goYltiaV0pO1xuICAgICAgICAgICAgICAgIGJpKys7XG4gICAgICAgICAgICB9XG4gICAgICAgICAgICBlbHNlIGlmIChhW2FpXSA9PT0gJyonICYmXG4gICAgICAgICAgICAgICAgYltiaV0gJiZcbiAgICAgICAgICAgICAgICAodGhpcy5vcHRpb25zLmRvdCB8fCAhYltiaV0uc3RhcnRzV2l0aCgnLicpKSAmJlxuICAgICAgICAgICAgICAgIGJbYmldICE9PSAnKionKSB7XG4gICAgICAgICAgICAgICAgaWYgKHdoaWNoID09PSAnYicpXG4gICAgICAgICAgICAgICAgICAgIHJldHVybiBmYWxzZTtcbiAgICAgICAgICAgICAgICB3aGljaCA9ICdhJztcbiAgICAgICAgICAgICAgICByZXN1bHQucHVzaChhW2FpXSk7XG4gICAgICAgICAgICAgICAgYWkrKztcbiAgICAgICAgICAgICAgICBiaSsrO1xuICAgICAgICAgICAgfVxuICAgICAgICAgICAgZWxzZSBpZiAoYltiaV0gPT09ICcqJyAmJlxuICAgICAgICAgICAgICAgIGFbYWldICYmXG4gICAgICAgICAgICAgICAgKHRoaXMub3B0aW9ucy5kb3QgfHwgIWFbYWldLnN0YXJ0c1dpdGgoJy4nKSkgJiZcbiAgICAgICAgICAgICAgICBhW2FpXSAhPT0gJyoqJykge1xuICAgICAgICAgICAgICAgIGlmICh3aGljaCA9PT0gJ2EnKVxuICAgICAgICAgICAgICAgICAgICByZXR1cm4gZmFsc2U7XG4gICAgICAgICAgICAgICAgd2hpY2ggPSAnYic7XG4gICAgICAgICAgICAgICAgcmVzdWx0LnB1c2goYltiaV0pO1xuICAgICAgICAgICAgICAgIGFpKys7XG4gICAgICAgICAgICAgICAgYmkrKztcbiAgICAgICAgICAgIH1cbiAgICAgICAgICAgIGVsc2Uge1xuICAgICAgICAgICAgICAgIHJldHVybiBmYWxzZTtcbiAgICAgICAgICAgIH1cbiAgICAgICAgfVxuICAgICAgICAvLyBpZiB3ZSBmYWxsIG91dCBvZiB0aGUgbG9vcCwgaXQgbWVhbnMgdGhleSB0d28gYXJlIGlkZW50aWNhbFxuICAgICAgICAvLyBhcyBsb25nIGFzIHRoZWlyIGxlbmd0aHMgbWF0Y2hcbiAgICAgICAgcmV0dXJuIGEubGVuZ3RoID09PSBiLmxlbmd0aCAmJiByZXN1bHQ7XG4gICAgfVxuICAgIHBhcnNlTmVnYXRlKCkge1xuICAgICAgICBpZiAodGhpcy5ub25lZ2F0ZSlcbiAgICAgICAgICAgIHJldHVybjtcbiAgICAgICAgY29uc3QgcGF0dGVybiA9IHRoaXMucGF0dGVybjtcbiAgICAgICAgbGV0IG5lZ2F0ZSA9IGZhbHNlO1xuICAgICAgICBsZXQgbmVnYXRlT2Zmc2V0ID0gMDtcbiAgICAgICAgZm9yIChsZXQgaSA9IDA7IGkgPCBwYXR0ZXJuLmxlbmd0aCAmJiBwYXR0ZXJuLmNoYXJBdChpKSA9PT0gJyEnOyBpKyspIHtcbiAgICAgICAgICAgIG5lZ2F0ZSA9ICFuZWdhdGU7XG4gICAgICAgICAgICBuZWdhdGVPZmZzZXQrKztcbiAgICAgICAgfVxuICAgICAgICBpZiAobmVnYXRlT2Zmc2V0KVxuICAgICAgICAgICAgdGhpcy5wYXR0ZXJuID0gcGF0dGVybi5zbGljZShuZWdhdGVPZmZzZXQpO1xuICAgICAgICB0aGlzLm5lZ2F0ZSA9IG5lZ2F0ZTtcbiAgICB9XG4gICAgLy8gc2V0IHBhcnRpYWwgdG8gdHJ1ZSB0byB0ZXN0IGlmLCBmb3IgZXhhbXBsZSxcbiAgICAvLyBcIi9hL2JcIiBtYXRjaGVzIHRoZSBzdGFydCBvZiBcIi8qL2IvKi9kXCJcbiAgICAvLyBQYXJ0aWFsIG1lYW5zLCBpZiB5b3UgcnVuIG91dCBvZiBmaWxlIGJlZm9yZSB5b3UgcnVuXG4gICAgLy8gb3V0IG9mIHBhdHRlcm4sIHRoZW4gdGhhdCdzIGZpbmUsIGFzIGxvbmcgYXMgYWxsXG4gICAgLy8gdGhlIHBhcnRzIG1hdGNoLlxuICAgIG1hdGNoT25lKGZpbGUsIHBhdHRlcm4sIHBhcnRpYWwgPSBmYWxzZSkge1xuICAgICAgICBjb25zdCBvcHRpb25zID0gdGhpcy5vcHRpb25zO1xuICAgICAgICAvLyBVTkMgcGF0aHMgbGlrZSAvLz8vWDovLi4uIGNhbiBtYXRjaCBYOi8uLi4gYW5kIHZpY2UgdmVyc2FcbiAgICAgICAgLy8gRHJpdmUgbGV0dGVycyBpbiBhYnNvbHV0ZSBkcml2ZSBvciB1bmMgcGF0aHMgYXJlIGFsd2F5cyBjb21wYXJlZFxuICAgICAgICAvLyBjYXNlLWluc2Vuc2l0aXZlbHkuXG4gICAgICAgIGlmICh0aGlzLmlzV2luZG93cykge1xuICAgICAgICAgICAgY29uc3QgZmlsZURyaXZlID0gdHlwZW9mIGZpbGVbMF0gPT09ICdzdHJpbmcnICYmIC9eW2Etel06JC9pLnRlc3QoZmlsZVswXSk7XG4gICAgICAgICAgICBjb25zdCBmaWxlVU5DID0gIWZpbGVEcml2ZSAmJlxuICAgICAgICAgICAgICAgIGZpbGVbMF0gPT09ICcnICYmXG4gICAgICAgICAgICAgICAgZmlsZVsxXSA9PT0gJycgJiZcbiAgICAgICAgICAgICAgICBmaWxlWzJdID09PSAnPycgJiZcbiAgICAgICAgICAgICAgICAvXlthLXpdOiQvaS50ZXN0KGZpbGVbM10pO1xuICAgICAgICAgICAgY29uc3QgcGF0dGVybkRyaXZlID0gdHlwZW9mIHBhdHRlcm5bMF0gPT09ICdzdHJpbmcnICYmIC9eW2Etel06JC9pLnRlc3QocGF0dGVyblswXSk7XG4gICAgICAgICAgICBjb25zdCBwYXR0ZXJuVU5DID0gIXBhdHRlcm5Ecml2ZSAmJlxuICAgICAgICAgICAgICAgIHBhdHRlcm5bMF0gPT09ICcnICYmXG4gICAgICAgICAgICAgICAgcGF0dGVyblsxXSA9PT0gJycgJiZcbiAgICAgICAgICAgICAgICBwYXR0ZXJuWzJdID09PSAnPycgJiZcbiAgICAgICAgICAgICAgICB0eXBlb2YgcGF0dGVyblszXSA9PT0gJ3N0cmluZycgJiZcbiAgICAgICAgICAgICAgICAvXlthLXpdOiQvaS50ZXN0KHBhdHRlcm5bM10pO1xuICAgICAgICAgICAgY29uc3QgZmRpID0gZmlsZVVOQyA/IDMgOiBmaWxlRHJpdmUgPyAwIDogdW5kZWZpbmVkO1xuICAgICAgICAgICAgY29uc3QgcGRpID0gcGF0dGVyblVOQyA/IDMgOiBwYXR0ZXJuRHJpdmUgPyAwIDogdW5kZWZpbmVkO1xuICAgICAgICAgICAgaWYgKHR5cGVvZiBmZGkgPT09ICdudW1iZXInICYmIHR5cGVvZiBwZGkgPT09ICdudW1iZXInKSB7XG4gICAgICAgICAgICAgICAgY29uc3QgW2ZkLCBwZF0gPSBbZmlsZVtmZGldLCBwYXR0ZXJuW3BkaV1dO1xuICAgICAgICAgICAgICAgIGlmIChmZC50b0xvd2VyQ2FzZSgpID09PSBwZC50b0xvd2VyQ2FzZSgpKSB7XG4gICAgICAgICAgICAgICAgICAgIHBhdHRlcm5bcGRpXSA9IGZkO1xuICAgICAgICAgICAgICAgICAgICBpZiAocGRpID4gZmRpKSB7XG4gICAgICAgICAgICAgICAgICAgICAgICBwYXR0ZXJuID0gcGF0dGVybi5zbGljZShwZGkpO1xuICAgICAgICAgICAgICAgICAgICB9XG4gICAgICAgICAgICAgICAgICAgIGVsc2UgaWYgKGZkaSA+IHBkaSkge1xuICAgICAgICAgICAgICAgICAgICAgICAgZmlsZSA9IGZpbGUuc2xpY2UoZmRpKTtcbiAgICAgICAgICAgICAgICAgICAgfVxuICAgICAgICAgICAgICAgIH1cbiAgICAgICAgICAgIH1cbiAgICAgICAgfVxuICAgICAgICAvLyByZXNvbHZlIGFuZCByZWR1Y2UgLiBhbmQgLi4gcG9ydGlvbnMgaW4gdGhlIGZpbGUgYXMgd2VsbC5cbiAgICAgICAgLy8gZG9udCcgbmVlZCB0byBkbyB0aGUgc2Vjb25kIHBoYXNlLCBiZWNhdXNlIGl0J3Mgb25seSBvbmUgc3RyaW5nW11cbiAgICAgICAgY29uc3QgeyBvcHRpbWl6YXRpb25MZXZlbCA9IDEgfSA9IHRoaXMub3B0aW9ucztcbiAgICAgICAgaWYgKG9wdGltaXphdGlvbkxldmVsID49IDIpIHtcbiAgICAgICAgICAgIGZpbGUgPSB0aGlzLmxldmVsVHdvRmlsZU9wdGltaXplKGZpbGUpO1xuICAgICAgICB9XG4gICAgICAgIHRoaXMuZGVidWcoJ21hdGNoT25lJywgdGhpcywgeyBmaWxlLCBwYXR0ZXJuIH0pO1xuICAgICAgICB0aGlzLmRlYnVnKCdtYXRjaE9uZScsIGZpbGUubGVuZ3RoLCBwYXR0ZXJuLmxlbmd0aCk7XG4gICAgICAgIGZvciAodmFyIGZpID0gMCwgcGkgPSAwLCBmbCA9IGZpbGUubGVuZ3RoLCBwbCA9IHBhdHRlcm4ubGVuZ3RoOyBmaSA8IGZsICYmIHBpIDwgcGw7IGZpKyssIHBpKyspIHtcbiAgICAgICAgICAgIHRoaXMuZGVidWcoJ21hdGNoT25lIGxvb3AnKTtcbiAgICAgICAgICAgIHZhciBwID0gcGF0dGVybltwaV07XG4gICAgICAgICAgICB2YXIgZiA9IGZpbGVbZmldO1xuICAgICAgICAgICAgdGhpcy5kZWJ1ZyhwYXR0ZXJuLCBwLCBmKTtcbiAgICAgICAgICAgIC8vIHNob3VsZCBiZSBpbXBvc3NpYmxlLlxuICAgICAgICAgICAgLy8gc29tZSBpbnZhbGlkIHJlZ2V4cCBzdHVmZiBpbiB0aGUgc2V0LlxuICAgICAgICAgICAgLyogYzggaWdub3JlIHN0YXJ0ICovXG4gICAgICAgICAgICBpZiAocCA9PT0gZmFsc2UpIHtcbiAgICAgICAgICAgICAgICByZXR1cm4gZmFsc2U7XG4gICAgICAgICAgICB9XG4gICAgICAgICAgICAvKiBjOCBpZ25vcmUgc3RvcCAqL1xuICAgICAgICAgICAgaWYgKHAgPT09IGV4cG9ydHMuR0xPQlNUQVIpIHtcbiAgICAgICAgICAgICAgICB0aGlzLmRlYnVnKCdHTE9CU1RBUicsIFtwYXR0ZXJuLCBwLCBmXSk7XG4gICAgICAgICAgICAgICAgLy8gXCIqKlwiXG4gICAgICAgICAgICAgICAgLy8gYS8qKi9iLyoqL2Mgd291bGQgbWF0Y2ggdGhlIGZvbGxvd2luZzpcbiAgICAgICAgICAgICAgICAvLyBhL2IveC95L3ovY1xuICAgICAgICAgICAgICAgIC8vIGEveC95L3ovYi9jXG4gICAgICAgICAgICAgICAgLy8gYS9iL3gvYi94L2NcbiAgICAgICAgICAgICAgICAvLyBhL2IvY1xuICAgICAgICAgICAgICAgIC8vIFRvIGRvIHRoaXMsIHRha2UgdGhlIHJlc3Qgb2YgdGhlIHBhdHRlcm4gYWZ0ZXJcbiAgICAgICAgICAgICAgICAvLyB0aGUgKiosIGFuZCBzZWUgaWYgaXQgd291bGQgbWF0Y2ggdGhlIGZpbGUgcmVtYWluZGVyLlxuICAgICAgICAgICAgICAgIC8vIElmIHNvLCByZXR1cm4gc3VjY2Vzcy5cbiAgICAgICAgICAgICAgICAvLyBJZiBub3QsIHRoZSAqKiBcInN3YWxsb3dzXCIgYSBzZWdtZW50LCBhbmQgdHJ5IGFnYWluLlxuICAgICAgICAgICAgICAgIC8vIFRoaXMgaXMgcmVjdXJzaXZlbHkgYXdmdWwuXG4gICAgICAgICAgICAgICAgLy9cbiAgICAgICAgICAgICAgICAvLyBhLyoqL2IvKiovYyBtYXRjaGluZyBhL2IveC95L3ovY1xuICAgICAgICAgICAgICAgIC8vIC0gYSBtYXRjaGVzIGFcbiAgICAgICAgICAgICAgICAvLyAtIGRvdWJsZXN0YXJcbiAgICAgICAgICAgICAgICAvLyAgIC0gbWF0Y2hPbmUoYi94L3kvei9jLCBiLyoqL2MpXG4gICAgICAgICAgICAgICAgLy8gICAgIC0gYiBtYXRjaGVzIGJcbiAgICAgICAgICAgICAgICAvLyAgICAgLSBkb3VibGVzdGFyXG4gICAgICAgICAgICAgICAgLy8gICAgICAgLSBtYXRjaE9uZSh4L3kvei9jLCBjKSAtPiBub1xuICAgICAgICAgICAgICAgIC8vICAgICAgIC0gbWF0Y2hPbmUoeS96L2MsIGMpIC0+IG5vXG4gICAgICAgICAgICAgICAgLy8gICAgICAgLSBtYXRjaE9uZSh6L2MsIGMpIC0+IG5vXG4gICAgICAgICAgICAgICAgLy8gICAgICAgLSBtYXRjaE9uZShjLCBjKSB5ZXMsIGhpdFxuICAgICAgICAgICAgICAgIHZhciBmciA9IGZpO1xuICAgICAgICAgICAgICAgIHZhciBwciA9IHBpICsgMTtcbiAgICAgICAgICAgICAgICBpZiAocHIgPT09IHBsKSB7XG4gICAgICAgICAgICAgICAgICAgIHRoaXMuZGVidWcoJyoqIGF0IHRoZSBlbmQnKTtcbiAgICAgICAgICAgICAgICAgICAgLy8gYSAqKiBhdCB0aGUgZW5kIHdpbGwganVzdCBzd2FsbG93IHRoZSByZXN0LlxuICAgICAgICAgICAgICAgICAgICAvLyBXZSBoYXZlIGZvdW5kIGEgbWF0Y2guXG4gICAgICAgICAgICAgICAgICAgIC8vIGhvd2V2ZXIsIGl0IHdpbGwgbm90IHN3YWxsb3cgLy54LCB1bmxlc3NcbiAgICAgICAgICAgICAgICAgICAgLy8gb3B0aW9ucy5kb3QgaXMgc2V0LlxuICAgICAgICAgICAgICAgICAgICAvLyAuIGFuZCAuLiBhcmUgKm5ldmVyKiBtYXRjaGVkIGJ5ICoqLCBmb3IgZXhwbG9zaXZlbHlcbiAgICAgICAgICAgICAgICAgICAgLy8gZXhwb25lbnRpYWwgcmVhc29ucy5cbiAgICAgICAgICAgICAgICAgICAgZm9yICg7IGZpIDwgZmw7IGZpKyspIHtcbiAgICAgICAgICAgICAgICAgICAgICAgIGlmIChmaWxlW2ZpXSA9PT0gJy4nIHx8XG4gICAgICAgICAgICAgICAgICAgICAgICAgICAgZmlsZVtmaV0gPT09ICcuLicgfHxcbiAgICAgICAgICAgICAgICAgICAgICAgICAgICAoIW9wdGlvbnMuZG90ICYmIGZpbGVbZmldLmNoYXJBdCgwKSA9PT0gJy4nKSlcbiAgICAgICAgICAgICAgICAgICAgICAgICAgICByZXR1cm4gZmFsc2U7XG4gICAgICAgICAgICAgICAgICAgIH1cbiAgICAgICAgICAgICAgICAgICAgcmV0dXJuIHRydWU7XG4gICAgICAgICAgICAgICAgfVxuICAgICAgICAgICAgICAgIC8vIG9rLCBsZXQncyBzZWUgaWYgd2UgY2FuIHN3YWxsb3cgd2hhdGV2ZXIgd2UgY2FuLlxuICAgICAgICAgICAgICAgIHdoaWxlIChmciA8IGZsKSB7XG4gICAgICAgICAgICAgICAgICAgIHZhciBzd2FsbG93ZWUgPSBmaWxlW2ZyXTtcbiAgICAgICAgICAgICAgICAgICAgdGhpcy5kZWJ1ZygnXFxuZ2xvYnN0YXIgd2hpbGUnLCBmaWxlLCBmciwgcGF0dGVybiwgcHIsIHN3YWxsb3dlZSk7XG4gICAgICAgICAgICAgICAgICAgIC8vIFhYWCByZW1vdmUgdGhpcyBzbGljZS4gIEp1c3QgcGFzcyB0aGUgc3RhcnQgaW5kZXguXG4gICAgICAgICAgICAgICAgICAgIGlmICh0aGlzLm1hdGNoT25lKGZpbGUuc2xpY2UoZnIpLCBwYXR0ZXJuLnNsaWNlKHByKSwgcGFydGlhbCkpIHtcbiAgICAgICAgICAgICAgICAgICAgICAgIHRoaXMuZGVidWcoJ2dsb2JzdGFyIGZvdW5kIG1hdGNoIScsIGZyLCBmbCwgc3dhbGxvd2VlKTtcbiAgICAgICAgICAgICAgICAgICAgICAgIC8vIGZvdW5kIGEgbWF0Y2guXG4gICAgICAgICAgICAgICAgICAgICAgICByZXR1cm4gdHJ1ZTtcbiAgICAgICAgICAgICAgICAgICAgfVxuICAgICAgICAgICAgICAgICAgICBlbHNlIHtcbiAgICAgICAgICAgICAgICAgICAgICAgIC8vIGNhbid0IHN3YWxsb3cgXCIuXCIgb3IgXCIuLlwiIGV2ZXIuXG4gICAgICAgICAgICAgICAgICAgICAgICAvLyBjYW4gb25seSBzd2FsbG93IFwiLmZvb1wiIHdoZW4gZXhwbGljaXRseSBhc2tlZC5cbiAgICAgICAgICAgICAgICAgICAgICAgIGlmIChzd2FsbG93ZWUgPT09ICcuJyB8fFxuICAgICAgICAgICAgICAgICAgICAgICAgICAgIHN3YWxsb3dlZSA9PT0gJy4uJyB8fFxuICAgICAgICAgICAgICAgICAgICAgICAgICAgICghb3B0aW9ucy5kb3QgJiYgc3dhbGxvd2VlLmNoYXJBdCgwKSA9PT0gJy4nKSkge1xuICAgICAgICAgICAgICAgICAgICAgICAgICAgIHRoaXMuZGVidWcoJ2RvdCBkZXRlY3RlZCEnLCBmaWxlLCBmciwgcGF0dGVybiwgcHIpO1xuICAgICAgICAgICAgICAgICAgICAgICAgICAgIGJyZWFrO1xuICAgICAgICAgICAgICAgICAgICAgICAgfVxuICAgICAgICAgICAgICAgICAgICAgICAgLy8gKiogc3dhbGxvd3MgYSBzZWdtZW50LCBhbmQgY29udGludWUuXG4gICAgICAgICAgICAgICAgICAgICAgICB0aGlzLmRlYnVnKCdnbG9ic3RhciBzd2FsbG93IGEgc2VnbWVudCwgYW5kIGNvbnRpbnVlJyk7XG4gICAgICAgICAgICAgICAgICAgICAgICBmcisrO1xuICAgICAgICAgICAgICAgICAgICB9XG4gICAgICAgICAgICAgICAgfVxuICAgICAgICAgICAgICAgIC8vIG5vIG1hdGNoIHdhcyBmb3VuZC5cbiAgICAgICAgICAgICAgICAvLyBIb3dldmVyLCBpbiBwYXJ0aWFsIG1vZGUsIHdlIGNhbid0IHNheSB0aGlzIGlzIG5lY2Vzc2FyaWx5IG92ZXIuXG4gICAgICAgICAgICAgICAgLyogYzggaWdub3JlIHN0YXJ0ICovXG4gICAgICAgICAgICAgICAgaWYgKHBhcnRpYWwpIHtcbiAgICAgICAgICAgICAgICAgICAgLy8gcmFuIG91dCBvZiBmaWxlXG4gICAgICAgICAgICAgICAgICAgIHRoaXMuZGVidWcoJ1xcbj4+PiBubyBtYXRjaCwgcGFydGlhbD8nLCBmaWxlLCBmciwgcGF0dGVybiwgcHIpO1xuICAgICAgICAgICAgICAgICAgICBpZiAoZnIgPT09IGZsKSB7XG4gICAgICAgICAgICAgICAgICAgICAgICByZXR1cm4gdHJ1ZTtcbiAgICAgICAgICAgICAgICAgICAgfVxuICAgICAgICAgICAgICAgIH1cbiAgICAgICAgICAgICAgICAvKiBjOCBpZ25vcmUgc3RvcCAqL1xuICAgICAgICAgICAgICAgIHJldHVybiBmYWxzZTtcbiAgICAgICAgICAgIH1cbiAgICAgICAgICAgIC8vIHNvbWV0aGluZyBvdGhlciB0aGFuICoqXG4gICAgICAgICAgICAvLyBub24tbWFnaWMgcGF0dGVybnMganVzdCBoYXZlIHRvIG1hdGNoIGV4YWN0bHlcbiAgICAgICAgICAgIC8vIHBhdHRlcm5zIHdpdGggbWFnaWMgaGF2ZSBiZWVuIHR1cm5lZCBpbnRvIHJlZ2V4cHMuXG4gICAgICAgICAgICBsZXQgaGl0O1xuICAgICAgICAgICAgaWYgKHR5cGVvZiBwID09PSAnc3RyaW5nJykge1xuICAgICAgICAgICAgICAgIGhpdCA9IGYgPT09IHA7XG4gICAgICAgICAgICAgICAgdGhpcy5kZWJ1Zygnc3RyaW5nIG1hdGNoJywgcCwgZiwgaGl0KTtcbiAgICAgICAgICAgIH1cbiAgICAgICAgICAgIGVsc2Uge1xuICAgICAgICAgICAgICAgIGhpdCA9IHAudGVzdChmKTtcbiAgICAgICAgICAgICAgICB0aGlzLmRlYnVnKCdwYXR0ZXJuIG1hdGNoJywgcCwgZiwgaGl0KTtcbiAgICAgICAgICAgIH1cbiAgICAgICAgICAgIGlmICghaGl0KVxuICAgICAgICAgICAgICAgIHJldHVybiBmYWxzZTtcbiAgICAgICAgfVxuICAgICAgICAvLyBOb3RlOiBlbmRpbmcgaW4gLyBtZWFucyB0aGF0IHdlJ2xsIGdldCBhIGZpbmFsIFwiXCJcbiAgICAgICAgLy8gYXQgdGhlIGVuZCBvZiB0aGUgcGF0dGVybi4gIFRoaXMgY2FuIG9ubHkgbWF0Y2ggYVxuICAgICAgICAvLyBjb3JyZXNwb25kaW5nIFwiXCIgYXQgdGhlIGVuZCBvZiB0aGUgZmlsZS5cbiAgICAgICAgLy8gSWYgdGhlIGZpbGUgZW5kcyBpbiAvLCB0aGVuIGl0IGNhbiBvbmx5IG1hdGNoIGFcbiAgICAgICAgLy8gYSBwYXR0ZXJuIHRoYXQgZW5kcyBpbiAvLCB1bmxlc3MgdGhlIHBhdHRlcm4ganVzdFxuICAgICAgICAvLyBkb2Vzbid0IGhhdmUgYW55IG1vcmUgZm9yIGl0LiBCdXQsIGEvYi8gc2hvdWxkICpub3QqXG4gICAgICAgIC8vIG1hdGNoIFwiYS9iLypcIiwgZXZlbiB0aG91Z2ggXCJcIiBtYXRjaGVzIGFnYWluc3QgdGhlXG4gICAgICAgIC8vIFteL10qPyBwYXR0ZXJuLCBleGNlcHQgaW4gcGFydGlhbCBtb2RlLCB3aGVyZSBpdCBtaWdodFxuICAgICAgICAvLyBzaW1wbHkgbm90IGJlIHJlYWNoZWQgeWV0LlxuICAgICAgICAvLyBIb3dldmVyLCBhL2IvIHNob3VsZCBzdGlsbCBzYXRpc2Z5IGEvKlxuICAgICAgICAvLyBub3cgZWl0aGVyIHdlIGZlbGwgb2ZmIHRoZSBlbmQgb2YgdGhlIHBhdHRlcm4sIG9yIHdlJ3JlIGRvbmUuXG4gICAgICAgIGlmIChmaSA9PT0gZmwgJiYgcGkgPT09IHBsKSB7XG4gICAgICAgICAgICAvLyByYW4gb3V0IG9mIHBhdHRlcm4gYW5kIGZpbGVuYW1lIGF0IHRoZSBzYW1lIHRpbWUuXG4gICAgICAgICAgICAvLyBhbiBleGFjdCBoaXQhXG4gICAgICAgICAgICByZXR1cm4gdHJ1ZTtcbiAgICAgICAgfVxuICAgICAgICBlbHNlIGlmIChmaSA9PT0gZmwpIHtcbiAgICAgICAgICAgIC8vIHJhbiBvdXQgb2YgZmlsZSwgYnV0IHN0aWxsIGhhZCBwYXR0ZXJuIGxlZnQuXG4gICAgICAgICAgICAvLyB0aGlzIGlzIG9rIGlmIHdlJ3JlIGRvaW5nIHRoZSBtYXRjaCBhcyBwYXJ0IG9mXG4gICAgICAgICAgICAvLyBhIGdsb2IgZnMgdHJhdmVyc2FsLlxuICAgICAgICAgICAgcmV0dXJuIHBhcnRpYWw7XG4gICAgICAgIH1cbiAgICAgICAgZWxzZSBpZiAocGkgPT09IHBsKSB7XG4gICAgICAgICAgICAvLyByYW4gb3V0IG9mIHBhdHRlcm4sIHN0aWxsIGhhdmUgZmlsZSBsZWZ0LlxuICAgICAgICAgICAgLy8gdGhpcyBpcyBvbmx5IGFjY2VwdGFibGUgaWYgd2UncmUgb24gdGhlIHZlcnkgbGFzdFxuICAgICAgICAgICAgLy8gZW1wdHkgc2VnbWVudCBvZiBhIGZpbGUgd2l0aCBhIHRyYWlsaW5nIHNsYXNoLlxuICAgICAgICAgICAgLy8gYS8qIHNob3VsZCBtYXRjaCBhL2IvXG4gICAgICAgICAgICByZXR1cm4gZmkgPT09IGZsIC0gMSAmJiBmaWxlW2ZpXSA9PT0gJyc7XG4gICAgICAgICAgICAvKiBjOCBpZ25vcmUgc3RhcnQgKi9cbiAgICAgICAgfVxuICAgICAgICBlbHNlIHtcbiAgICAgICAgICAgIC8vIHNob3VsZCBiZSB1bnJlYWNoYWJsZS5cbiAgICAgICAgICAgIHRocm93IG5ldyBFcnJvcignd3RmPycpO1xuICAgICAgICB9XG4gICAgICAgIC8qIGM4IGlnbm9yZSBzdG9wICovXG4gICAgfVxuICAgIGJyYWNlRXhwYW5kKCkge1xuICAgICAgICByZXR1cm4gKDAsIGV4cG9ydHMuYnJhY2VFeHBhbmQpKHRoaXMucGF0dGVybiwgdGhpcy5vcHRpb25zKTtcbiAgICB9XG4gICAgcGFyc2UocGF0dGVybikge1xuICAgICAgICAoMCwgYXNzZXJ0X3ZhbGlkX3BhdHRlcm5fanNfMS5hc3NlcnRWYWxpZFBhdHRlcm4pKHBhdHRlcm4pO1xuICAgICAgICBjb25zdCBvcHRpb25zID0gdGhpcy5vcHRpb25zO1xuICAgICAgICAvLyBzaG9ydGN1dHNcbiAgICAgICAgaWYgKHBhdHRlcm4gPT09ICcqKicpXG4gICAgICAgICAgICByZXR1cm4gZXhwb3J0cy5HTE9CU1RBUjtcbiAgICAgICAgaWYgKHBhdHRlcm4gPT09ICcnKVxuICAgICAgICAgICAgcmV0dXJuICcnO1xuICAgICAgICAvLyBmYXIgYW5kIGF3YXksIHRoZSBtb3N0IGNvbW1vbiBnbG9iIHBhdHRlcm4gcGFydHMgYXJlXG4gICAgICAgIC8vICosICouKiwgYW5kICouPGV4dD4gIEFkZCBhIGZhc3QgY2hlY2sgbWV0aG9kIGZvciB0aG9zZS5cbiAgICAgICAgbGV0IG07XG4gICAgICAgIGxldCBmYXN0VGVzdCA9IG51bGw7XG4gICAgICAgIGlmICgobSA9IHBhdHRlcm4ubWF0Y2goc3RhclJFKSkpIHtcbiAgICAgICAgICAgIGZhc3RUZXN0ID0gb3B0aW9ucy5kb3QgPyBzdGFyVGVzdERvdCA6IHN0YXJUZXN0O1xuICAgICAgICB9XG4gICAgICAgIGVsc2UgaWYgKChtID0gcGF0dGVybi5tYXRjaChzdGFyRG90RXh0UkUpKSkge1xuICAgICAgICAgICAgZmFzdFRlc3QgPSAob3B0aW9ucy5ub2Nhc2VcbiAgICAgICAgICAgICAgICA/IG9wdGlvbnMuZG90XG4gICAgICAgICAgICAgICAgICAgID8gc3RhckRvdEV4dFRlc3ROb2Nhc2VEb3RcbiAgICAgICAgICAgICAgICAgICAgOiBzdGFyRG90RXh0VGVzdE5vY2FzZVxuICAgICAgICAgICAgICAgIDogb3B0aW9ucy5kb3RcbiAgICAgICAgICAgICAgICAgICAgPyBzdGFyRG90RXh0VGVzdERvdFxuICAgICAgICAgICAgICAgICAgICA6IHN0YXJEb3RFeHRUZXN0KShtWzFdKTtcbiAgICAgICAgfVxuICAgICAgICBlbHNlIGlmICgobSA9IHBhdHRlcm4ubWF0Y2gocW1hcmtzUkUpKSkge1xuICAgICAgICAgICAgZmFzdFRlc3QgPSAob3B0aW9ucy5ub2Nhc2VcbiAgICAgICAgICAgICAgICA/IG9wdGlvbnMuZG90XG4gICAgICAgICAgICAgICAgICAgID8gcW1hcmtzVGVzdE5vY2FzZURvdFxuICAgICAgICAgICAgICAgICAgICA6IHFtYXJrc1Rlc3ROb2Nhc2VcbiAgICAgICAgICAgICAgICA6IG9wdGlvbnMuZG90XG4gICAgICAgICAgICAgICAgICAgID8gcW1hcmtzVGVzdERvdFxuICAgICAgICAgICAgICAgICAgICA6IHFtYXJrc1Rlc3QpKG0pO1xuICAgICAgICB9XG4gICAgICAgIGVsc2UgaWYgKChtID0gcGF0dGVybi5tYXRjaChzdGFyRG90U3RhclJFKSkpIHtcbiAgICAgICAgICAgIGZhc3RUZXN0ID0gb3B0aW9ucy5kb3QgPyBzdGFyRG90U3RhclRlc3REb3QgOiBzdGFyRG90U3RhclRlc3Q7XG4gICAgICAgIH1cbiAgICAgICAgZWxzZSBpZiAoKG0gPSBwYXR0ZXJuLm1hdGNoKGRvdFN0YXJSRSkpKSB7XG4gICAgICAgICAgICBmYXN0VGVzdCA9IGRvdFN0YXJUZXN0O1xuICAgICAgICB9XG4gICAgICAgIGNvbnN0IHJlID0gYXN0X2pzXzEuQVNULmZyb21HbG9iKHBhdHRlcm4sIHRoaXMub3B0aW9ucykudG9NTVBhdHRlcm4oKTtcbiAgICAgICAgaWYgKGZhc3RUZXN0ICYmIHR5cGVvZiByZSA9PT0gJ29iamVjdCcpIHtcbiAgICAgICAgICAgIC8vIEF2b2lkcyBvdmVycmlkaW5nIGluIGZyb3plbiBlbnZpcm9ubWVudHNcbiAgICAgICAgICAgIFJlZmxlY3QuZGVmaW5lUHJvcGVydHkocmUsICd0ZXN0JywgeyB2YWx1ZTogZmFzdFRlc3QgfSk7XG4gICAgICAgIH1cbiAgICAgICAgcmV0dXJuIHJlO1xuICAgIH1cbiAgICBtYWtlUmUoKSB7XG4gICAgICAgIGlmICh0aGlzLnJlZ2V4cCB8fCB0aGlzLnJlZ2V4cCA9PT0gZmFsc2UpXG4gICAgICAgICAgICByZXR1cm4gdGhpcy5yZWdleHA7XG4gICAgICAgIC8vIGF0IHRoaXMgcG9pbnQsIHRoaXMuc2V0IGlzIGEgMmQgYXJyYXkgb2YgcGFydGlhbFxuICAgICAgICAvLyBwYXR0ZXJuIHN0cmluZ3MsIG9yIFwiKipcIi5cbiAgICAgICAgLy9cbiAgICAgICAgLy8gSXQncyBiZXR0ZXIgdG8gdXNlIC5tYXRjaCgpLiAgVGhpcyBmdW5jdGlvbiBzaG91bGRuJ3RcbiAgICAgICAgLy8gYmUgdXNlZCwgcmVhbGx5LCBidXQgaXQncyBwcmV0dHkgY29udmVuaWVudCBzb21ldGltZXMsXG4gICAgICAgIC8vIHdoZW4geW91IGp1c3Qgd2FudCB0byB3b3JrIHdpdGggYSByZWdleC5cbiAgICAgICAgY29uc3Qgc2V0ID0gdGhpcy5zZXQ7XG4gICAgICAgIGlmICghc2V0Lmxlbmd0aCkge1xuICAgICAgICAgICAgdGhpcy5yZWdleHAgPSBmYWxzZTtcbiAgICAgICAgICAgIHJldHVybiB0aGlzLnJlZ2V4cDtcbiAgICAgICAgfVxuICAgICAgICBjb25zdCBvcHRpb25zID0gdGhpcy5vcHRpb25zO1xuICAgICAgICBjb25zdCB0d29TdGFyID0gb3B0aW9ucy5ub2dsb2JzdGFyXG4gICAgICAgICAgICA/IHN0YXJcbiAgICAgICAgICAgIDogb3B0aW9ucy5kb3RcbiAgICAgICAgICAgICAgICA/IHR3b1N0YXJEb3RcbiAgICAgICAgICAgICAgICA6IHR3b1N0YXJOb0RvdDtcbiAgICAgICAgY29uc3QgZmxhZ3MgPSBuZXcgU2V0KG9wdGlvbnMubm9jYXNlID8gWydpJ10gOiBbXSk7XG4gICAgICAgIC8vIHJlZ2V4cGlmeSBub24tZ2xvYnN0YXIgcGF0dGVybnNcbiAgICAgICAgLy8gaWYgKiogaXMgb25seSBpdGVtLCB0aGVuIHdlIGp1c3QgZG8gb25lIHR3b1N0YXJcbiAgICAgICAgLy8gaWYgKiogaXMgZmlyc3QsIGFuZCB0aGVyZSBhcmUgbW9yZSwgcHJlcGVuZCAoXFwvfHR3b1N0YXJcXC8pPyB0byBuZXh0XG4gICAgICAgIC8vIGlmICoqIGlzIGxhc3QsIGFwcGVuZCAoXFwvdHdvU3RhcnwpIHRvIHByZXZpb3VzXG4gICAgICAgIC8vIGlmICoqIGlzIGluIHRoZSBtaWRkbGUsIGFwcGVuZCAoXFwvfFxcL3R3b1N0YXJcXC8pIHRvIHByZXZpb3VzXG4gICAgICAgIC8vIHRoZW4gZmlsdGVyIG91dCBHTE9CU1RBUiBzeW1ib2xzXG4gICAgICAgIGxldCByZSA9IHNldFxuICAgICAgICAgICAgLm1hcChwYXR0ZXJuID0+IHtcbiAgICAgICAgICAgIGNvbnN0IHBwID0gcGF0dGVybi5tYXAocCA9PiB7XG4gICAgICAgICAgICAgICAgaWYgKHAgaW5zdGFuY2VvZiBSZWdFeHApIHtcbiAgICAgICAgICAgICAgICAgICAgZm9yIChjb25zdCBmIG9mIHAuZmxhZ3Muc3BsaXQoJycpKVxuICAgICAgICAgICAgICAgICAgICAgICAgZmxhZ3MuYWRkKGYpO1xuICAgICAgICAgICAgICAgIH1cbiAgICAgICAgICAgICAgICByZXR1cm4gdHlwZW9mIHAgPT09ICdzdHJpbmcnXG4gICAgICAgICAgICAgICAgICAgID8gcmVnRXhwRXNjYXBlKHApXG4gICAgICAgICAgICAgICAgICAgIDogcCA9PT0gZXhwb3J0cy5HTE9CU1RBUlxuICAgICAgICAgICAgICAgICAgICAgICAgPyBleHBvcnRzLkdMT0JTVEFSXG4gICAgICAgICAgICAgICAgICAgICAgICA6IHAuX3NyYztcbiAgICAgICAgICAgIH0pO1xuICAgICAgICAgICAgcHAuZm9yRWFjaCgocCwgaSkgPT4ge1xuICAgICAgICAgICAgICAgIGNvbnN0IG5leHQgPSBwcFtpICsgMV07XG4gICAgICAgICAgICAgICAgY29uc3QgcHJldiA9IHBwW2kgLSAxXTtcbiAgICAgICAgICAgICAgICBpZiAocCAhPT0gZXhwb3J0cy5HTE9CU1RBUiB8fCBwcmV2ID09PSBleHBvcnRzLkdMT0JTVEFSKSB7XG4gICAgICAgICAgICAgICAgICAgIHJldHVybjtcbiAgICAgICAgICAgICAgICB9XG4gICAgICAgICAgICAgICAgaWYgKHByZXYgPT09IHVuZGVmaW5lZCkge1xuICAgICAgICAgICAgICAgICAgICBpZiAobmV4dCAhPT0gdW5kZWZpbmVkICYmIG5leHQgIT09IGV4cG9ydHMuR0xPQlNUQVIpIHtcbiAgICAgICAgICAgICAgICAgICAgICAgIHBwW2kgKyAxXSA9ICcoPzpcXFxcL3wnICsgdHdvU3RhciArICdcXFxcLyk/JyArIG5leHQ7XG4gICAgICAgICAgICAgICAgICAgIH1cbiAgICAgICAgICAgICAgICAgICAgZWxzZSB7XG4gICAgICAgICAgICAgICAgICAgICAgICBwcFtpXSA9IHR3b1N0YXI7XG4gICAgICAgICAgICAgICAgICAgIH1cbiAgICAgICAgICAgICAgICB9XG4gICAgICAgICAgICAgICAgZWxzZSBpZiAobmV4dCA9PT0gdW5kZWZpbmVkKSB7XG4gICAgICAgICAgICAgICAgICAgIHBwW2kgLSAxXSA9IHByZXYgKyAnKD86XFxcXC98JyArIHR3b1N0YXIgKyAnKT8nO1xuICAgICAgICAgICAgICAgIH1cbiAgICAgICAgICAgICAgICBlbHNlIGlmIChuZXh0ICE9PSBleHBvcnRzLkdMT0JTVEFSKSB7XG4gICAgICAgICAgICAgICAgICAgIHBwW2kgLSAxXSA9IHByZXYgKyAnKD86XFxcXC98XFxcXC8nICsgdHdvU3RhciArICdcXFxcLyknICsgbmV4dDtcbiAgICAgICAgICAgICAgICAgICAgcHBbaSArIDFdID0gZXhwb3J0cy5HTE9CU1RBUjtcbiAgICAgICAgICAgICAgICB9XG4gICAgICAgICAgICB9KTtcbiAgICAgICAgICAgIHJldHVybiBwcC5maWx0ZXIocCA9PiBwICE9PSBleHBvcnRzLkdMT0JTVEFSKS5qb2luKCcvJyk7XG4gICAgICAgIH0pXG4gICAgICAgICAgICAuam9pbignfCcpO1xuICAgICAgICAvLyBuZWVkIHRvIHdyYXAgaW4gcGFyZW5zIGlmIHdlIGhhZCBtb3JlIHRoYW4gb25lIHRoaW5nIHdpdGggfCxcbiAgICAgICAgLy8gb3RoZXJ3aXNlIG9ubHkgdGhlIGZpcnN0IHdpbGwgYmUgYW5jaG9yZWQgdG8gXiBhbmQgdGhlIGxhc3QgdG8gJFxuICAgICAgICBjb25zdCBbb3BlbiwgY2xvc2VdID0gc2V0Lmxlbmd0aCA+IDEgPyBbJyg/OicsICcpJ10gOiBbJycsICcnXTtcbiAgICAgICAgLy8gbXVzdCBtYXRjaCBlbnRpcmUgcGF0dGVyblxuICAgICAgICAvLyBlbmRpbmcgaW4gYSAqIG9yICoqIHdpbGwgbWFrZSBpdCBsZXNzIHN0cmljdC5cbiAgICAgICAgcmUgPSAnXicgKyBvcGVuICsgcmUgKyBjbG9zZSArICckJztcbiAgICAgICAgLy8gY2FuIG1hdGNoIGFueXRoaW5nLCBhcyBsb25nIGFzIGl0J3Mgbm90IHRoaXMuXG4gICAgICAgIGlmICh0aGlzLm5lZ2F0ZSlcbiAgICAgICAgICAgIHJlID0gJ14oPyEnICsgcmUgKyAnKS4rJCc7XG4gICAgICAgIHRyeSB7XG4gICAgICAgICAgICB0aGlzLnJlZ2V4cCA9IG5ldyBSZWdFeHAocmUsIFsuLi5mbGFnc10uam9pbignJykpO1xuICAgICAgICAgICAgLyogYzggaWdub3JlIHN0YXJ0ICovXG4gICAgICAgIH1cbiAgICAgICAgY2F0Y2ggKGV4KSB7XG4gICAgICAgICAgICAvLyBzaG91bGQgYmUgaW1wb3NzaWJsZVxuICAgICAgICAgICAgdGhpcy5yZWdleHAgPSBmYWxzZTtcbiAgICAgICAgfVxuICAgICAgICAvKiBjOCBpZ25vcmUgc3RvcCAqL1xuICAgICAgICByZXR1cm4gdGhpcy5yZWdleHA7XG4gICAgfVxuICAgIHNsYXNoU3BsaXQocCkge1xuICAgICAgICAvLyBpZiBwIHN0YXJ0cyB3aXRoIC8vIG9uIHdpbmRvd3MsIHdlIHByZXNlcnZlIHRoYXRcbiAgICAgICAgLy8gc28gdGhhdCBVTkMgcGF0aHMgYXJlbid0IGJyb2tlbi4gIE90aGVyd2lzZSwgYW55IG51bWJlciBvZlxuICAgICAgICAvLyAvIGNoYXJhY3RlcnMgYXJlIGNvYWxlc2NlZCBpbnRvIG9uZSwgdW5sZXNzXG4gICAgICAgIC8vIHByZXNlcnZlTXVsdGlwbGVTbGFzaGVzIGlzIHNldCB0byB0cnVlLlxuICAgICAgICBpZiAodGhpcy5wcmVzZXJ2ZU11bHRpcGxlU2xhc2hlcykge1xuICAgICAgICAgICAgcmV0dXJuIHAuc3BsaXQoJy8nKTtcbiAgICAgICAgfVxuICAgICAgICBlbHNlIGlmICh0aGlzLmlzV2luZG93cyAmJiAvXlxcL1xcL1teXFwvXSsvLnRlc3QocCkpIHtcbiAgICAgICAgICAgIC8vIGFkZCBhbiBleHRyYSAnJyBmb3IgdGhlIG9uZSB3ZSBsb3NlXG4gICAgICAgICAgICByZXR1cm4gWycnLCAuLi5wLnNwbGl0KC9cXC8rLyldO1xuICAgICAgICB9XG4gICAgICAgIGVsc2Uge1xuICAgICAgICAgICAgcmV0dXJuIHAuc3BsaXQoL1xcLysvKTtcbiAgICAgICAgfVxuICAgIH1cbiAgICBtYXRjaChmLCBwYXJ0aWFsID0gdGhpcy5wYXJ0aWFsKSB7XG4gICAgICAgIHRoaXMuZGVidWcoJ21hdGNoJywgZiwgdGhpcy5wYXR0ZXJuKTtcbiAgICAgICAgLy8gc2hvcnQtY2lyY3VpdCBpbiB0aGUgY2FzZSBvZiBidXN0ZWQgdGhpbmdzLlxuICAgICAgICAvLyBjb21tZW50cywgZXRjLlxuICAgICAgICBpZiAodGhpcy5jb21tZW50KSB7XG4gICAgICAgICAgICByZXR1cm4gZmFsc2U7XG4gICAgICAgIH1cbiAgICAgICAgaWYgKHRoaXMuZW1wdHkpIHtcbiAgICAgICAgICAgIHJldHVybiBmID09PSAnJztcbiAgICAgICAgfVxuICAgICAgICBpZiAoZiA9PT0gJy8nICYmIHBhcnRpYWwpIHtcbiAgICAgICAgICAgIHJldHVybiB0cnVlO1xuICAgICAgICB9XG4gICAgICAgIGNvbnN0IG9wdGlvbnMgPSB0aGlzLm9wdGlvbnM7XG4gICAgICAgIC8vIHdpbmRvd3M6IG5lZWQgdG8gdXNlIC8sIG5vdCBcXFxuICAgICAgICBpZiAodGhpcy5pc1dpbmRvd3MpIHtcbiAgICAgICAgICAgIGYgPSBmLnNwbGl0KCdcXFxcJykuam9pbignLycpO1xuICAgICAgICB9XG4gICAgICAgIC8vIHRyZWF0IHRoZSB0ZXN0IHBhdGggYXMgYSBzZXQgb2YgcGF0aHBhcnRzLlxuICAgICAgICBjb25zdCBmZiA9IHRoaXMuc2xhc2hTcGxpdChmKTtcbiAgICAgICAgdGhpcy5kZWJ1Zyh0aGlzLnBhdHRlcm4sICdzcGxpdCcsIGZmKTtcbiAgICAgICAgLy8ganVzdCBPTkUgb2YgdGhlIHBhdHRlcm4gc2V0cyBpbiB0aGlzLnNldCBuZWVkcyB0byBtYXRjaFxuICAgICAgICAvLyBpbiBvcmRlciBmb3IgaXQgdG8gYmUgdmFsaWQuICBJZiBuZWdhdGluZywgdGhlbiBqdXN0IG9uZVxuICAgICAgICAvLyBtYXRjaCBtZWFucyB0aGF0IHdlIGhhdmUgZmFpbGVkLlxuICAgICAgICAvLyBFaXRoZXIgd2F5LCByZXR1cm4gb24gdGhlIGZpcnN0IGhpdC5cbiAgICAgICAgY29uc3Qgc2V0ID0gdGhpcy5zZXQ7XG4gICAgICAgIHRoaXMuZGVidWcodGhpcy5wYXR0ZXJuLCAnc2V0Jywgc2V0KTtcbiAgICAgICAgLy8gRmluZCB0aGUgYmFzZW5hbWUgb2YgdGhlIHBhdGggYnkgbG9va2luZyBmb3IgdGhlIGxhc3Qgbm9uLWVtcHR5IHNlZ21lbnRcbiAgICAgICAgbGV0IGZpbGVuYW1lID0gZmZbZmYubGVuZ3RoIC0gMV07XG4gICAgICAgIGlmICghZmlsZW5hbWUpIHtcbiAgICAgICAgICAgIGZvciAobGV0IGkgPSBmZi5sZW5ndGggLSAyOyAhZmlsZW5hbWUgJiYgaSA+PSAwOyBpLS0pIHtcbiAgICAgICAgICAgICAgICBmaWxlbmFtZSA9IGZmW2ldO1xuICAgICAgICAgICAgfVxuICAgICAgICB9XG4gICAgICAgIGZvciAobGV0IGkgPSAwOyBpIDwgc2V0Lmxlbmd0aDsgaSsrKSB7XG4gICAgICAgICAgICBjb25zdCBwYXR0ZXJuID0gc2V0W2ldO1xuICAgICAgICAgICAgbGV0IGZpbGUgPSBmZjtcbiAgICAgICAgICAgIGlmIChvcHRpb25zLm1hdGNoQmFzZSAmJiBwYXR0ZXJuLmxlbmd0aCA9PT0gMSkge1xuICAgICAgICAgICAgICAgIGZpbGUgPSBbZmlsZW5hbWVdO1xuICAgICAgICAgICAgfVxuICAgICAgICAgICAgY29uc3QgaGl0ID0gdGhpcy5tYXRjaE9uZShmaWxlLCBwYXR0ZXJuLCBwYXJ0aWFsKTtcbiAgICAgICAgICAgIGlmIChoaXQpIHtcbiAgICAgICAgICAgICAgICBpZiAob3B0aW9ucy5mbGlwTmVnYXRlKSB7XG4gICAgICAgICAgICAgICAgICAgIHJldHVybiB0cnVlO1xuICAgICAgICAgICAgICAgIH1cbiAgICAgICAgICAgICAgICByZXR1cm4gIXRoaXMubmVnYXRlO1xuICAgICAgICAgICAgfVxuICAgICAgICB9XG4gICAgICAgIC8vIGRpZG4ndCBnZXQgYW55IGhpdHMuICB0aGlzIGlzIHN1Y2Nlc3MgaWYgaXQncyBhIG5lZ2F0aXZlXG4gICAgICAgIC8vIHBhdHRlcm4sIGZhaWx1cmUgb3RoZXJ3aXNlLlxuICAgICAgICBpZiAob3B0aW9ucy5mbGlwTmVnYXRlKSB7XG4gICAgICAgICAgICByZXR1cm4gZmFsc2U7XG4gICAgICAgIH1cbiAgICAgICAgcmV0dXJuIHRoaXMubmVnYXRlO1xuICAgIH1cbiAgICBzdGF0aWMgZGVmYXVsdHMoZGVmKSB7XG4gICAgICAgIHJldHVybiBleHBvcnRzLm1pbmltYXRjaC5kZWZhdWx0cyhkZWYpLk1pbmltYXRjaDtcbiAgICB9XG59XG5leHBvcnRzLk1pbmltYXRjaCA9IE1pbmltYXRjaDtcbi8qIGM4IGlnbm9yZSBzdGFydCAqL1xudmFyIGFzdF9qc18yID0gcmVxdWlyZShcIi4vYXN0LmpzXCIpO1xuT2JqZWN0LmRlZmluZVByb3BlcnR5KGV4cG9ydHMsIFwiQVNUXCIsIHsgZW51bWVyYWJsZTogdHJ1ZSwgZ2V0OiBmdW5jdGlvbiAoKSB7IHJldHVybiBhc3RfanNfMi5BU1Q7IH0gfSk7XG52YXIgZXNjYXBlX2pzXzIgPSByZXF1aXJlKFwiLi9lc2NhcGUuanNcIik7XG5PYmplY3QuZGVmaW5lUHJvcGVydHkoZXhwb3J0cywgXCJlc2NhcGVcIiwgeyBlbnVtZXJhYmxlOiB0cnVlLCBnZXQ6IGZ1bmN0aW9uICgpIHsgcmV0dXJuIGVzY2FwZV9qc18yLmVzY2FwZTsgfSB9KTtcbnZhciB1bmVzY2FwZV9qc18yID0gcmVxdWlyZShcIi4vdW5lc2NhcGUuanNcIik7XG5PYmplY3QuZGVmaW5lUHJvcGVydHkoZXhwb3J0cywgXCJ1bmVzY2FwZVwiLCB7IGVudW1lcmFibGU6IHRydWUsIGdldDogZnVuY3Rpb24gKCkgeyByZXR1cm4gdW5lc2NhcGVfanNfMi51bmVzY2FwZTsgfSB9KTtcbi8qIGM4IGlnbm9yZSBzdG9wICovXG5leHBvcnRzLm1pbmltYXRjaC5BU1QgPSBhc3RfanNfMS5BU1Q7XG5leHBvcnRzLm1pbmltYXRjaC5NaW5pbWF0Y2ggPSBNaW5pbWF0Y2g7XG5leHBvcnRzLm1pbmltYXRjaC5lc2NhcGUgPSBlc2NhcGVfanNfMS5lc2NhcGU7XG5leHBvcnRzLm1pbmltYXRjaC51bmVzY2FwZSA9IHVuZXNjYXBlX2pzXzEudW5lc2NhcGU7XG4vLyMgc291cmNlTWFwcGluZ1VSTD1pbmRleC5qcy5tYXAiLCJcInVzZSBzdHJpY3RcIjtcbk9iamVjdC5kZWZpbmVQcm9wZXJ0eShleHBvcnRzLCBcIl9fZXNNb2R1bGVcIiwgeyB2YWx1ZTogdHJ1ZSB9KTtcbmV4cG9ydHMudW5lc2NhcGUgPSB2b2lkIDA7XG4vKipcbiAqIFVuLWVzY2FwZSBhIHN0cmluZyB0aGF0IGhhcyBiZWVuIGVzY2FwZWQgd2l0aCB7QGxpbmsgZXNjYXBlfS5cbiAqXG4gKiBJZiB0aGUge0BsaW5rIHdpbmRvd3NQYXRoc05vRXNjYXBlfSBvcHRpb24gaXMgdXNlZCwgdGhlbiBzcXVhcmUtYnJhY2VcbiAqIGVzY2FwZXMgYXJlIHJlbW92ZWQsIGJ1dCBub3QgYmFja3NsYXNoIGVzY2FwZXMuICBGb3IgZXhhbXBsZSwgaXQgd2lsbCB0dXJuXG4gKiB0aGUgc3RyaW5nIGAnWypdJ2AgaW50byBgKmAsIGJ1dCBpdCB3aWxsIG5vdCB0dXJuIGAnXFxcXConYCBpbnRvIGAnKidgLFxuICogYmVjdWFzZSBgXFxgIGlzIGEgcGF0aCBzZXBhcmF0b3IgaW4gYHdpbmRvd3NQYXRoc05vRXNjYXBlYCBtb2RlLlxuICpcbiAqIFdoZW4gYHdpbmRvd3NQYXRoc05vRXNjYXBlYCBpcyBub3Qgc2V0LCB0aGVuIGJvdGggYnJhY2UgZXNjYXBlcyBhbmRcbiAqIGJhY2tzbGFzaCBlc2NhcGVzIGFyZSByZW1vdmVkLlxuICpcbiAqIFNsYXNoZXMgKGFuZCBiYWNrc2xhc2hlcyBpbiBgd2luZG93c1BhdGhzTm9Fc2NhcGVgIG1vZGUpIGNhbm5vdCBiZSBlc2NhcGVkXG4gKiBvciB1bmVzY2FwZWQuXG4gKi9cbmNvbnN0IHVuZXNjYXBlID0gKHMsIHsgd2luZG93c1BhdGhzTm9Fc2NhcGUgPSBmYWxzZSwgfSA9IHt9KSA9PiB7XG4gICAgcmV0dXJuIHdpbmRvd3NQYXRoc05vRXNjYXBlXG4gICAgICAgID8gcy5yZXBsYWNlKC9cXFsoW15cXC9cXFxcXSlcXF0vZywgJyQxJylcbiAgICAgICAgOiBzLnJlcGxhY2UoLygoPyFcXFxcKS58XilcXFsoW15cXC9cXFxcXSlcXF0vZywgJyQxJDInKS5yZXBsYWNlKC9cXFxcKFteXFwvXSkvZywgJyQxJyk7XG59O1xuZXhwb3J0cy51bmVzY2FwZSA9IHVuZXNjYXBlO1xuLy8jIHNvdXJjZU1hcHBpbmdVUkw9dW5lc2NhcGUuanMubWFwIiwidmFyIGJhbGFuY2VkID0gcmVxdWlyZSgnYmFsYW5jZWQtbWF0Y2gnKTtcblxubW9kdWxlLmV4cG9ydHMgPSBleHBhbmRUb3A7XG5cbnZhciBlc2NTbGFzaCA9ICdcXDBTTEFTSCcrTWF0aC5yYW5kb20oKSsnXFwwJztcbnZhciBlc2NPcGVuID0gJ1xcME9QRU4nK01hdGgucmFuZG9tKCkrJ1xcMCc7XG52YXIgZXNjQ2xvc2UgPSAnXFwwQ0xPU0UnK01hdGgucmFuZG9tKCkrJ1xcMCc7XG52YXIgZXNjQ29tbWEgPSAnXFwwQ09NTUEnK01hdGgucmFuZG9tKCkrJ1xcMCc7XG52YXIgZXNjUGVyaW9kID0gJ1xcMFBFUklPRCcrTWF0aC5yYW5kb20oKSsnXFwwJztcblxuZnVuY3Rpb24gbnVtZXJpYyhzdHIpIHtcbiAgcmV0dXJuIHBhcnNlSW50KHN0ciwgMTApID09IHN0clxuICAgID8gcGFyc2VJbnQoc3RyLCAxMClcbiAgICA6IHN0ci5jaGFyQ29kZUF0KDApO1xufVxuXG5mdW5jdGlvbiBlc2NhcGVCcmFjZXMoc3RyKSB7XG4gIHJldHVybiBzdHIuc3BsaXQoJ1xcXFxcXFxcJykuam9pbihlc2NTbGFzaClcbiAgICAgICAgICAgIC5zcGxpdCgnXFxcXHsnKS5qb2luKGVzY09wZW4pXG4gICAgICAgICAgICAuc3BsaXQoJ1xcXFx9Jykuam9pbihlc2NDbG9zZSlcbiAgICAgICAgICAgIC5zcGxpdCgnXFxcXCwnKS5qb2luKGVzY0NvbW1hKVxuICAgICAgICAgICAgLnNwbGl0KCdcXFxcLicpLmpvaW4oZXNjUGVyaW9kKTtcbn1cblxuZnVuY3Rpb24gdW5lc2NhcGVCcmFjZXMoc3RyKSB7XG4gIHJldHVybiBzdHIuc3BsaXQoZXNjU2xhc2gpLmpvaW4oJ1xcXFwnKVxuICAgICAgICAgICAgLnNwbGl0KGVzY09wZW4pLmpvaW4oJ3snKVxuICAgICAgICAgICAgLnNwbGl0KGVzY0Nsb3NlKS5qb2luKCd9JylcbiAgICAgICAgICAgIC5zcGxpdChlc2NDb21tYSkuam9pbignLCcpXG4gICAgICAgICAgICAuc3BsaXQoZXNjUGVyaW9kKS5qb2luKCcuJyk7XG59XG5cblxuLy8gQmFzaWNhbGx5IGp1c3Qgc3RyLnNwbGl0KFwiLFwiKSwgYnV0IGhhbmRsaW5nIGNhc2VzXG4vLyB3aGVyZSB3ZSBoYXZlIG5lc3RlZCBicmFjZWQgc2VjdGlvbnMsIHdoaWNoIHNob3VsZCBiZVxuLy8gdHJlYXRlZCBhcyBpbmRpdmlkdWFsIG1lbWJlcnMsIGxpa2Uge2Ese2IsY30sZH1cbmZ1bmN0aW9uIHBhcnNlQ29tbWFQYXJ0cyhzdHIpIHtcbiAgaWYgKCFzdHIpXG4gICAgcmV0dXJuIFsnJ107XG5cbiAgdmFyIHBhcnRzID0gW107XG4gIHZhciBtID0gYmFsYW5jZWQoJ3snLCAnfScsIHN0cik7XG5cbiAgaWYgKCFtKVxuICAgIHJldHVybiBzdHIuc3BsaXQoJywnKTtcblxuICB2YXIgcHJlID0gbS5wcmU7XG4gIHZhciBib2R5ID0gbS5ib2R5O1xuICB2YXIgcG9zdCA9IG0ucG9zdDtcbiAgdmFyIHAgPSBwcmUuc3BsaXQoJywnKTtcblxuICBwW3AubGVuZ3RoLTFdICs9ICd7JyArIGJvZHkgKyAnfSc7XG4gIHZhciBwb3N0UGFydHMgPSBwYXJzZUNvbW1hUGFydHMocG9zdCk7XG4gIGlmIChwb3N0Lmxlbmd0aCkge1xuICAgIHBbcC5sZW5ndGgtMV0gKz0gcG9zdFBhcnRzLnNoaWZ0KCk7XG4gICAgcC5wdXNoLmFwcGx5KHAsIHBvc3RQYXJ0cyk7XG4gIH1cblxuICBwYXJ0cy5wdXNoLmFwcGx5KHBhcnRzLCBwKTtcblxuICByZXR1cm4gcGFydHM7XG59XG5cbmZ1bmN0aW9uIGV4cGFuZFRvcChzdHIpIHtcbiAgaWYgKCFzdHIpXG4gICAgcmV0dXJuIFtdO1xuXG4gIC8vIEkgZG9uJ3Qga25vdyB3aHkgQmFzaCA0LjMgZG9lcyB0aGlzLCBidXQgaXQgZG9lcy5cbiAgLy8gQW55dGhpbmcgc3RhcnRpbmcgd2l0aCB7fSB3aWxsIGhhdmUgdGhlIGZpcnN0IHR3byBieXRlcyBwcmVzZXJ2ZWRcbiAgLy8gYnV0ICpvbmx5KiBhdCB0aGUgdG9wIGxldmVsLCBzbyB7fSxhfWIgd2lsbCBub3QgZXhwYW5kIHRvIGFueXRoaW5nLFxuICAvLyBidXQgYXt9LGJ9YyB3aWxsIGJlIGV4cGFuZGVkIHRvIFthfWMsYWJjXS5cbiAgLy8gT25lIGNvdWxkIGFyZ3VlIHRoYXQgdGhpcyBpcyBhIGJ1ZyBpbiBCYXNoLCBidXQgc2luY2UgdGhlIGdvYWwgb2ZcbiAgLy8gdGhpcyBtb2R1bGUgaXMgdG8gbWF0Y2ggQmFzaCdzIHJ1bGVzLCB3ZSBlc2NhcGUgYSBsZWFkaW5nIHt9XG4gIGlmIChzdHIuc3Vic3RyKDAsIDIpID09PSAne30nKSB7XG4gICAgc3RyID0gJ1xcXFx7XFxcXH0nICsgc3RyLnN1YnN0cigyKTtcbiAgfVxuXG4gIHJldHVybiBleHBhbmQoZXNjYXBlQnJhY2VzKHN0ciksIHRydWUpLm1hcCh1bmVzY2FwZUJyYWNlcyk7XG59XG5cbmZ1bmN0aW9uIGVtYnJhY2Uoc3RyKSB7XG4gIHJldHVybiAneycgKyBzdHIgKyAnfSc7XG59XG5mdW5jdGlvbiBpc1BhZGRlZChlbCkge1xuICByZXR1cm4gL14tPzBcXGQvLnRlc3QoZWwpO1xufVxuXG5mdW5jdGlvbiBsdGUoaSwgeSkge1xuICByZXR1cm4gaSA8PSB5O1xufVxuZnVuY3Rpb24gZ3RlKGksIHkpIHtcbiAgcmV0dXJuIGkgPj0geTtcbn1cblxuZnVuY3Rpb24gZXhwYW5kKHN0ciwgaXNUb3ApIHtcbiAgdmFyIGV4cGFuc2lvbnMgPSBbXTtcblxuICB2YXIgbSA9IGJhbGFuY2VkKCd7JywgJ30nLCBzdHIpO1xuICBpZiAoIW0pIHJldHVybiBbc3RyXTtcblxuICAvLyBubyBuZWVkIHRvIGV4cGFuZCBwcmUsIHNpbmNlIGl0IGlzIGd1YXJhbnRlZWQgdG8gYmUgZnJlZSBvZiBicmFjZS1zZXRzXG4gIHZhciBwcmUgPSBtLnByZTtcbiAgdmFyIHBvc3QgPSBtLnBvc3QubGVuZ3RoXG4gICAgPyBleHBhbmQobS5wb3N0LCBmYWxzZSlcbiAgICA6IFsnJ107XG5cbiAgaWYgKC9cXCQkLy50ZXN0KG0ucHJlKSkgeyAgICBcbiAgICBmb3IgKHZhciBrID0gMDsgayA8IHBvc3QubGVuZ3RoOyBrKyspIHtcbiAgICAgIHZhciBleHBhbnNpb24gPSBwcmUrICd7JyArIG0uYm9keSArICd9JyArIHBvc3Rba107XG4gICAgICBleHBhbnNpb25zLnB1c2goZXhwYW5zaW9uKTtcbiAgICB9XG4gIH0gZWxzZSB7XG4gICAgdmFyIGlzTnVtZXJpY1NlcXVlbmNlID0gL14tP1xcZCtcXC5cXC4tP1xcZCsoPzpcXC5cXC4tP1xcZCspPyQvLnRlc3QobS5ib2R5KTtcbiAgICB2YXIgaXNBbHBoYVNlcXVlbmNlID0gL15bYS16QS1aXVxcLlxcLlthLXpBLVpdKD86XFwuXFwuLT9cXGQrKT8kLy50ZXN0KG0uYm9keSk7XG4gICAgdmFyIGlzU2VxdWVuY2UgPSBpc051bWVyaWNTZXF1ZW5jZSB8fCBpc0FscGhhU2VxdWVuY2U7XG4gICAgdmFyIGlzT3B0aW9ucyA9IG0uYm9keS5pbmRleE9mKCcsJykgPj0gMDtcbiAgICBpZiAoIWlzU2VxdWVuY2UgJiYgIWlzT3B0aW9ucykge1xuICAgICAgLy8ge2F9LGJ9XG4gICAgICBpZiAobS5wb3N0Lm1hdGNoKC8sLipcXH0vKSkge1xuICAgICAgICBzdHIgPSBtLnByZSArICd7JyArIG0uYm9keSArIGVzY0Nsb3NlICsgbS5wb3N0O1xuICAgICAgICByZXR1cm4gZXhwYW5kKHN0cik7XG4gICAgICB9XG4gICAgICByZXR1cm4gW3N0cl07XG4gICAgfVxuXG4gICAgdmFyIG47XG4gICAgaWYgKGlzU2VxdWVuY2UpIHtcbiAgICAgIG4gPSBtLmJvZHkuc3BsaXQoL1xcLlxcLi8pO1xuICAgIH0gZWxzZSB7XG4gICAgICBuID0gcGFyc2VDb21tYVBhcnRzKG0uYm9keSk7XG4gICAgICBpZiAobi5sZW5ndGggPT09IDEpIHtcbiAgICAgICAgLy8geHt7YSxifX15ID09PiB4e2F9eSB4e2J9eVxuICAgICAgICBuID0gZXhwYW5kKG5bMF0sIGZhbHNlKS5tYXAoZW1icmFjZSk7XG4gICAgICAgIGlmIChuLmxlbmd0aCA9PT0gMSkge1xuICAgICAgICAgIHJldHVybiBwb3N0Lm1hcChmdW5jdGlvbihwKSB7XG4gICAgICAgICAgICByZXR1cm4gbS5wcmUgKyBuWzBdICsgcDtcbiAgICAgICAgICB9KTtcbiAgICAgICAgfVxuICAgICAgfVxuICAgIH1cblxuICAgIC8vIGF0IHRoaXMgcG9pbnQsIG4gaXMgdGhlIHBhcnRzLCBhbmQgd2Uga25vdyBpdCdzIG5vdCBhIGNvbW1hIHNldFxuICAgIC8vIHdpdGggYSBzaW5nbGUgZW50cnkuXG4gICAgdmFyIE47XG5cbiAgICBpZiAoaXNTZXF1ZW5jZSkge1xuICAgICAgdmFyIHggPSBudW1lcmljKG5bMF0pO1xuICAgICAgdmFyIHkgPSBudW1lcmljKG5bMV0pO1xuICAgICAgdmFyIHdpZHRoID0gTWF0aC5tYXgoblswXS5sZW5ndGgsIG5bMV0ubGVuZ3RoKVxuICAgICAgdmFyIGluY3IgPSBuLmxlbmd0aCA9PSAzXG4gICAgICAgID8gTWF0aC5hYnMobnVtZXJpYyhuWzJdKSlcbiAgICAgICAgOiAxO1xuICAgICAgdmFyIHRlc3QgPSBsdGU7XG4gICAgICB2YXIgcmV2ZXJzZSA9IHkgPCB4O1xuICAgICAgaWYgKHJldmVyc2UpIHtcbiAgICAgICAgaW5jciAqPSAtMTtcbiAgICAgICAgdGVzdCA9IGd0ZTtcbiAgICAgIH1cbiAgICAgIHZhciBwYWQgPSBuLnNvbWUoaXNQYWRkZWQpO1xuXG4gICAgICBOID0gW107XG5cbiAgICAgIGZvciAodmFyIGkgPSB4OyB0ZXN0KGksIHkpOyBpICs9IGluY3IpIHtcbiAgICAgICAgdmFyIGM7XG4gICAgICAgIGlmIChpc0FscGhhU2VxdWVuY2UpIHtcbiAgICAgICAgICBjID0gU3RyaW5nLmZyb21DaGFyQ29kZShpKTtcbiAgICAgICAgICBpZiAoYyA9PT0gJ1xcXFwnKVxuICAgICAgICAgICAgYyA9ICcnO1xuICAgICAgICB9IGVsc2Uge1xuICAgICAgICAgIGMgPSBTdHJpbmcoaSk7XG4gICAgICAgICAgaWYgKHBhZCkge1xuICAgICAgICAgICAgdmFyIG5lZWQgPSB3aWR0aCAtIGMubGVuZ3RoO1xuICAgICAgICAgICAgaWYgKG5lZWQgPiAwKSB7XG4gICAgICAgICAgICAgIHZhciB6ID0gbmV3IEFycmF5KG5lZWQgKyAxKS5qb2luKCcwJyk7XG4gICAgICAgICAgICAgIGlmIChpIDwgMClcbiAgICAgICAgICAgICAgICBjID0gJy0nICsgeiArIGMuc2xpY2UoMSk7XG4gICAgICAgICAgICAgIGVsc2VcbiAgICAgICAgICAgICAgICBjID0geiArIGM7XG4gICAgICAgICAgICB9XG4gICAgICAgICAgfVxuICAgICAgICB9XG4gICAgICAgIE4ucHVzaChjKTtcbiAgICAgIH1cbiAgICB9IGVsc2Uge1xuICAgICAgTiA9IFtdO1xuXG4gICAgICBmb3IgKHZhciBqID0gMDsgaiA8IG4ubGVuZ3RoOyBqKyspIHtcbiAgICAgICAgTi5wdXNoLmFwcGx5KE4sIGV4cGFuZChuW2pdLCBmYWxzZSkpO1xuICAgICAgfVxuICAgIH1cblxuICAgIGZvciAodmFyIGogPSAwOyBqIDwgTi5sZW5ndGg7IGorKykge1xuICAgICAgZm9yICh2YXIgayA9IDA7IGsgPCBwb3N0Lmxlbmd0aDsgaysrKSB7XG4gICAgICAgIHZhciBleHBhbnNpb24gPSBwcmUgKyBOW2pdICsgcG9zdFtrXTtcbiAgICAgICAgaWYgKCFpc1RvcCB8fCBpc1NlcXVlbmNlIHx8IGV4cGFuc2lvbilcbiAgICAgICAgICBleHBhbnNpb25zLnB1c2goZXhwYW5zaW9uKTtcbiAgICAgIH1cbiAgICB9XG4gIH1cblxuICByZXR1cm4gZXhwYW5zaW9ucztcbn1cblxuIiwibW9kdWxlLmV4cG9ydHMgPSByZXF1aXJlKFwiY2hpbGRfcHJvY2Vzc1wiKTsiLCJtb2R1bGUuZXhwb3J0cyA9IHJlcXVpcmUoXCJldmVudHNcIik7IiwibW9kdWxlLmV4cG9ydHMgPSByZXF1aXJlKFwiZnNcIik7IiwibW9kdWxlLmV4cG9ydHMgPSByZXF1aXJlKFwicGF0aFwiKTsiLCJtb2R1bGUuZXhwb3J0cyA9IHJlcXVpcmUoXCJwcm9jZXNzXCIpOyIsIi8vIFRoZSBtb2R1bGUgY2FjaGVcbnZhciBfX3dlYnBhY2tfbW9kdWxlX2NhY2hlX18gPSB7fTtcblxuLy8gVGhlIHJlcXVpcmUgZnVuY3Rpb25cbmZ1bmN0aW9uIF9fd2VicGFja19yZXF1aXJlX18obW9kdWxlSWQpIHtcblx0Ly8gQ2hlY2sgaWYgbW9kdWxlIGlzIGluIGNhY2hlXG5cdHZhciBjYWNoZWRNb2R1bGUgPSBfX3dlYnBhY2tfbW9kdWxlX2NhY2hlX19bbW9kdWxlSWRdO1xuXHRpZiAoY2FjaGVkTW9kdWxlICE9PSB1bmRlZmluZWQpIHtcblx0XHRyZXR1cm4gY2FjaGVkTW9kdWxlLmV4cG9ydHM7XG5cdH1cblx0Ly8gQ3JlYXRlIGEgbmV3IG1vZHVsZSAoYW5kIHB1dCBpdCBpbnRvIHRoZSBjYWNoZSlcblx0dmFyIG1vZHVsZSA9IF9fd2VicGFja19tb2R1bGVfY2FjaGVfX1ttb2R1bGVJZF0gPSB7XG5cdFx0Ly8gbm8gbW9kdWxlLmlkIG5lZWRlZFxuXHRcdC8vIG5vIG1vZHVsZS5sb2FkZWQgbmVlZGVkXG5cdFx0ZXhwb3J0czoge31cblx0fTtcblxuXHQvLyBFeGVjdXRlIHRoZSBtb2R1bGUgZnVuY3Rpb25cblx0X193ZWJwYWNrX21vZHVsZXNfX1ttb2R1bGVJZF0uY2FsbChtb2R1bGUuZXhwb3J0cywgbW9kdWxlLCBtb2R1bGUuZXhwb3J0cywgX193ZWJwYWNrX3JlcXVpcmVfXyk7XG5cblx0Ly8gUmV0dXJuIHRoZSBleHBvcnRzIG9mIHRoZSBtb2R1bGVcblx0cmV0dXJuIG1vZHVsZS5leHBvcnRzO1xufVxuXG4iLCIjIS91c3IvYmluL2VudiBub2RlXG5cbi8qXG4gKiBDb3B5cmlnaHQgKGMpIDIwMjQgSHVhd2VpIERldmljZSBDby4sIEx0ZC5cbiAqIExpY2Vuc2VkIHVuZGVyIHRoZSBBcGFjaGUgTGljZW5zZSwgVmVyc2lvbiAyLjAgKHRoZSBcIkxpY2Vuc2VcIik7XG4gKiB5b3UgbWF5IG5vdCB1c2UgdGhpcyBmaWxlIGV4Y2VwdCBpbiBjb21wbGlhbmNlIHdpdGggdGhlIExpY2Vuc2UuXG4gKiBZb3UgbWF5IG9idGFpbiBhIGNvcHkgb2YgdGhlIExpY2Vuc2UgYXRcbiAqXG4gKiBodHRwOi8vd3d3LmFwYWNoZS5vcmcvbGljZW5zZXMvTElDRU5TRS0yLjBcbiAqXG4gKiBVbmxlc3MgcmVxdWlyZWQgYnkgYXBwbGljYWJsZSBsYXcgb3IgYWdyZWVkIHRvIGluIHdyaXRpbmcsIHNvZnR3YXJlXG4gKiBkaXN0cmlidXRlZCB1bmRlciB0aGUgTGljZW5zZSBpcyBkaXN0cmlidXRlZCBvbiBhbiBcIkFTIElTXCIgQkFTSVMsXG4gKiBXSVRIT1VUIFdBUlJBTlRJRVMgT1IgQ09ORElUSU9OUyBPRiBBTlkgS0lORCwgZWl0aGVyIGV4cHJlc3Mgb3IgaW1wbGllZC5cbiAqIFNlZSB0aGUgTGljZW5zZSBmb3IgdGhlIHNwZWNpZmljIGxhbmd1YWdlIGdvdmVybmluZyBwZXJtaXNzaW9ucyBhbmRcbiAqIGxpbWl0YXRpb25zIHVuZGVyIHRoZSBMaWNlbnNlLlxuICovXG5cbmltcG9ydCB7IHByb2dyYW0gfSBmcm9tIFwiY29tbWFuZGVyXCJcbmltcG9ydCAqIGFzIGZzIGZyb20gXCJmc1wiXG5pbXBvcnQgKiBhcyBwYXRoIGZyb20gXCJwYXRoXCJcbmltcG9ydCAqIGFzIGNoaWxkX3Byb2Nlc3MgZnJvbSBcImNoaWxkX3Byb2Nlc3NcIlxuaW1wb3J0IHsgbWluaW1hdGNoIH0gZnJvbSAnbWluaW1hdGNoJ1xuXG5jb25zdCByZWFkZGlyU3luY1JlY3Vyc2l2ZTogKGRpcjogc3RyaW5nKSA9PiBzdHJpbmdbXSA9IChkaXI6IHN0cmluZykgPT5cbiAgICBmcy5yZWFkZGlyU3luYyhkaXIpLnJlZHVjZSgoZmlsZXM6IHN0cmluZ1tdLCBmaWxlOiBzdHJpbmcpID0+IHtcbiAgICAgICAgY29uc3QgbmFtZSA9IHBhdGguam9pbihkaXIsIGZpbGUpXG4gICAgICAgIHJldHVybiBmcy5sc3RhdFN5bmMobmFtZSkuaXNEaXJlY3RvcnkoKSA/IFsuLi5maWxlcywgLi4ucmVhZGRpclN5bmNSZWN1cnNpdmUobmFtZSldIDogWy4uLmZpbGVzLCBuYW1lXVxuICAgIH0sIFtdKVxuXG5jb25zdCBvcHRpb25zID0gcHJvZ3JhbVxuICAgIC5vcHRpb24oJy0taW5wdXQtZmlsZXMgPHBhdGg+JywgJ1BhdGggdG8gaW5wdXQgZmlsZShzKSwgY29tbWEgc2VwYXJhdGVkJylcbiAgICAub3B0aW9uKCctLW91dHB1dC1kaXIgPHBhdGg+JywgJ1BhdGggdG8gb3V0cHV0IGRpcicpXG4gICAgLm9wdGlvbignLS1jb21waWxlciA8cGF0aD4nLCAnUGF0aCB0byBjb21waWxlcicpXG4gICAgLm9wdGlvbignLS1saW5rLW5hbWUgPHBhdGg+JywgJ05hbWUgb2YgY29tYmluZWQgbGluay1uYW1lLmFiYycsIFwiYWxsXCIpXG4gICAgLm9wdGlvbignLS10YXJnZXQgPG5pbmphfG1ha2U+JywgJ1RhcmdldCBidWlsZCBzeXN0ZW0nLCBcIm5pbmphXCIpXG4gICAgLm9wdGlvbignLS1maWxlLW9wdGlvbicsICdXaGVuIHByb3ZpZGVkIHBhc3MgdGhlIHNvdXJjZSBhcyAtLWZpbGUgPHBhdGg+IHJhdGhlciB0aGFuIGEgZnJlZSBvcHRpb24nKVxuICAgIC5vcHRpb24oJy0tYW90LWxpYnMgPGxpYnM+JywgJ0NvbW1hLXNlcGFyYXRlZCBBT1QgbGlicmFyaWVzIHRvIGluY2x1ZGUnKVxuICAgIC5vcHRpb24oJy0tb25seS1hb3QgPGZpbGU+JywgJ0FPVCBhbiAuYWJjIHRha2luZyAtLWFvdC1saWJzIGludG8gYWNjb3VudCcpXG4gICAgLm9wdGlvbignLS1hb3QtdGFyZ2V0IDxhcm18YXJtNjR8eDg2fHg4Nl82ND4nLCAnQ29tcGlsYXRpb24gdGFyZ2V0IGZvciBBT1QnKVxuXG4gICAgLnBhcnNlKClcbiAgICAub3B0cygpXG5cbmlmIChvcHRpb25zLm9ubHlBb3QpXG4gICAgbWFpbkFvdChwYXRoLnJlc29sdmUob3B0aW9ucy5vbmx5QW90KSlcbmVsc2VcbiAgICBtYWluKG9wdGlvbnMuaW5wdXRGaWxlcywgcGF0aC5yZXNvbHZlKG9wdGlvbnMub3V0cHV0RGlyKSwgb3B0aW9ucy5saW5rTmFtZSwgb3B0aW9ucy50YXJnZXQpXG5cbmZ1bmN0aW9uIGZpbmRNYXRjaGluZyhiYXNlOiBzdHJpbmcsIGluY2x1ZGU6IHN0cmluZ1tdLCBleGNsdWRlOiBzdHJpbmdbXSk6IHN0cmluZ1tdIHtcbiAgICByZXR1cm4gcmVhZGRpclN5bmNSZWN1cnNpdmUoYmFzZSlcbiAgICAgICAgLm1hcChpdCA9PiBwYXRoLnJlc29sdmUoaXQpKVxuICAgICAgICAuZmlsdGVyKGl0ID0+IGluY2x1ZGUuc29tZSh2YWx1ZSA9PiBtaW5pbWF0Y2goaXQsIHBhdGguam9pbihiYXNlLCB2YWx1ZSksIHttYXRjaEJhc2U6IHRydWV9KSkpXG4gICAgICAgIC5maWx0ZXIoaXQgPT4gIWV4Y2x1ZGUuc29tZSh2YWx1ZSA9PiBtaW5pbWF0Y2goaXQsIHBhdGguam9pbihiYXNlLCB2YWx1ZSksIHttYXRjaEJhc2U6IHRydWV9KSkpXG59XG5cbmZ1bmN0aW9uIHByb2R1Y2VQYWlycyhmaWxlczogc3RyaW5nW10sXG4gICAgICAgICAgICAgICAgICAgICAgYmFzZURpcjogc3RyaW5nLFxuICAgICAgICAgICAgICAgICAgICAgIHJvb3REaXI6IHN0cmluZyB8IHVuZGVmaW5lZCxcbiAgICAgICAgICAgICAgICAgICAgICBidWlsZERpcjogc3RyaW5nIHwgdW5kZWZpbmVkKTogeyBpbnB1dDogc3RyaW5nLCBvdXRwdXQ6IHN0cmluZyB9W10ge1xuICAgIHJldHVybiBmaWxlcy5tYXAoc3JjRmlsZSA9PiB7XG4gICAgICAgIGNvbnN0IGZpbGVCdWlsZERpciA9IGJ1aWxkRGlyXG4gICAgICAgICAgICA/IHBhdGguam9pbihidWlsZERpciwgcGF0aC5yZWxhdGl2ZShyb290RGlyID8/IGJhc2VEaXIsIHBhdGguZGlybmFtZShzcmNGaWxlKSkpXG4gICAgICAgICAgICA6IHBhdGguZGlybmFtZShzcmNGaWxlKVxuICAgICAgICBmcy5ta2RpclN5bmMoZmlsZUJ1aWxkRGlyLCB7cmVjdXJzaXZlOiB0cnVlfSlcbiAgICAgICAgcmV0dXJuIHtcbiAgICAgICAgICAgIGlucHV0OiBzcmNGaWxlLFxuICAgICAgICAgICAgb3V0cHV0OiBgJHtwYXRoLmpvaW4oZmlsZUJ1aWxkRGlyLCBwYXRoLmJhc2VuYW1lKHNyY0ZpbGUpLnJlcGxhY2UocGF0aC5leHRuYW1lKHNyY0ZpbGUpLCBcIi5hYmNcIikpfWBcbiAgICAgICAgfVxuICAgIH0pXG59XG5cbmZ1bmN0aW9uIGFyY2hEaXIoKTogc3RyaW5nIHtcbiAgICBjb25zdCBhcmNoID0gcHJvY2Vzcy5hcmNoXG4gICAgbGV0IHNka0FyY2ggPSBcIlwiO1xuICAgIHN3aXRjaCAoYXJjaCkge1xuICAgICAgICBjYXNlIFwieDY0XCI6XG4gICAgICAgICAgICBzZGtBcmNoID0gXCJcIlxuICAgICAgICAgICAgYnJlYWtcbiAgICAgICAgY2FzZSBcImFybTY0XCI6XG4gICAgICAgICAgICBzZGtBcmNoID0gXCJhcm02NFwiXG4gICAgICAgICAgICBicmVha1xuICAgICAgICBkZWZhdWx0OiB0aHJvdyBuZXcgRXJyb3IoYFVuZXhwZWN0ZWQgYXJjaDogJHthcmNofWApXG5cbiAgICB9XG4gICAgY29uc3QgcGxhdGZvcm0gPSBwcm9jZXNzLnBsYXRmb3JtXG4gICAgbGV0IHNka1BsYXRmb3JtID0gXCJcIlxuICAgIHN3aXRjaCAocGxhdGZvcm0pIHtcbiAgICAgICAgY2FzZSBcImxpbnV4XCI6IHNka1BsYXRmb3JtID0gXCJsaW51eFwiXG4gICAgICAgICAgICBicmVha1xuICAgICAgICBjYXNlIFwid2luMzJcIjogc2RrUGxhdGZvcm0gPSBcIndpbmRvd3NcIlxuICAgICAgICAgICAgYnJlYWtcbiAgICAgICAgY2FzZSBcImRhcndpblwiOiBzZGtQbGF0Zm9ybSA9IFwibWFjb3NcIlxuICAgICAgICAgICAgYnJlYWtcbiAgICAgICAgZGVmYXVsdDogdGhyb3cgbmV3IEVycm9yKGBVbnN1cHBvcnRlZCBwbGF0Zm9ybSAke3BsYXRmb3JtfWApXG4gICAgfVxuICAgIGNvbnN0IHN1ZmZpeCA9IFwiaG9zdF90b29sc1wiXG4gICAgcmV0dXJuIFtzZGtQbGF0Zm9ybSwgc2RrQXJjaCwgc3VmZml4XS5maWx0ZXIoaXQgPT4gaXQgIT0gXCJcIikuam9pbihcIl9cIilcbn1cblxuZnVuY3Rpb24gcHJvZHVjZU1ha2VmaWxlKGNvbXBpbGVyOiBzdHJpbmcsXG4gICAgICAgICAgICAgICAgICAgICAgICAgZmlsZXM6IHtpbnB1dDogc3RyaW5nLCBvdXRwdXQ6IHN0cmluZ31bXSxcbiAgICAgICAgICAgICAgICAgICAgICAgICBvdXRwdXREaXI6IHN0cmluZyxcbiAgICAgICAgICAgICAgICAgICAgICAgICBjb25maWc6IHN0cmluZyxcbiAgICAgICAgICAgICAgICAgICAgICAgICBsaW5rTmFtZTogc3RyaW5nKTogc3RyaW5nIHtcbiAgICBsZXQgcmVzdWx0OiBzdHJpbmdbXSA9IFtdXG4gICAgbGV0IGFsbDogc3RyaW5nW10gPSBbXVxuICAgIHJlc3VsdC5wdXNoKFwiZGVmYXVsdDogYWxsXCIpXG4gICAgbGV0IGJhc2VuYW1lID0gcGF0aC5iYXNlbmFtZShjb21waWxlcilcbiAgICBsZXQgbGlua2VyID0gY29tcGlsZXIucmVwbGFjZShiYXNlbmFtZSwgJ2Fya2xpbmsnKVxuXG4gICAgZmlsZXMuZm9yRWFjaChpdCA9PiB7XG4gICAgICAgIGFsbC5wdXNoKGl0Lm91dHB1dClcbiAgICAgICAgcmVzdWx0LnB1c2goYCR7aXQub3V0cHV0fTogJHtpdC5pbnB1dH1gKVxuICAgICAgICByZXN1bHQucHVzaChgXFx0JHtjb21waWxlcn0gLS1ldHMtbW9kdWxlIC0tYXJrdHNjb25maWcgJHtwYXRoLnJlc29sdmUoY29uZmlnKX0gJHtvcHRpb25zLmZpbGVPcHRpb24gPyBcIi0tZmlsZVwiIDogXCJcIn0gJHtpdC5pbnB1dH0gLS1vdXRwdXQgJHtpdC5vdXRwdXR9YClcbiAgICB9KVxuICAgIHJlc3VsdC5wdXNoKGBjb21waWxlOiAke2FsbC5qb2luKCcgJyl9YClcbiAgICByZXN1bHQucHVzaChgbGluazogY29tcGlsZWApXG4gICAgcmVzdWx0LnB1c2goYFxcdCR7bGlua2VyfSAtLW91dHB1dCAke291dHB1dERpcn0vJHtsaW5rTmFtZX0uYWJjIC0tICR7YWxsLmpvaW4oJyAnKX1gKVxuICAgIHJlc3VsdC5wdXNoKGBhbGw6IGxpbmtgKVxuICAgIHJldHVybiByZXN1bHQuam9pbignXFxuJylcbn1cblxuZnVuY3Rpb24gcHJvZHVjZU5pbmphZmlsZShjb21waWxlcjogc3RyaW5nLFxuICAgICAgICAgICAgICAgICAgICAgICAgICBmaWxlczoge2lucHV0OiBzdHJpbmcsIG91dHB1dDogc3RyaW5nfVtdLFxuICAgICAgICAgICAgICAgICAgICAgICAgICBvdXRwdXREaXI6IHN0cmluZyxcbiAgICAgICAgICAgICAgICAgICAgICAgICAgY29uZmlnOiBzdHJpbmcsXG4gICAgICAgICAgICAgICAgICAgICAgICAgIGxpbmtOYW1lOiBzdHJpbmdcbiAgICAgICAgICAgICAgICAgICAgICAgICk6IHN0cmluZyB7XG4gICAgLy8gV2UgaGF2ZSBubyBQYW5kYSBTREsgZm9yIG1hY09TLlxuICAgIGNvbnN0IHRvb2xzX3ByZWZpeCA9ICBwcm9jZXNzLnBsYXRmb3JtID09IFwiZGFyd2luXCIgPyBcImVjaG8gXCIgOiBcIlwiXG4gICAgbGV0IHJlc3VsdDogc3RyaW5nW10gPSBbXVxuICAgIGxldCBhbGw6IHN0cmluZ1tdID0gW11cbiAgICBsZXQgYmFzZW5hbWUgPSBwYXRoLmJhc2VuYW1lKGNvbXBpbGVyKVxuICAgIGxldCBsaW5rZXIgPSBjb21waWxlci5yZXBsYWNlKGJhc2VuYW1lLCAnYXJrbGluaycpXG4gICAgY29uc3QgZ3JvdXBTaXplID0gMTAwO1xuXG4gICAgbGV0IHByZWZpeCA9IGBcbnJ1bGUgYXJrdHNfY29tcGlsZXJcbiAgICBjb21tYW5kID0gJHt0b29sc19wcmVmaXh9JHtjb21waWxlcn0gLS1ldHMtbW9kdWxlIC0tYXJrdHNjb25maWcgJHtwYXRoLnJlc29sdmUoY29uZmlnKX0gJHtvcHRpb25zLmZpbGVPcHRpb24gPyBcIi0tZmlsZVwiIDogXCJcIn0gJGluIC0tb3V0cHV0ICRvdXRcbiAgICBkZXNjcmlwdGlvbiA9IFwiQ29tcGlsaW5nIEFSS1RTICRvdXRcIlxucnVsZSBhcmt0c19saW5rZXJcbiAgICBjb21tYW5kID0gJHt0b29sc19wcmVmaXh9JHtsaW5rZXJ9IC0tb3V0cHV0ICRvdXQgLS0gJGluXG4gICAgZGVzY3JpcHRpb24gPSBcIkxpbmtpbmcgQVJLVFMgJG91dFwiYFxuICAgIGZpbGVzLmZvckVhY2goaXQgPT4ge1xuICAgICAgICBhbGwucHVzaChpdC5vdXRwdXQpXG4gICAgICAgIHJlc3VsdC5wdXNoKGBidWlsZCAke2l0Lm91dHB1dH06IGFya3RzX2NvbXBpbGVyICR7aXQuaW5wdXR9XFxuYClcbiAgICB9KVxuICAgIHJlc3VsdC5wdXNoKGBidWlsZCBjb21waWxlOiBwaG9ueSAke2FsbC5qb2luKCcgJyl9YClcblxuICAgIGlmIChhbGwubGVuZ3RoIDw9IGdyb3VwU2l6ZSkge1xuICAgICAgICByZXN1bHQucHVzaChgYnVpbGQgJHtvdXRwdXREaXJ9LyR7bGlua05hbWV9LmFiYzogYXJrdHNfbGlua2VyICR7YWxsLmpvaW4oJyAnKX1cXG5gKVxuICAgIH0gZWxzZSB7XG4gICAgICAgIC8vIElmIHRvbyBtdWNoIGZpbGUsIGRpdmlkZSBpbnRvIGdyb3VwcyBhdm9pZCAncG9zaXhfc3Bhd246IEFyZ3VtZW50IGxpc3QgdG9vIGxvbmcnIGlzc3VlXG4gICAgICAgIGNvbnN0IGFsbFBhcnRzID0gW11cblxuICAgICAgICBmb3IgKGxldCBpID0gMDsgaSA8IGFsbC5sZW5ndGg7IGkgKz0gZ3JvdXBTaXplKSB7XG4gICAgICAgICAgICBjb25zdCBiYXRjaCA9IGFsbC5zbGljZShpLCBpICsgZ3JvdXBTaXplKVxuICAgICAgICAgICAgY29uc3QgcGFydE5hbWU6c3RyaW5nID0gYCR7b3V0cHV0RGlyfS8ke2xpbmtOYW1lfS5wYXJ0JHthbGxQYXJ0cy5sZW5ndGggKyAxfS5hYmNgXG4gICAgICAgICAgICBhbGxQYXJ0cy5wdXNoKHBhcnROYW1lKTtcblxuICAgICAgICAgICAgcmVzdWx0LnB1c2goYGJ1aWxkICR7cGFydE5hbWV9OiBhcmt0c19saW5rZXIgJHtiYXRjaC5qb2luKCcgJyl9XFxuYClcbiAgICAgICAgfVxuICAgICAgICByZXN1bHQucHVzaChgYnVpbGQgJHtvdXRwdXREaXJ9LyR7bGlua05hbWV9LmFiYzogYXJrdHNfbGlua2VyICR7YWxsUGFydHMuam9pbignICcpfWApXG4gICAgfVxuXG4gICAgcmVzdWx0LnB1c2goYGJ1aWxkIGxpbms6IHBob255ICR7b3V0cHV0RGlyfS8ke2xpbmtOYW1lfS5hYmNgKVxuICAgIHJlc3VsdC5wdXNoKGBidWlsZCBhbGw6IHBob255IGxpbmtgKVxuICAgIHJlc3VsdC5wdXNoKFwiZGVmYXVsdCBhbGxcXG5cIilcbiAgICByZXR1cm4gcHJlZml4ICsgJ1xcbicgKyByZXN1bHQuam9pbignXFxuJylcbn1cblxuZnVuY3Rpb24gbWFpbihpbnB1dEZpbGU6IHN0cmluZywgb3V0cHV0RGlyOiBzdHJpbmcsIGxpbmtOYW1lOiBzdHJpbmcsIHRhcmdldDogc3RyaW5nKSB7XG4gICAgbGV0IGNvbmZpZyA9IEpTT04ucGFyc2UoZnMucmVhZEZpbGVTeW5jKGlucHV0RmlsZSwgJ3V0ZjgnKSlcbiAgICBsZXQgYmFzZURpciA9IHBhdGgucmVzb2x2ZShwYXRoLmRpcm5hbWUoaW5wdXRGaWxlKSlcbiAgICBsZXQgaW5jbHVkZSA9IChjb25maWcuaW5jbHVkZSBhcyBzdHJpbmdbXSkubWFwKGl0ID0+IGl0LnJlcGxhY2UoJ1xcXFwuJywgJy4nKSlcbiAgICBsZXQgZXhjbHVkZSA9IGNvbmZpZy5leGNsdWRlID8gKGNvbmZpZy5leGNsdWRlIGFzIHN0cmluZ1tdKS5tYXAoaXQgPT4gaXQucmVwbGFjZSgnXFxcXC4nLCAnLicpKSA6IFtdXG4gICAgY29uc3QgYnVpbGREaXIgPSBjb25maWcuY29tcGlsZXJPcHRpb25zLm91dERpciA/IChwYXRoLnJlc29sdmUoY29uZmlnLmNvbXBpbGVyT3B0aW9ucy5vdXREaXIpKSA6IHVuZGVmaW5lZFxuICAgIGNvbnN0IHJvb3REaXIgPSBjb25maWcuY29tcGlsZXJPcHRpb25zLnJvb3REaXIgPyAocGF0aC5yZXNvbHZlKGNvbmZpZy5jb21waWxlck9wdGlvbnMucm9vdERpcikpIDogdW5kZWZpbmVkXG4gICAgY29uc3QgZmlsZXMgPSBwcm9kdWNlUGFpcnMoZmluZE1hdGNoaW5nKGJhc2VEaXIsIGluY2x1ZGUsIGV4Y2x1ZGUpLCBiYXNlRGlyLCByb290RGlyLCBidWlsZERpcilcbiAgICBpZiAoZmlsZXMubGVuZ3RoID09IDApIHtcbiAgICAgICAgdGhyb3cgbmV3IEVycm9yKGBObyBmaWxlcyBtYXRjaGluZyBpbmNsdWRlIFwiJHtpbmNsdWRlLmpvaW4oXCIsXCIpfVwiIGV4Y2x1ZGUgXCIke2V4Y2x1ZGUuam9pbihcIixcIil9XCJgKVxuICAgIH1cbiAgICBmcy5ta2RpclN5bmMob3V0cHV0RGlyLCB7IHJlY3Vyc2l2ZTogdHJ1ZSB9KVxuICAgIGlmICh0YXJnZXQgPT0gJ21ha2UnKSB7XG4gICAgICAgIGxldCBtYWtlciA9IHByb2R1Y2VNYWtlZmlsZShwYXRoLnJlc29sdmUob3B0aW9ucy5jb21waWxlciksIGZpbGVzLCBvdXRwdXREaXIsIGlucHV0RmlsZSwgbGlua05hbWUpXG4gICAgICAgIGZzLndyaXRlRmlsZVN5bmMoYCR7b3V0cHV0RGlyfS9NYWtlZmlsZWAsIG1ha2VyKVxuICAgIH0gZWxzZSB7XG4gICAgICAgIGxldCBuaW5qYSA9IHByb2R1Y2VOaW5qYWZpbGUocGF0aC5yZXNvbHZlKG9wdGlvbnMuY29tcGlsZXIpLCBmaWxlcywgb3V0cHV0RGlyLCBpbnB1dEZpbGUsIGxpbmtOYW1lKVxuICAgICAgICBmcy53cml0ZUZpbGVTeW5jKGAke291dHB1dERpcn0vYnVpbGQubmluamFgLCBuaW5qYSlcbiAgICB9XG59XG5cbmZ1bmN0aW9uIG1haW5Bb3QoYWJjOiBzdHJpbmcpIHtcbiAgICBsZXQgc2RrID0gb3B0aW9ucy5zZGsgPz8gcGF0aC5yZXNvbHZlKHBhdGguam9pbihfX2Rpcm5hbWUsICcuLicsICcuLicsICdwYW5kYScsICdub2RlX21vZHVsZXMnLCAnQHBhbmRhJywgJ3NkaycpKVxuICAgIGxldCBhb3QgPSBwYXRoLmpvaW4oc2RrLCBhcmNoRGlyKCksICdiaW4nLCAnYXJrX2FvdCcpXG4gICAgbGV0IHN0ZGxpYiA9IHBhdGgucmVzb2x2ZShwYXRoLmpvaW4oc2RrLCBcImV0c1wiLCBcImV0c3N0ZGxpYi5hYmNcIikpXG4gICAgY29uc3QgYW90TGlicyA9IGFiYy5pbmRleE9mKFwiZXRzc3RkbGliXCIpID09IC0xID8gW3N0ZGxpYl0gOiBbXVxuICAgIGlmIChvcHRpb25zLmFvdExpYnMpIGFvdExpYnMucHVzaCguLi4gb3B0aW9ucy5hb3RMaWJzLnNwbGl0KFwiLFwiKSlcbiAgICBsZXQgYXJnczogc3RyaW5nW10gPSBbXVxuICAgIGlmIChwcm9jZXNzLnBsYXRmb3JtID09IFwiZGFyd2luXCIpIHtcbiAgICAgICAgLy8gTm8gdG9vbHMgb24gbWFjT1MsIGp1c3QgZWNob1xuICAgICAgICBhcmdzLnB1c2goYW90KVxuICAgICAgICBhb3QgPSBcImVjaG9cIlxuICAgIH1cbiAgICBsZXQgZGlyID0gb3B0aW9ucy5vdXRwdXREaXIgPz8gcGF0aC5kaXJuYW1lKGFiYylcbiAgICBsZXQgcmVzdWx0ID0gcGF0aC5qb2luKGRpciwgcGF0aC5iYXNlbmFtZShhYmMpLnJlcGxhY2UoJy5hYmMnLCAnLmFuJykpXG4gICAgYXJncy5wdXNoKC4uLiBvcHRpb25zLmFvdFRhcmdldCA/IFtgLS1jb21waWxlci1jcm9zcy1hcmNoPSR7b3B0aW9ucy5hb3RUYXJnZXR9YF0gOiBbXSlcbiAgICBhcmdzLnB1c2goLi4uIFtcbiAgICAgICAgYC0tbG9hZC1ydW50aW1lcz1ldHNgLFxuICAgICAgICBgLS1ib290LXBhbmRhLWZpbGVzPSR7YW90TGlicy5tYXAoaXQgPT4gcGF0aC5yZXNvbHZlKGl0KSkuY29uY2F0KGFiYykuam9pbignOicpfWAsXG4gICAgICAgIGAtLXBhb2MtcGFuZGEtZmlsZXM9JHthYmN9YCxcbiAgICAgICAgYC0tcGFvYy1vdXRwdXQ9JHtyZXN1bHR9YFxuICAgIF0pXG4gICAgY29uc29sZS5sb2coYEFPVCBjb21waWxlICR7YWJjfSB0byAke3Jlc3VsdH0uLi5gKVxuICAgIGNvbnNvbGUubG9nKGBMYXVuY2ggJHthb3R9ICR7YXJncy5qb2luKFwiIFwiKX1gKVxuICAgIGNvbnN0IGNoaWxkID0gY2hpbGRfcHJvY2Vzcy5zcGF3bihhb3QsIGFyZ3MpXG4gICAgY2hpbGQuc3Rkb3V0Lm9uKCdkYXRhJywgKGRhdGEpID0+IHtcbiAgICAgICAgcHJvY2Vzcy5zdGRvdXQud3JpdGUoZGF0YSk7XG4gICAgfSlcbiAgICBjaGlsZC5zdGRlcnIub24oJ2RhdGEnLCAoZGF0YSkgPT4ge1xuICAgICAgICBwcm9jZXNzLnN0ZGVyci53cml0ZShkYXRhKTtcbiAgICB9KVxuICAgIGNoaWxkLm9uKCdjbG9zZScsIChjb2RlKSA9PiB7XG4gICAgICAgIGlmIChjb2RlICE9IDApXG4gICAgICAgICAgICBjb25zb2xlLmxvZyhgQ29tbWFuZCAke2FvdH0gJHthcmdzLmpvaW4oXCIgXCIpfSBmYWlsZWQgd2l0aCByZXR1cm4gY29kZSAke2NvZGV9YClcbiAgICAgICAgZWxzZVxuICAgICAgICAgICAgY29uc29sZS5sb2coYFByb2R1Y2VkIEFPVCBmaWxlICR7cmVzdWx0fTogJHtNYXRoLnJvdW5kKGZzLnN0YXRTeW5jKHJlc3VsdCkuc2l6ZSAvIDEwMjQgLyAxMDI0KX1NYClcbiAgICAgICAgcHJvY2Vzcy5leGl0KGNvZGUgPz8gdW5kZWZpbmVkKVxuICAgIH0pXG4gICAgY2hpbGQub24oJ2V4aXQnLCAoY29kZSwgc2lnbmFsKSA9PiB7XG4gICAgICAgIGlmIChzaWduYWwpIHtcbiAgICAgICAgICAgIGNvbnNvbGUubG9nKGBSZWNlaXZlZCBzaWduYWw6ICR7c2lnbmFsfSBmcm9tICcke2FvdH0gJHthcmdzLmpvaW4oJyAnKX0nYClcbiAgICAgICAgICAgIHByb2Nlc3MuZXhpdCgxKVxuICAgICAgICB9XG4gICAgfSlcbn1cbiJdLCJuYW1lcyI6W10sInNvdXJjZVJvb3QiOiIifQ==