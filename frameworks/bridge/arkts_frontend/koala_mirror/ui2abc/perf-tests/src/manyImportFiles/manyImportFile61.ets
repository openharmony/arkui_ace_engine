
import { Component, Column, Text } from "@ohos.arkui"
import { State } from "@ohos.arkui"
import { ManyImportComponent122 } from "./manyImportFile122"
import { ManyImportComponent123 } from "./manyImportFile123"


@Component
export struct ManyImportComponent61 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent122()
            ManyImportComponent123()

        }
    }
}
