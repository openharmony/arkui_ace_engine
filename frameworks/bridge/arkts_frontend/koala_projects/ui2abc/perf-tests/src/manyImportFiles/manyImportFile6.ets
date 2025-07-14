
import { Component, Column, Text } from "@ohos.arkui"
import { State } from "@ohos.arkui"
import { ManyImportComponent12 } from "./manyImportFile12"
import { ManyImportComponent13 } from "./manyImportFile13"


@Component
export struct ManyImportComponent6 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent12()
            ManyImportComponent13()

        }
    }
}
