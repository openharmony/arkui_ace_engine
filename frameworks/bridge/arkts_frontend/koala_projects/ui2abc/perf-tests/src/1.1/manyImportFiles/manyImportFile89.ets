
import { ManyImportComponent178 } from "./manyImportFile178"
import { ManyImportComponent179 } from "./manyImportFile179"


@Component
export struct ManyImportComponent89 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent178()
            ManyImportComponent179()

        }
    }
}
