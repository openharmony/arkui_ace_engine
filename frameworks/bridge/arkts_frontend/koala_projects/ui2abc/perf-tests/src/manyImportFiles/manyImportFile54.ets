
import { Component, Column, Text } from "@ohos.arkui"
import { State } from "@ohos.arkui"
import { ManyImportComponent108 } from "./manyImportFile108"
import { ManyImportComponent109 } from "./manyImportFile109"


@Component
export struct ManyImportComponent54 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent108()
            ManyImportComponent109()

        }
    }
}
