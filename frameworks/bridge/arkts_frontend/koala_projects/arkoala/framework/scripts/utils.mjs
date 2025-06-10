import fs from "fs"
import { exit } from "process"
import { spawnSync } from "child_process"
import chalk from "chalk"
import path from "path"
import url from "url"

const __dirname = path.dirname(url.fileURLToPath(import.meta.url));

class Version {
    constructor(version) {
        let [major, minor, patch] = version.split(/\./).map(x => +x);
        this.major = major;
        this.minor = minor;
        this.patch = patch;
    }

    toString() {
        return `${this.major}.${this.minor}.${this.patch}`;
    }
}

export function toIniValue(value) {
    if (typeof value == "string") {
        value = value.replace("'", "\\'");
        return `'${value}'`;
    } else if (Array.isArray(value)) {
        let res = ''
        for (let i in value) {
            res += toIniValue(value[i]) + (i < value.length - 1 ? ', ' : '')
        }
        return '[' + res + ']';
    } else {
        return value.toString();
    }
}


export function CrossFile(target, root = path.join(__dirname, '..')) {
    let filename = target + '.ini';
    let filepath = path.join(root, filename);

    let lines = []
    return {
        section(name, values) {
            lines.push(`\n[${name}]\n`);
            if (values) {
                for (let prop in values) {
                    if (values.hasOwnProperty(prop)) {
                        this.property(prop, values[prop]);
                    }
                }
            }
            return this;
        },
        property(name, value) {
            value = toIniValue(value);
            lines.push(`${name} = ${value}\n`);
            return this;
        },
        close() {
            fs.writeFileSync(filepath, lines.join(''));
        },
        get path() {
            return filepath;
        }
    }
}

class Meson {
    #version;

    constructor(version) {
        this.#version = new Version(version);
    }

    get version() {
        return this.#version;
    }

    configure(options) {
        let builddir = options.builddir;
        let crossFiles = options.crossFiles || [];
        let defs = options.options || {};
        let dryRun = options.dryRun || false;

        let args = ["setup", builddir];
        if (options.prefix) {
            args.push("--prefix", options.prefix);
        }
        if (options.binDir) {
            args.push("--bindir", options.binDir);
        }
        if (options.libDir) {
            args.push("--libdir", options.libDir);
        }
        for (const file of crossFiles) {
            args.push("--cross-file", file);
        }
        for (const def in defs) {
            let value = defs[def];
            if (defs.hasOwnProperty(def) && value != null) {
                args.push(`-D${def}=${value}`);
            }
        }
        if (options.wipe) {
            args.push("--wipe");
        }
        if (options.reconfigure) {
            args.push("--reconfigure");
        }
        if (options.vsenv) {
            // Force MSVC instead of clang
            args.push("--vsenv");
        }
        if (options.vm_kind) {
            args.push(`-Dvm_kind=${options.vm_kind}`);
        }
        console.log(`> meson ${args.join(' ')}`);
        if (!dryRun) {
            let stdio = options.verbose ? ['inherit', 'inherit', 'inherit'] : void 0;
            let env = process.env
            let meson = spawnSync("meson", args, { encoding: "utf8", stdio, env });
            if (meson.status != 0) {
                throw new Error("failed to configure");
            }
        }
    }
}

export function findMeson() {
    try {
        let version = spawnSync("meson", ["-v"], { encoding: "utf8" }).output.join('').trim();
        console.log("Meson: " + chalk.green(version));
        return new Meson(version);
    } catch (err) {
        console.log("Meson: " + chalk.red("NOT FOUND"));
        exit(1);
    }
}

export function findNinja() {
    try {
        let version = spawnSync("ninja", ["--version"], { encoding: "utf8" }).output.join('').trim();
        console.log("Ninja: " + chalk.green(version));
        return { version: new Version(version) };
    } catch (err) {
        console.log("Ninja: " + chalk.red("NOT FOUND"));
        exit(1);
    }
}

export function findPython() {
    try {
        let version = spawnSync("python3", ["--version"], { encoding: "utf8" }).output.join('').trim();
        version = version.replace(/^Python\s*/i, "");
        console.log("Python: " + chalk.green(version));
        return { version: new Version(version) };
    } catch (err) {
        console.log("Python: " + chalk.red("NOT FOUND"));
        exit(1);
    }
}

export function requireEnv(name, description) {
    let value = process.env[name];
    if (value) {
        console.log(`${name}: ${chalk.green(value)}`);
        return value;
    } else {
        console.log(name + ": " + chalk.red("not found") + "\r\n" +
            chalk.gray(`  set environment variable ${name}=<${description}>`));
        exit(1);
    }
}

export function relativeToSourceRoot(abspath) {
    let sourceRoot = path.resolve(__dirname, "..");
    return path.relative(sourceRoot, abspath);
}

export function sourceRoot() {
    return path.resolve(__dirname, "..");
}

class CMake {
    #version;

    constructor(version) {
        this.#version = new Version(version);
    }

    get version() {
        return this.#version;
    }

    configure(options) {
        let builddir = options.builddir;
        let srcdir = options.srcdir
        let defs = options.defs;
        let dryRun = options.dryRun || false;

        let args = ['-GNinja', `-S${srcdir}`, `-B${builddir}`];
        for (const def in defs) {
            let value = defs[def];
            if (defs.hasOwnProperty(def) && value != null) {
                args.push(`-D${def}=${value}`);
            }
        }
        console.log(`> cmake ${args.join(' ')}`);
        if (!dryRun) {
            let stdio = options.verbose ? ['inherit', 'inherit', 'inherit'] : void 0;
            let cmake = spawnSync("cmake", args, {
                encoding: "utf8",
                stdio
            });
            if (cmake.status != 0) {
                throw new Error("failed to configure");
            }
        }
    }
}

export function findCmake() {
    try {
        let version = spawnSync("cmake", ["--version"], { encoding: "utf8" }).output.join('').trim();
        console.log("CMake: " + chalk.green(version));
        return new CMake(version);
    } catch (err) {
        console.log("CMake: " + chalk.red("NOT FOUND"));
        exit(1);
    }
}
