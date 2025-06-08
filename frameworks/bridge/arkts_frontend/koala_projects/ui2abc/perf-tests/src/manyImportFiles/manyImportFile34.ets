
import { Component, Column, Text } from "@ohos.arkui"
import { State } from "@ohos.arkui"
import { ManyImportComponent68 } from "./manyImportFile68"
import { ManyImportComponent69 } from "./manyImportFile69"


@Component
export struct ManyImportComponent34 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent68()
            ManyImportComponent69()

        }
    }
}
