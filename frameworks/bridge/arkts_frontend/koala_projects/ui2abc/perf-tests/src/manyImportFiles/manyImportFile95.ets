
import { Component, Column, Text } from "@ohos.arkui"
import { State } from "@ohos.arkui"
import { ManyImportComponent190 } from "./manyImportFile190"
import { ManyImportComponent191 } from "./manyImportFile191"


@Component
export struct ManyImportComponent95 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent190()
            ManyImportComponent191()

        }
    }
}
