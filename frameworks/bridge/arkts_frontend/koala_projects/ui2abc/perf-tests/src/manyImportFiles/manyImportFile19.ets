
import { Component, Column, Text } from "@ohos.arkui"
import { State } from "@ohos.arkui"
import { ManyImportComponent38 } from "./manyImportFile38"
import { ManyImportComponent39 } from "./manyImportFile39"


@Component
export struct ManyImportComponent19 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent38()
            ManyImportComponent39()

        }
    }
}
