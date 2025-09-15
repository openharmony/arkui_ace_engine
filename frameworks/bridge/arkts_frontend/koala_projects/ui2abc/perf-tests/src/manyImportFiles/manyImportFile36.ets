
import { Component, Column, Text } from "@ohos.arkui"
import { State } from "@ohos.arkui"
import { ManyImportComponent72 } from "./manyImportFile72"
import { ManyImportComponent73 } from "./manyImportFile73"


@Component
export struct ManyImportComponent36 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent72()
            ManyImportComponent73()

        }
    }
}
