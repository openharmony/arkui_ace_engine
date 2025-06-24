
import { Component, Column, Text } from "@ohos.arkui"
import { State } from "@ohos.arkui"
import { ManyImportComponent54 } from "./manyImportFile54"
import { ManyImportComponent55 } from "./manyImportFile55"


@Component
export struct ManyImportComponent27 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent54()
            ManyImportComponent55()

        }
    }
}
