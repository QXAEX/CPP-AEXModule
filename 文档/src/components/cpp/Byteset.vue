<template>
    <div class="byteset">
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
                    <p>了解过易语言吗？易语言中有个数据类型为 "字节集" 的概念，它可以存储一系列字节,而C++储存字节集也有很多方式,但是要快速构建对应框架的话还是挺麻烦的。</p>
                    <p>它可以让你直接{ 0x1, 0x2, ... } 等等,在上面有代码示例。</p>
                    <p>以及一些常用的运算符也可以对此类型使用。</p>
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
                {//从字符串构造
                    label: "Byteset", comment: "从字符串构造",
                    code: `Byteset(const std::string& str);`,
                    params: {
                        arr: [
                            { param: "str", type: "const std::string&", desc: "字符串" }
                        ],
                        ret: { type: "void", desc: "无返回值" }
                    }
                }, {//从字节数组构造
                    label: "Byteset", comment: "从字节数组构造",
                    code: `Byteset(const void* bytes, long long size);`,
                    params: {
                        arr: [
                            { param: "bytes", type: "const void*", desc: "字节数组" },
                            { param: "size", type: "long long", desc: "字节数组大小" }
                        ],
                        ret: { type: "void", desc: "无返回值" }
                    }
                }, {//从字节数组构造
                    label: "Byteset", comment: "从字节数组构造",
                    code: `Byteset(const char* bytes);`,
                    params: {
                        arr: [
                            { param: "bytes", type: "const char*", desc: "字节数组" }
                        ],
                        ret: { type: "void", desc: "无返回值" }
                    }
                }, {//从int类型构造
                    label: "Byteset", comment: "从int类型构造",
                    code: `Byteset(int num);`,
                    params: {
                        arr: [
                            { param: "num", type: "int", desc: "整数" }
                        ],
                        ret: { type: "void", desc: "无返回值" }
                    }
                }, {//从long类型构造
                    label: "Byteset", comment: "从long类型构造",
                    code: `Byteset(long num);`,
                    params: {
                        arr: [
                            { param: "num", type: "long", desc: "长整数" }
                        ],
                        ret: { type: "void", desc: "无返回值" }
                    }
                }, {//从long long类型构造
                    label: "Byteset", comment: "从long long类型构造",
                    code: `Byteset(long long num);`,
                    params: {
                        arr: [
                            { param: "num", type: "long long", desc: "长长整数" }
                        ],
                        ret: { type: "void", desc: "无返回值" }
                    }
                }, {//从size_t类型构造
                    label: "Byteset", comment: "从size_t类型构造",
                    code: `Byteset(size_t num);`,
                    params: {
                        arr: [
                            { param: "num", type: "size_t", desc: "字节集大小" }
                        ],
                        ret: { type: "void", desc: "无返回值" }
                    }
                }, {//从float类型构造
                    label: "Byteset", comment: "从float类型构造",
                    code: `Byteset(float num);`,
                    params: {
                        arr: [
                            { param: "num", type: "float", desc: "浮点数" }
                        ],
                        ret: { type: "void", desc: "无返回值" }
                    }
                }, {//从double类型构造
                    label: "Byteset", comment: "从double类型构造",
                    code: `Byteset(double num);`,
                    params: {
                        arr: [
                            { param: "num", type: "double", desc: "双精度浮点数" }
                        ],
                        ret: { type: "void", desc: "无返回值" }
                    }
                }, {//从long double类型构造
                    label: "Byteset", comment: "从long double类型构造",
                    code: `Byteset(long double num);`,
                    params: {
                        arr: [
                            { param: "num", type: "long double", desc: "长双精度浮点数" }
                        ],
                        ret: { type: "void", desc: "无返回值" }
                    }
                }, {//从bool类型构造
                    label: "Byteset", comment: "从bool类型构造",
                    code: `Byteset(bool flag);`,
                    params: {
                        arr: [
                            { param: "flag", type: "bool", desc: "布尔值" }
                        ],
                        ret: { type: "void", desc: "无返回值" }
                    }
                }, {//从char类型构造
                    label: "Byteset", comment: "从char类型构造",
                    code: `Byteset(char ch);`,
                    params: {
                        arr: [
                            { param: "ch", type: "char", desc: "字符" }
                        ],
                        ret: { type: "void", desc: "无返回值" }
                    }
                }, {//从short类型构造
                    label: "Byteset", comment: "从short类型构造",
                    code: `Byteset(short num);`,
                    params: {
                        arr: [
                            { param: "num", type: "short", desc: "短整数" }
                        ],
                        ret: { type: "void", desc: "无返回值" }
                    }
                }, {// 拷贝构造函数
                    label: "Byteset", comment: "拷贝构造函数",
                    code: `Byteset(const Byteset& other);`,
                    params: {
                        arr: [
                            { param: "other", type: "const Byteset&", desc: "要拷贝的字节集" }
                        ],
                        ret: { type: "void", desc: "无返回值" }
                    }
                }, {// 移动构造函数
                    label: "Byteset", comment: "移动构造函数",
                    code: `Byteset(Byteset&& other) noexcept;`,
                    params: {
                        arr: [
                            { param: "other", type: "Byteset&&", desc: "要移动的字节集" }
                        ],
                        ret: { type: "void", desc: "无返回值" }
                    }
                }, {//数据比较处理
                    label: "operator==", comment: "数据比较处理",
                    code: `bool operator==(const Byteset& other) const;`,
                    params: {
                        arr: [
                            { param: "other", type: "const Byteset&", desc: "要比较的字节集" }
                        ],
                        ret: { type: "bool", desc: "true:相等,false:不等" }
                    }
                }, {//数据不等比较处理
                    label: "operator!=", comment: "数据不等比较处理",
                    code: `bool operator!=(const Byteset& other) const;`,
                    params: {
                        arr: [
                            { param: "other", type: "const Byteset&", desc: "要比较的字节集" }
                        ],
                        ret: { type: "bool", desc: "true:不等,false:相等" }
                    }
                }, {// 拷贝赋值操作符
                    label: "operator=", comment: "拷贝赋值操作符",
                    code: `Byteset& operator=(const Byteset& other);`,
                    params: {
                        arr: [
                            { param: "other", type: "const Byteset&", desc: "要拷贝的字节集" }
                        ],
                        ret: { type: "Byteset&", desc: "当前字节集" }
                    }
                }, {//拷贝赋值操作符:文本字符串
                    label: "operator=", comment: "拷贝赋值操作符:文本字符串",
                    code: `Byteset& operator=(const std::string& str);`,
                    params: {
                        arr: [
                            { param: "str", type: "const std::string&", desc: "要拷贝的字符串" }
                        ],
                        ret: { type: "Byteset&", desc: "当前字节集" }
                    }
                }, {//拷贝赋值操作符:字节数组
                    label: "operator=", comment: "拷贝赋值操作符:字节数组",
                    code: `Byteset& operator=(const char* bytes);`,
                    params: {
                        arr: [
                            { param: "bytes", type: "const char*", desc: "要拷贝的字节数组" }
                        ],
                        ret: { type: "Byteset&", desc: "当前字节集" }
                    }
                }, {// 初始化列表构造函数
                    label: "Byteset", comment: "初始化列表构造函数",
                    code: `Byteset(std::initializer_list<unsigned char> init_list);`,
                    params: {
                        arr: [
                            { param: "init_list", type: "std::initializer_list<unsigned char>", desc: "初始化列表" }
                        ],
                        ret: { type: "void", desc: "无返回值" }
                    }
                }, {// 追加字节
                    label: "append", comment: "追加字节",
                    code: `Byteset& append(const void* bytes, long long size);`,
                    params: {
                        arr: [
                            { param: "bytes", type: "const void*", desc: "字节数组" },
                            { param: "size", type: "long long", desc: "字节数组大小" }
                        ],
                        ret: { type: "Byteset&", desc: "当前字节集" }
                    }
                }, {// 追加另一个 Byteset
                    label: "append", comment: "追加另一个 Byteset",
                    code: `Byteset& append(const Byteset& other);`,
                    params: {
                        arr: [
                            { param: "other", type: "const Byteset&", desc: "要追加的字节集" }
                        ],
                        ret: { type: "Byteset&", desc: "当前字节集" }
                    }
                }, {// 追加字节
                    label: "push_back", comment: "追加字节",
                    code: `void push_back(unsigned char byte);`,
                    params: {
                        arr: [
                            { param: "byte", type: "unsigned char", desc: "字节" }
                        ],
                        ret: { type: "void", desc: "无返回值" }
                    }
                }, {// 弹出最后一个字节
                    label: "pop_back", comment: "弹出最后一个字节",
                    code: `unsigned char pop_back();`,
                    params: {
                        arr: [],
                        ret: { type: "unsigned char", desc: "弹出的字节" }
                    }
                }, {// 访问字节
                    label: "operator[]", comment: "访问字节",
                    code: `unsigned char& operator[](long long index);`,
                    params: {
                        arr: [
                            { param: "index", type: "long long", desc: "字节索引" }
                        ],
                        ret: { type: "unsigned char&", desc: "字节" }
                    }
                }, {// 访问字节
                    label: "operator[]", comment: "访问字节",
                    code: `const unsigned char& operator[](long long index) const;`,
                    params: {
                        arr: [
                            { param: "index", type: "long long", desc: "字节索引" }
                        ],
                        ret: { type: "const unsigned char&", desc: "字节" }
                    }
                }, {// 获取字节集大小
                    label: "size", comment: "获取字节集大小",
                    code: `long long size() const;`,
                    params: {
                        arr: [],
                        ret: { type: "long long", desc: "字节集大小" }
                    }
                }, {// 调整字节集大小
                    label: "resize", comment: "调整字节集大小",
                    code: `void resize(long long size);`,
                    params: {
                        arr: [
                            { param: "size", type: "long long", desc: "字节集大小" }
                        ],
                        ret: { type: "void", desc: "无返回值" }
                    }
                }, {// 判断是否为空
                    label: "empty", comment: "判断是否为空",
                    code: `bool empty() const;`,
                    params: {
                        arr: [],
                        ret: { type: "bool", desc: "true:为空,false:不为空" }
                    }
                }, {// 清空字节集
                    label: "clear", comment: "清空字节集",
                    code: `void clear();`,
                    params: {
                        arr: [],
                        ret: { type: "void", desc: "无返回值" }
                    }
                }, {// 获取内部数据指针
                    label: "data", comment: "获取内部数据指针",
                    code: `const unsigned char* data(long long index = NULL) const;`,
                    params: {
                        arr: [
                            { param: "index", type: "long long", desc: "字节集索引,默认NULL" }
                        ],
                        ret: { type: "const unsigned char*", desc: "字节集数据指针" }
                    }
                }, {//标准化输出
                    label: "operator<<", comment: "标准化输出",
                    code: `friend std::ostream& operator<<(std::ostream& os, const Byteset& byteset);`,
                    params: {
                        arr: [
                            { param: "os", type: "std::ostream&", desc: "输出流" },
                            { param: "byteset", type: "const Byteset&", desc: "字节集" }
                        ],
                        ret: { type: "std::ostream&", desc: "输出流" }
                    }
                }, {// 寻找字节集
                    label: "find", comment: "寻找字节集",
                    code: `long long find(const Byteset& other, long long pos = NULL, bool vague = false, const Byteset& vagueContent = nullptr) const;`,
                    params: {
                        arr: [
                            { param: "other", type: "const Byteset&", desc: "要寻找的字节集" },
                            { param: "pos", type: "long long", desc: "开始搜索的位置,默认NULL" },
                            { param: "vague", type: "bool", desc: "是否模糊查找,默认false" },
                            { param: "vagueContent", type: "const Byteset&", desc: "模糊查找的忽略字节集,默认{0}" }
                        ],
                        ret: { type: "long long", desc: "找到的位置,如果没有找到,则返回-1" }
                    }
                }, {// 替换字节集
                    label: "replace", comment: "替换字节集",
                    code: `long long replace(const Byteset& old, const Byteset& new_str, int count = -1, long long pos = NULL);`,
                    params: {
                        arr: [
                            { param: "old", type: "const Byteset&", desc: "要替换的字节集" },
                            { param: "new_str", type: "const Byteset&", desc: "新的字节集" },
                            { param: "count", type: "int", desc: "替换次数,默认-1全部替换" },
                            { param: "pos", type: "long long", desc: "开始搜索的位置,默认NULL" }
                        ],
                        ret: { type: "long long", desc: "被替换的字节集个数" }
                    }
                }, {// 移除字节集
                    label: "remove", comment: "移除字节集",
                    code: `long long remove(const Byteset& other, long long pos = NULL, int count = -1);`,
                    params: {
                        arr: [
                            { param: "other", type: "const Byteset&", desc: "要移除的字节集" },
                            { param: "pos", type: "long long", desc: "开始搜索的位置,默认NULL" },
                            { param: "count", type: "int", desc: "移除次数,默认-1全部移除" }
                        ],
                        ret: { type: "long long", desc: "被移除的字节集个数" }
                    }
                }, {// 获取字节集的子集
                    label: "subBytes", comment: "获取字节集的子集",
                    code: `Byteset subBytes(long long pos, long long len) const;`,
                    params: {
                        arr: [
                            { param: "pos", type: "long long", desc: "开始位置" },
                            { param: "len", type: "long long", desc: "子集长度" }
                        ],
                        ret: { type: "Byteset", desc: "子集" }
                    }
                }, {//字节集的开始位置
                    label: "begin", comment: "字节集的开始位置",
                    code: `std::vector<unsigned char>::iterator begin();`,
                    params: {
                        arr: [],
                        ret: { type: "std::vector<unsigned char>::iterator", desc: "字节集的开始位置" }
                    }
                }, {//字节集的开始位置
                    label: "begin", comment: "字节集的开始位置",
                    code: `std::vector<unsigned char>::const_iterator begin() const;`,
                    params: {
                        arr: [],
                        ret: { type: "std::vector<unsigned char>::const_iterator", desc: "字节集的开始位置" }
                    }
                }, {//字节集的结束位置
                    label: "end", comment: "字节集的结束位置",
                    code: `std::vector<unsigned char>::iterator end();`,
                    params: {
                        arr: [],
                        ret: { type: "std::vector<unsigned char>::iterator", desc: "字节集的结束位置" }
                    }
                }, {//字节集的结束位置
                    label: "end", comment: "字节集的结束位置",
                    code: `std::vector<unsigned char>::const_iterator end() const;`,
                    params: {
                        arr: [],
                        ret: { type: "std::vector<unsigned char>::const_iterator", desc: "字节集的结束位置" }
                    }
                }, {//字节集的逆向开始位置
                    label: "rbegin", comment: "字节集的逆向开始位置",
                    code: `std::vector<unsigned char>::reverse_iterator rbegin();`,
                    params: {
                        arr: [],
                        ret: { type: "std::vector<unsigned char>::reverse_iterator", desc: "字节集的逆向开始位置" }
                    }
                }, {//字节集的逆向开始位置
                    label: "rbegin", comment: "字节集的逆向开始位置",
                    code: `std::vector<unsigned char>::const_reverse_iterator rbegin() const;`,
                    params: {
                        arr: [],
                        ret: { type: "std::vector<unsigned char>::const_reverse_iterator", desc: "字节集的逆向开始位置" }
                    }
                }, {//字节集的逆向结束位置
                    label: "rend", comment: "字节集的逆向结束位置",
                    code: `std::vector<unsigned char>::reverse_iterator rend();`,
                    params: {
                        arr: [],
                        ret: { type: "std::vector<unsigned char>::reverse_iterator", desc: "字节集的逆向结束位置" }
                    }
                }, {//字节集的逆向结束位置
                    label: "rend", comment: "字节集的逆向结束位置",
                    code: `std::vector<unsigned char>::const_reverse_iterator rend() const;`,
                    params: {
                        arr: [],
                        ret: { type: "std::vector<unsigned char>::const_reverse_iterator", desc: "字节集的逆向结束位置" }
                    }
                }
            ],
            text: [
                `
    Byteset data;
    data.append({ 0xFF, 0xE8, 0x30, 0x46 });//动态添加字节集
    std::cout << " Data size: " << data.size() << " data: " << data << std::endl;//输出字节集
                `,
                `
    // 从字符串构造
    Byteset(const std::string& str);

    // 从字节数组构造
    Byteset(const void* bytes, long long size);

    // 从字节数组构造
    Byteset(const char* bytes);

    //从int类型构造
    Byteset(int num);

    //从long类型构造
    Byteset(long num);

    //从long long类型构造
    Byteset(long long num);

    //从size_t类型构造
    Byteset(size_t num);

    //从float类型构造
    Byteset(float num);

    //从double类型构造
    Byteset(double num);

    //从long double类型构造
    Byteset(long double num);

    //从bool类型构造
    Byteset(bool flag);

    //从char类型构造
    Byteset(char ch);

    //从short类型构造
    Byteset(short num);

    // 拷贝构造函数
    Byteset(const Byteset& other);

    // 移动构造函数
    Byteset(Byteset&& other) noexcept;

    //数据比较处理
    bool operator==(const Byteset& other) const;

    //数据不等比较处理
    bool operator!=(const Byteset& other) const;

    // 拷贝赋值操作符
    Byteset& operator=(const Byteset& other);

    //拷贝赋值操作符:文本字符串
    Byteset& operator=(const std::string& str);

    //拷贝赋值操作符:字节数组
    Byteset& operator=(const char* bytes);

    // 初始化列表构造函数
    Byteset(std::initializer_list<unsigned char> init_list);

    /*
    * 追加字节
    * @param bytes 字节数组
    * @param size 字节数组大小
    */
    Byteset& append(const void* bytes, long long size);

    // 追加另一个 Byteset
    Byteset& append(const Byteset& other);

    // 追加字节
    void push_back(unsigned char byte);

    // 弹出最后一个字节
    unsigned char pop_back();

    // 访问字节
    unsigned char& operator[](long long index);

    // 访问字节
    const unsigned char& operator[](long long index) const;

    // 获取字节集大小
    long long size() const;

    // 调整字节集大小
    void resize(long long size);
    // 判断是否为空
    bool empty() const;

    // 清空字节集
    void clear();

    /*
    * 获取内部数据指针
    * @param index 要获取的字节集的索引,默认为NULL,表示获取整个字节集
    * @return 字节集数据指针
    */
    const unsigned char* data(long long index = NULL) const;

    //标准化输出
    friend std::ostream& operator<<(std::ostream& os, const Byteset& byteset);
    /*
    * 寻找字节集
    * @param other 要寻找的字节集
    * @param pos 开始搜索的位置
    * @param vague 是否模糊查找,模糊查找时,忽略other中与之匹配的字节,默认 不模糊查找
    * @param vagueContent 模糊查找的忽略字节集,默认为{0}
    * @return 找到的位置，如果没有找到，则返回-1
    */
    long long find(const Byteset& other, long long pos = NULL, bool vague = false, const Byteset& vagueContent = nullptr) const;

    /*
    * 替换字节集
    * @param old 要替换的字节集
    * @param new_str 新的字节集
    * @param count 替换次数,默认-1全部替换
    * @param pos 开始搜索的位置
    * @return 被替换的字节集个数
    */
    long long replace(const Byteset& old, const Byteset& new_str, int count = -1, long long pos = NULL);

    /*
    * 移除字节集
    * @param other 要移除的字节集
    * @param pos 开始搜索的位置
    * @param count 移除次数,默认-1全部移除
    * @return 被移除的字节集个数
    */
    long long remove(const Byteset& other, long long pos = NULL, int count = -1);

    /*
    * 获取字节集的子集
    * @param pos 开始位置
    * @param len 子集长度
    * @return 子集
    */
    Byteset subBytes(long long pos, long long len) const;

    //字节集的开始位置
    std::vector<unsigned char>::iterator begin();

    //字节集的开始位置
    std::vector<unsigned char>::const_iterator begin() const;

    //字节集的结束位置
    std::vector<unsigned char>::iterator end();

    //字节集的结束位置
    std::vector<unsigned char>::const_iterator end() const;

    //字节集的逆向开始位置
    std::vector<unsigned char>::reverse_iterator rbegin();

    //字节集的逆向开始位置
    std::vector<unsigned char>::const_reverse_iterator rbegin() const;

    //字节集的逆向结束位置
    std::vector<unsigned char>::reverse_iterator rend();

    //字节集的逆向结束位置
    std::vector<unsigned char>::const_reverse_iterator rend() const;
                `
            ]
        }
    }
};
</script>
<style lang="scss" scoped>
.byteset {
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
