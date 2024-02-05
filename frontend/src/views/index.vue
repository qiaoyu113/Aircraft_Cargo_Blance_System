<template>
  <div id="index">
    <dv-full-screen-container class="bg">

      <dv-loading v-if="loading">Loading...</dv-loading>
      <div v-else class="host-body">
          <div class="nav">
            <div class="nav-text">
              <span class="wel">Welcome to </span>
              <span> Aircraft Cargo Blance System</span>
            </div>
            <dv-decoration-2 :reverse="false" style="width: 300px;
              height: 5px;
              position: relative;
              top: 160px;
              left: 40px;
              z-index: 1000;" />
            <div class="nav-img"></div>
            <div class="nav-shadow"></div>
          </div>

        <div class="body-box">
          <!-- 第三行数据 -->
          <div class="content-box">
            <!-- 左侧 -->
            <div>
              <!-- <dv-border-box-12> -->
              <bottomLeft />
              <!-- </dv-border-box-12> -->
            </div>
            <!-- 右侧 -->
            <status></status>
          </div>
        </div>
      </div>
    </dv-full-screen-container>
  </div>
</template>

<script>
// import center from "./center";
import bottomLeft from "./bottomLeft";
import status from "./status";
// import centreLeft1 from "./centreLeft1";
export default {
  data() {
    return {
      loading: true
    };
  },
  components: {
    bottomLeft,
    status
  },
  mounted() {
    this.cancelLoading();
  },
  methods: {
    cancelLoading() {
      setTimeout(() => {
        this.loading = false;
      }, 2000);
    }
  }
};
</script>

<style lang="scss" scoped>
@import "../assets/scss/index.scss";
</style>