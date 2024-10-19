<template>
    <div class="file">
        <div class="info">
            <div class="item" style="flex: 100%;">
                <h2>main方法使用</h2>
                <pre v-html="utils.highlightCppKeywords(text[0])"></pre>
            </div>
            <div class="item" style="width: 800px;">
                <h2>可存储类型/构造函数/运算操作</h2>
                <pre v-html="utils.highlightCppKeywords(text[1])"></pre>
            </div>
            <div class="item" style="flex: 40%;height: 50%;padding: 0;">
                <div class="item" style="height: 50%;">
                    <h2>描述</h2>
                    <p>此类型对象可以支持相当多的类型(如果不够就联系作者,看看能不能酌情添加)。</p>
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
                {//Open
                    label: "Open", comment: "打开文件",
                    code: `bool Open(std::string path);`,
                    params: {
                        arr: [
                            { param: "path", type: "std::string", desc: "文件路径" }
                        ],
                        ret: { type: "bool", desc: "是否成功打开文件" }
                    }
                }, {//Close
                    label: "Close", comment: "关闭文件",
                    code: `bool Close();`,
                    params: {
                        arr: [],
                        ret: { type: "bool", desc: "是否成功关闭文件" }
                    }
                }, {//Seek
                    label: "Seek", comment: "设置文件指针",
                    code: `bool Seek(long long pos = 0) const;`,
                    params: {
                        arr: [
                            { param: "pos", type: "long long", desc: "位置, 默认为0" }
                        ],
                        ret: { type: "bool", desc: "是否成功置文件指针" }
                    }
                }, {//Size
                    label: "Size", comment: "取文件大小",
                    code: `size_t Size() const;`,
                    params: {
                        arr: [],
                        ret: { type: "size_t", desc: "文件大小" }
                    }
                }, {//Write
                    label: "Write", comment: "写入数据",
                    code: `bool Write(Byteset data) const;`,
                    params: {
                        arr: [
                            { param: "data", type: "Byteset", desc: "待写入数据" }
                        ],
                        ret: { type: "bool", desc: "是否成功写入数据" }
                    }
                }, {//Read
                    label: "Read", comment: "读取数据",
                    code: `Byteset Read(long long size) const;`,
                    params: {
                        arr: [
                            { param: "size", type: "long long", desc: "读取数据的大小" }
                        ],
                        ret: { type: "Byteset", desc: "读取到的数据" }
                    }
                }, {//Delete
                    label: "Delete", comment: "删除数据",
                    code: `bool Delete(long long size) const;`,
                    params: {
                        arr: [
                            { param: "size", type: "long long", desc: "待删除数据的大小" }
                        ],
                        ret: { type: "bool", desc: "是否成功删除数据" }
                    }
                }, {//Replace
                    label: "Replace", comment: "替换数据",
                    code: `bool Replace(Byteset new_data,long long size) const;`,
                    params: {
                        arr: [
                            { param: "new_data", type: "Byteset", desc: "待替换的数据" },
                            { param: "size", type: "long long", desc: "替换长度" }
                        ],
                        ret: { type: "bool", desc: "是否成功替换数据" }
                    }
                }, {//Find
                    label: "Find", comment: "查找数据",
                    code: `size_t Find(Byteset data,size_t index = NULL,bool flag = false) const;`,
                    params: {
                        arr: [
                            { param: "data", type: "Byteset", desc: "待查找的数据" },
                            { param: "index", type: "size_t", desc: "起始查找位置, 默认为0" },
                            { param: "flag", type: "bool", desc: "是否倒找,默认为false" }
                        ],
                        ret: { type: "size_t", desc: "找到的数据的位置, -1表示未找到" }
                    }
                }
            ],
            text: [
                `
    /*
    * File类使用方法
    * File带有自动关闭文件的功能
    * 构造函数可以直接打开文件,也可以使用Open方法打开文件
    * 析构函数会自动关闭文件
    * 成员函数有Open(打开文件)、Close(关闭文件)、Seek(设置文件指针)、Size(取文件大小)、Write(写入数据)、Read(读取数据)、Delete(删除数据)、Replace(替换数据)、Find(查找数据)
    * 其中Seek, Size, Write, Read, Delete, Replace, Find都是常用的操作
    * 其他成员函数请参考源码
    */
    File file("C:\\Users\\QX\\Desktop\\test.txt");//构造函数直接打开文件
    std::cout << "文件是否打开: " << file.is_open << std::endl;//判断状态
    file.Seek(0);//设置文件指针位置
    std::cout <<"读数据:"<< file.Read(10) << std::endl;//输出空字节集
    file.Seek(0);//设置文件指针位置
    std::cout << "写数据:" << file.Write({ "Hello World!" }) << std::endl;//输出bool 值
    file.Seek(0);//设置文件指针位置
    std::cout << "读数据:" << file.Read(10) << std::endl;//输出字节集
    file.Seek(5);//设置文件指针位置
    std::cout << "删数据:" << file.Delete(5) << std::endl;//输出bool 值
    file.Seek(0);//设置文件指针位置
    std::cout << "读数据:" << file.Read(10) << std::endl;//输出字节集
                `,
                `
    /*
    * 打开文件
    * @param path 文件路径
    * @return 是否成功打开文件
    */
    bool Open(std::string path);
    /*
    * 关闭文件
    * @return 是否成功关闭文件
    */
    bool Close();
    /*
    * 置文件指针到指定位置
    * @param pos 位置, 默认为0
    * @return 是否成功置文件指针
    */
    bool Seek(long long pos = 0) const;
    /*
    * 取文件大小
    * @return 文件大小
    */
    size_t Size() const;
    /*
    * 写入数据
    * @param data 待写入数据
    * @return 是否成功写入数据
    */
    bool Write(Byteset data) const;
    /*
    * 读取数据
    * @param size 读取数据的大小
    * @return 读取到的数据
    */
    Byteset Read(long long size) const;
    /*
    * 删除数据
    * @param size 待删除数据的大小
    * @return 是否成功删除数据
    */
    bool Delete(long long size) const;
    /*
    * 替换数据
    * @param new_data 待替换的数据
    * @param size 替换长度
    * @return 是否成功替换数据
    */
    bool Replace(Byteset new_data,long long size) const;
    /*
    * 查找数据
    * @param data 待查找的数据
    * @param index 起始查找位置, 默认为0
    * @param flag 是否倒找,默认为false
    * @return 找到的数据的位置, -1表示未找到
    */
    size_t Find(Byteset data,size_t index = NULL,bool flag = false) const;
                `
            ]
        }
    }
};
</script>
<style lang="scss" scoped>
.file {
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
