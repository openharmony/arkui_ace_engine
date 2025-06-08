
import { Component, Column, Text } from "@ohos.arkui"
import { State } from "@ohos.arkui"
import { ManyImportComponent182 } from "./manyImportFile182"
import { ManyImportComponent183 } from "./manyImportFile183"


@Component
export struct ManyImportComponent91 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent182()
            ManyImportComponent183()

        }
    }
}
