/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

import * as path from 'path';
import * as fs from 'fs';
import * as cp from 'child_process';

import * as rollup from 'rollup';
import nodeResolve from '@rollup/plugin-node-resolve';
import commonjs from '@rollup/plugin-commonjs';

// TODO better plugin integration

interface RollupPluginWithCache extends rollup.Plugin {
  shouldInvalidCache(): boolean;
}

export function makeArkoalaPlugin(options: any): RollupPluginWithCache {
  const { getResolveModules, projectConfig, globalModulePaths, arkoalaSdkRoot } = options;

  const ARKOALA_ENTRY_STUB = '@arkoala/arkoala-app';
  const ARKOALA_RESOURCES_MODULE = '@arkoala/arkoala-app-resources';

  let debug = console.log.bind(console)

  let arkoalaBuildPath = '';
  let arkoalaGeneratedPath = '';
  let arkoalaGeneratedJSPath = '';
  let arkoalaGeneratedMemoPath = '';
  let ohosTscPath = '';
  let tscPath = '';
  let arkoalaEtsPluginPath = '';
  let arkoalaTscPluginPath = '';
  let etsRoot = '';

  let arkoalaNativeEmitted = false;

  let emittedChunkFiles = new Set<string>();

  return {
    name: 'arkoalaEtsTransform',

    buildStart(options): void {
      debug = ((share) => {
        let logger = share.getLogger('arkoalaPlugin');
        const blue = process.stdout.isTTY ? '\u001b[34m' : '';
        const reset = process.stdout.isTTY ? '\u001b[39m' : '';
        return (...args) => logger.debug(blue, ...args, reset);
      })((this as any).share);

      debug('PC', projectConfig);
      configureArkoala();
      preprocessEts();
      processMemo();
    },

    resolveId(source, importer, options): rollup.ResolveIdResult {
      if (source === ARKOALA_ENTRY_STUB) {
        return { id: ARKOALA_ENTRY_STUB, external: true };
      }

      if (source === ARKOALA_RESOURCES_MODULE) {
        return { id: ARKOALA_RESOURCES_MODULE, external: true };
      }

      if (options.isEntry && (source.endsWith('.ets') || source.endsWith('.ts'))) {
        // TODO resolve with node-loader?
        debug('RESOLVE ENTRY ' + source);
        return `${source}`;
      }

      return null;
    },

    async load(id): Promise<rollup.LoadResult> {
      let cacheRoot = projectConfig.cachePath;
      let projectRoot = projectConfig.projectRootPath;
      let { bundleName, moduleName } = projectConfig;

      if (id === ARKOALA_ENTRY_STUB) {
        return { code: 'export async function startArkoala() {}' };
      }

      debug('LOADING ARKOALA BUNDLE', id);
      if (id.endsWith(".js")) {
        return 
      }

      let generatedPath = id
        .replace(etsRoot, arkoalaGeneratedMemoPath)
        .replace(/\.e?ts$/, '.js');

      // TODO try to pick only a bindle wich imports entry point stub, other files are unnecessary

      let bundle = await rollup.rollup({
        input: generatedPath,
        external: /@(ohos|system|hms)\./, // TODO get from ets-loader
        plugins: [
          nodeResolve({
            modulePaths: [
              path.resolve(projectConfig.projectPath),
              path.resolve('node_modules'),
              path.resolve(__dirname, 'node_modules'),
              arkoalaSdkRoot,
              ...globalModulePaths,
              ...(projectConfig.aceModuleJsonPath ?
                getResolveModules(path.resolve(projectConfig.projectPath), false) :
                getResolveModules(path.resolve(projectConfig.projectPath), true)
              ),
            ],
            exportConditions: ['ark', 'node', 'main'],
          }),
          commonjs() as any,
          makeArkoalaEntryPoint(),
        ],
      });

      const ARKOALA_CHUNK_NAME = "arkoala"

      // TODO check errors
      let { output } = await bundle.generate({
        format: 'esm',
        sourcemap: true,
        manualChunks: { [ARKOALA_CHUNK_NAME]: [ARKOALA_ENTRY_STUB] },
      });

      let arkoalaFileName = ''
      let arkoalaFilePath = ''

      for (const chunk of output) {
        if (chunk.type === 'chunk' && chunk.name === ARKOALA_CHUNK_NAME) {
          arkoalaFileName = chunk.fileName
          let chunkId = path.join(path.dirname(id), arkoalaFileName)
          arkoalaFilePath = writeBundleToCache(chunk.code, chunkId, projectRoot, projectRoot, true).path
          emittedChunkFiles.add(arkoalaFilePath)
        }
      }

      let arkoalaBundleId = ""
      if (arkoalaFilePath) {
        let modulePathParts = id.match(/(\S+)(?:\/|\\)src(?:\/|\\)(?:main|ohosTest)(?:\/|\\)(ets|js)(?:\/|\\)(\S+)/);
        if (modulePathParts) {
          let [, , moduleType, modulePath] = modulePathParts;
          let chunkDirName = path.dirname(modulePath).replace(path.sep, "/");
          let chunkBaseName = arkoalaFilePath ? path.basename(arkoalaFileName).replace(/\.js$/, "") : ""
          arkoalaBundleId = `@bundle:${bundleName}/${moduleName}/${moduleType}/${chunkDirName}/${chunkBaseName}`
        }
      }

      for (const chunk of output) {
        if (chunk.type === 'chunk') {
          let code = chunk.code
          if (arkoalaBundleId) {
            code = code.replace(`./${arkoalaFileName}`, arkoalaBundleId)
          }
          writeBundleToCache(code, id, projectRoot, cacheRoot);
          return chunk;
        }
      }
      debug('NOT LOADED!');
      return { code: '' };
    },

    shouldInvalidCache(): boolean {
      return true;
    },

    buildEnd() {
      for (const filepath of emittedChunkFiles) {
        debug("DELETE " + filepath);
        try {
          fs.unlinkSync(filepath);
        } catch (e) {
          debug("Failed to remove: " + e)
        }
      }
      emittedChunkFiles.clear()
    }
  };

  function writeBundleToCache(bundleCode: string, id: string, projectRoot: string, cacheRoot: string, isJsBundle = false): { path: string } {
    // TODO emit unmemoized ts?
    // TODO process exports with ark_utils.ts methods
    let code = bundleCode.replace(
      /\bLOAD_NATIVE\b/g,
      'globalThis.requireNapi("ArkoalaNative", true)'
    ); // TODO @rollup/plugin-inject
    if (!isJsBundle) {
      code = code.replace(/@ohos\./g, '@ohos:');
    }
    let cachedPath = id
      .replace(projectRoot, cacheRoot)
      .replace(/\.ets$/, '.ts');
    debug('CACHE', id, '->', cachedPath);
    fs.mkdirSync(path.dirname(cachedPath), { recursive: true });
    fs.writeFileSync(cachedPath, code, 'utf-8');

    return { path: cachedPath }
  }

  function configureArkoala(): void {
    arkoalaBuildPath = path.join(projectConfig.buildPath, '../../../arkoala_out');
    arkoalaGeneratedPath = path.join(arkoalaBuildPath, 'generated');
    arkoalaGeneratedJSPath = path.join(arkoalaBuildPath, 'js_output');
    arkoalaGeneratedMemoPath = path.join(arkoalaBuildPath, 'generated_memo');
    arkoalaEtsPluginPath = arkoalaResolve('@koalaui/ets-plugin');
    arkoalaTscPluginPath = arkoalaResolve('@koalaui/compiler-plugin');
    ohosTscPath = arkoalaResolve('ohos-typescript');
    if (ohosTscPath) {
      ohosTscPath = path.join(path.dirname(ohosTscPath), 'tsc.js');
    }
    tscPath = arkoalaResolve('typescript');
    if (ohosTscPath) {
      tscPath = path.join(path.dirname(tscPath), 'tsc.js');
    };

    etsRoot = projectConfig.projectPath;
    debug('ARKOALA: ', {
      arkoalaSdkRoot,
      arkoalaEtsPluginPath,
      arkoalaTscPluginPath,
      arkoalaBuildPath,
      arkoalaGeneratedPath,
      arkoalaGeneratedJSPath,
      arkoalaGeneratedMemoPath,
      ohosTscPath,
      tscPath,
      etsRoot,
    });
  }

  function processMemo(): void {
    const sdkStubs = path.join(
      arkoalaResolve('@koalaui/arkui-common'),
      '../../../../ohos-sdk-ets/HarmonyOS-NEXT-DB1/openharmony/ets/'
    );
    const tsConfig = {
      compilerOptions: {
        target: 'ESNext',
        module: 'ESNext',
        lib: ['ESNext', 'DOM', 'ESNext.WeakRef'],
        moduleResolution: 'node',
        composite: true,
        incremental: true,
        declarationMap: true,
        sourceMap: true,
        declaration: true,
        strict: true,
        skipLibCheck: true,
        removeComments: false,
        importsNotUsedAsValues: 'remove',
        plugins: [{ transform: arkoalaTscPluginPath, trace: false }],
        outDir: arkoalaGeneratedMemoPath,
        experimentalDecorators: true,
        ...tsConfigKoalaUIPaths()
      },
      files: [
        path.join(sdkStubs, 'component/index-full.d.ts'),
        path.join(sdkStubs, 'component/koala-extensions.d.ts'),
        path.join(sdkStubs, 'api/@internal/full/global.d.ts'),
      ],
      include: ['**/*'],
    };

    const tsConfigPath = path.join(
      arkoalaGeneratedPath,
      'memo.tsconfig.json'
    ); // TODO generate in a build dir or do not generate at all
    fs.writeFileSync(tsConfigPath, JSON.stringify(tsConfig), 'utf-8');
    try {
      const nodeExe = process.argv0; // TODO get from config?
      debug('MEMO PREPROCESS');
      let tscProc = cp.spawnSync(nodeExe, [tscPath, '-p', tsConfigPath], {
        stdio: 'inherit',
        cwd: arkoalaGeneratedPath,
      });
      debug('TSC', tscProc.status, tscProc.error);
      debug('MEMO PREPROCESS DONE');
    } finally {
      //TODO check status
      fs.rmSync(tsConfigPath);
    }
  }

  function preprocessEts(): void {
    const ohosTsConfig = {
      extends: arkoalaResolve('@koalaui/arkui-common/config/tsconfig.base.json'),
      exclude: ['node_modules', 'js_output', 'dependencies'],
      include: ['**/*.ets', '**/*.ts'],
      compilerOptions: {
        outDir: arkoalaGeneratedJSPath,
        plugins: [
          {
            transform: arkoalaEtsPluginPath,
            destination: arkoalaGeneratedPath,
            arkui: '@koalaui/arkoala-arkui',
          },
        ],
        skipLibCheck: true,
        ...tsConfigKoalaUIPaths(),
      },
    };
    const ohosTsConfigPath = path.join(etsRoot, 'arkoala.tsconfig.json'); // TODO generate in a build dir or do not generate at all
    fs.writeFileSync(ohosTsConfigPath, JSON.stringify(ohosTsConfig), 'utf-8');
    try {
      const nodeExe = process.argv0; // TODO get from config?
      debug('ETS PREPROCESS');
      let ohosTscProc = cp.spawnSync(
        nodeExe,
        [ohosTscPath, '-p', ohosTsConfigPath],
        { stdio: 'inherit', cwd: etsRoot }
      );
      debug('ETS PREPROCESS DONE');
    } finally {
      //TODO check status
      fs.rmSync(ohosTsConfigPath);
    }
  }
  
  function makeArkoalaEntryPoint(): rollup.Plugin {
    return {
      name: 'arkoala-entry-plugin',
      async resolveId(source, importer, options): Promise<rollup.ResolveIdResult> {
        if (source === ARKOALA_ENTRY_STUB) {
          return '\0' + ARKOALA_ENTRY_STUB;
        }
        if (source === ARKOALA_RESOURCES_MODULE) {
          return { id: '\0' + ARKOALA_RESOURCES_MODULE, moduleSideEffects: true };
        }
        if (!arkoalaNativeEmitted && source === '@koalaui/arkoala') {
          let resolved = await this.resolve(source, importer, options);
          if (resolved) {
            let libPath = path.join(path.dirname(resolved.id), '../libArkoalaNative.so');
            let buildPath = path.dirname(projectConfig.buildPath);
            let libDir = path.join(buildPath, '../../libs', path.basename(buildPath), 'arm64-v8a');
            try {
              fs.mkdirSync(libDir, { recursive: true });
              fs.copyFileSync(libPath, path.join(libDir, path.basename(libPath)));
            } catch (e) {
              console.warn('Failed to load native library: ' + e);
            }
          }
          arkoalaNativeEmitted = true;
        }

        return null;
      },
      load(id): rollup.LoadResult {
        if (id === '\0' + ARKOALA_RESOURCES_MODULE) {
          const moduleJsonPath = projectConfig.aceModuleJsonPath;
          return { code: genResourceMapModule({ moduleJsonPath }) };
        }

        if (id === '\0' + ARKOALA_ENTRY_STUB) {
          const indexPagePath = path.join(arkoalaGeneratedMemoPath, 'pages/Index');
          const routerInitPath = path.join(arkoalaGeneratedMemoPath, '__router_initialization');
          return {
            code: `
import ${JSON.stringify(ARKOALA_RESOURCES_MODULE)}
import { startApplication } from '@koalaui/arkoala'
import { ArkRooted } from '@koalaui/arkoala-arkui'
import { __Entry } from ${JSON.stringify(indexPagePath)}
import { registerRoutes } from ${JSON.stringify(routerInitPath)}

export function startArkoala() {
registerRoutes();
return startApplication({
    waitForVSync: undefined
}, ArkRooted(__Entry))
}`,
          };
        }

        return null;
      },
    };
  }

  function arkoalaResolve(modulePath: string): string {
    let pathsToTest = [
      path.join(arkoalaSdkRoot, modulePath),
      path.join(arkoalaSdkRoot, `node_modules/${modulePath}`),
    ];
    let resolved;
    let errors: string[] = []
    for (const path of pathsToTest) {
      try {
        resolved = require.resolve(path)
      } catch (e: any) {
        errors.push(e.message || ""+e)
      }
      if (resolved) break;
    }
    
    if (!resolved) {
      throw new Error(`Failed to resolve package ${modulePath} in the Arkoala SDK:\n  ${errors.join('\n  ')}`);
    }

    return resolved
  }

  function tsConfigKoalaUIPaths(): Record<string, any> {
    return {
      baseUrl: '.',
      paths: {
        '*': globalModulePaths.map((dir: string) => path.join(dir, '*')),
        '@arkoala/*': [path.join(arkoalaSdkRoot, '@arkoala/*'), path.join(arkoalaSdkRoot, '@koalaui/arkoala-arkui/*')],
        '@koalaui/*': [path.join(arkoalaSdkRoot, '@koalaui/*')],
        '@koalaui/arkoala/*': [path.join(arkoalaSdkRoot, '@koalaui/arkoala/build/lib/src/*')],
        '@koalaui/arkoala-arkui/*': [path.join(arkoalaSdkRoot, '@koalaui/arkoala-arkui/build/lib/src/*')],
        '@koalaui/arkui-common/*': [path.join(arkoalaSdkRoot, '@koalaui/arkui-common/build/lib/src/*')],
        '@koalaui/common/*': [path.join(arkoalaSdkRoot, '@koalaui/common/build/lib/src/*')],
        '@koalaui/interop/*': [path.join(arkoalaSdkRoot, '@koalaui/interop/build/lib/src/*')],
        '@koalaui/runtime/*': [path.join(arkoalaSdkRoot, '@koalaui/runtime/build/lib/src/*')],
      }
    };
  }
}


function genResourceMapModule(options: CodegenOptions): string {
  const moduleJsonPath = options.moduleJsonPath;
  const resourceTablePath = path.join(path.dirname(moduleJsonPath), 'ResourceTable.txt');
  const importString = options.arkoalaImport ?? '@koalaui/arkoala-arkui';

  const module = readModuleManifest(moduleJsonPath);
  const resourceTable = readResourceTable(resourceTablePath);
  const resourceMap = makeResourceMap(resourceTable);

  return [
    `import { __registerResources, _r, _rawfile } from ${JSON.stringify(importString)};\n\n`,
    `const bundleName = ${JSON.stringify(module.bundleName || '')};\n`,
    `const moduleName = ${JSON.stringify(module.moduleName || '')};\n`,
    `const resources = ${JSON.stringify(resourceMap || {})};\n\n`,
    '__registerResources(bundleName, moduleName, resources);\n',
    'export function $r(name, ...args) { return _r(name, ...args) };\n',
    'export function $rawfile(name) { return _rawfile(name) };\n',
    'Object.assign(globalThis, { $r: $r, $rawfile: $rawfile });\n',
    // TODO: replace with plugin-inject
  ].join('');
}


interface ResourceTableEntry {
  type: string
  name: string
  id: number
}

interface ModuleInfo {
  bundleName: string
  moduleName: string
}

function readResourceTable(filepath: string): ResourceTableEntry[] {
  let content = fs.readFileSync(filepath, 'utf-8').trim();
  let lines = content.split(/(\r?\n)+/gm);

  let entries: ResourceTableEntry[] = [];
  for (const line of lines) {
    let items = line.trim().split(/\s+/g);
    if (items.length === 0 || items[0] === '') {
      continue;
    }

    const itemsInRow = 3;
    if (items.length !== itemsInRow) {
      throw new Error(`Illegal resource table format (at line '${items}')`);
    }

    const [type, name, idStr] = items;
    if (!/^0x[0-9A-Fa-f]{8}$/i.test(idStr)) { // int32 in hex, 0xFFFFFFFF
      throw new Error(`Illegal resource id: ${idStr}`);
    }

    const id = parseInt(idStr, 16);

    entries.push({ type, name, id });
  }

  return entries;
}

function readModuleManifest(filepath: string): ModuleInfo {
  let json = fs.readFileSync(filepath, 'utf-8').trim();
  let manifest = JSON.parse(json);
  let moduleName = manifest.module.name;
  let bundleName = manifest.app?.bundleName ?? 'com.huawei.arkoala'; // TODO remove hardcoded constant

  return { moduleName, bundleName };
}

function makeResourceMap(resources: ResourceTableEntry[]): Record<string, number> {
  let output: Record<string, number> = {};
  for (const {type, name, id} of resources) {
    let key = type + '.' + name;
    if (key in output) {
      throw new Error(`Duplicated resource key: ${key}`);
    }
    output[key] = id;
  }

  return output;
}

interface CodegenOptions {
  arkoalaImport?: string,
  moduleJsonPath: string,
}
