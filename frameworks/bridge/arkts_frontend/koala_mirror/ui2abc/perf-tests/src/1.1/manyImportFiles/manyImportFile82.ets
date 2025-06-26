
import { ManyImportComponent164 } from "./manyImportFile164"
import { ManyImportComponent165 } from "./manyImportFile165"


@Component
export struct ManyImportComponent82 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent164()
            ManyImportComponent165()

        }
    }
}
