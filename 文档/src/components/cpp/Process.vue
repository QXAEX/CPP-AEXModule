<template>
    <div class="process">
        <div class="info">
            <div class="item" style="flex: 100%;">
                <h2>main方法使用</h2>
                <pre v-html="utils.highlightCppKeywords(text[0])"></pre>
            </div>
            <div class="item" style="width: 800px;">
                <h2>进程信息/进程操作</h2>
                <pre v-html="utils.highlightCppKeywords(text[1])"></pre>
            </div>
            <div class="item" style="flex: 40%;height: 50%;padding: 0;">
                <div class="item" style="height: 50%;">
                    <h2>描述</h2>
                    <p>此进程类提供了获取指定进程相关信息的功能,例如进程名取PID、路径等等</p>
                </div>
                <div class="item" style="height: 50%;" v-for="(item, i) in list" :key="i">
                    <h2 v-text="item.label"></h2>
                    <pre v-html="utils.highlightCppKeywords(item.code)"></pre>
                    <p class="comment" v-text="item.comment"></p>
                    <h3>参数说明</h3>
                    <table class="params-table">
                        <tr class="top">
                            <th>参数名</th>
                            <th>类型</th>
                            <th>说明</th>
                        </tr>
                        <tr class="param" v-for="(param, i) in item.params.arr" :key="i">
                            <td>
                                <span class="dict">{{ param.param }}</span>
                            </td>
                            <td>
                                <span class="dict">{{ param.type }}</span>
                            </td>
                            <td v-html="param.desc"></td>
                        </tr>
                        <tr class="ret">
                            <td>
                                <span class="dict">返回值</span>
                            </td>
                            <td>
                                <span class="dict" v-text="item.params.ret.type"></span>
                            </td>
                            <td v-text="item.params.ret.desc"></td>
                        </tr>
                    </table>
                </div>
            </div>
        </div>
    </div>
</template>

<script>
export default {
    props: ['utils'],
    data() {
        return {
            list: [
                {//GetProcessPath
                    label: "GetProcessPath", comment: "获取进程路径",
                    code: `std::string GetProcessPath(DWORD processID);`,
                    params: {
                        arr: [
                            { param: 'processID', type: 'DWORD', desc: '进程ID' },
                        ],
                        ret: { type: 'std::string', desc: '进程路径' }
                    }
                }, {//GetProcessCommandLine
                    label: "GetProcessCommandLine", comment: "获取进程命令行",
                    code: `std::string GetProcessCommandLine(DWORD processID);`,
                    params: {
                        arr: [
                            { param: 'processID', type: 'DWORD', desc: '进程ID' },
                        ],
                        ret: { type: 'std::string', desc: '进程命令行' }
                    }
                }, {//GetWindowTitle
                    label: "GetWindowTitle", comment: "获取窗口标题",
                    code: `std::string GetWindowTitle(HWND hwnd);`,
                    params: {
                        arr: [
                            { param: 'hwnd', type: 'HWND', desc: '窗口句柄' },
                        ],
                        ret: { type: 'std::string', desc: '窗口标题' }
                    }
                }, {//GetProcessWinHandle
                    label: "GetProcessWinHandle", comment: "进程ID取窗口句柄",
                    code: `HWND GetProcessWinHandle(DWORD processID);`,
                    params: {
                        arr: [
                            { param: 'processID', type: 'DWORD', desc: '进程ID' },
                        ],
                        ret: { type: 'HWND', desc: '窗口句柄' }
                    }
                }, {//ProcessList
                    label: "ProcessList", comment: "获取所有进程信息",
                    code: `std::vector<ProcessInfo> ProcessList();`,
                    params: {
                        arr: [],
                        ret: { type: 'std::vector<ProcessInfo>', desc: '所有进程的信息' }
                    }
                }, {//ProcessGetID
                    label: "ProcessGetID", comment: "进程名取进程ID",
                    code: `DWORD ProcessGetID(std::string processName);`,
                    params: {
                        arr: [
                            { param: 'processName', type: 'std::string', desc: '进程名' },
                        ],
                        ret: { type: 'DWORD', desc: '进程ID' }
                    }
                }, {//ProcessGetName
                    label: "ProcessGetName", comment: "进程ID取进程名",
                    code: `std::string ProcessGetName(DWORD processID);`,
                    params: {
                        arr: [
                            { param: 'processID', type: 'DWORD', desc: '进程ID' },
                        ],
                        ret: { type: 'std::string', desc: '进程名' }
                    }
                }, {//ProcessGetWinHandle
                    label: "ProcessGetWinHandle", comment: "进程ID取窗口句柄",
                    code: `HWND ProcessGetWinHandle(DWORD processID);`,
                    params: {
                        arr: [
                            { param: 'processID', type: 'DWORD', desc: '进程ID' },
                        ],
                        ret: { type: 'HWND', desc: '窗口句柄' }
                    }
                }

            ],
            text: [`
    Process::GetProcessPath(114514);//获取进程路径
    //Process功能集合是个namespace,里面有很多功能函数,这里只列举了几个常用的功能函数。
    //可通过Process::...来调用。
                `,
                `
    //枚举进程信息列表
    struct ProcessInfo {
        DWORD PID = NULL;//进程ID
        std::string Name;//进程名
        std::wstring WName;//进程名(宽字符)
        std::string WinTitle;//进程窗口标题
        HWND WinHandle = NULL;//进程窗口句柄
        std::string Path;//进程路径
        std::string CommandLine;//进程命令行
    };
    /*
    * 获取进程路径
    * @param processID 进程ID
    * @return 进程路径
    */
    std::string GetProcessPath(DWORD processID);
    /*
    * 获取进程命令行
    * @param processID 进程ID
    * @return 进程命令行
    */
    std::string GetProcessCommandLine(DWORD processID);
    /*
    * 获取窗口标题
    * @param hwnd 窗口句柄
    * @return 窗口标题
    */
    std::string GetWindowTitle(HWND hwnd);
    /*
    * 进程ID取窗口句柄
    * @param processID 进程ID
    * @return 窗口句柄,NULL表示未找到
    */
    HWND GetProcessWinHandle(DWORD processID);
    /*
    * 获取所有进程信息
    * @return 所有进程的信息
    */
    std::vector<ProcessInfo> ProcessList();
    /*
    * 进程名取进程ID
    * @param processName 进程名
    * @return 进程ID,-1表示未找到
    */
    DWORD ProcessGetID(std::string processName);
    /*
    * 进程ID取进程名
    * @param processID 进程ID
    * @return 进程名,空字符串表示未找到
    */
    std::string ProcessGetName(DWORD processID);
    /*
    * 进程ID取窗口句柄
    * @param processID 进程ID
    * @return 窗口句柄,NULL表示未找到
    */
    HWND ProcessGetWinHandle(DWORD processID);
                `
            ],
        }
    }
};
</script>
<style lang="scss" scoped>
.process {
    .info {
        display: flex;
        justify-content: center;
        flex-wrap: wrap;


        * {
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
        }

        .item {
            position: relative;
            overflow: hidden;
            line-height: 2em;
            padding: 10px 0;
            box-sizing: border-box;

            h2 {
                font-style: oblique;
                background-color: #8111cb;
                padding: 5px 10px;
                display: inline-block;
                border-top-left-radius: 5px;
                border-top-right-radius: 5px;

                &::before {
                    position: absolute;
                    content: "";
                    width: 110%;
                    height: 2px;
                    background-color: #8111cb;
                    left: -10px;
                    top: 2.15em;
                }
            }

            h3 {
                background-color: #9b62c2;
                padding: 5px 10px;
                display: inline-block;
                border-top-left-radius: 5px;
                border-top-right-radius: 5px;

                &::before {
                    position: absolute;
                    content: "";
                    width: 110%;
                    height: 2px;
                    background-color: #9b62c2;
                    left: -10px;
                    margin-top: 2em;
                }
            }

            .comment {
                font-size: 1.2em;
                text-indent: 0.5em;
                margin: 5px 0;
            }

            pre {
                font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
                line-height: 1em;
                display: block;
                width: 100%;
                border-radius: 5px;
                padding: 15px 0;
                background-color: #1c1c1c;
                overflow: auto;
                font-size: 1.3rem;
            }

            .params-table {
                display: block;
                border-collapse: collapse;
                width: 100%;
                overflow: auto;


                th,
                td {
                    border: 1px solid #9b62c2;
                    padding: 8px;
                    text-align: left;
                    text-wrap: nowrap;
                }

                .top th {
                    user-select: none;
                    font-size: 1.2em;
                    font-style: oblique;
                    background-color: #8648b0;
                    text-align: center;

                    &:nth-child(3) {
                        text-align: left;
                    }
                }

                .dict {
                    background-color: #795c8c;
                    padding: 5px 10px;
                    font-weight: bold;
                    border-radius: 100px;
                }

                .param td,
                .ret td {
                    text-align: center;

                    &:nth-child(3) {
                        text-align: left;
                        width: 100%;
                    }
                }
            }
        }
    }
}
</style>
