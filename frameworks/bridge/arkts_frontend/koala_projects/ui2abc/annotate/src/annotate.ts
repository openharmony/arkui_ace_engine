/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import * as fs from 'fs'
import * as path from 'path'
import { minimatch } from 'minimatch'

class Config {
	inputDir: string = "./src"
	outputDir: string = "./ets"
	include: string[] = [ "./src/**/*" ]
	exclude: string[] = []
	fileExtension?: string
}

const memoImport = "@koalaui/runtime/annotations"

export function main(options: Config) {
	console.log(options)

	const readdirSyncRecursive: (dir: string) => string[] = (dir: string) =>
		fs.readdirSync(dir).reduce((files: string[], file: string) => {
			const name = path.join(dir, file)
			return fs.lstatSync(name).isDirectory() ? [...files, ...readdirSyncRecursive(name)] : [...files, name]
		}, [])


	const files = readdirSyncRecursive(options.inputDir)
		.map(it => path.relative(options.inputDir, it))

	fs.mkdirSync(options.outputDir, { recursive: true })

	const include = options.include.map(it => path.resolve(it))
	const exclude = options.exclude.map(it => path.resolve(it))

	files.forEach(it => {
		const inputFile = path.join(options.inputDir, it)
		let outputFile = path.join(options.outputDir, it)
		if (options.fileExtension) {
			let { dir, name, ext } = path.parse(outputFile)
			if (ext) {
				outputFile = path.join(dir, name + options.fileExtension)
			}
		}
		if (include.some(value => minimatch(path.resolve(inputFile), value))
			&& !exclude.some(value => minimatch(path.resolve(inputFile), value))
		) {
			const text = fs.readFileSync(inputFile, 'utf8').toString()
			const newText = convertMemo(text, memoImport)
			if (fs.existsSync(outputFile)) {
				// This is not to update already annotated files
				if (newText == fs.readFileSync(outputFile, 'utf8').toString()) {
					return
				}
			}
			console.log(inputFile, " -> ", outputFile)
			fs.mkdirSync(path.dirname(outputFile), { recursive: true })
			fs.writeFileSync(outputFile, newText, 'utf8')
		}
	})
}

function convertMemo(text: string, memoImport: string): string {
	const result = text
		.replaceAll(/\/\*\* @memo \*\//g, "@memo")
		.replaceAll(/\/\*\* @memo:intrinsic \*\//g, "@memo_intrinsic")
		.replaceAll(/\/\*\* @memo:stable \*\//g, "@memo_stable")
		.replaceAll(/\/\*\* @memo:entry \*\//g, "@memo_entry")
		.replaceAll(/\/\*\* @skip:memo \*\//g, "@memo_skip")
	if (result == text) {
		return result
	}
	return `import { memo, memo_intrinsic, memo_entry, memo_stable, memo_skip } from "${memoImport}"\n` + result
}

if (process.argv.length == 3) {
	const configPath = path.resolve(process.argv[2])
	const config = JSON.parse(fs.readFileSync(configPath, 'utf8'))
	main({ ...(new Config()), ...config })
} else {
	main(new Config())
}
