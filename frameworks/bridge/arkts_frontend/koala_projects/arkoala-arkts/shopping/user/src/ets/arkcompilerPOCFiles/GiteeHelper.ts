import { PRs, MockPRsData } from './GiteeHelperData'

export class GiteeHelper {
  static FetchMockData(page: number, per_page: number, cb: (res: PRs) => void) {
    cb(new PRs(MockPRsData().values!.slice(page * per_page, per_page)))
  }
}
