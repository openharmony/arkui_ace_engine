
import { ManyImportComponent186 } from "./manyImportFile186"
import { ManyImportComponent187 } from "./manyImportFile187"


@Component
export struct ManyImportComponent93 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent186()
            ManyImportComponent187()

        }
    }
}
