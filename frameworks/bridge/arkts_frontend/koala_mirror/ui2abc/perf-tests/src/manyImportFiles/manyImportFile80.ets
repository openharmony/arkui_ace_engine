
import { Component, Column, Text } from "@ohos.arkui"
import { State } from "@ohos.arkui"
import { ManyImportComponent160 } from "./manyImportFile160"
import { ManyImportComponent161 } from "./manyImportFile161"


@Component
export struct ManyImportComponent80 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent160()
            ManyImportComponent161()

        }
    }
}
