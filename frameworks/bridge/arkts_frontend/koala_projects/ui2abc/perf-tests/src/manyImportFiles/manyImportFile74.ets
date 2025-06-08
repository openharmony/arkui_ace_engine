
import { Component, Column, Text } from "@ohos.arkui"
import { State } from "@ohos.arkui"
import { ManyImportComponent148 } from "./manyImportFile148"
import { ManyImportComponent149 } from "./manyImportFile149"


@Component
export struct ManyImportComponent74 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent148()
            ManyImportComponent149()

        }
    }
}
