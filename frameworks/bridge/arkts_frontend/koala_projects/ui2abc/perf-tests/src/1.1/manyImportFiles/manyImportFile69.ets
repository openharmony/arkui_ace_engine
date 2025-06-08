
import { ManyImportComponent138 } from "./manyImportFile138"
import { ManyImportComponent139 } from "./manyImportFile139"


@Component
export struct ManyImportComponent69 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent138()
            ManyImportComponent139()

        }
    }
}
