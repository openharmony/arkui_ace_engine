
import { ManyImportComponent14 } from "./manyImportFile14"
import { ManyImportComponent15 } from "./manyImportFile15"


@Component
export struct ManyImportComponent7 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent14()
            ManyImportComponent15()

        }
    }
}
