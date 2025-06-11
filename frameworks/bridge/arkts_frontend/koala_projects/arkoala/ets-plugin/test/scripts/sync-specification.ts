import { collectFiles, copy, directoriesManager } from "../utils"

const specificationDir = directoriesManager.getOrDownloadSpecificationTestsDir()
const copyDir = directoriesManager.testsDir
const tests = collectFiles(specificationDir)
const copied = copy(specificationDir, copyDir, tests, true, true, true, true)
console.log(`${copied.length} new test files`)

const pagesFrom = directoriesManager.getOrDownloadSpecificationPagesDir()
const pagesTo = directoriesManager.testPagesDir
const pages = collectFiles(pagesFrom)
const copiedPages = copy(pagesFrom, pagesTo, pages, false, false, true, true)
console.log(`${copiedPages.length} new test dependencies files`)