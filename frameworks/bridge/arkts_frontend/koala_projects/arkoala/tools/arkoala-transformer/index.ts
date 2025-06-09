import memoPlugin from "@koalaui/compiler-plugin";
import { makeEtsExpander } from "@koalaui/ets-plugin";
import type * as ts from "@koalaui/ets-tsc"
import * as fs from "fs"
import * as path from "path"

import chalk from "chalk"

let debugOutput = console.debug
const debug = (...args) => debugOutput(`[${chalk.bold.blue("DEBUG")}]`, ...args)

if (process.env.CREATED_BY == 'deveco') {
    chalk.level = 2 // Force colors for DevEco build output (TODO: better way to run)
}
if (process.env.ARKOALA_PLUGIN_LOG) {
    chalk.level = 0;
    let out = fs.createWriteStream(process.env.ARKOALA_PLUGIN_LOG, {
        highWaterMark: 1,
        encoding: "utf-8"
    })
    debugOutput = (...args) => {
        out.cork()
        for (const arg of args) {
            out.write(arg)
            out.write(" ")
        }
        out.write("\n")
        process.nextTick(() => out.uncork())
    }
}

const DISABLE_CACHE = true /* Disabled because of possiblity of uncompiled sources in result, need to investigate */ // 'ARKOALA_NO_CACHE' in process.env;

type CacheMap = Map<string, ts.SourceFile>; 
type CacheCompilerHost = ts.CompilerHost & {
    fileCache: CacheMap;
};

const globalEtsFileCache: CacheMap = new Map()
const globalMemoFileCache: CacheMap = new Map()

function makeCacheCompilerHost(
    host: ts.CompilerHost | undefined,
    tsInstance: typeof ts,
    compilerOptions: ts.CompilerOptions,
    fileCache
): CacheCompilerHost {
    const compilerHost = host ?? tsInstance.createCompilerHost(compilerOptions, true);
    const originalGetSourceFile = compilerHost.getSourceFile;

    return Object.assign(compilerHost, {
      getSourceFile(fileName: string, ...rest) {
        const fileCache = this.fileCache;
        fileName = (tsInstance as any).normalizePath(fileName);
        if (fileCache.has(fileName)) {
            return fileCache.get(fileName);
        }

        const sourceFile = originalGetSourceFile.call(this, fileName, ...rest);
        // fileCache.set(fileName, sourceFile); // Seems to be unnecessary
  
        return sourceFile;
      },
      fileCache
    });
}

interface ArkoalaPluginOptions {
    filter?: (fileName: string) => boolean, // TODO a micromatch/picomatch pattern to allow use in JSON?
    routerRootDir?: string,
}
  
export default function programTransformer(
    program: ts.Program,
    host: ts.CompilerHost | undefined,
    options: ArkoalaPluginOptions,
    extras: ts.TransformerExtras
) {
    // TODO transform per-module
    if (process.env.aceModuleRoot) {
        // debug("ENV", process.env);
        console.trace = () => {};

        let root = (extras.ts as any).normalizePath(process.env.aceModuleRoot)
        options.filter = options.filter ?? (fileName => true)
        options.routerRootDir = root
    }

    const compilerOptions = program.getCompilerOptions()
    extras.diagnostics = extras.diagnostics ?? []

    const etsCompilerHost = makeCacheCompilerHost(undefined, extras.ts, compilerOptions, new Map())
    const etsProg = transformETSCode(program, etsCompilerHost, options, extras)

    const memoCompilerHost = makeCacheCompilerHost(etsCompilerHost, extras.ts, compilerOptions, new Map())
    const memoProg = transformMemoCode(etsProg, memoCompilerHost, options, extras)

    return memoProg
}

function transformMemoCode(program: ts.Program, compilerHost: CacheCompilerHost, options: ArkoalaPluginOptions, extras: ts.TransformerExtras): ts.Program {
    const compilerOptions = program.getCompilerOptions()
    const rootFiles: string[] = program.getRootFileNames().map((extras.ts as any).normalizePath)
    const rootFileSet = new Set(rootFiles)
    // debug(["Memo transform program roots:", ...rootFiles].join("\n  - "))

    const fileFilter = options.filter ?? (fileName => rootFileSet.has(fileName))
    const sourceFiles = program.getSourceFiles().filter(file => {
        let fileName = (extras.ts as any).normalizePath(file.fileName)
        let alreadyTransformed = !DISABLE_CACHE && globalMemoFileCache.has(file.fileName);
        let canTransform = fileName.match(/(?<!\.d)\.e?ts$/) && fileFilter(fileName)
        if (canTransform && alreadyTransformed) {
            debug("Skipping memo transform for " + fileName);
        }
        return canTransform && !alreadyTransformed
    })
    if (sourceFiles.length == 0) {
        debug("Nothing to memo transform");
        return program;
    }
    // debug(["Memo transform source files:", ...program.getSourceFiles().map(f => f.fileName)].join("\n  - "))
    debug(["Memo transform for:", ...sourceFiles.map(f => f.fileName).sort()].join("\n  - "))
    const transformers = [
        memoPlugin(program as any, {
            only_unmemoize: false,
            trace: false
        }, extras)
    ]
    const transformResult = extras.ts.transform(sourceFiles, transformers, { ...compilerOptions, noEmit: true });
    const transformedSources = transformResult.transformed

    // for (const diag of transformResult.diagnostics ?? []) {
    //     debug("Memo error in " + diag.file.fileName)
    //     debug(diag.source ?? program.getSourceFile(diag.file.fileName))
    //     debug()
    // }

    !DISABLE_CACHE && globalMemoFileCache.forEach((v, k) => compilerHost.fileCache.set(k, v));
    let { printFile } = extras.ts.createPrinter({ removeComments: false });
    for (const sourceFile of transformedSources) {
        let { fileName, languageVersion } = sourceFile;
        fileName = (extras.ts as any).normalizePath(fileName);
        const code = printFile(sourceFile);
        const transformedFile = extras.ts.createSourceFile(fileName, code, languageVersion);
        (transformedFile as any).version = languageVersion
        compilerHost.fileCache.set(fileName, transformedFile)
        !DISABLE_CACHE && globalMemoFileCache.set(fileName, transformedFile)
        debug("Transformed memo in file: " + fileName + ", size = " + transformedFile.end + ", version = " + languageVersion)
        // debug(printFile(sourceFile))
    }

    let prog = extras.ts.createProgram(rootFiles, compilerOptions, compilerHost, program)
    return prog;
}

function transformETSCode(program: ts.Program, compilerHost: CacheCompilerHost, options: ArkoalaPluginOptions, extras: ts.TransformerExtras): ts.Program {
    const arkui = "@koalaui/arkoala-arkui"
    const compilerOptions = program.getCompilerOptions()
    const rootFiles: string[] = program.getRootFileNames().map((extras.ts as any).normalizePath)

    const buildJson = loadBuildJson()
    if (buildJson) {
        const indexFull = path.join(buildJson.projectRootPath, "oh_modules", arkui, "index-full.d.ts")
        if (fs.existsSync(indexFull)) {
            // support arkoala/ts
            debug("Including " + indexFull)
            rootFiles.unshift(indexFull)
            program = extras.ts.createProgram(rootFiles, compilerOptions, compilerHost, program)
        }
    }

    const rootFileSet = new Set(rootFiles)
    // debug(["Ets transform program roots:", ...rootFiles].join("\n  - "))

    const fileFilter = options.filter ?? (fileName => rootFileSet.has(fileName))
    const sourceFiles = program.getSourceFiles().filter(file => {
        let fileName = (extras.ts as any).normalizePath(file.fileName)
        let alreadyTransformed = !DISABLE_CACHE && globalEtsFileCache.has(fileName);
        let canTransform = fileName.match(/(?<!\.d)\.ets$/) && fileFilter(fileName);
        if (canTransform && alreadyTransformed) {
            debug("Skipping ETS transform for " + fileName);
        }
        return canTransform && !alreadyTransformed
    })
    if (sourceFiles.length == 0) {
        debug("Nothing to ETS transform");
        return program;
    }
    // debug(["Ets transform source files:", ...program.getSourceFiles().map(f => f.fileName)].join("\n  - "))
    debug(["Ets transform for:", ...sourceFiles.map(f => f.fileName).sort()].join("\n  - "))
    const transformers = [
        makeEtsExpander(program.getTypeChecker() as any, {
            trace: false,
            arkui: arkui,
            source: options.routerRootDir,
        }, extras as any) as any // TODO ts 
    ]
    const transformResult = extras.ts.transform(sourceFiles, transformers, { ...compilerOptions, noEmit: true });
    const transformedSources = transformResult.transformed

    // for (const diag of transformResult.diagnostics ?? []) {
    //     debug("Ets error in " + diag.file.fileName)
    //     debug(diag.source ?? program.getSourceFile(diag.file.fileName))
    //     debug()
    // }

    !DISABLE_CACHE && globalEtsFileCache.forEach((v, k) => compilerHost.fileCache.set(k, v));
    let { printFile } = extras.ts.createPrinter({ removeComments: false });
    for (const sourceFile of transformedSources) {
        let { fileName, languageVersion } = sourceFile;
        fileName = (extras.ts as any).normalizePath(fileName);
        const transformedFile = extras.ts.createSourceFile(fileName, printFile(sourceFile), languageVersion);
        (transformedFile as any).version = languageVersion
        !DISABLE_CACHE && globalEtsFileCache.set(fileName, transformedFile)
        compilerHost.fileCache.set(fileName, transformedFile)
        debug("Transformed ets in file: " + fileName + ", size = " + transformedFile.end + ", version = " + languageVersion)
        // debug(printFile(sourceFile))
    }
    let prog = extras.ts.createProgram(rootFiles, compilerOptions, compilerHost, program)
    return prog;
}

function loadBuildJson() {
    if (process.env.aceBuildJson && fs.existsSync(process.env.aceBuildJson)) {
        return JSON.parse(fs.readFileSync(process.env.aceBuildJson).toString())
    }
    return undefined
}

programTransformer.debug = debug