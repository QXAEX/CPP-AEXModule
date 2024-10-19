<template>
  <keep-alive>
    <router-view v-slot="{ Component }">
      <div :class="`title`">
        <h1>AEXModule {{ version }}</h1>
      </div>
      <div>
        <component :is="Component" :version="version" />
      </div>
      <div class="bottom">
        <p>
          感谢您使用AEXModule, 我们将收集各种意见, 并采取最佳解决方案优化. 被采纳者可以提供你的联系信息,我们会记录在文档中。
        </p>
      </div>
    </router-view>
  </keep-alive>
</template>

<script>
export default {
  data() {
    return {
      version: '1.2.5.2'
    }
  }
}
</script>

<style lang="scss">
.title {
  background-color: #1c1c1c;
  margin-bottom: 10px;
  box-shadow: 0 2px 4px rgba(#dc52b6, 0.4);
  height: 60px;
  line-height: 60px;
  padding: 0 5px;

  h1 {
    font-size: 30px;
    text-align: center;
    display: block;
    background: linear-gradient(to right, #362643, #362643 35%, #dc52b6 55%, #dc52b6);
    -webkit-background-clip: text;
    -webkit-text-fill-color: transparent;
    user-select: none;
  }

  .light-btn {
    cursor: pointer;
    position: absolute;
    right: 10px;
    top: 8px;
    width: 40px;
    height: 40px;
    border-radius: 50%;
  }
}

body {
  background-color: #242424;
}

.bottom {
  padding: 5px;
  margin-top: 10px;
  border-top: 2px solid;
  text-align: center;
  color: #af3d8f;
  user-select: none;
}
</style>