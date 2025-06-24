
import { ManyImportComponent136 } from "./manyImportFile136"
import { ManyImportComponent137 } from "./manyImportFile137"


@Component
export struct ManyImportComponent68 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent136()
            ManyImportComponent137()

        }
    }
}
