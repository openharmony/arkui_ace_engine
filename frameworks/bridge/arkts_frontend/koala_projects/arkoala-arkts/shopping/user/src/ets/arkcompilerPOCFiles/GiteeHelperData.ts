export class PRs {
  constructor(values?: Array<PR>) {
    this.values = values;
  }

  values?: Array<PR>;
}

export class PR {
  constructor(
    id?: number,
    url?: string,
    html_url?: string,
    diff_url?: string,
    patch_url?: string,
    issue_url?: string,
    commits_url?: string,
    review_comments_url?: string,
    review_comment_url?: string,
    comments_url?: string,
    number?: number,
    close_related_issue?: number,
    prune_branch?: boolean,
    state?: string,
    assignees_number?: number,
    testers_number?: number,
    assignees?: Assignees,
    testers?: Assignees,
    api_reviewers_number?: number,
    api_reviewers?: ApiReviewers,
    milestone?: Milestone,
    labels?: Labels,
    locked?: boolean,
    created_at?: Date,
    updated_at?: Date,
    closed_at?: Date,
    draft?: boolean,
    merged_at?: Date,
    mergeable?: boolean,
    can_merge_check?: boolean,
    _links?: Links,
    user?: User,
    ref_pull_requests?: PRs,
    title?: string,
    body?: string,
    head?: Head,
    base?: Base
  ) {
    this.id = id;
    this.url = url;
    this.html_url = html_url;
    this.diff_url = diff_url;
    this.patch_url = patch_url;
    this.issue_url = issue_url;
    this.commits_url = commits_url;
    this.review_comments_url = review_comments_url;
    this.review_comment_url = review_comment_url;
    this.comments_url = comments_url;
    this.number = number;
    this.close_related_issue = close_related_issue;
    this.prune_branch = prune_branch;
    this.state = state;
    this.assignees_number = assignees_number;
    this.testers_number = testers_number;
    this.assignees = assignees;
    this.testers = testers;
    this.api_reviewers_number = api_reviewers_number;
    this.api_reviewers = api_reviewers;
    this.milestone = milestone;
    this.labels = labels;
    this.locked = locked;
    this.created_at = created_at;
    this.updated_at = updated_at;
    this.closed_at = closed_at;
    this.draft = draft;
    this.merged_at = merged_at;
    this.mergeable = mergeable;
    this.can_merge_check = can_merge_check;
    this._links = _links;
    this.user = user;
    this.ref_pull_requests = ref_pull_requests;
    this.title = title;
    this.body = body;
    this.head = head;
    this.base = base;
  }

  id?: number;
  url?: string;
  html_url?: string;
  diff_url?: string;
  patch_url?: string;
  issue_url?: string;
  commits_url?: string;
  review_comments_url?: string;
  review_comment_url?: string;
  comments_url?: string;
  number?: number;
  close_related_issue?: number;
  prune_branch?: boolean;
  state?: string;
  assignees_number?: number;
  testers_number?: number;
  assignees?: Assignees;
  testers?: Assignees;
  api_reviewers_number?: number;
  api_reviewers?: ApiReviewers;
  milestone?: Milestone;
  labels?: Labels;
  locked?: boolean;
  created_at?: Date;
  updated_at?: Date;
  closed_at?: Date;
  draft?: boolean;
  merged_at?: Date;
  mergeable?: boolean;
  can_merge_check?: boolean;
  _links?: Links;
  user?: User;
  ref_pull_requests?: PRs;
  title?: string;
  body?: string;
  head?: Head;
  base?: Base;
}

export class Assignees {
  constructor(values?: Array<Assignee>) {
    this.values = values;
  }

  values?: Array<Assignee>;
}

export class Assignee {
  constructor(
    id?: number,
    login?: string,
    name?: string,
    avatar_url?: string,
    url?: string,
    html_url?: string,
    remark?: string,
    followers_url?: string,
    following_url?: string,
    gists_url?: string,
    starred_url?: string,
    subscriptions_url?: string,
    organizations_url?: string,
    repos_url?: string,
    events_url?: string,
    received_events_url?: string,
    type?: string,
    assignee?: boolean,
    code_owner?: boolean,
    accept?: boolean
  ) {
    this.id = id;
    this.login = login;
    this.name = name;
    this.avatar_url = avatar_url;
    this.url = url;
    this.html_url = html_url;
    this.remark = remark;
    this.followers_url = followers_url;
    this.following_url = following_url;
    this.gists_url = gists_url;
    this.starred_url = starred_url;
    this.subscriptions_url = subscriptions_url;
    this.organizations_url = organizations_url;
    this.repos_url = repos_url;
    this.events_url = events_url;
    this.received_events_url = received_events_url;
    this.type = type;
    this.assignee = assignee;
    this.code_owner = code_owner;
    this.accept = accept;
  }

  id?: number;
  login?: string;
  name?: string;
  avatar_url?: string;
  url?: string;
  html_url?: string;
  remark?: string;
  followers_url?: string;
  following_url?: string;
  gists_url?: string;
  starred_url?: string;
  subscriptions_url?: string;
  organizations_url?: string;
  repos_url?: string;
  events_url?: string;
  received_events_url?: string;
  type?: string;
  assignee?: boolean;
  code_owner?: boolean;
  accept?: boolean;
}

export class ApiReviewers {
  constructor(values?: Array<ApiReviewer>) {
    this.values = values;
  }

  values?: Array<ApiReviewer>;
}

class ApiReviewer {}

class Milestone {}

export class Labels {
  constructor(values?: Array<Label>) {
    this.values = values;
  }

  values?: Array<Label>;
}

export class Label {
  constructor(
    id?: number,
    color?: string,
    name?: string,
    repository_id?: number,
    url?: string,
    created_at?: Date,
    updated_at?: Date
  ) {
    this.id = id;
    this.color = color;
    this.name = name;
    this.repository_id = repository_id;
    this.url = url;
    this.created_at = created_at;
    this.updated_at = updated_at;
  }

  id?: number;
  color?: string;
  name?: string;
  repository_id?: number;
  url?: string;
  created_at?: Date;
  updated_at?: Date;
}

export class Links {
  constructor(
    self?: Link,
    html?: Link,
    issue?: Link,
    comments?: Link,
    review_comments?: Link,
    review_comment?: Link,
    commits?: Link
  ) {
    this.self = self;
    this.html = html;
    this.issue = issue;
    this.comments = comments;
    this.review_comments = review_comments;
    this.review_comment = review_comment;
    this.commits = commits;
  }

  self?: Link;
  html?: Link;
  issue?: Link;
  comments?: Link;
  review_comments?: Link;
  review_comment?: Link;
  commits?: Link;
}

export class Link {
  constructor(href?: string) {
    this.href = href;
  }

  href?: string;
}

export class User {
  constructor(
    id?: number,
    login?: string,
    name?: string,
    avatar_url?: string,
    url?: string,
    html_url?: string,
    remark?: string,
    followers_url?: string,
    following_url?: string,
    gists_url?: string,
    starred_url?: string,
    subscriptions_url?: string,
    organizations_url?: string,
    repos_url?: string,
    events_url?: string,
    received_events_url?: string,
    type?: string
  ) {
    this.id = id;
    this.login = login;
    this.name = name;
    this.avatar_url = avatar_url;
    this.url = url;
    this.html_url = html_url;
    this.remark = remark;
    this.followers_url = followers_url;
    this.following_url = following_url;
    this.gists_url = gists_url;
    this.starred_url = starred_url;
    this.subscriptions_url = subscriptions_url;
    this.organizations_url = organizations_url;
    this.repos_url = repos_url;
    this.events_url = events_url;
    this.received_events_url = received_events_url;
    this.type = type;
  }

  id?: number;
  login?: string;
  name?: string;
  avatar_url?: string;
  url?: string;
  html_url?: string;
  remark?: string;
  followers_url?: string;
  following_url?: string;
  gists_url?: string;
  starred_url?: string;
  subscriptions_url?: string;
  organizations_url?: string;
  repos_url?: string;
  events_url?: string;
  received_events_url?: string;
  type?: string;
}

export class Head {
  constructor(
    label?: string,
    ref?: string,
    sha?: string,
    user?: User,
    repo?: Repo
  ) {
    this.label = label;
    this.ref = ref;
    this.sha = sha;
    this.user = user;
    this.repo = repo;
  }

  label?: string;
  ref?: string;
  sha?: string;
  user?: User;
  repo?: Repo;
}

export class Repo {
  constructor(
    id?: number,
    full_name?: string,
    human_name?: string,
    url?: string,
    namespace_?: Namespace,
    path?: string,
    name?: string,
    owner?: User,
    assigner?: User,
    description?: string,
    private_?: boolean,
    public_?: boolean,
    internal_?: boolean,
    fork?: boolean,
    html_url?: string,
    ssh_url?: string
  ) {
    this.id = id;
    this.full_name = full_name;
    this.human_name = human_name;
    this.url = url;
    this.namespace_ = namespace_;
    this.path = path;
    this.name = name;
    this.owner = owner;
    this.assigner = assigner;
    this.description = description;
    this.private_ = private_;
    this.public_ = public_;
    this.internal_ = internal_;
    this.fork = fork;
    this.html_url = html_url;
    this.ssh_url = ssh_url;
  }

  id?: number;
  full_name?: string;
  human_name?: string;
  url?: string;
  namespace_?: Namespace;
  path?: string;
  name?: string;
  owner?: User;
  assigner?: User;
  description?: string;
  private_?: boolean;
  public_?: boolean;
  internal_?: boolean;
  fork?: boolean;
  html_url?: string;
  ssh_url?: string;
}

export class Namespace {
  constructor(
    id?: number,
    type?: string,
    name?: string,
    path?: string,
    html_url?: string
  ) {
    this.id = id;
    this.type = type;
    this.name = name;
    this.path = path;
    this.html_url = html_url;
  }

  id?: number;
  type?: string;
  name?: string;
  path?: string;
  html_url?: string;
}

export class Base {
  constructor(
    label?: string,
    ref?: string,
    sha?: string,
    user?: User,
    repo?: Repo
  ) {
    this.label = label;
    this.ref = ref;
    this.sha = sha;
    this.user = user;
    this.repo = repo;
  }

  label?: string;
  ref?: string;
  sha?: string;
  user?: User;
  repo?: Repo;
}

export function MockPRsData(): PRs {
  return new PRs(
    /*values = */ new Array<PR>(
      MockPR0(),
      MockPR1(),
      MockPR2(),
      MockPR3(),
      MockPR4()
    )
  );
}
function MockPR0(): PR {
  return new PR(
    /*id = */ 13121900,
    /*url = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core/pulls/3006`,
    /*html_url = */ `https://gitee.com/openharmony/arkcompiler_runtime_core/pulls/3006`,
    /*diff_url = */ `https://gitee.com/openharmony/arkcompiler_runtime_core/pulls/3006.diff`,
    /*patch_url = */ `https://gitee.com/openharmony/arkcompiler_runtime_core/pulls/3006.patch`,
    /*issue_url = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core/pulls/3006/issues`,
    /*commits_url = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core/pulls/3006/commits`,
    /*review_comments_url = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core/pulls/comments/{/number}`,
    /*review_comment_url = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core/pulls/comments`,
    /*comments_url = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core/pulls/3006/comments`,
    /*number = */ 3006,
    /*close_related_issue = */ 1,
    /*prune_branch = */ false,
    /*state = */ `open`,
    /*assignees_number = */ 1,
    /*testers_number = */ 1,
    /*assignees = */ new Assignees(
      /*values = */ new Array<Assignee>(
        new Assignee(
          /*id = */ 5654864,
          /*login = */ `egavrin`,
          /*name = */ `egavrin`,
          /*avatar_url = */ `https://gitee.com/assets/no_portrait.png`,
          /*url = */ `https://gitee.com/api//users/egavrin`,
          /*html_url = */ `https://gitee.com/egavrin`,
          /*remark = */ ``,
          /*followers_url = */ `https://gitee.com/api//users/egavrin/followers`,
          /*following_url = */ `https://gitee.com/api//users/egavrin/following_url{/other_user}`,
          /*gists_url = */ `https://gitee.com/api//users/egavrin/gists{/gist_id}`,
          /*starred_url = */ `https://gitee.com/api//users/egavrin/starred{/owner}{/repo}`,
          /*subscriptions_url = */ `https://gitee.com/api//users/egavrin/subscriptions`,
          /*organizations_url = */ `https://gitee.com/api//users/egavrin/orgs`,
          /*repos_url = */ `https://gitee.com/api//users/egavrin/repos`,
          /*events_url = */ `https://gitee.com/api//users/egavrin/events{/privacy}`,
          /*received_events_url = */ `https://gitee.com/api//users/egavrin/received_events`,
          /*type = */ `User`,
          /*assignee = */ false,
          /*code_owner = */ true,
          /*accept = */ false
        ),
        new Assignee(
          /*id = */ 7847922,
          /*login = */ `godmiaozi`,
          /*name = */ `godmiaozi`,
          /*avatar_url = */ `https://gitee.com/assets/no_portrait.png`,
          /*url = */ `https://gitee.com/api//users/godmiaozi`,
          /*html_url = */ `https://gitee.com/godmiaozi`,
          /*remark = */ ``,
          /*followers_url = */ `https://gitee.com/api//users/godmiaozi/followers`,
          /*following_url = */ `https://gitee.com/api//users/godmiaozi/following_url{/other_user}`,
          /*gists_url = */ `https://gitee.com/api//users/godmiaozi/gists{/gist_id}`,
          /*starred_url = */ `https://gitee.com/api//users/godmiaozi/starred{/owner}{/repo}`,
          /*subscriptions_url = */ `https://gitee.com/api//users/godmiaozi/subscriptions`,
          /*organizations_url = */ `https://gitee.com/api//users/godmiaozi/orgs`,
          /*repos_url = */ `https://gitee.com/api//users/godmiaozi/repos`,
          /*events_url = */ `https://gitee.com/api//users/godmiaozi/events{/privacy}`,
          /*received_events_url = */ `https://gitee.com/api//users/godmiaozi/received_events`,
          /*type = */ `User`,
          /*assignee = */ true,
          /*code_owner = */ false,
          /*accept = */ false
        ),
        new Assignee(
          /*id = */ 9580322,
          /*login = */ `ctw-ian`,
          /*name = */ `ctw-ian`,
          /*avatar_url = */ `https://gitee.com/assets/no_portrait.png`,
          /*url = */ `https://gitee.com/api//users/ctw-ian`,
          /*html_url = */ `https://gitee.com/ctw-ian`,
          /*remark = */ ``,
          /*followers_url = */ `https://gitee.com/api//users/ctw-ian/followers`,
          /*following_url = */ `https://gitee.com/api//users/ctw-ian/following_url{/other_user}`,
          /*gists_url = */ `https://gitee.com/api//users/ctw-ian/gists{/gist_id}`,
          /*starred_url = */ `https://gitee.com/api//users/ctw-ian/starred{/owner}{/repo}`,
          /*subscriptions_url = */ `https://gitee.com/api//users/ctw-ian/subscriptions`,
          /*organizations_url = */ `https://gitee.com/api//users/ctw-ian/orgs`,
          /*repos_url = */ `https://gitee.com/api//users/ctw-ian/repos`,
          /*events_url = */ `https://gitee.com/api//users/ctw-ian/events{/privacy}`,
          /*received_events_url = */ `https://gitee.com/api//users/ctw-ian/received_events`,
          /*type = */ `User`,
          /*assignee = */ true,
          /*code_owner = */ false,
          /*accept = */ false
        ),
        new Assignee(
          /*id = */ 9663914,
          /*login = */ `peijiajun`,
          /*name = */ `peijiajun`,
          /*avatar_url = */ `https://gitee.com/assets/no_portrait.png`,
          /*url = */ `https://gitee.com/api//users/peijiajun`,
          /*html_url = */ `https://gitee.com/peijiajun`,
          /*remark = */ ``,
          /*followers_url = */ `https://gitee.com/api//users/peijiajun/followers`,
          /*following_url = */ `https://gitee.com/api//users/peijiajun/following_url{/other_user}`,
          /*gists_url = */ `https://gitee.com/api//users/peijiajun/gists{/gist_id}`,
          /*starred_url = */ `https://gitee.com/api//users/peijiajun/starred{/owner}{/repo}`,
          /*subscriptions_url = */ `https://gitee.com/api//users/peijiajun/subscriptions`,
          /*organizations_url = */ `https://gitee.com/api//users/peijiajun/orgs`,
          /*repos_url = */ `https://gitee.com/api//users/peijiajun/repos`,
          /*events_url = */ `https://gitee.com/api//users/peijiajun/events{/privacy}`,
          /*received_events_url = */ `https://gitee.com/api//users/peijiajun/received_events`,
          /*type = */ `User`,
          /*assignee = */ true,
          /*code_owner = */ false,
          /*accept = */ false
        ),
        new Assignee(
          /*id = */ 11228302,
          /*login = */ `Prof1983`,
          /*name = */ `Ishin Pavel`,
          /*avatar_url = */ `https://foruda.gitee.com/avatar/1677231228555595315/11228302_prof1983_1657184805.png`,
          /*url = */ `https://gitee.com/api//users/Prof1983`,
          /*html_url = */ `https://gitee.com/Prof1983`,
          /*remark = */ ``,
          /*followers_url = */ `https://gitee.com/api//users/Prof1983/followers`,
          /*following_url = */ `https://gitee.com/api//users/Prof1983/following_url{/other_user}`,
          /*gists_url = */ `https://gitee.com/api//users/Prof1983/gists{/gist_id}`,
          /*starred_url = */ `https://gitee.com/api//users/Prof1983/starred{/owner}{/repo}`,
          /*subscriptions_url = */ `https://gitee.com/api//users/Prof1983/subscriptions`,
          /*organizations_url = */ `https://gitee.com/api//users/Prof1983/orgs`,
          /*repos_url = */ `https://gitee.com/api//users/Prof1983/repos`,
          /*events_url = */ `https://gitee.com/api//users/Prof1983/events{/privacy}`,
          /*received_events_url = */ `https://gitee.com/api//users/Prof1983/received_events`,
          /*type = */ `User`,
          /*assignee = */ true,
          /*code_owner = */ false,
          /*accept = */ false
        )
      )
    ),
    /*testers = */ new Assignees(
      /*values = */ new Array<Assignee>(
        new Assignee(
          /*id = */ 7387629,
          /*login = */ `openharmony_ci`,
          /*name = */ `openharmony_ci`,
          /*avatar_url = */ `https://foruda.gitee.com/avatar/1677075395966509043/7387629_openharmony_ci_1656582662.png`,
          /*url = */ `https://gitee.com/api//users/openharmony_ci`,
          /*html_url = */ `https://gitee.com/openharmony_ci`,
          /*remark = */ ``,
          /*followers_url = */ `https://gitee.com/api//users/openharmony_ci/followers`,
          /*following_url = */ `https://gitee.com/api//users/openharmony_ci/following_url{/other_user}`,
          /*gists_url = */ `https://gitee.com/api//users/openharmony_ci/gists{/gist_id}`,
          /*starred_url = */ `https://gitee.com/api//users/openharmony_ci/starred{/owner}{/repo}`,
          /*subscriptions_url = */ `https://gitee.com/api//users/openharmony_ci/subscriptions`,
          /*organizations_url = */ `https://gitee.com/api//users/openharmony_ci/orgs`,
          /*repos_url = */ `https://gitee.com/api//users/openharmony_ci/repos`,
          /*events_url = */ `https://gitee.com/api//users/openharmony_ci/events{/privacy}`,
          /*received_events_url = */ `https://gitee.com/api//users/openharmony_ci/received_events`,
          /*type = */ `User`,
          /*assignee = */ true,
          /*code_owner = */ false,
          /*accept = */ false
        )
      )
    ),
    /*api_reviewers_number = */ 0,
    /*api_reviewers = */ new ApiReviewers(
      /*values = */ new Array<ApiReviewer>()
    ),
    /*milestone = */ undefined,
    /*labels = */ new Labels(
      /*values = */ new Array<Label>(
        new Label(
          /*id = */ 113667295,
          /*color = */ `20c22e`,
          /*name = */ `dco检查成功`,
          /*repository_id = */ 6511493,
          /*url = */ `https://gitee.com/api/v5/enterprises/open_harmony/labels/dco检查成功`,
          /*created_at = */ new Date(1624000115000),
          /*updated_at = */ new Date(1733748579000)
        ),
        new Label(
          /*id = */ 200819422,
          /*color = */ `1083d6`,
          /*name = */ `waiting_on_author`,
          /*repository_id = */ 6511493,
          /*url = */ `https://gitee.com/api/v5/enterprises/open_harmony/labels/waiting_on_author`,
          /*created_at = */ new Date(1682247421000),
          /*updated_at = */ new Date(1733748606000)
        )
      )
    ),
    /*locked = */ false,
    /*created_at = */ new Date(1733743853000),
    /*updated_at = */ new Date(1733748563000),
    /*closed_at = */ undefined,
    /*draft = */ false,
    /*merged_at = */ undefined,
    /*mergeable = */ true,
    /*can_merge_check = */ false,
    /*_links = */ new Links(
      /*self = */ new Link(
        /*href = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core/pulls/3006`
      ),
      /*html = */ new Link(
        /*href = */ `https://gitee.com/openharmony/arkcompiler_runtime_core/pulls/3006`
      ),
      /*issue = */ new Link(
        /*href = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core/pulls/3006/issues`
      ),
      /*comments = */ new Link(
        /*href = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core/pulls/3006/comments`
      ),
      /*review_comments = */ new Link(
        /*href = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core/pulls/3006/comments`
      ),
      /*review_comment = */ new Link(
        /*href = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core/pulls/comments/3006`
      ),
      /*commits = */ new Link(
        /*href = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core/pulls/3006/commits`
      )
    ),
    /*user = */ new User(
      /*id = */ 7872983,
      /*login = */ `lu_jiahui`,
      /*name = */ `陆佳慧`,
      /*avatar_url = */ `https://gitee.com/assets/no_portrait.png`,
      /*url = */ `https://gitee.com/api/v5/users/lu_jiahui`,
      /*html_url = */ `https://gitee.com/lu_jiahui`,
      /*remark = */ ``,
      /*followers_url = */ `https://gitee.com/api/v5/users/lu_jiahui/followers`,
      /*following_url = */ `https://gitee.com/api/v5/users/lu_jiahui/following_url{/other_user}`,
      /*gists_url = */ `https://gitee.com/api/v5/users/lu_jiahui/gists{/gist_id}`,
      /*starred_url = */ `https://gitee.com/api/v5/users/lu_jiahui/starred{/owner}{/repo}`,
      /*subscriptions_url = */ `https://gitee.com/api/v5/users/lu_jiahui/subscriptions`,
      /*organizations_url = */ `https://gitee.com/api/v5/users/lu_jiahui/orgs`,
      /*repos_url = */ `https://gitee.com/api/v5/users/lu_jiahui/repos`,
      /*events_url = */ `https://gitee.com/api/v5/users/lu_jiahui/events{/privacy}`,
      /*received_events_url = */ `https://gitee.com/api/v5/users/lu_jiahui/received_events`,
      /*type = */ `User`
    ),
    /*ref_pull_requests = */ new PRs(/*values = */ new Array<PR>()),
    /*title = */ `Adapt Interop codes for new napi interfaces`,
    /*body = */ `Change-Id: I184592c59982999911d6becc445384dc9f1c9f03
### **Issue**
https://gitee.com/openharmony/arkcompiler_ets_runtime/issues/IBA4HA
### **Reason**
Adapt interop_js codes with new  napi interfaces

### **Description**
Adapt interop_js codes with napi_wrap_proxy、napi_unwrap_proxy、napi_create_proxy_reference

### **Tests**

ninja ets_interop_tests
ark_js_host_unittest

**All required pre-merge tests passed. Results are available in the internal CI.**
`,
    /*head = */ new Head(
      /*label = */ `adaptInteropForNewNapiInterface1108`,
      /*ref = */ `adaptInteropForNewNapiInterface1108`,
      /*sha = */ `2a252dfacd1210f74db4b47b352113a64046c558`,
      /*user = */ new User(
        /*id = */ 7872983,
        /*login = */ `lu_jiahui`,
        /*name = */ `陆佳慧`,
        /*avatar_url = */ `https://gitee.com/assets/no_portrait.png`,
        /*url = */ `https://gitee.com/api/v5/users/lu_jiahui`,
        /*html_url = */ `https://gitee.com/lu_jiahui`,
        /*remark = */ ``,
        /*followers_url = */ `https://gitee.com/api/v5/users/lu_jiahui/followers`,
        /*following_url = */ `https://gitee.com/api/v5/users/lu_jiahui/following_url{/other_user}`,
        /*gists_url = */ `https://gitee.com/api/v5/users/lu_jiahui/gists{/gist_id}`,
        /*starred_url = */ `https://gitee.com/api/v5/users/lu_jiahui/starred{/owner}{/repo}`,
        /*subscriptions_url = */ `https://gitee.com/api/v5/users/lu_jiahui/subscriptions`,
        /*organizations_url = */ `https://gitee.com/api/v5/users/lu_jiahui/orgs`,
        /*repos_url = */ `https://gitee.com/api/v5/users/lu_jiahui/repos`,
        /*events_url = */ `https://gitee.com/api/v5/users/lu_jiahui/events{/privacy}`,
        /*received_events_url = */ `https://gitee.com/api/v5/users/lu_jiahui/received_events`,
        /*type = */ `User`
      ),
      /*repo = */ new Repo(
        /*id = */ 35777454,
        /*full_name = */ `lu_jiahui/arkcompiler_runtime_core`,
        /*human_name = */ `陆佳慧/arkcompiler_runtime_core`,
        /*url = */ `https://gitee.com/api/v5/repos/lu_jiahui/arkcompiler_runtime_core`,
        /*namespace_ = */ new Namespace(
          /*id = */ 6425144,
          /*type = */ `personal`,
          /*name = */ `陆佳慧`,
          /*path = */ `lu_jiahui`,
          /*html_url = */ `https://gitee.com/lu_jiahui`
        ),
        /*path = */ `arkcompiler_runtime_core`,
        /*name = */ `arkcompiler_runtime_core`,
        /*owner = */ new User(
          /*id = */ 7872983,
          /*login = */ `lu_jiahui`,
          /*name = */ `陆佳慧`,
          /*avatar_url = */ `https://gitee.com/assets/no_portrait.png`,
          /*url = */ `https://gitee.com/api/v5/users/lu_jiahui`,
          /*html_url = */ `https://gitee.com/lu_jiahui`,
          /*remark = */ ``,
          /*followers_url = */ `https://gitee.com/api/v5/users/lu_jiahui/followers`,
          /*following_url = */ `https://gitee.com/api/v5/users/lu_jiahui/following_url{/other_user}`,
          /*gists_url = */ `https://gitee.com/api/v5/users/lu_jiahui/gists{/gist_id}`,
          /*starred_url = */ `https://gitee.com/api/v5/users/lu_jiahui/starred{/owner}{/repo}`,
          /*subscriptions_url = */ `https://gitee.com/api/v5/users/lu_jiahui/subscriptions`,
          /*organizations_url = */ `https://gitee.com/api/v5/users/lu_jiahui/orgs`,
          /*repos_url = */ `https://gitee.com/api/v5/users/lu_jiahui/repos`,
          /*events_url = */ `https://gitee.com/api/v5/users/lu_jiahui/events{/privacy}`,
          /*received_events_url = */ `https://gitee.com/api/v5/users/lu_jiahui/received_events`,
          /*type = */ `User`
        ),
        /*assigner = */ new User(
          /*id = */ 7872983,
          /*login = */ `lu_jiahui`,
          /*name = */ `陆佳慧`,
          /*avatar_url = */ `https://gitee.com/assets/no_portrait.png`,
          /*url = */ `https://gitee.com/api/v5/users/lu_jiahui`,
          /*html_url = */ `https://gitee.com/lu_jiahui`,
          /*remark = */ ``,
          /*followers_url = */ `https://gitee.com/api/v5/users/lu_jiahui/followers`,
          /*following_url = */ `https://gitee.com/api/v5/users/lu_jiahui/following_url{/other_user}`,
          /*gists_url = */ `https://gitee.com/api/v5/users/lu_jiahui/gists{/gist_id}`,
          /*starred_url = */ `https://gitee.com/api/v5/users/lu_jiahui/starred{/owner}{/repo}`,
          /*subscriptions_url = */ `https://gitee.com/api/v5/users/lu_jiahui/subscriptions`,
          /*organizations_url = */ `https://gitee.com/api/v5/users/lu_jiahui/orgs`,
          /*repos_url = */ `https://gitee.com/api/v5/users/lu_jiahui/repos`,
          /*events_url = */ `https://gitee.com/api/v5/users/lu_jiahui/events{/privacy}`,
          /*received_events_url = */ `https://gitee.com/api/v5/users/lu_jiahui/received_events`,
          /*type = */ `User`
        ),
        /*description = */ `暂无描述`,
        /*private_ = */ false,
        /*public_ = */ true,
        /*internal_ = */ false,
        /*fork = */ true,
        /*html_url = */ `https://gitee.com/lu_jiahui/arkcompiler_runtime_core.git`,
        /*ssh_url = */ `git@gitee.com:lu_jiahui/arkcompiler_runtime_core.git`
      )
    ),
    /*base = */ new Base(
      /*label = */ `OpenHarmony_feature_20241108`,
      /*ref = */ `OpenHarmony_feature_20241108`,
      /*sha = */ `d212656f6aaa6a5a7cbfb74e07888030e38f8046`,
      /*user = */ new User(
        /*id = */ 7928036,
        /*login = */ `openharmony_admin`,
        /*name = */ `openharmony`,
        /*avatar_url = */ `https://foruda.gitee.com/avatar/1677102952566165682/7928036_openharmony_admin_1622551091.png`,
        /*url = */ `https://gitee.com/api/v5/users/openharmony_admin`,
        /*html_url = */ `https://gitee.com/openharmony_admin`,
        /*remark = */ ``,
        /*followers_url = */ `https://gitee.com/api/v5/users/openharmony_admin/followers`,
        /*following_url = */ `https://gitee.com/api/v5/users/openharmony_admin/following_url{/other_user}`,
        /*gists_url = */ `https://gitee.com/api/v5/users/openharmony_admin/gists{/gist_id}`,
        /*starred_url = */ `https://gitee.com/api/v5/users/openharmony_admin/starred{/owner}{/repo}`,
        /*subscriptions_url = */ `https://gitee.com/api/v5/users/openharmony_admin/subscriptions`,
        /*organizations_url = */ `https://gitee.com/api/v5/users/openharmony_admin/orgs`,
        /*repos_url = */ `https://gitee.com/api/v5/users/openharmony_admin/repos`,
        /*events_url = */ `https://gitee.com/api/v5/users/openharmony_admin/events{/privacy}`,
        /*received_events_url = */ `https://gitee.com/api/v5/users/openharmony_admin/received_events`,
        /*type = */ `User`
      ),
      /*repo = */ new Repo(
        /*id = */ 17812929,
        /*full_name = */ `openharmony/arkcompiler_runtime_core`,
        /*human_name = */ `OpenHarmony/arkcompiler_runtime_core`,
        /*url = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core`,
        /*namespace_ = */ new Namespace(
          /*id = */ 6486504,
          /*type = */ `group`,
          /*name = */ `OpenHarmony`,
          /*path = */ `openharmony`,
          /*html_url = */ `https://gitee.com/openharmony`
        ),
        /*path = */ `arkcompiler_runtime_core`,
        /*name = */ `arkcompiler_runtime_core`,
        /*owner = */ new User(
          /*id = */ 7928036,
          /*login = */ `openharmony_admin`,
          /*name = */ `openharmony`,
          /*avatar_url = */ `https://foruda.gitee.com/avatar/1677102952566165682/7928036_openharmony_admin_1622551091.png`,
          /*url = */ `https://gitee.com/api/v5/users/openharmony_admin`,
          /*html_url = */ `https://gitee.com/openharmony_admin`,
          /*remark = */ ``,
          /*followers_url = */ `https://gitee.com/api/v5/users/openharmony_admin/followers`,
          /*following_url = */ `https://gitee.com/api/v5/users/openharmony_admin/following_url{/other_user}`,
          /*gists_url = */ `https://gitee.com/api/v5/users/openharmony_admin/gists{/gist_id}`,
          /*starred_url = */ `https://gitee.com/api/v5/users/openharmony_admin/starred{/owner}{/repo}`,
          /*subscriptions_url = */ `https://gitee.com/api/v5/users/openharmony_admin/subscriptions`,
          /*organizations_url = */ `https://gitee.com/api/v5/users/openharmony_admin/orgs`,
          /*repos_url = */ `https://gitee.com/api/v5/users/openharmony_admin/repos`,
          /*events_url = */ `https://gitee.com/api/v5/users/openharmony_admin/events{/privacy}`,
          /*received_events_url = */ `https://gitee.com/api/v5/users/openharmony_admin/received_events`,
          /*type = */ `User`
        ),
        /*assigner = */ new User(
          /*id = */ 7928036,
          /*login = */ `openharmony_admin`,
          /*name = */ `openharmony`,
          /*avatar_url = */ `https://foruda.gitee.com/avatar/1677102952566165682/7928036_openharmony_admin_1622551091.png`,
          /*url = */ `https://gitee.com/api/v5/users/openharmony_admin`,
          /*html_url = */ `https://gitee.com/openharmony_admin`,
          /*remark = */ ``,
          /*followers_url = */ `https://gitee.com/api/v5/users/openharmony_admin/followers`,
          /*following_url = */ `https://gitee.com/api/v5/users/openharmony_admin/following_url{/other_user}`,
          /*gists_url = */ `https://gitee.com/api/v5/users/openharmony_admin/gists{/gist_id}`,
          /*starred_url = */ `https://gitee.com/api/v5/users/openharmony_admin/starred{/owner}{/repo}`,
          /*subscriptions_url = */ `https://gitee.com/api/v5/users/openharmony_admin/subscriptions`,
          /*organizations_url = */ `https://gitee.com/api/v5/users/openharmony_admin/orgs`,
          /*repos_url = */ `https://gitee.com/api/v5/users/openharmony_admin/repos`,
          /*events_url = */ `https://gitee.com/api/v5/users/openharmony_admin/events{/privacy}`,
          /*received_events_url = */ `https://gitee.com/api/v5/users/openharmony_admin/received_events`,
          /*type = */ `User`
        ),
        /*description = */ `暂无描述`,
        /*private_ = */ false,
        /*public_ = */ true,
        /*internal_ = */ false,
        /*fork = */ false,
        /*html_url = */ `https://gitee.com/openharmony/arkcompiler_runtime_core.git`,
        /*ssh_url = */ `git@gitee.com:openharmony/arkcompiler_runtime_core.git`
      )
    )
  );
}
function MockPR1(): PR {
  return new PR(
    /*id = */ 13121191,
    /*url = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core/pulls/3005`,
    /*html_url = */ `https://gitee.com/openharmony/arkcompiler_runtime_core/pulls/3005`,
    /*diff_url = */ `https://gitee.com/openharmony/arkcompiler_runtime_core/pulls/3005.diff`,
    /*patch_url = */ `https://gitee.com/openharmony/arkcompiler_runtime_core/pulls/3005.patch`,
    /*issue_url = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core/pulls/3005/issues`,
    /*commits_url = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core/pulls/3005/commits`,
    /*review_comments_url = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core/pulls/comments/{/number}`,
    /*review_comment_url = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core/pulls/comments`,
    /*comments_url = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core/pulls/3005/comments`,
    /*number = */ 3005,
    /*close_related_issue = */ 1,
    /*prune_branch = */ false,
    /*state = */ `open`,
    /*assignees_number = */ 1,
    /*testers_number = */ 1,
    /*assignees = */ new Assignees(
      /*values = */ new Array<Assignee>(
        new Assignee(
          /*id = */ 5654864,
          /*login = */ `egavrin`,
          /*name = */ `egavrin`,
          /*avatar_url = */ `https://gitee.com/assets/no_portrait.png`,
          /*url = */ `https://gitee.com/api//users/egavrin`,
          /*html_url = */ `https://gitee.com/egavrin`,
          /*remark = */ ``,
          /*followers_url = */ `https://gitee.com/api//users/egavrin/followers`,
          /*following_url = */ `https://gitee.com/api//users/egavrin/following_url{/other_user}`,
          /*gists_url = */ `https://gitee.com/api//users/egavrin/gists{/gist_id}`,
          /*starred_url = */ `https://gitee.com/api//users/egavrin/starred{/owner}{/repo}`,
          /*subscriptions_url = */ `https://gitee.com/api//users/egavrin/subscriptions`,
          /*organizations_url = */ `https://gitee.com/api//users/egavrin/orgs`,
          /*repos_url = */ `https://gitee.com/api//users/egavrin/repos`,
          /*events_url = */ `https://gitee.com/api//users/egavrin/events{/privacy}`,
          /*received_events_url = */ `https://gitee.com/api//users/egavrin/received_events`,
          /*type = */ `User`,
          /*assignee = */ false,
          /*code_owner = */ true,
          /*accept = */ false
        ),
        new Assignee(
          /*id = */ 7847922,
          /*login = */ `godmiaozi`,
          /*name = */ `godmiaozi`,
          /*avatar_url = */ `https://gitee.com/assets/no_portrait.png`,
          /*url = */ `https://gitee.com/api//users/godmiaozi`,
          /*html_url = */ `https://gitee.com/godmiaozi`,
          /*remark = */ ``,
          /*followers_url = */ `https://gitee.com/api//users/godmiaozi/followers`,
          /*following_url = */ `https://gitee.com/api//users/godmiaozi/following_url{/other_user}`,
          /*gists_url = */ `https://gitee.com/api//users/godmiaozi/gists{/gist_id}`,
          /*starred_url = */ `https://gitee.com/api//users/godmiaozi/starred{/owner}{/repo}`,
          /*subscriptions_url = */ `https://gitee.com/api//users/godmiaozi/subscriptions`,
          /*organizations_url = */ `https://gitee.com/api//users/godmiaozi/orgs`,
          /*repos_url = */ `https://gitee.com/api//users/godmiaozi/repos`,
          /*events_url = */ `https://gitee.com/api//users/godmiaozi/events{/privacy}`,
          /*received_events_url = */ `https://gitee.com/api//users/godmiaozi/received_events`,
          /*type = */ `User`,
          /*assignee = */ true,
          /*code_owner = */ false,
          /*accept = */ false
        ),
        new Assignee(
          /*id = */ 9580322,
          /*login = */ `ctw-ian`,
          /*name = */ `ctw-ian`,
          /*avatar_url = */ `https://gitee.com/assets/no_portrait.png`,
          /*url = */ `https://gitee.com/api//users/ctw-ian`,
          /*html_url = */ `https://gitee.com/ctw-ian`,
          /*remark = */ ``,
          /*followers_url = */ `https://gitee.com/api//users/ctw-ian/followers`,
          /*following_url = */ `https://gitee.com/api//users/ctw-ian/following_url{/other_user}`,
          /*gists_url = */ `https://gitee.com/api//users/ctw-ian/gists{/gist_id}`,
          /*starred_url = */ `https://gitee.com/api//users/ctw-ian/starred{/owner}{/repo}`,
          /*subscriptions_url = */ `https://gitee.com/api//users/ctw-ian/subscriptions`,
          /*organizations_url = */ `https://gitee.com/api//users/ctw-ian/orgs`,
          /*repos_url = */ `https://gitee.com/api//users/ctw-ian/repos`,
          /*events_url = */ `https://gitee.com/api//users/ctw-ian/events{/privacy}`,
          /*received_events_url = */ `https://gitee.com/api//users/ctw-ian/received_events`,
          /*type = */ `User`,
          /*assignee = */ true,
          /*code_owner = */ false,
          /*accept = */ false
        ),
        new Assignee(
          /*id = */ 9663914,
          /*login = */ `peijiajun`,
          /*name = */ `peijiajun`,
          /*avatar_url = */ `https://gitee.com/assets/no_portrait.png`,
          /*url = */ `https://gitee.com/api//users/peijiajun`,
          /*html_url = */ `https://gitee.com/peijiajun`,
          /*remark = */ ``,
          /*followers_url = */ `https://gitee.com/api//users/peijiajun/followers`,
          /*following_url = */ `https://gitee.com/api//users/peijiajun/following_url{/other_user}`,
          /*gists_url = */ `https://gitee.com/api//users/peijiajun/gists{/gist_id}`,
          /*starred_url = */ `https://gitee.com/api//users/peijiajun/starred{/owner}{/repo}`,
          /*subscriptions_url = */ `https://gitee.com/api//users/peijiajun/subscriptions`,
          /*organizations_url = */ `https://gitee.com/api//users/peijiajun/orgs`,
          /*repos_url = */ `https://gitee.com/api//users/peijiajun/repos`,
          /*events_url = */ `https://gitee.com/api//users/peijiajun/events{/privacy}`,
          /*received_events_url = */ `https://gitee.com/api//users/peijiajun/received_events`,
          /*type = */ `User`,
          /*assignee = */ true,
          /*code_owner = */ false,
          /*accept = */ false
        ),
        new Assignee(
          /*id = */ 11228302,
          /*login = */ `Prof1983`,
          /*name = */ `Ishin Pavel`,
          /*avatar_url = */ `https://foruda.gitee.com/avatar/1677231228555595315/11228302_prof1983_1657184805.png`,
          /*url = */ `https://gitee.com/api//users/Prof1983`,
          /*html_url = */ `https://gitee.com/Prof1983`,
          /*remark = */ ``,
          /*followers_url = */ `https://gitee.com/api//users/Prof1983/followers`,
          /*following_url = */ `https://gitee.com/api//users/Prof1983/following_url{/other_user}`,
          /*gists_url = */ `https://gitee.com/api//users/Prof1983/gists{/gist_id}`,
          /*starred_url = */ `https://gitee.com/api//users/Prof1983/starred{/owner}{/repo}`,
          /*subscriptions_url = */ `https://gitee.com/api//users/Prof1983/subscriptions`,
          /*organizations_url = */ `https://gitee.com/api//users/Prof1983/orgs`,
          /*repos_url = */ `https://gitee.com/api//users/Prof1983/repos`,
          /*events_url = */ `https://gitee.com/api//users/Prof1983/events{/privacy}`,
          /*received_events_url = */ `https://gitee.com/api//users/Prof1983/received_events`,
          /*type = */ `User`,
          /*assignee = */ true,
          /*code_owner = */ false,
          /*accept = */ false
        )
      )
    ),
    /*testers = */ new Assignees(
      /*values = */ new Array<Assignee>(
        new Assignee(
          /*id = */ 7387629,
          /*login = */ `openharmony_ci`,
          /*name = */ `openharmony_ci`,
          /*avatar_url = */ `https://foruda.gitee.com/avatar/1677075395966509043/7387629_openharmony_ci_1656582662.png`,
          /*url = */ `https://gitee.com/api//users/openharmony_ci`,
          /*html_url = */ `https://gitee.com/openharmony_ci`,
          /*remark = */ ``,
          /*followers_url = */ `https://gitee.com/api//users/openharmony_ci/followers`,
          /*following_url = */ `https://gitee.com/api//users/openharmony_ci/following_url{/other_user}`,
          /*gists_url = */ `https://gitee.com/api//users/openharmony_ci/gists{/gist_id}`,
          /*starred_url = */ `https://gitee.com/api//users/openharmony_ci/starred{/owner}{/repo}`,
          /*subscriptions_url = */ `https://gitee.com/api//users/openharmony_ci/subscriptions`,
          /*organizations_url = */ `https://gitee.com/api//users/openharmony_ci/orgs`,
          /*repos_url = */ `https://gitee.com/api//users/openharmony_ci/repos`,
          /*events_url = */ `https://gitee.com/api//users/openharmony_ci/events{/privacy}`,
          /*received_events_url = */ `https://gitee.com/api//users/openharmony_ci/received_events`,
          /*type = */ `User`,
          /*assignee = */ true,
          /*code_owner = */ false,
          /*accept = */ false
        )
      )
    ),
    /*api_reviewers_number = */ 0,
    /*api_reviewers = */ new ApiReviewers(
      /*values = */ new Array<ApiReviewer>()
    ),
    /*milestone = */ undefined,
    /*labels = */ new Labels(
      /*values = */ new Array<Label>(
        new Label(
          /*id = */ 113667295,
          /*color = */ `20c22e`,
          /*name = */ `dco检查成功`,
          /*repository_id = */ 6511493,
          /*url = */ `https://gitee.com/api/v5/enterprises/open_harmony/labels/dco检查成功`,
          /*created_at = */ new Date(1624000115000),
          /*updated_at = */ new Date(1733748579000)
        ),
        new Label(
          /*id = */ 200819422,
          /*color = */ `1083d6`,
          /*name = */ `waiting_on_author`,
          /*repository_id = */ 6511493,
          /*url = */ `https://gitee.com/api/v5/enterprises/open_harmony/labels/waiting_on_author`,
          /*created_at = */ new Date(1682247421000),
          /*updated_at = */ new Date(1733748606000)
        )
      )
    ),
    /*locked = */ false,
    /*created_at = */ new Date(1733739214000),
    /*updated_at = */ new Date(1733739358000),
    /*closed_at = */ undefined,
    /*draft = */ true,
    /*merged_at = */ undefined,
    /*mergeable = */ true,
    /*can_merge_check = */ false,
    /*_links = */ new Links(
      /*self = */ new Link(
        /*href = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core/pulls/3005`
      ),
      /*html = */ new Link(
        /*href = */ `https://gitee.com/openharmony/arkcompiler_runtime_core/pulls/3005`
      ),
      /*issue = */ new Link(
        /*href = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core/pulls/3005/issues`
      ),
      /*comments = */ new Link(
        /*href = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core/pulls/3005/comments`
      ),
      /*review_comments = */ new Link(
        /*href = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core/pulls/3005/comments`
      ),
      /*review_comment = */ new Link(
        /*href = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core/pulls/comments/3005`
      ),
      /*commits = */ new Link(
        /*href = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core/pulls/3005/commits`
      )
    ),
    /*user = */ new User(
      /*id = */ 14356530,
      /*login = */ `kkonkuznetsov`,
      /*name = */ `konstantin.kuznetsov`,
      /*avatar_url = */ `https://gitee.com/assets/no_portrait.png`,
      /*url = */ `https://gitee.com/api/v5/users/kkonkuznetsov`,
      /*html_url = */ `https://gitee.com/kkonkuznetsov`,
      /*remark = */ ``,
      /*followers_url = */ `https://gitee.com/api/v5/users/kkonkuznetsov/followers`,
      /*following_url = */ `https://gitee.com/api/v5/users/kkonkuznetsov/following_url{/other_user}`,
      /*gists_url = */ `https://gitee.com/api/v5/users/kkonkuznetsov/gists{/gist_id}`,
      /*starred_url = */ `https://gitee.com/api/v5/users/kkonkuznetsov/starred{/owner}{/repo}`,
      /*subscriptions_url = */ `https://gitee.com/api/v5/users/kkonkuznetsov/subscriptions`,
      /*organizations_url = */ `https://gitee.com/api/v5/users/kkonkuznetsov/orgs`,
      /*repos_url = */ `https://gitee.com/api/v5/users/kkonkuznetsov/repos`,
      /*events_url = */ `https://gitee.com/api/v5/users/kkonkuznetsov/events{/privacy}`,
      /*received_events_url = */ `https://gitee.com/api/v5/users/kkonkuznetsov/received_events`,
      /*type = */ `User`
    ),
    /*ref_pull_requests = */ new PRs(/*values = */ new Array<PR>()),
    /*title = */ `Remove interface tests from ignore lists`,
    /*body = */ `### **Issue**

### **Reason**

Remove interface tests from ignore lists

### **Description**

1) Updated all interface_fields tests and removed field assignment. Field assignment is prohibited in interfaces according to 10.5 Interface Properties specification. Added negative tests.
2) Marked all interface_fields_without_types tests as negative. Cannot create an interface field without assignment and without type.
3) Updated several_interface_fields test and removed field assignment. Field assignment is prohibited in interfaces according to 10.5 Interface Properties specification. Added negative test.
4) Marked some interface_members tests as negative. The body of an interface cannot contain other classes and interfaces. Also removed field assignment.
5) Marked some hided_members tests as negative. The body of an interface cannot contain other classes and interfaces. Also removed field assignment.
6) Marked member_type_access tests as negative. The body of an interface cannot contain other classes and interfaces.
7) Marked member_type_declaration tests as negative. The body of an interface cannot contain other classes and interfaces.
8) Marked multiple_member_inheritence test as negative. The body of an interface cannot contain other classes and interfaces.
9) Updated interface_field_decl test and removed field assignment. Field assignment is prohibited in interfaces according to 10.5 Interface Properties specification. Added negative test.
10) field_without_initializer is now a positive test.
11) Updated extend_clause test. Added this to function call.

### **Tests**


ninja all tests

**All required pre-merge tests passed. Results are available in the internal CI.**
`,
    /*head = */ new Head(
      /*label = */ `interface-tests`,
      /*ref = */ `interface-tests`,
      /*sha = */ `bd4b9db5da3a68da16a351482b7180cc353db2ad`,
      /*user = */ new User(
        /*id = */ 14356530,
        /*login = */ `kkonkuznetsov`,
        /*name = */ `konstantin.kuznetsov`,
        /*avatar_url = */ `https://gitee.com/assets/no_portrait.png`,
        /*url = */ `https://gitee.com/api/v5/users/kkonkuznetsov`,
        /*html_url = */ `https://gitee.com/kkonkuznetsov`,
        /*remark = */ ``,
        /*followers_url = */ `https://gitee.com/api/v5/users/kkonkuznetsov/followers`,
        /*following_url = */ `https://gitee.com/api/v5/users/kkonkuznetsov/following_url{/other_user}`,
        /*gists_url = */ `https://gitee.com/api/v5/users/kkonkuznetsov/gists{/gist_id}`,
        /*starred_url = */ `https://gitee.com/api/v5/users/kkonkuznetsov/starred{/owner}{/repo}`,
        /*subscriptions_url = */ `https://gitee.com/api/v5/users/kkonkuznetsov/subscriptions`,
        /*organizations_url = */ `https://gitee.com/api/v5/users/kkonkuznetsov/orgs`,
        /*repos_url = */ `https://gitee.com/api/v5/users/kkonkuznetsov/repos`,
        /*events_url = */ `https://gitee.com/api/v5/users/kkonkuznetsov/events{/privacy}`,
        /*received_events_url = */ `https://gitee.com/api/v5/users/kkonkuznetsov/received_events`,
        /*type = */ `User`
      ),
      /*repo = */ new Repo(
        /*id = */ 36251025,
        /*full_name = */ `kkonkuznetsov/arkcompiler_runtime_core`,
        /*human_name = */ `konstantin.kuznetsov/arkcompiler_runtime_core`,
        /*url = */ `https://gitee.com/api/v5/repos/kkonkuznetsov/arkcompiler_runtime_core`,
        /*namespace_ = */ new Namespace(
          /*id = */ 13481676,
          /*type = */ `personal`,
          /*name = */ `konstantin.kuznetsov`,
          /*path = */ `kkonkuznetsov`,
          /*html_url = */ `https://gitee.com/kkonkuznetsov`
        ),
        /*path = */ `arkcompiler_runtime_core`,
        /*name = */ `arkcompiler_runtime_core`,
        /*owner = */ new User(
          /*id = */ 14356530,
          /*login = */ `kkonkuznetsov`,
          /*name = */ `konstantin.kuznetsov`,
          /*avatar_url = */ `https://gitee.com/assets/no_portrait.png`,
          /*url = */ `https://gitee.com/api/v5/users/kkonkuznetsov`,
          /*html_url = */ `https://gitee.com/kkonkuznetsov`,
          /*remark = */ ``,
          /*followers_url = */ `https://gitee.com/api/v5/users/kkonkuznetsov/followers`,
          /*following_url = */ `https://gitee.com/api/v5/users/kkonkuznetsov/following_url{/other_user}`,
          /*gists_url = */ `https://gitee.com/api/v5/users/kkonkuznetsov/gists{/gist_id}`,
          /*starred_url = */ `https://gitee.com/api/v5/users/kkonkuznetsov/starred{/owner}{/repo}`,
          /*subscriptions_url = */ `https://gitee.com/api/v5/users/kkonkuznetsov/subscriptions`,
          /*organizations_url = */ `https://gitee.com/api/v5/users/kkonkuznetsov/orgs`,
          /*repos_url = */ `https://gitee.com/api/v5/users/kkonkuznetsov/repos`,
          /*events_url = */ `https://gitee.com/api/v5/users/kkonkuznetsov/events{/privacy}`,
          /*received_events_url = */ `https://gitee.com/api/v5/users/kkonkuznetsov/received_events`,
          /*type = */ `User`
        ),
        /*assigner = */ new User(
          /*id = */ 14356530,
          /*login = */ `kkonkuznetsov`,
          /*name = */ `konstantin.kuznetsov`,
          /*avatar_url = */ `https://gitee.com/assets/no_portrait.png`,
          /*url = */ `https://gitee.com/api/v5/users/kkonkuznetsov`,
          /*html_url = */ `https://gitee.com/kkonkuznetsov`,
          /*remark = */ ``,
          /*followers_url = */ `https://gitee.com/api/v5/users/kkonkuznetsov/followers`,
          /*following_url = */ `https://gitee.com/api/v5/users/kkonkuznetsov/following_url{/other_user}`,
          /*gists_url = */ `https://gitee.com/api/v5/users/kkonkuznetsov/gists{/gist_id}`,
          /*starred_url = */ `https://gitee.com/api/v5/users/kkonkuznetsov/starred{/owner}{/repo}`,
          /*subscriptions_url = */ `https://gitee.com/api/v5/users/kkonkuznetsov/subscriptions`,
          /*organizations_url = */ `https://gitee.com/api/v5/users/kkonkuznetsov/orgs`,
          /*repos_url = */ `https://gitee.com/api/v5/users/kkonkuznetsov/repos`,
          /*events_url = */ `https://gitee.com/api/v5/users/kkonkuznetsov/events{/privacy}`,
          /*received_events_url = */ `https://gitee.com/api/v5/users/kkonkuznetsov/received_events`,
          /*type = */ `User`
        ),
        /*description = */ `暂无描述`,
        /*private_ = */ false,
        /*public_ = */ true,
        /*internal_ = */ false,
        /*fork = */ true,
        /*html_url = */ `https://gitee.com/kkonkuznetsov/arkcompiler_runtime_core.git`,
        /*ssh_url = */ `git@gitee.com:kkonkuznetsov/arkcompiler_runtime_core.git`
      )
    ),
    /*base = */ new Base(
      /*label = */ `OpenHarmony_feature_20241108`,
      /*ref = */ `OpenHarmony_feature_20241108`,
      /*sha = */ `d212656f6aaa6a5a7cbfb74e07888030e38f8046`,
      /*user = */ new User(
        /*id = */ 7928036,
        /*login = */ `openharmony_admin`,
        /*name = */ `openharmony`,
        /*avatar_url = */ `https://foruda.gitee.com/avatar/1677102952566165682/7928036_openharmony_admin_1622551091.png`,
        /*url = */ `https://gitee.com/api/v5/users/openharmony_admin`,
        /*html_url = */ `https://gitee.com/openharmony_admin`,
        /*remark = */ ``,
        /*followers_url = */ `https://gitee.com/api/v5/users/openharmony_admin/followers`,
        /*following_url = */ `https://gitee.com/api/v5/users/openharmony_admin/following_url{/other_user}`,
        /*gists_url = */ `https://gitee.com/api/v5/users/openharmony_admin/gists{/gist_id}`,
        /*starred_url = */ `https://gitee.com/api/v5/users/openharmony_admin/starred{/owner}{/repo}`,
        /*subscriptions_url = */ `https://gitee.com/api/v5/users/openharmony_admin/subscriptions`,
        /*organizations_url = */ `https://gitee.com/api/v5/users/openharmony_admin/orgs`,
        /*repos_url = */ `https://gitee.com/api/v5/users/openharmony_admin/repos`,
        /*events_url = */ `https://gitee.com/api/v5/users/openharmony_admin/events{/privacy}`,
        /*received_events_url = */ `https://gitee.com/api/v5/users/openharmony_admin/received_events`,
        /*type = */ `User`
      ),
      /*repo = */ new Repo(
        /*id = */ 17812929,
        /*full_name = */ `openharmony/arkcompiler_runtime_core`,
        /*human_name = */ `OpenHarmony/arkcompiler_runtime_core`,
        /*url = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core`,
        /*namespace_ = */ new Namespace(
          /*id = */ 6486504,
          /*type = */ `group`,
          /*name = */ `OpenHarmony`,
          /*path = */ `openharmony`,
          /*html_url = */ `https://gitee.com/openharmony`
        ),
        /*path = */ `arkcompiler_runtime_core`,
        /*name = */ `arkcompiler_runtime_core`,
        /*owner = */ new User(
          /*id = */ 7928036,
          /*login = */ `openharmony_admin`,
          /*name = */ `openharmony`,
          /*avatar_url = */ `https://foruda.gitee.com/avatar/1677102952566165682/7928036_openharmony_admin_1622551091.png`,
          /*url = */ `https://gitee.com/api/v5/users/openharmony_admin`,
          /*html_url = */ `https://gitee.com/openharmony_admin`,
          /*remark = */ ``,
          /*followers_url = */ `https://gitee.com/api/v5/users/openharmony_admin/followers`,
          /*following_url = */ `https://gitee.com/api/v5/users/openharmony_admin/following_url{/other_user}`,
          /*gists_url = */ `https://gitee.com/api/v5/users/openharmony_admin/gists{/gist_id}`,
          /*starred_url = */ `https://gitee.com/api/v5/users/openharmony_admin/starred{/owner}{/repo}`,
          /*subscriptions_url = */ `https://gitee.com/api/v5/users/openharmony_admin/subscriptions`,
          /*organizations_url = */ `https://gitee.com/api/v5/users/openharmony_admin/orgs`,
          /*repos_url = */ `https://gitee.com/api/v5/users/openharmony_admin/repos`,
          /*events_url = */ `https://gitee.com/api/v5/users/openharmony_admin/events{/privacy}`,
          /*received_events_url = */ `https://gitee.com/api/v5/users/openharmony_admin/received_events`,
          /*type = */ `User`
        ),
        /*assigner = */ new User(
          /*id = */ 7928036,
          /*login = */ `openharmony_admin`,
          /*name = */ `openharmony`,
          /*avatar_url = */ `https://foruda.gitee.com/avatar/1677102952566165682/7928036_openharmony_admin_1622551091.png`,
          /*url = */ `https://gitee.com/api/v5/users/openharmony_admin`,
          /*html_url = */ `https://gitee.com/openharmony_admin`,
          /*remark = */ ``,
          /*followers_url = */ `https://gitee.com/api/v5/users/openharmony_admin/followers`,
          /*following_url = */ `https://gitee.com/api/v5/users/openharmony_admin/following_url{/other_user}`,
          /*gists_url = */ `https://gitee.com/api/v5/users/openharmony_admin/gists{/gist_id}`,
          /*starred_url = */ `https://gitee.com/api/v5/users/openharmony_admin/starred{/owner}{/repo}`,
          /*subscriptions_url = */ `https://gitee.com/api/v5/users/openharmony_admin/subscriptions`,
          /*organizations_url = */ `https://gitee.com/api/v5/users/openharmony_admin/orgs`,
          /*repos_url = */ `https://gitee.com/api/v5/users/openharmony_admin/repos`,
          /*events_url = */ `https://gitee.com/api/v5/users/openharmony_admin/events{/privacy}`,
          /*received_events_url = */ `https://gitee.com/api/v5/users/openharmony_admin/received_events`,
          /*type = */ `User`
        ),
        /*description = */ `暂无描述`,
        /*private_ = */ false,
        /*public_ = */ true,
        /*internal_ = */ false,
        /*fork = */ false,
        /*html_url = */ `https://gitee.com/openharmony/arkcompiler_runtime_core.git`,
        /*ssh_url = */ `git@gitee.com:openharmony/arkcompiler_runtime_core.git`
      )
    )
  );
}
function MockPR2(): PR {
  return new PR(
    /*id = */ 13118260,
    /*url = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core/pulls/3004`,
    /*html_url = */ `https://gitee.com/openharmony/arkcompiler_runtime_core/pulls/3004`,
    /*diff_url = */ `https://gitee.com/openharmony/arkcompiler_runtime_core/pulls/3004.diff`,
    /*patch_url = */ `https://gitee.com/openharmony/arkcompiler_runtime_core/pulls/3004.patch`,
    /*issue_url = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core/pulls/3004/issues`,
    /*commits_url = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core/pulls/3004/commits`,
    /*review_comments_url = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core/pulls/comments/{/number}`,
    /*review_comment_url = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core/pulls/comments`,
    /*comments_url = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core/pulls/3004/comments`,
    /*number = */ 3004,
    /*close_related_issue = */ 1,
    /*prune_branch = */ false,
    /*state = */ `open`,
    /*assignees_number = */ 1,
    /*testers_number = */ 1,
    /*assignees = */ new Assignees(
      /*values = */ new Array<Assignee>(
        new Assignee(
          /*id = */ 5654864,
          /*login = */ `egavrin`,
          /*name = */ `egavrin`,
          /*avatar_url = */ `https://gitee.com/assets/no_portrait.png`,
          /*url = */ `https://gitee.com/api//users/egavrin`,
          /*html_url = */ `https://gitee.com/egavrin`,
          /*remark = */ ``,
          /*followers_url = */ `https://gitee.com/api//users/egavrin/followers`,
          /*following_url = */ `https://gitee.com/api//users/egavrin/following_url{/other_user}`,
          /*gists_url = */ `https://gitee.com/api//users/egavrin/gists{/gist_id}`,
          /*starred_url = */ `https://gitee.com/api//users/egavrin/starred{/owner}{/repo}`,
          /*subscriptions_url = */ `https://gitee.com/api//users/egavrin/subscriptions`,
          /*organizations_url = */ `https://gitee.com/api//users/egavrin/orgs`,
          /*repos_url = */ `https://gitee.com/api//users/egavrin/repos`,
          /*events_url = */ `https://gitee.com/api//users/egavrin/events{/privacy}`,
          /*received_events_url = */ `https://gitee.com/api//users/egavrin/received_events`,
          /*type = */ `User`,
          /*assignee = */ false,
          /*code_owner = */ true,
          /*accept = */ false
        ),
        new Assignee(
          /*id = */ 7847922,
          /*login = */ `godmiaozi`,
          /*name = */ `godmiaozi`,
          /*avatar_url = */ `https://gitee.com/assets/no_portrait.png`,
          /*url = */ `https://gitee.com/api//users/godmiaozi`,
          /*html_url = */ `https://gitee.com/godmiaozi`,
          /*remark = */ ``,
          /*followers_url = */ `https://gitee.com/api//users/godmiaozi/followers`,
          /*following_url = */ `https://gitee.com/api//users/godmiaozi/following_url{/other_user}`,
          /*gists_url = */ `https://gitee.com/api//users/godmiaozi/gists{/gist_id}`,
          /*starred_url = */ `https://gitee.com/api//users/godmiaozi/starred{/owner}{/repo}`,
          /*subscriptions_url = */ `https://gitee.com/api//users/godmiaozi/subscriptions`,
          /*organizations_url = */ `https://gitee.com/api//users/godmiaozi/orgs`,
          /*repos_url = */ `https://gitee.com/api//users/godmiaozi/repos`,
          /*events_url = */ `https://gitee.com/api//users/godmiaozi/events{/privacy}`,
          /*received_events_url = */ `https://gitee.com/api//users/godmiaozi/received_events`,
          /*type = */ `User`,
          /*assignee = */ true,
          /*code_owner = */ false,
          /*accept = */ false
        ),
        new Assignee(
          /*id = */ 9580322,
          /*login = */ `ctw-ian`,
          /*name = */ `ctw-ian`,
          /*avatar_url = */ `https://gitee.com/assets/no_portrait.png`,
          /*url = */ `https://gitee.com/api//users/ctw-ian`,
          /*html_url = */ `https://gitee.com/ctw-ian`,
          /*remark = */ ``,
          /*followers_url = */ `https://gitee.com/api//users/ctw-ian/followers`,
          /*following_url = */ `https://gitee.com/api//users/ctw-ian/following_url{/other_user}`,
          /*gists_url = */ `https://gitee.com/api//users/ctw-ian/gists{/gist_id}`,
          /*starred_url = */ `https://gitee.com/api//users/ctw-ian/starred{/owner}{/repo}`,
          /*subscriptions_url = */ `https://gitee.com/api//users/ctw-ian/subscriptions`,
          /*organizations_url = */ `https://gitee.com/api//users/ctw-ian/orgs`,
          /*repos_url = */ `https://gitee.com/api//users/ctw-ian/repos`,
          /*events_url = */ `https://gitee.com/api//users/ctw-ian/events{/privacy}`,
          /*received_events_url = */ `https://gitee.com/api//users/ctw-ian/received_events`,
          /*type = */ `User`,
          /*assignee = */ true,
          /*code_owner = */ false,
          /*accept = */ false
        ),
        new Assignee(
          /*id = */ 9663914,
          /*login = */ `peijiajun`,
          /*name = */ `peijiajun`,
          /*avatar_url = */ `https://gitee.com/assets/no_portrait.png`,
          /*url = */ `https://gitee.com/api//users/peijiajun`,
          /*html_url = */ `https://gitee.com/peijiajun`,
          /*remark = */ ``,
          /*followers_url = */ `https://gitee.com/api//users/peijiajun/followers`,
          /*following_url = */ `https://gitee.com/api//users/peijiajun/following_url{/other_user}`,
          /*gists_url = */ `https://gitee.com/api//users/peijiajun/gists{/gist_id}`,
          /*starred_url = */ `https://gitee.com/api//users/peijiajun/starred{/owner}{/repo}`,
          /*subscriptions_url = */ `https://gitee.com/api//users/peijiajun/subscriptions`,
          /*organizations_url = */ `https://gitee.com/api//users/peijiajun/orgs`,
          /*repos_url = */ `https://gitee.com/api//users/peijiajun/repos`,
          /*events_url = */ `https://gitee.com/api//users/peijiajun/events{/privacy}`,
          /*received_events_url = */ `https://gitee.com/api//users/peijiajun/received_events`,
          /*type = */ `User`,
          /*assignee = */ true,
          /*code_owner = */ false,
          /*accept = */ false
        ),
        new Assignee(
          /*id = */ 11228302,
          /*login = */ `Prof1983`,
          /*name = */ `Ishin Pavel`,
          /*avatar_url = */ `https://foruda.gitee.com/avatar/1677231228555595315/11228302_prof1983_1657184805.png`,
          /*url = */ `https://gitee.com/api//users/Prof1983`,
          /*html_url = */ `https://gitee.com/Prof1983`,
          /*remark = */ ``,
          /*followers_url = */ `https://gitee.com/api//users/Prof1983/followers`,
          /*following_url = */ `https://gitee.com/api//users/Prof1983/following_url{/other_user}`,
          /*gists_url = */ `https://gitee.com/api//users/Prof1983/gists{/gist_id}`,
          /*starred_url = */ `https://gitee.com/api//users/Prof1983/starred{/owner}{/repo}`,
          /*subscriptions_url = */ `https://gitee.com/api//users/Prof1983/subscriptions`,
          /*organizations_url = */ `https://gitee.com/api//users/Prof1983/orgs`,
          /*repos_url = */ `https://gitee.com/api//users/Prof1983/repos`,
          /*events_url = */ `https://gitee.com/api//users/Prof1983/events{/privacy}`,
          /*received_events_url = */ `https://gitee.com/api//users/Prof1983/received_events`,
          /*type = */ `User`,
          /*assignee = */ true,
          /*code_owner = */ false,
          /*accept = */ false
        )
      )
    ),
    /*testers = */ new Assignees(
      /*values = */ new Array<Assignee>(
        new Assignee(
          /*id = */ 7387629,
          /*login = */ `openharmony_ci`,
          /*name = */ `openharmony_ci`,
          /*avatar_url = */ `https://foruda.gitee.com/avatar/1677075395966509043/7387629_openharmony_ci_1656582662.png`,
          /*url = */ `https://gitee.com/api//users/openharmony_ci`,
          /*html_url = */ `https://gitee.com/openharmony_ci`,
          /*remark = */ ``,
          /*followers_url = */ `https://gitee.com/api//users/openharmony_ci/followers`,
          /*following_url = */ `https://gitee.com/api//users/openharmony_ci/following_url{/other_user}`,
          /*gists_url = */ `https://gitee.com/api//users/openharmony_ci/gists{/gist_id}`,
          /*starred_url = */ `https://gitee.com/api//users/openharmony_ci/starred{/owner}{/repo}`,
          /*subscriptions_url = */ `https://gitee.com/api//users/openharmony_ci/subscriptions`,
          /*organizations_url = */ `https://gitee.com/api//users/openharmony_ci/orgs`,
          /*repos_url = */ `https://gitee.com/api//users/openharmony_ci/repos`,
          /*events_url = */ `https://gitee.com/api//users/openharmony_ci/events{/privacy}`,
          /*received_events_url = */ `https://gitee.com/api//users/openharmony_ci/received_events`,
          /*type = */ `User`,
          /*assignee = */ true,
          /*code_owner = */ false,
          /*accept = */ true
        )
      )
    ),
    /*api_reviewers_number = */ 0,
    /*api_reviewers = */ new ApiReviewers(
      /*values = */ new Array<ApiReviewer>()
    ),
    /*milestone = */ undefined,
    /*labels = */ new Labels(
      /*values = */ new Array<Label>(
        new Label(
          /*id = */ 98591264,
          /*color = */ `20c22e`,
          /*name = */ `静态检查成功`,
          /*repository_id = */ 6511493,
          /*url = */ `https://gitee.com/api/v5/enterprises/open_harmony/labels/静态检查成功`,
          /*created_at = */ new Date(1614331626000),
          /*updated_at = */ new Date(1733748586000)
        ),
        new Label(
          /*id = */ 113667295,
          /*color = */ `20c22e`,
          /*name = */ `dco检查成功`,
          /*repository_id = */ 6511493,
          /*url = */ `https://gitee.com/api/v5/enterprises/open_harmony/labels/dco检查成功`,
          /*created_at = */ new Date(1624000115000),
          /*updated_at = */ new Date(1733748579000)
        ),
        new Label(
          /*id = */ 119085125,
          /*color = */ `20c22e`,
          /*name = */ `编译成功`,
          /*repository_id = */ 6511493,
          /*url = */ `https://gitee.com/api/v5/enterprises/open_harmony/labels/编译成功`,
          /*created_at = */ new Date(1627727891000),
          /*updated_at = */ new Date(1733748578000)
        ),
        new Label(
          /*id = */ 130891955,
          /*color = */ `20c22e`,
          /*name = */ `冒烟测试成功`,
          /*repository_id = */ 6511493,
          /*url = */ `https://gitee.com/api/v5/enterprises/open_harmony/labels/冒烟测试成功`,
          /*created_at = */ new Date(1635499748000),
          /*updated_at = */ new Date(1733748587000)
        ),
        new Label(
          /*id = */ 200819465,
          /*color = */ `1083d6`,
          /*name = */ `waiting_for_review`,
          /*repository_id = */ 6511493,
          /*url = */ `https://gitee.com/api/v5/enterprises/open_harmony/labels/waiting_for_review`,
          /*created_at = */ new Date(1682247436000),
          /*updated_at = */ new Date(1733748607000)
        )
      )
    ),
    /*locked = */ false,
    /*created_at = */ new Date(1733729808000),
    /*updated_at = */ new Date(1733739996000),
    /*closed_at = */ undefined,
    /*draft = */ false,
    /*merged_at = */ undefined,
    /*mergeable = */ true,
    /*can_merge_check = */ false,
    /*_links = */ new Links(
      /*self = */ new Link(
        /*href = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core/pulls/3004`
      ),
      /*html = */ new Link(
        /*href = */ `https://gitee.com/openharmony/arkcompiler_runtime_core/pulls/3004`
      ),
      /*issue = */ new Link(
        /*href = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core/pulls/3004/issues`
      ),
      /*comments = */ new Link(
        /*href = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core/pulls/3004/comments`
      ),
      /*review_comments = */ new Link(
        /*href = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core/pulls/3004/comments`
      ),
      /*review_comment = */ new Link(
        /*href = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core/pulls/comments/3004`
      ),
      /*commits = */ new Link(
        /*href = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core/pulls/3004/commits`
      )
    ),
    /*user = */ new User(
      /*id = */ 15198848,
      /*login = */ `troeglazovamaria`,
      /*name = */ `troeglazovamaria`,
      /*avatar_url = */ `https://gitee.com/assets/no_portrait.png`,
      /*url = */ `https://gitee.com/api/v5/users/troeglazovamaria`,
      /*html_url = */ `https://gitee.com/troeglazovamaria`,
      /*remark = */ ``,
      /*followers_url = */ `https://gitee.com/api/v5/users/troeglazovamaria/followers`,
      /*following_url = */ `https://gitee.com/api/v5/users/troeglazovamaria/following_url{/other_user}`,
      /*gists_url = */ `https://gitee.com/api/v5/users/troeglazovamaria/gists{/gist_id}`,
      /*starred_url = */ `https://gitee.com/api/v5/users/troeglazovamaria/starred{/owner}{/repo}`,
      /*subscriptions_url = */ `https://gitee.com/api/v5/users/troeglazovamaria/subscriptions`,
      /*organizations_url = */ `https://gitee.com/api/v5/users/troeglazovamaria/orgs`,
      /*repos_url = */ `https://gitee.com/api/v5/users/troeglazovamaria/repos`,
      /*events_url = */ `https://gitee.com/api/v5/users/troeglazovamaria/events{/privacy}`,
      /*received_events_url = */ `https://gitee.com/api/v5/users/troeglazovamaria/received_events`,
      /*type = */ `User`
    ),
    /*ref_pull_requests = */ new PRs(/*values = */ new Array<PR>()),
    /*title = */ `Add tests for partial utility type`,
    /*body = */ `### **Issue**
https://gitee.com/openharmony/arkcompiler_runtime_core/issues/IB9O7V?from=project-issue

### **Reason**
Add tests for partial utility type with primitive types

### **Description**
Add tests for partial utility type with primitive types

### **Tests**
**All required pre-merge tests passed. Results are available in the internal CI.**
`,
    /*head = */ new Head(
      /*label = */ `mtroeglazova/test_partial_priitive_types`,
      /*ref = */ `mtroeglazova/test_partial_priitive_types`,
      /*sha = */ `4bd311017a88e0096a9dbf9685da351dae8ecc49`,
      /*user = */ new User(
        /*id = */ 15198848,
        /*login = */ `troeglazovamaria`,
        /*name = */ `troeglazovamaria`,
        /*avatar_url = */ `https://gitee.com/assets/no_portrait.png`,
        /*url = */ `https://gitee.com/api/v5/users/troeglazovamaria`,
        /*html_url = */ `https://gitee.com/troeglazovamaria`,
        /*remark = */ ``,
        /*followers_url = */ `https://gitee.com/api/v5/users/troeglazovamaria/followers`,
        /*following_url = */ `https://gitee.com/api/v5/users/troeglazovamaria/following_url{/other_user}`,
        /*gists_url = */ `https://gitee.com/api/v5/users/troeglazovamaria/gists{/gist_id}`,
        /*starred_url = */ `https://gitee.com/api/v5/users/troeglazovamaria/starred{/owner}{/repo}`,
        /*subscriptions_url = */ `https://gitee.com/api/v5/users/troeglazovamaria/subscriptions`,
        /*organizations_url = */ `https://gitee.com/api/v5/users/troeglazovamaria/orgs`,
        /*repos_url = */ `https://gitee.com/api/v5/users/troeglazovamaria/repos`,
        /*events_url = */ `https://gitee.com/api/v5/users/troeglazovamaria/events{/privacy}`,
        /*received_events_url = */ `https://gitee.com/api/v5/users/troeglazovamaria/received_events`,
        /*type = */ `User`
      ),
      /*repo = */ new Repo(
        /*id = */ 38808573,
        /*full_name = */ `troeglazovamaria/arkcompiler_runtime_core`,
        /*human_name = */ `troeglazovamaria/arkcompiler_runtime_core`,
        /*url = */ `https://gitee.com/api/v5/repos/troeglazovamaria/arkcompiler_runtime_core`,
        /*namespace_ = */ new Namespace(
          /*id = */ 14389441,
          /*type = */ `personal`,
          /*name = */ `troeglazovamaria`,
          /*path = */ `troeglazovamaria`,
          /*html_url = */ `https://gitee.com/troeglazovamaria`
        ),
        /*path = */ `arkcompiler_runtime_core`,
        /*name = */ `arkcompiler_runtime_core`,
        /*owner = */ new User(
          /*id = */ 15198848,
          /*login = */ `troeglazovamaria`,
          /*name = */ `troeglazovamaria`,
          /*avatar_url = */ `https://gitee.com/assets/no_portrait.png`,
          /*url = */ `https://gitee.com/api/v5/users/troeglazovamaria`,
          /*html_url = */ `https://gitee.com/troeglazovamaria`,
          /*remark = */ ``,
          /*followers_url = */ `https://gitee.com/api/v5/users/troeglazovamaria/followers`,
          /*following_url = */ `https://gitee.com/api/v5/users/troeglazovamaria/following_url{/other_user}`,
          /*gists_url = */ `https://gitee.com/api/v5/users/troeglazovamaria/gists{/gist_id}`,
          /*starred_url = */ `https://gitee.com/api/v5/users/troeglazovamaria/starred{/owner}{/repo}`,
          /*subscriptions_url = */ `https://gitee.com/api/v5/users/troeglazovamaria/subscriptions`,
          /*organizations_url = */ `https://gitee.com/api/v5/users/troeglazovamaria/orgs`,
          /*repos_url = */ `https://gitee.com/api/v5/users/troeglazovamaria/repos`,
          /*events_url = */ `https://gitee.com/api/v5/users/troeglazovamaria/events{/privacy}`,
          /*received_events_url = */ `https://gitee.com/api/v5/users/troeglazovamaria/received_events`,
          /*type = */ `User`
        ),
        /*assigner = */ new User(
          /*id = */ 15198848,
          /*login = */ `troeglazovamaria`,
          /*name = */ `troeglazovamaria`,
          /*avatar_url = */ `https://gitee.com/assets/no_portrait.png`,
          /*url = */ `https://gitee.com/api/v5/users/troeglazovamaria`,
          /*html_url = */ `https://gitee.com/troeglazovamaria`,
          /*remark = */ ``,
          /*followers_url = */ `https://gitee.com/api/v5/users/troeglazovamaria/followers`,
          /*following_url = */ `https://gitee.com/api/v5/users/troeglazovamaria/following_url{/other_user}`,
          /*gists_url = */ `https://gitee.com/api/v5/users/troeglazovamaria/gists{/gist_id}`,
          /*starred_url = */ `https://gitee.com/api/v5/users/troeglazovamaria/starred{/owner}{/repo}`,
          /*subscriptions_url = */ `https://gitee.com/api/v5/users/troeglazovamaria/subscriptions`,
          /*organizations_url = */ `https://gitee.com/api/v5/users/troeglazovamaria/orgs`,
          /*repos_url = */ `https://gitee.com/api/v5/users/troeglazovamaria/repos`,
          /*events_url = */ `https://gitee.com/api/v5/users/troeglazovamaria/events{/privacy}`,
          /*received_events_url = */ `https://gitee.com/api/v5/users/troeglazovamaria/received_events`,
          /*type = */ `User`
        ),
        /*description = */ `暂无描述`,
        /*private_ = */ false,
        /*public_ = */ true,
        /*internal_ = */ false,
        /*fork = */ true,
        /*html_url = */ `https://gitee.com/troeglazovamaria/arkcompiler_runtime_core.git`,
        /*ssh_url = */ `git@gitee.com:troeglazovamaria/arkcompiler_runtime_core.git`
      )
    ),
    /*base = */ new Base(
      /*label = */ `OpenHarmony_feature_20241108`,
      /*ref = */ `OpenHarmony_feature_20241108`,
      /*sha = */ `d212656f6aaa6a5a7cbfb74e07888030e38f8046`,
      /*user = */ new User(
        /*id = */ 7928036,
        /*login = */ `openharmony_admin`,
        /*name = */ `openharmony`,
        /*avatar_url = */ `https://foruda.gitee.com/avatar/1677102952566165682/7928036_openharmony_admin_1622551091.png`,
        /*url = */ `https://gitee.com/api/v5/users/openharmony_admin`,
        /*html_url = */ `https://gitee.com/openharmony_admin`,
        /*remark = */ ``,
        /*followers_url = */ `https://gitee.com/api/v5/users/openharmony_admin/followers`,
        /*following_url = */ `https://gitee.com/api/v5/users/openharmony_admin/following_url{/other_user}`,
        /*gists_url = */ `https://gitee.com/api/v5/users/openharmony_admin/gists{/gist_id}`,
        /*starred_url = */ `https://gitee.com/api/v5/users/openharmony_admin/starred{/owner}{/repo}`,
        /*subscriptions_url = */ `https://gitee.com/api/v5/users/openharmony_admin/subscriptions`,
        /*organizations_url = */ `https://gitee.com/api/v5/users/openharmony_admin/orgs`,
        /*repos_url = */ `https://gitee.com/api/v5/users/openharmony_admin/repos`,
        /*events_url = */ `https://gitee.com/api/v5/users/openharmony_admin/events{/privacy}`,
        /*received_events_url = */ `https://gitee.com/api/v5/users/openharmony_admin/received_events`,
        /*type = */ `User`
      ),
      /*repo = */ new Repo(
        /*id = */ 17812929,
        /*full_name = */ `openharmony/arkcompiler_runtime_core`,
        /*human_name = */ `OpenHarmony/arkcompiler_runtime_core`,
        /*url = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core`,
        /*namespace_ = */ new Namespace(
          /*id = */ 6486504,
          /*type = */ `group`,
          /*name = */ `OpenHarmony`,
          /*path = */ `openharmony`,
          /*html_url = */ `https://gitee.com/openharmony`
        ),
        /*path = */ `arkcompiler_runtime_core`,
        /*name = */ `arkcompiler_runtime_core`,
        /*owner = */ new User(
          /*id = */ 7928036,
          /*login = */ `openharmony_admin`,
          /*name = */ `openharmony`,
          /*avatar_url = */ `https://foruda.gitee.com/avatar/1677102952566165682/7928036_openharmony_admin_1622551091.png`,
          /*url = */ `https://gitee.com/api/v5/users/openharmony_admin`,
          /*html_url = */ `https://gitee.com/openharmony_admin`,
          /*remark = */ ``,
          /*followers_url = */ `https://gitee.com/api/v5/users/openharmony_admin/followers`,
          /*following_url = */ `https://gitee.com/api/v5/users/openharmony_admin/following_url{/other_user}`,
          /*gists_url = */ `https://gitee.com/api/v5/users/openharmony_admin/gists{/gist_id}`,
          /*starred_url = */ `https://gitee.com/api/v5/users/openharmony_admin/starred{/owner}{/repo}`,
          /*subscriptions_url = */ `https://gitee.com/api/v5/users/openharmony_admin/subscriptions`,
          /*organizations_url = */ `https://gitee.com/api/v5/users/openharmony_admin/orgs`,
          /*repos_url = */ `https://gitee.com/api/v5/users/openharmony_admin/repos`,
          /*events_url = */ `https://gitee.com/api/v5/users/openharmony_admin/events{/privacy}`,
          /*received_events_url = */ `https://gitee.com/api/v5/users/openharmony_admin/received_events`,
          /*type = */ `User`
        ),
        /*assigner = */ new User(
          /*id = */ 7928036,
          /*login = */ `openharmony_admin`,
          /*name = */ `openharmony`,
          /*avatar_url = */ `https://foruda.gitee.com/avatar/1677102952566165682/7928036_openharmony_admin_1622551091.png`,
          /*url = */ `https://gitee.com/api/v5/users/openharmony_admin`,
          /*html_url = */ `https://gitee.com/openharmony_admin`,
          /*remark = */ ``,
          /*followers_url = */ `https://gitee.com/api/v5/users/openharmony_admin/followers`,
          /*following_url = */ `https://gitee.com/api/v5/users/openharmony_admin/following_url{/other_user}`,
          /*gists_url = */ `https://gitee.com/api/v5/users/openharmony_admin/gists{/gist_id}`,
          /*starred_url = */ `https://gitee.com/api/v5/users/openharmony_admin/starred{/owner}{/repo}`,
          /*subscriptions_url = */ `https://gitee.com/api/v5/users/openharmony_admin/subscriptions`,
          /*organizations_url = */ `https://gitee.com/api/v5/users/openharmony_admin/orgs`,
          /*repos_url = */ `https://gitee.com/api/v5/users/openharmony_admin/repos`,
          /*events_url = */ `https://gitee.com/api/v5/users/openharmony_admin/events{/privacy}`,
          /*received_events_url = */ `https://gitee.com/api/v5/users/openharmony_admin/received_events`,
          /*type = */ `User`
        ),
        /*description = */ `暂无描述`,
        /*private_ = */ false,
        /*public_ = */ true,
        /*internal_ = */ false,
        /*fork = */ false,
        /*html_url = */ `https://gitee.com/openharmony/arkcompiler_runtime_core.git`,
        /*ssh_url = */ `git@gitee.com:openharmony/arkcompiler_runtime_core.git`
      )
    )
  );
}
function MockPR3(): PR {
  return new PR(
    /*id = */ 13112640,
    /*url = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core/pulls/3003`,
    /*html_url = */ `https://gitee.com/openharmony/arkcompiler_runtime_core/pulls/3003`,
    /*diff_url = */ `https://gitee.com/openharmony/arkcompiler_runtime_core/pulls/3003.diff`,
    /*patch_url = */ `https://gitee.com/openharmony/arkcompiler_runtime_core/pulls/3003.patch`,
    /*issue_url = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core/pulls/3003/issues`,
    /*commits_url = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core/pulls/3003/commits`,
    /*review_comments_url = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core/pulls/comments/{/number}`,
    /*review_comment_url = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core/pulls/comments`,
    /*comments_url = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core/pulls/3003/comments`,
    /*number = */ 3003,
    /*close_related_issue = */ 1,
    /*prune_branch = */ false,
    /*state = */ `open`,
    /*assignees_number = */ 1,
    /*testers_number = */ 1,
    /*assignees = */ new Assignees(
      /*values = */ new Array<Assignee>(
        new Assignee(
          /*id = */ 7847922,
          /*login = */ `godmiaozi`,
          /*name = */ `godmiaozi`,
          /*avatar_url = */ `https://gitee.com/assets/no_portrait.png`,
          /*url = */ `https://gitee.com/api//users/godmiaozi`,
          /*html_url = */ `https://gitee.com/godmiaozi`,
          /*remark = */ ``,
          /*followers_url = */ `https://gitee.com/api//users/godmiaozi/followers`,
          /*following_url = */ `https://gitee.com/api//users/godmiaozi/following_url{/other_user}`,
          /*gists_url = */ `https://gitee.com/api//users/godmiaozi/gists{/gist_id}`,
          /*starred_url = */ `https://gitee.com/api//users/godmiaozi/starred{/owner}{/repo}`,
          /*subscriptions_url = */ `https://gitee.com/api//users/godmiaozi/subscriptions`,
          /*organizations_url = */ `https://gitee.com/api//users/godmiaozi/orgs`,
          /*repos_url = */ `https://gitee.com/api//users/godmiaozi/repos`,
          /*events_url = */ `https://gitee.com/api//users/godmiaozi/events{/privacy}`,
          /*received_events_url = */ `https://gitee.com/api//users/godmiaozi/received_events`,
          /*type = */ `User`,
          /*assignee = */ true,
          /*code_owner = */ false,
          /*accept = */ false
        ),
        new Assignee(
          /*id = */ 8612218,
          /*login = */ `klooer`,
          /*name = */ `klooer`,
          /*avatar_url = */ `https://gitee.com/assets/no_portrait.png`,
          /*url = */ `https://gitee.com/api//users/klooer`,
          /*html_url = */ `https://gitee.com/klooer`,
          /*remark = */ ``,
          /*followers_url = */ `https://gitee.com/api//users/klooer/followers`,
          /*following_url = */ `https://gitee.com/api//users/klooer/following_url{/other_user}`,
          /*gists_url = */ `https://gitee.com/api//users/klooer/gists{/gist_id}`,
          /*starred_url = */ `https://gitee.com/api//users/klooer/starred{/owner}{/repo}`,
          /*subscriptions_url = */ `https://gitee.com/api//users/klooer/subscriptions`,
          /*organizations_url = */ `https://gitee.com/api//users/klooer/orgs`,
          /*repos_url = */ `https://gitee.com/api//users/klooer/repos`,
          /*events_url = */ `https://gitee.com/api//users/klooer/events{/privacy}`,
          /*received_events_url = */ `https://gitee.com/api//users/klooer/received_events`,
          /*type = */ `User`,
          /*assignee = */ false,
          /*code_owner = */ true,
          /*accept = */ false
        ),
        new Assignee(
          /*id = */ 9580322,
          /*login = */ `ctw-ian`,
          /*name = */ `ctw-ian`,
          /*avatar_url = */ `https://gitee.com/assets/no_portrait.png`,
          /*url = */ `https://gitee.com/api//users/ctw-ian`,
          /*html_url = */ `https://gitee.com/ctw-ian`,
          /*remark = */ ``,
          /*followers_url = */ `https://gitee.com/api//users/ctw-ian/followers`,
          /*following_url = */ `https://gitee.com/api//users/ctw-ian/following_url{/other_user}`,
          /*gists_url = */ `https://gitee.com/api//users/ctw-ian/gists{/gist_id}`,
          /*starred_url = */ `https://gitee.com/api//users/ctw-ian/starred{/owner}{/repo}`,
          /*subscriptions_url = */ `https://gitee.com/api//users/ctw-ian/subscriptions`,
          /*organizations_url = */ `https://gitee.com/api//users/ctw-ian/orgs`,
          /*repos_url = */ `https://gitee.com/api//users/ctw-ian/repos`,
          /*events_url = */ `https://gitee.com/api//users/ctw-ian/events{/privacy}`,
          /*received_events_url = */ `https://gitee.com/api//users/ctw-ian/received_events`,
          /*type = */ `User`,
          /*assignee = */ true,
          /*code_owner = */ false,
          /*accept = */ false
        ),
        new Assignee(
          /*id = */ 9663914,
          /*login = */ `peijiajun`,
          /*name = */ `peijiajun`,
          /*avatar_url = */ `https://gitee.com/assets/no_portrait.png`,
          /*url = */ `https://gitee.com/api//users/peijiajun`,
          /*html_url = */ `https://gitee.com/peijiajun`,
          /*remark = */ ``,
          /*followers_url = */ `https://gitee.com/api//users/peijiajun/followers`,
          /*following_url = */ `https://gitee.com/api//users/peijiajun/following_url{/other_user}`,
          /*gists_url = */ `https://gitee.com/api//users/peijiajun/gists{/gist_id}`,
          /*starred_url = */ `https://gitee.com/api//users/peijiajun/starred{/owner}{/repo}`,
          /*subscriptions_url = */ `https://gitee.com/api//users/peijiajun/subscriptions`,
          /*organizations_url = */ `https://gitee.com/api//users/peijiajun/orgs`,
          /*repos_url = */ `https://gitee.com/api//users/peijiajun/repos`,
          /*events_url = */ `https://gitee.com/api//users/peijiajun/events{/privacy}`,
          /*received_events_url = */ `https://gitee.com/api//users/peijiajun/received_events`,
          /*type = */ `User`,
          /*assignee = */ true,
          /*code_owner = */ false,
          /*accept = */ false
        ),
        new Assignee(
          /*id = */ 11228302,
          /*login = */ `Prof1983`,
          /*name = */ `Ishin Pavel`,
          /*avatar_url = */ `https://foruda.gitee.com/avatar/1677231228555595315/11228302_prof1983_1657184805.png`,
          /*url = */ `https://gitee.com/api//users/Prof1983`,
          /*html_url = */ `https://gitee.com/Prof1983`,
          /*remark = */ ``,
          /*followers_url = */ `https://gitee.com/api//users/Prof1983/followers`,
          /*following_url = */ `https://gitee.com/api//users/Prof1983/following_url{/other_user}`,
          /*gists_url = */ `https://gitee.com/api//users/Prof1983/gists{/gist_id}`,
          /*starred_url = */ `https://gitee.com/api//users/Prof1983/starred{/owner}{/repo}`,
          /*subscriptions_url = */ `https://gitee.com/api//users/Prof1983/subscriptions`,
          /*organizations_url = */ `https://gitee.com/api//users/Prof1983/orgs`,
          /*repos_url = */ `https://gitee.com/api//users/Prof1983/repos`,
          /*events_url = */ `https://gitee.com/api//users/Prof1983/events{/privacy}`,
          /*received_events_url = */ `https://gitee.com/api//users/Prof1983/received_events`,
          /*type = */ `User`,
          /*assignee = */ true,
          /*code_owner = */ false,
          /*accept = */ false
        )
      )
    ),
    /*testers = */ new Assignees(
      /*values = */ new Array<Assignee>(
        new Assignee(
          /*id = */ 7387629,
          /*login = */ `openharmony_ci`,
          /*name = */ `openharmony_ci`,
          /*avatar_url = */ `https://foruda.gitee.com/avatar/1677075395966509043/7387629_openharmony_ci_1656582662.png`,
          /*url = */ `https://gitee.com/api//users/openharmony_ci`,
          /*html_url = */ `https://gitee.com/openharmony_ci`,
          /*remark = */ ``,
          /*followers_url = */ `https://gitee.com/api//users/openharmony_ci/followers`,
          /*following_url = */ `https://gitee.com/api//users/openharmony_ci/following_url{/other_user}`,
          /*gists_url = */ `https://gitee.com/api//users/openharmony_ci/gists{/gist_id}`,
          /*starred_url = */ `https://gitee.com/api//users/openharmony_ci/starred{/owner}{/repo}`,
          /*subscriptions_url = */ `https://gitee.com/api//users/openharmony_ci/subscriptions`,
          /*organizations_url = */ `https://gitee.com/api//users/openharmony_ci/orgs`,
          /*repos_url = */ `https://gitee.com/api//users/openharmony_ci/repos`,
          /*events_url = */ `https://gitee.com/api//users/openharmony_ci/events{/privacy}`,
          /*received_events_url = */ `https://gitee.com/api//users/openharmony_ci/received_events`,
          /*type = */ `User`,
          /*assignee = */ true,
          /*code_owner = */ false,
          /*accept = */ true
        )
      )
    ),
    /*api_reviewers_number = */ 0,
    /*api_reviewers = */ new ApiReviewers(
      /*values = */ new Array<ApiReviewer>()
    ),
    /*milestone = */ undefined,
    /*labels = */ new Labels(
      /*values = */ new Array<Label>(
        new Label(
          /*id = */ 98591264,
          /*color = */ `20c22e`,
          /*name = */ `静态检查成功`,
          /*repository_id = */ 6511493,
          /*url = */ `https://gitee.com/api/v5/enterprises/open_harmony/labels/静态检查成功`,
          /*created_at = */ new Date(1614331626000),
          /*updated_at = */ new Date(1733748586000)
        ),
        new Label(
          /*id = */ 113667295,
          /*color = */ `20c22e`,
          /*name = */ `dco检查成功`,
          /*repository_id = */ 6511493,
          /*url = */ `https://gitee.com/api/v5/enterprises/open_harmony/labels/dco检查成功`,
          /*created_at = */ new Date(1624000115000),
          /*updated_at = */ new Date(1733748579000)
        ),
        new Label(
          /*id = */ 119085125,
          /*color = */ `20c22e`,
          /*name = */ `编译成功`,
          /*repository_id = */ 6511493,
          /*url = */ `https://gitee.com/api/v5/enterprises/open_harmony/labels/编译成功`,
          /*created_at = */ new Date(1627727891000),
          /*updated_at = */ new Date(1733748578000)
        ),
        new Label(
          /*id = */ 130891955,
          /*color = */ `20c22e`,
          /*name = */ `冒烟测试成功`,
          /*repository_id = */ 6511493,
          /*url = */ `https://gitee.com/api/v5/enterprises/open_harmony/labels/冒烟测试成功`,
          /*created_at = */ new Date(1635499748000),
          /*updated_at = */ new Date(1733748587000)
        ),
        new Label(
          /*id = */ 131024541,
          /*color = */ `20c22e`,
          /*name = */ `格式化检查成功`,
          /*repository_id = */ 6511493,
          /*url = */ `https://gitee.com/api/v5/enterprises/open_harmony/labels/格式化检查成功`,
          /*created_at = */ new Date(1635585650000),
          /*updated_at = */ new Date(1733748597000)
        )
      )
    ),
    /*locked = */ false,
    /*created_at = */ new Date(1733664590000),
    /*updated_at = */ new Date(1733734974000),
    /*closed_at = */ undefined,
    /*draft = */ false,
    /*merged_at = */ undefined,
    /*mergeable = */ true,
    /*can_merge_check = */ false,
    /*_links = */ new Links(
      /*self = */ new Link(
        /*href = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core/pulls/3003`
      ),
      /*html = */ new Link(
        /*href = */ `https://gitee.com/openharmony/arkcompiler_runtime_core/pulls/3003`
      ),
      /*issue = */ new Link(
        /*href = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core/pulls/3003/issues`
      ),
      /*comments = */ new Link(
        /*href = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core/pulls/3003/comments`
      ),
      /*review_comments = */ new Link(
        /*href = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core/pulls/3003/comments`
      ),
      /*review_comment = */ new Link(
        /*href = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core/pulls/comments/3003`
      ),
      /*commits = */ new Link(
        /*href = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core/pulls/3003/commits`
      )
    ),
    /*user = */ new User(
      /*id = */ 10473821,
      /*login = */ `ElevenDuan`,
      /*name = */ `ElevenDuan`,
      /*avatar_url = */ `https://gitee.com/assets/no_portrait.png`,
      /*url = */ `https://gitee.com/api/v5/users/ElevenDuan`,
      /*html_url = */ `https://gitee.com/ElevenDuan`,
      /*remark = */ ``,
      /*followers_url = */ `https://gitee.com/api/v5/users/ElevenDuan/followers`,
      /*following_url = */ `https://gitee.com/api/v5/users/ElevenDuan/following_url{/other_user}`,
      /*gists_url = */ `https://gitee.com/api/v5/users/ElevenDuan/gists{/gist_id}`,
      /*starred_url = */ `https://gitee.com/api/v5/users/ElevenDuan/starred{/owner}{/repo}`,
      /*subscriptions_url = */ `https://gitee.com/api/v5/users/ElevenDuan/subscriptions`,
      /*organizations_url = */ `https://gitee.com/api/v5/users/ElevenDuan/orgs`,
      /*repos_url = */ `https://gitee.com/api/v5/users/ElevenDuan/repos`,
      /*events_url = */ `https://gitee.com/api/v5/users/ElevenDuan/events{/privacy}`,
      /*received_events_url = */ `https://gitee.com/api/v5/users/ElevenDuan/received_events`,
      /*type = */ `User`
    ),
    /*ref_pull_requests = */ new PRs(/*values = */ new Array<PR>()),
    /*title = */ `对Release模式下编译abc文件的行号信息添加维测`,
    /*body = */ `### **Issue**
https://gitee.com/openharmony/arkcompiler_ets_frontend/issues/IB9UEI

### **Reason**
Release模式下编译abc文件的行号信息没有测试用例看护

### **Description**
Release模式下编译abc文件的行号信息添加维测，看护方法：
abc2program dump包含行号信息，使用abc2program dump信息进行行号看护，对常见语法和已知问题场景进行看护
添加TS常用语法进行行号信息看护，如下：
1.基础类型（boolean, number, string, undefined, null）
2.联合类型
3.枚举（enum）
4.数组和元组
5.对象字面量
6.接口（interface）
7.类（class）和继承
8.泛型
9.函数类型
10.类型断言
11.类型保护
12.高级类型（如 Partial）
13.异步函数


### **Tests**
runtime_core UT
![输入图片说明](https://foruda.gitee.com/images/1733664565987528752/716d00df_10473821.png "屏幕截图")`,
    /*head = */ new Head(
      /*label = */ `add_line_number_test`,
      /*ref = */ `add_line_number_test`,
      /*sha = */ `6f823b235ce56d46b45688c72ff9a85d649e15df`,
      /*user = */ new User(
        /*id = */ 10473821,
        /*login = */ `ElevenDuan`,
        /*name = */ `ElevenDuan`,
        /*avatar_url = */ `https://gitee.com/assets/no_portrait.png`,
        /*url = */ `https://gitee.com/api/v5/users/ElevenDuan`,
        /*html_url = */ `https://gitee.com/ElevenDuan`,
        /*remark = */ ``,
        /*followers_url = */ `https://gitee.com/api/v5/users/ElevenDuan/followers`,
        /*following_url = */ `https://gitee.com/api/v5/users/ElevenDuan/following_url{/other_user}`,
        /*gists_url = */ `https://gitee.com/api/v5/users/ElevenDuan/gists{/gist_id}`,
        /*starred_url = */ `https://gitee.com/api/v5/users/ElevenDuan/starred{/owner}{/repo}`,
        /*subscriptions_url = */ `https://gitee.com/api/v5/users/ElevenDuan/subscriptions`,
        /*organizations_url = */ `https://gitee.com/api/v5/users/ElevenDuan/orgs`,
        /*repos_url = */ `https://gitee.com/api/v5/users/ElevenDuan/repos`,
        /*events_url = */ `https://gitee.com/api/v5/users/ElevenDuan/events{/privacy}`,
        /*received_events_url = */ `https://gitee.com/api/v5/users/ElevenDuan/received_events`,
        /*type = */ `User`
      ),
      /*repo = */ new Repo(
        /*id = */ 32309085,
        /*full_name = */ `ElevenDuan/runtime_core`,
        /*human_name = */ `ElevenDuan/runtime_core`,
        /*url = */ `https://gitee.com/api/v5/repos/ElevenDuan/runtime_core`,
        /*namespace_ = */ new Namespace(
          /*id = */ 9306282,
          /*type = */ `personal`,
          /*name = */ `ElevenDuan`,
          /*path = */ `ElevenDuan`,
          /*html_url = */ `https://gitee.com/ElevenDuan`
        ),
        /*path = */ `runtime_core`,
        /*name = */ `runtime_core`,
        /*owner = */ new User(
          /*id = */ 10473821,
          /*login = */ `ElevenDuan`,
          /*name = */ `ElevenDuan`,
          /*avatar_url = */ `https://gitee.com/assets/no_portrait.png`,
          /*url = */ `https://gitee.com/api/v5/users/ElevenDuan`,
          /*html_url = */ `https://gitee.com/ElevenDuan`,
          /*remark = */ ``,
          /*followers_url = */ `https://gitee.com/api/v5/users/ElevenDuan/followers`,
          /*following_url = */ `https://gitee.com/api/v5/users/ElevenDuan/following_url{/other_user}`,
          /*gists_url = */ `https://gitee.com/api/v5/users/ElevenDuan/gists{/gist_id}`,
          /*starred_url = */ `https://gitee.com/api/v5/users/ElevenDuan/starred{/owner}{/repo}`,
          /*subscriptions_url = */ `https://gitee.com/api/v5/users/ElevenDuan/subscriptions`,
          /*organizations_url = */ `https://gitee.com/api/v5/users/ElevenDuan/orgs`,
          /*repos_url = */ `https://gitee.com/api/v5/users/ElevenDuan/repos`,
          /*events_url = */ `https://gitee.com/api/v5/users/ElevenDuan/events{/privacy}`,
          /*received_events_url = */ `https://gitee.com/api/v5/users/ElevenDuan/received_events`,
          /*type = */ `User`
        ),
        /*assigner = */ new User(
          /*id = */ 10473821,
          /*login = */ `ElevenDuan`,
          /*name = */ `ElevenDuan`,
          /*avatar_url = */ `https://gitee.com/assets/no_portrait.png`,
          /*url = */ `https://gitee.com/api/v5/users/ElevenDuan`,
          /*html_url = */ `https://gitee.com/ElevenDuan`,
          /*remark = */ ``,
          /*followers_url = */ `https://gitee.com/api/v5/users/ElevenDuan/followers`,
          /*following_url = */ `https://gitee.com/api/v5/users/ElevenDuan/following_url{/other_user}`,
          /*gists_url = */ `https://gitee.com/api/v5/users/ElevenDuan/gists{/gist_id}`,
          /*starred_url = */ `https://gitee.com/api/v5/users/ElevenDuan/starred{/owner}{/repo}`,
          /*subscriptions_url = */ `https://gitee.com/api/v5/users/ElevenDuan/subscriptions`,
          /*organizations_url = */ `https://gitee.com/api/v5/users/ElevenDuan/orgs`,
          /*repos_url = */ `https://gitee.com/api/v5/users/ElevenDuan/repos`,
          /*events_url = */ `https://gitee.com/api/v5/users/ElevenDuan/events{/privacy}`,
          /*received_events_url = */ `https://gitee.com/api/v5/users/ElevenDuan/received_events`,
          /*type = */ `User`
        ),
        /*description = */ `null`,
        /*private_ = */ false,
        /*public_ = */ true,
        /*internal_ = */ false,
        /*fork = */ true,
        /*html_url = */ `https://gitee.com/ElevenDuan/runtime_core.git`,
        /*ssh_url = */ `git@gitee.com:ElevenDuan/runtime_core.git`
      )
    ),
    /*base = */ new Base(
      /*label = */ `master`,
      /*ref = */ `master`,
      /*sha = */ `6fcb55cfa53bb043dce9e63e0d402ebebfb98c17`,
      /*user = */ new User(
        /*id = */ 7928036,
        /*login = */ `openharmony_admin`,
        /*name = */ `openharmony`,
        /*avatar_url = */ `https://foruda.gitee.com/avatar/1677102952566165682/7928036_openharmony_admin_1622551091.png`,
        /*url = */ `https://gitee.com/api/v5/users/openharmony_admin`,
        /*html_url = */ `https://gitee.com/openharmony_admin`,
        /*remark = */ ``,
        /*followers_url = */ `https://gitee.com/api/v5/users/openharmony_admin/followers`,
        /*following_url = */ `https://gitee.com/api/v5/users/openharmony_admin/following_url{/other_user}`,
        /*gists_url = */ `https://gitee.com/api/v5/users/openharmony_admin/gists{/gist_id}`,
        /*starred_url = */ `https://gitee.com/api/v5/users/openharmony_admin/starred{/owner}{/repo}`,
        /*subscriptions_url = */ `https://gitee.com/api/v5/users/openharmony_admin/subscriptions`,
        /*organizations_url = */ `https://gitee.com/api/v5/users/openharmony_admin/orgs`,
        /*repos_url = */ `https://gitee.com/api/v5/users/openharmony_admin/repos`,
        /*events_url = */ `https://gitee.com/api/v5/users/openharmony_admin/events{/privacy}`,
        /*received_events_url = */ `https://gitee.com/api/v5/users/openharmony_admin/received_events`,
        /*type = */ `User`
      ),
      /*repo = */ new Repo(
        /*id = */ 17812929,
        /*full_name = */ `openharmony/arkcompiler_runtime_core`,
        /*human_name = */ `OpenHarmony/arkcompiler_runtime_core`,
        /*url = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core`,
        /*namespace_ = */ new Namespace(
          /*id = */ 6486504,
          /*type = */ `group`,
          /*name = */ `OpenHarmony`,
          /*path = */ `openharmony`,
          /*html_url = */ `https://gitee.com/openharmony`
        ),
        /*path = */ `arkcompiler_runtime_core`,
        /*name = */ `arkcompiler_runtime_core`,
        /*owner = */ new User(
          /*id = */ 7928036,
          /*login = */ `openharmony_admin`,
          /*name = */ `openharmony`,
          /*avatar_url = */ `https://foruda.gitee.com/avatar/1677102952566165682/7928036_openharmony_admin_1622551091.png`,
          /*url = */ `https://gitee.com/api/v5/users/openharmony_admin`,
          /*html_url = */ `https://gitee.com/openharmony_admin`,
          /*remark = */ ``,
          /*followers_url = */ `https://gitee.com/api/v5/users/openharmony_admin/followers`,
          /*following_url = */ `https://gitee.com/api/v5/users/openharmony_admin/following_url{/other_user}`,
          /*gists_url = */ `https://gitee.com/api/v5/users/openharmony_admin/gists{/gist_id}`,
          /*starred_url = */ `https://gitee.com/api/v5/users/openharmony_admin/starred{/owner}{/repo}`,
          /*subscriptions_url = */ `https://gitee.com/api/v5/users/openharmony_admin/subscriptions`,
          /*organizations_url = */ `https://gitee.com/api/v5/users/openharmony_admin/orgs`,
          /*repos_url = */ `https://gitee.com/api/v5/users/openharmony_admin/repos`,
          /*events_url = */ `https://gitee.com/api/v5/users/openharmony_admin/events{/privacy}`,
          /*received_events_url = */ `https://gitee.com/api/v5/users/openharmony_admin/received_events`,
          /*type = */ `User`
        ),
        /*assigner = */ new User(
          /*id = */ 7928036,
          /*login = */ `openharmony_admin`,
          /*name = */ `openharmony`,
          /*avatar_url = */ `https://foruda.gitee.com/avatar/1677102952566165682/7928036_openharmony_admin_1622551091.png`,
          /*url = */ `https://gitee.com/api/v5/users/openharmony_admin`,
          /*html_url = */ `https://gitee.com/openharmony_admin`,
          /*remark = */ ``,
          /*followers_url = */ `https://gitee.com/api/v5/users/openharmony_admin/followers`,
          /*following_url = */ `https://gitee.com/api/v5/users/openharmony_admin/following_url{/other_user}`,
          /*gists_url = */ `https://gitee.com/api/v5/users/openharmony_admin/gists{/gist_id}`,
          /*starred_url = */ `https://gitee.com/api/v5/users/openharmony_admin/starred{/owner}{/repo}`,
          /*subscriptions_url = */ `https://gitee.com/api/v5/users/openharmony_admin/subscriptions`,
          /*organizations_url = */ `https://gitee.com/api/v5/users/openharmony_admin/orgs`,
          /*repos_url = */ `https://gitee.com/api/v5/users/openharmony_admin/repos`,
          /*events_url = */ `https://gitee.com/api/v5/users/openharmony_admin/events{/privacy}`,
          /*received_events_url = */ `https://gitee.com/api/v5/users/openharmony_admin/received_events`,
          /*type = */ `User`
        ),
        /*description = */ `暂无描述`,
        /*private_ = */ false,
        /*public_ = */ true,
        /*internal_ = */ false,
        /*fork = */ false,
        /*html_url = */ `https://gitee.com/openharmony/arkcompiler_runtime_core.git`,
        /*ssh_url = */ `git@gitee.com:openharmony/arkcompiler_runtime_core.git`
      )
    )
  );
}
function MockPR4(): PR {
  return new PR(
    /*id = */ 13110954,
    /*url = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core/pulls/3002`,
    /*html_url = */ `https://gitee.com/openharmony/arkcompiler_runtime_core/pulls/3002`,
    /*diff_url = */ `https://gitee.com/openharmony/arkcompiler_runtime_core/pulls/3002.diff`,
    /*patch_url = */ `https://gitee.com/openharmony/arkcompiler_runtime_core/pulls/3002.patch`,
    /*issue_url = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core/pulls/3002/issues`,
    /*commits_url = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core/pulls/3002/commits`,
    /*review_comments_url = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core/pulls/comments/{/number}`,
    /*review_comment_url = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core/pulls/comments`,
    /*comments_url = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core/pulls/3002/comments`,
    /*number = */ 3002,
    /*close_related_issue = */ 1,
    /*prune_branch = */ false,
    /*state = */ `open`,
    /*assignees_number = */ 1,
    /*testers_number = */ 1,
    /*assignees = */ new Assignees(
      /*values = */ new Array<Assignee>(
        new Assignee(
          /*id = */ 5654864,
          /*login = */ `egavrin`,
          /*name = */ `egavrin`,
          /*avatar_url = */ `https://gitee.com/assets/no_portrait.png`,
          /*url = */ `https://gitee.com/api//users/egavrin`,
          /*html_url = */ `https://gitee.com/egavrin`,
          /*remark = */ ``,
          /*followers_url = */ `https://gitee.com/api//users/egavrin/followers`,
          /*following_url = */ `https://gitee.com/api//users/egavrin/following_url{/other_user}`,
          /*gists_url = */ `https://gitee.com/api//users/egavrin/gists{/gist_id}`,
          /*starred_url = */ `https://gitee.com/api//users/egavrin/starred{/owner}{/repo}`,
          /*subscriptions_url = */ `https://gitee.com/api//users/egavrin/subscriptions`,
          /*organizations_url = */ `https://gitee.com/api//users/egavrin/orgs`,
          /*repos_url = */ `https://gitee.com/api//users/egavrin/repos`,
          /*events_url = */ `https://gitee.com/api//users/egavrin/events{/privacy}`,
          /*received_events_url = */ `https://gitee.com/api//users/egavrin/received_events`,
          /*type = */ `User`,
          /*assignee = */ false,
          /*code_owner = */ true,
          /*accept = */ false
        ),
        new Assignee(
          /*id = */ 7847922,
          /*login = */ `godmiaozi`,
          /*name = */ `godmiaozi`,
          /*avatar_url = */ `https://gitee.com/assets/no_portrait.png`,
          /*url = */ `https://gitee.com/api//users/godmiaozi`,
          /*html_url = */ `https://gitee.com/godmiaozi`,
          /*remark = */ ``,
          /*followers_url = */ `https://gitee.com/api//users/godmiaozi/followers`,
          /*following_url = */ `https://gitee.com/api//users/godmiaozi/following_url{/other_user}`,
          /*gists_url = */ `https://gitee.com/api//users/godmiaozi/gists{/gist_id}`,
          /*starred_url = */ `https://gitee.com/api//users/godmiaozi/starred{/owner}{/repo}`,
          /*subscriptions_url = */ `https://gitee.com/api//users/godmiaozi/subscriptions`,
          /*organizations_url = */ `https://gitee.com/api//users/godmiaozi/orgs`,
          /*repos_url = */ `https://gitee.com/api//users/godmiaozi/repos`,
          /*events_url = */ `https://gitee.com/api//users/godmiaozi/events{/privacy}`,
          /*received_events_url = */ `https://gitee.com/api//users/godmiaozi/received_events`,
          /*type = */ `User`,
          /*assignee = */ true,
          /*code_owner = */ false,
          /*accept = */ false
        ),
        new Assignee(
          /*id = */ 9580322,
          /*login = */ `ctw-ian`,
          /*name = */ `ctw-ian`,
          /*avatar_url = */ `https://gitee.com/assets/no_portrait.png`,
          /*url = */ `https://gitee.com/api//users/ctw-ian`,
          /*html_url = */ `https://gitee.com/ctw-ian`,
          /*remark = */ ``,
          /*followers_url = */ `https://gitee.com/api//users/ctw-ian/followers`,
          /*following_url = */ `https://gitee.com/api//users/ctw-ian/following_url{/other_user}`,
          /*gists_url = */ `https://gitee.com/api//users/ctw-ian/gists{/gist_id}`,
          /*starred_url = */ `https://gitee.com/api//users/ctw-ian/starred{/owner}{/repo}`,
          /*subscriptions_url = */ `https://gitee.com/api//users/ctw-ian/subscriptions`,
          /*organizations_url = */ `https://gitee.com/api//users/ctw-ian/orgs`,
          /*repos_url = */ `https://gitee.com/api//users/ctw-ian/repos`,
          /*events_url = */ `https://gitee.com/api//users/ctw-ian/events{/privacy}`,
          /*received_events_url = */ `https://gitee.com/api//users/ctw-ian/received_events`,
          /*type = */ `User`,
          /*assignee = */ true,
          /*code_owner = */ false,
          /*accept = */ false
        ),
        new Assignee(
          /*id = */ 9663914,
          /*login = */ `peijiajun`,
          /*name = */ `peijiajun`,
          /*avatar_url = */ `https://gitee.com/assets/no_portrait.png`,
          /*url = */ `https://gitee.com/api//users/peijiajun`,
          /*html_url = */ `https://gitee.com/peijiajun`,
          /*remark = */ ``,
          /*followers_url = */ `https://gitee.com/api//users/peijiajun/followers`,
          /*following_url = */ `https://gitee.com/api//users/peijiajun/following_url{/other_user}`,
          /*gists_url = */ `https://gitee.com/api//users/peijiajun/gists{/gist_id}`,
          /*starred_url = */ `https://gitee.com/api//users/peijiajun/starred{/owner}{/repo}`,
          /*subscriptions_url = */ `https://gitee.com/api//users/peijiajun/subscriptions`,
          /*organizations_url = */ `https://gitee.com/api//users/peijiajun/orgs`,
          /*repos_url = */ `https://gitee.com/api//users/peijiajun/repos`,
          /*events_url = */ `https://gitee.com/api//users/peijiajun/events{/privacy}`,
          /*received_events_url = */ `https://gitee.com/api//users/peijiajun/received_events`,
          /*type = */ `User`,
          /*assignee = */ true,
          /*code_owner = */ false,
          /*accept = */ false
        ),
        new Assignee(
          /*id = */ 11228302,
          /*login = */ `Prof1983`,
          /*name = */ `Ishin Pavel`,
          /*avatar_url = */ `https://foruda.gitee.com/avatar/1677231228555595315/11228302_prof1983_1657184805.png`,
          /*url = */ `https://gitee.com/api//users/Prof1983`,
          /*html_url = */ `https://gitee.com/Prof1983`,
          /*remark = */ ``,
          /*followers_url = */ `https://gitee.com/api//users/Prof1983/followers`,
          /*following_url = */ `https://gitee.com/api//users/Prof1983/following_url{/other_user}`,
          /*gists_url = */ `https://gitee.com/api//users/Prof1983/gists{/gist_id}`,
          /*starred_url = */ `https://gitee.com/api//users/Prof1983/starred{/owner}{/repo}`,
          /*subscriptions_url = */ `https://gitee.com/api//users/Prof1983/subscriptions`,
          /*organizations_url = */ `https://gitee.com/api//users/Prof1983/orgs`,
          /*repos_url = */ `https://gitee.com/api//users/Prof1983/repos`,
          /*events_url = */ `https://gitee.com/api//users/Prof1983/events{/privacy}`,
          /*received_events_url = */ `https://gitee.com/api//users/Prof1983/received_events`,
          /*type = */ `User`,
          /*assignee = */ true,
          /*code_owner = */ false,
          /*accept = */ false
        )
      )
    ),
    /*testers = */ new Assignees(
      /*values = */ new Array<Assignee>(
        new Assignee(
          /*id = */ 7387629,
          /*login = */ `openharmony_ci`,
          /*name = */ `openharmony_ci`,
          /*avatar_url = */ `https://foruda.gitee.com/avatar/1677075395966509043/7387629_openharmony_ci_1656582662.png`,
          /*url = */ `https://gitee.com/api//users/openharmony_ci`,
          /*html_url = */ `https://gitee.com/openharmony_ci`,
          /*remark = */ ``,
          /*followers_url = */ `https://gitee.com/api//users/openharmony_ci/followers`,
          /*following_url = */ `https://gitee.com/api//users/openharmony_ci/following_url{/other_user}`,
          /*gists_url = */ `https://gitee.com/api//users/openharmony_ci/gists{/gist_id}`,
          /*starred_url = */ `https://gitee.com/api//users/openharmony_ci/starred{/owner}{/repo}`,
          /*subscriptions_url = */ `https://gitee.com/api//users/openharmony_ci/subscriptions`,
          /*organizations_url = */ `https://gitee.com/api//users/openharmony_ci/orgs`,
          /*repos_url = */ `https://gitee.com/api//users/openharmony_ci/repos`,
          /*events_url = */ `https://gitee.com/api//users/openharmony_ci/events{/privacy}`,
          /*received_events_url = */ `https://gitee.com/api//users/openharmony_ci/received_events`,
          /*type = */ `User`,
          /*assignee = */ true,
          /*code_owner = */ false,
          /*accept = */ false
        )
      )
    ),
    /*api_reviewers_number = */ 0,
    /*api_reviewers = */ new ApiReviewers(
      /*values = */ new Array<ApiReviewer>()
    ),
    /*milestone = */ undefined,
    /*labels = */ new Labels(
      /*values = */ new Array<Label>(
        new Label(
          /*id = */ 113667295,
          /*color = */ `20c22e`,
          /*name = */ `dco检查成功`,
          /*repository_id = */ 6511493,
          /*url = */ `https://gitee.com/api/v5/enterprises/open_harmony/labels/dco检查成功`,
          /*created_at = */ new Date(1624000115000),
          /*updated_at = */ new Date(1733748579000)
        ),
        new Label(
          /*id = */ 200819422,
          /*color = */ `1083d6`,
          /*name = */ `waiting_on_author`,
          /*repository_id = */ 6511493,
          /*url = */ `https://gitee.com/api/v5/enterprises/open_harmony/labels/waiting_on_author`,
          /*created_at = */ new Date(1682247421000),
          /*updated_at = */ new Date(1733748606000)
        )
      )
    ),
    /*locked = */ false,
    /*created_at = */ new Date(1733581090000),
    /*updated_at = */ new Date(1733747748000),
    /*closed_at = */ undefined,
    /*draft = */ false,
    /*merged_at = */ undefined,
    /*mergeable = */ true,
    /*can_merge_check = */ false,
    /*_links = */ new Links(
      /*self = */ new Link(
        /*href = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core/pulls/3002`
      ),
      /*html = */ new Link(
        /*href = */ `https://gitee.com/openharmony/arkcompiler_runtime_core/pulls/3002`
      ),
      /*issue = */ new Link(
        /*href = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core/pulls/3002/issues`
      ),
      /*comments = */ new Link(
        /*href = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core/pulls/3002/comments`
      ),
      /*review_comments = */ new Link(
        /*href = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core/pulls/3002/comments`
      ),
      /*review_comment = */ new Link(
        /*href = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core/pulls/comments/3002`
      ),
      /*commits = */ new Link(
        /*href = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core/pulls/3002/commits`
      )
    ),
    /*user = */ new User(
      /*id = */ 11395095,
      /*login = */ `panferovi`,
      /*name = */ `Panferov Ivan`,
      /*avatar_url = */ `https://gitee.com/assets/no_portrait.png`,
      /*url = */ `https://gitee.com/api/v5/users/panferovi`,
      /*html_url = */ `https://gitee.com/panferovi`,
      /*remark = */ ``,
      /*followers_url = */ `https://gitee.com/api/v5/users/panferovi/followers`,
      /*following_url = */ `https://gitee.com/api/v5/users/panferovi/following_url{/other_user}`,
      /*gists_url = */ `https://gitee.com/api/v5/users/panferovi/gists{/gist_id}`,
      /*starred_url = */ `https://gitee.com/api/v5/users/panferovi/starred{/owner}{/repo}`,
      /*subscriptions_url = */ `https://gitee.com/api/v5/users/panferovi/subscriptions`,
      /*organizations_url = */ `https://gitee.com/api/v5/users/panferovi/orgs`,
      /*repos_url = */ `https://gitee.com/api/v5/users/panferovi/repos`,
      /*events_url = */ `https://gitee.com/api/v5/users/panferovi/events{/privacy}`,
      /*received_events_url = */ `https://gitee.com/api/v5/users/panferovi/received_events`,
      /*type = */ `User`
    ),
    /*ref_pull_requests = */ new PRs(/*values = */ new Array<PR>()),
    /*title = */ `Schedule EAWorker in event loop`,
    /*body = */ `### **Issue**
#IB9S72 

### **Reason**
Schedule EAWorker in event loop

### **Description**
Schedule coroutines of EAWorker from event loop

### **Tests**

ninja all tests

**All required pre-merge tests passed. Results are available in the internal CI.**
`,
    /*head = */ new Head(
      /*label = */ `schedule-eaworker`,
      /*ref = */ `schedule-eaworker`,
      /*sha = */ `fd5c3992bd30ac4511b9e5f3fba0c9183b4ca6e9`,
      /*user = */ new User(
        /*id = */ 11395095,
        /*login = */ `panferovi`,
        /*name = */ `Panferov Ivan`,
        /*avatar_url = */ `https://gitee.com/assets/no_portrait.png`,
        /*url = */ `https://gitee.com/api/v5/users/panferovi`,
        /*html_url = */ `https://gitee.com/panferovi`,
        /*remark = */ ``,
        /*followers_url = */ `https://gitee.com/api/v5/users/panferovi/followers`,
        /*following_url = */ `https://gitee.com/api/v5/users/panferovi/following_url{/other_user}`,
        /*gists_url = */ `https://gitee.com/api/v5/users/panferovi/gists{/gist_id}`,
        /*starred_url = */ `https://gitee.com/api/v5/users/panferovi/starred{/owner}{/repo}`,
        /*subscriptions_url = */ `https://gitee.com/api/v5/users/panferovi/subscriptions`,
        /*organizations_url = */ `https://gitee.com/api/v5/users/panferovi/orgs`,
        /*repos_url = */ `https://gitee.com/api/v5/users/panferovi/repos`,
        /*events_url = */ `https://gitee.com/api/v5/users/panferovi/events{/privacy}`,
        /*received_events_url = */ `https://gitee.com/api/v5/users/panferovi/received_events`,
        /*type = */ `User`
      ),
      /*repo = */ new Repo(
        /*id = */ 31767178,
        /*full_name = */ `panferovi/arkcompiler_runtime_core`,
        /*human_name = */ `Panferov Ivan/arkcompiler_runtime_core`,
        /*url = */ `https://gitee.com/api/v5/repos/panferovi/arkcompiler_runtime_core`,
        /*namespace_ = */ new Namespace(
          /*id = */ 10281242,
          /*type = */ `personal`,
          /*name = */ `Panferov Ivan`,
          /*path = */ `panferovi`,
          /*html_url = */ `https://gitee.com/panferovi`
        ),
        /*path = */ `arkcompiler_runtime_core`,
        /*name = */ `arkcompiler_runtime_core`,
        /*owner = */ new User(
          /*id = */ 11395095,
          /*login = */ `panferovi`,
          /*name = */ `Panferov Ivan`,
          /*avatar_url = */ `https://gitee.com/assets/no_portrait.png`,
          /*url = */ `https://gitee.com/api/v5/users/panferovi`,
          /*html_url = */ `https://gitee.com/panferovi`,
          /*remark = */ ``,
          /*followers_url = */ `https://gitee.com/api/v5/users/panferovi/followers`,
          /*following_url = */ `https://gitee.com/api/v5/users/panferovi/following_url{/other_user}`,
          /*gists_url = */ `https://gitee.com/api/v5/users/panferovi/gists{/gist_id}`,
          /*starred_url = */ `https://gitee.com/api/v5/users/panferovi/starred{/owner}{/repo}`,
          /*subscriptions_url = */ `https://gitee.com/api/v5/users/panferovi/subscriptions`,
          /*organizations_url = */ `https://gitee.com/api/v5/users/panferovi/orgs`,
          /*repos_url = */ `https://gitee.com/api/v5/users/panferovi/repos`,
          /*events_url = */ `https://gitee.com/api/v5/users/panferovi/events{/privacy}`,
          /*received_events_url = */ `https://gitee.com/api/v5/users/panferovi/received_events`,
          /*type = */ `User`
        ),
        /*assigner = */ new User(
          /*id = */ 11395095,
          /*login = */ `panferovi`,
          /*name = */ `Panferov Ivan`,
          /*avatar_url = */ `https://gitee.com/assets/no_portrait.png`,
          /*url = */ `https://gitee.com/api/v5/users/panferovi`,
          /*html_url = */ `https://gitee.com/panferovi`,
          /*remark = */ ``,
          /*followers_url = */ `https://gitee.com/api/v5/users/panferovi/followers`,
          /*following_url = */ `https://gitee.com/api/v5/users/panferovi/following_url{/other_user}`,
          /*gists_url = */ `https://gitee.com/api/v5/users/panferovi/gists{/gist_id}`,
          /*starred_url = */ `https://gitee.com/api/v5/users/panferovi/starred{/owner}{/repo}`,
          /*subscriptions_url = */ `https://gitee.com/api/v5/users/panferovi/subscriptions`,
          /*organizations_url = */ `https://gitee.com/api/v5/users/panferovi/orgs`,
          /*repos_url = */ `https://gitee.com/api/v5/users/panferovi/repos`,
          /*events_url = */ `https://gitee.com/api/v5/users/panferovi/events{/privacy}`,
          /*received_events_url = */ `https://gitee.com/api/v5/users/panferovi/received_events`,
          /*type = */ `User`
        ),
        /*description = */ `null`,
        /*private_ = */ false,
        /*public_ = */ true,
        /*internal_ = */ false,
        /*fork = */ true,
        /*html_url = */ `https://gitee.com/panferovi/arkcompiler_runtime_core.git`,
        /*ssh_url = */ `git@gitee.com:panferovi/arkcompiler_runtime_core.git`
      )
    ),
    /*base = */ new Base(
      /*label = */ `OpenHarmony_feature_20241108`,
      /*ref = */ `OpenHarmony_feature_20241108`,
      /*sha = */ `d212656f6aaa6a5a7cbfb74e07888030e38f8046`,
      /*user = */ new User(
        /*id = */ 7928036,
        /*login = */ `openharmony_admin`,
        /*name = */ `openharmony`,
        /*avatar_url = */ `https://foruda.gitee.com/avatar/1677102952566165682/7928036_openharmony_admin_1622551091.png`,
        /*url = */ `https://gitee.com/api/v5/users/openharmony_admin`,
        /*html_url = */ `https://gitee.com/openharmony_admin`,
        /*remark = */ ``,
        /*followers_url = */ `https://gitee.com/api/v5/users/openharmony_admin/followers`,
        /*following_url = */ `https://gitee.com/api/v5/users/openharmony_admin/following_url{/other_user}`,
        /*gists_url = */ `https://gitee.com/api/v5/users/openharmony_admin/gists{/gist_id}`,
        /*starred_url = */ `https://gitee.com/api/v5/users/openharmony_admin/starred{/owner}{/repo}`,
        /*subscriptions_url = */ `https://gitee.com/api/v5/users/openharmony_admin/subscriptions`,
        /*organizations_url = */ `https://gitee.com/api/v5/users/openharmony_admin/orgs`,
        /*repos_url = */ `https://gitee.com/api/v5/users/openharmony_admin/repos`,
        /*events_url = */ `https://gitee.com/api/v5/users/openharmony_admin/events{/privacy}`,
        /*received_events_url = */ `https://gitee.com/api/v5/users/openharmony_admin/received_events`,
        /*type = */ `User`
      ),
      /*repo = */ new Repo(
        /*id = */ 17812929,
        /*full_name = */ `openharmony/arkcompiler_runtime_core`,
        /*human_name = */ `OpenHarmony/arkcompiler_runtime_core`,
        /*url = */ `https://gitee.com/api/v5/repos/openharmony/arkcompiler_runtime_core`,
        /*namespace_ = */ new Namespace(
          /*id = */ 6486504,
          /*type = */ `group`,
          /*name = */ `OpenHarmony`,
          /*path = */ `openharmony`,
          /*html_url = */ `https://gitee.com/openharmony`
        ),
        /*path = */ `arkcompiler_runtime_core`,
        /*name = */ `arkcompiler_runtime_core`,
        /*owner = */ new User(
          /*id = */ 7928036,
          /*login = */ `openharmony_admin`,
          /*name = */ `openharmony`,
          /*avatar_url = */ `https://foruda.gitee.com/avatar/1677102952566165682/7928036_openharmony_admin_1622551091.png`,
          /*url = */ `https://gitee.com/api/v5/users/openharmony_admin`,
          /*html_url = */ `https://gitee.com/openharmony_admin`,
          /*remark = */ ``,
          /*followers_url = */ `https://gitee.com/api/v5/users/openharmony_admin/followers`,
          /*following_url = */ `https://gitee.com/api/v5/users/openharmony_admin/following_url{/other_user}`,
          /*gists_url = */ `https://gitee.com/api/v5/users/openharmony_admin/gists{/gist_id}`,
          /*starred_url = */ `https://gitee.com/api/v5/users/openharmony_admin/starred{/owner}{/repo}`,
          /*subscriptions_url = */ `https://gitee.com/api/v5/users/openharmony_admin/subscriptions`,
          /*organizations_url = */ `https://gitee.com/api/v5/users/openharmony_admin/orgs`,
          /*repos_url = */ `https://gitee.com/api/v5/users/openharmony_admin/repos`,
          /*events_url = */ `https://gitee.com/api/v5/users/openharmony_admin/events{/privacy}`,
          /*received_events_url = */ `https://gitee.com/api/v5/users/openharmony_admin/received_events`,
          /*type = */ `User`
        ),
        /*assigner = */ new User(
          /*id = */ 7928036,
          /*login = */ `openharmony_admin`,
          /*name = */ `openharmony`,
          /*avatar_url = */ `https://foruda.gitee.com/avatar/1677102952566165682/7928036_openharmony_admin_1622551091.png`,
          /*url = */ `https://gitee.com/api/v5/users/openharmony_admin`,
          /*html_url = */ `https://gitee.com/openharmony_admin`,
          /*remark = */ ``,
          /*followers_url = */ `https://gitee.com/api/v5/users/openharmony_admin/followers`,
          /*following_url = */ `https://gitee.com/api/v5/users/openharmony_admin/following_url{/other_user}`,
          /*gists_url = */ `https://gitee.com/api/v5/users/openharmony_admin/gists{/gist_id}`,
          /*starred_url = */ `https://gitee.com/api/v5/users/openharmony_admin/starred{/owner}{/repo}`,
          /*subscriptions_url = */ `https://gitee.com/api/v5/users/openharmony_admin/subscriptions`,
          /*organizations_url = */ `https://gitee.com/api/v5/users/openharmony_admin/orgs`,
          /*repos_url = */ `https://gitee.com/api/v5/users/openharmony_admin/repos`,
          /*events_url = */ `https://gitee.com/api/v5/users/openharmony_admin/events{/privacy}`,
          /*received_events_url = */ `https://gitee.com/api/v5/users/openharmony_admin/received_events`,
          /*type = */ `User`
        ),
        /*description = */ `暂无描述`,
        /*private_ = */ false,
        /*public_ = */ true,
        /*internal_ = */ false,
        /*fork = */ false,
        /*html_url = */ `https://gitee.com/openharmony/arkcompiler_runtime_core.git`,
        /*ssh_url = */ `git@gitee.com:openharmony/arkcompiler_runtime_core.git`
      )
    )
  );
}
