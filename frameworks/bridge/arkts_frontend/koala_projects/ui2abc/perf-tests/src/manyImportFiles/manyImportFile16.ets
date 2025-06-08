
import { Component, Column, Text } from "@ohos.arkui"
import { State } from "@ohos.arkui"
import { ManyImportComponent32 } from "./manyImportFile32"
import { ManyImportComponent33 } from "./manyImportFile33"


@Component
export struct ManyImportComponent16 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent32()
            ManyImportComponent33()

        }
    }
}
