
import { Component, Column, Text } from "@ohos.arkui"
import { State } from "@ohos.arkui"
import { ManyImportComponent188 } from "./manyImportFile188"
import { ManyImportComponent189 } from "./manyImportFile189"


@Component
export struct ManyImportComponent94 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent188()
            ManyImportComponent189()

        }
    }
}
