/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

export class TestStats {
  private static stats: Record<string, { passed: number; failed: number; info?:string }> = {}

  static addResult(testName: string, passed: boolean, info?:string): void {
    if (!this.stats[testName]) {
      this.stats[testName] = { passed: 0, failed: 0, info: info }
    }

    console.log(`Adding test result: ${testName} = ${passed}`)
    passed ? this.stats[testName].passed++ : this.stats[testName].failed++
  }

  static getStats(testName: string): { passed: number; failed: number; info?:string } | undefined {
    return this.stats[testName]
  }

  static getAllStats(): Record<string, { passed: number; failed: number; info?:string }> {
    return this.stats
  }

  static reset(): void {
    this.stats = {}
  }

  static isAllPassed(): boolean {
    return Object.values(this.stats).every(({ passed, failed, info }) => failed === 0 && passed > 0)
  }
  // Gets final results as a one string.
  // addMarker true adds _ut to the beginning of lines to be easily seen in DevEco
  static getFinalReport(addMarker? :boolean): string {

    let runCount = 0
    let passedCount = 0
    let failedCount = 0
    let lines: string[] = []
    const unitTestIdentifier : string = '__ut';

    // Just adjust PASSED and FAILS to be aligned correctly
    let lenOfTestCaseNames = 10
    for (const testName in this.stats) {
      lenOfTestCaseNames = testName.length > lenOfTestCaseNames ? testName.length + 5 : lenOfTestCaseNames;
    }

    for (const testName in this.stats) {
      const { passed, failed, info } = this.stats[testName]
      const paddedName = testName.padEnd(lenOfTestCaseNames, ' ')
      runCount++

      if (failed > 0 || passed === 0) {
        failedCount++
        lines.push(`${paddedName} FAILED ${info}`)
      } else {
        passedCount++
        lines.push(`${paddedName} PASSED ${info}`)
      }
    }
    lines.push(`Summary:`)
    lines.push(`Executed: ${runCount}`)
    lines.push(`Passed:   ${passedCount}`)
    lines.push(`Failed:   ${failedCount}`)

    lines.push(`Final Result: ${this.isAllPassed() ? "Passed" : "Failed"}`)

    return lines.map(line => addMarker ? `${unitTestIdentifier} ${line}` : line).join('\n')

  }
}
