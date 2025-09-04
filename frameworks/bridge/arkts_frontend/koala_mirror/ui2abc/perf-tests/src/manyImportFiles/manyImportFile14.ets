
import { Component, Column, Text } from "@ohos.arkui"
import { State } from "@ohos.arkui"
import { ManyImportComponent28 } from "./manyImportFile28"
import { ManyImportComponent29 } from "./manyImportFile29"


@Component
export struct ManyImportComponent14 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent28()
            ManyImportComponent29()

        }
    }
}
