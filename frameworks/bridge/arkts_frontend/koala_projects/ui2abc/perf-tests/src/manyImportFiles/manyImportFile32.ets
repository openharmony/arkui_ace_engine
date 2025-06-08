
import { Component, Column, Text } from "@ohos.arkui"
import { State } from "@ohos.arkui"
import { ManyImportComponent64 } from "./manyImportFile64"
import { ManyImportComponent65 } from "./manyImportFile65"


@Component
export struct ManyImportComponent32 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent64()
            ManyImportComponent65()

        }
    }
}
