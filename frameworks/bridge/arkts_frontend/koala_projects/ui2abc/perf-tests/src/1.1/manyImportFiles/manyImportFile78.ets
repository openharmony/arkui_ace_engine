
import { ManyImportComponent156 } from "./manyImportFile156"
import { ManyImportComponent157 } from "./manyImportFile157"


@Component
export struct ManyImportComponent78 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent156()
            ManyImportComponent157()

        }
    }
}
