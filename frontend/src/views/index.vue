<template>
  <div id="index">
    <dv-full-screen-container class="bg">

      <dv-loading v-if="loading">Loading...</dv-loading>
      <div v-else class="host-body">
          <!-- <dv-decoration-10 style="width:33.3%;height:5px;" />
          <div class="d-flex jc-center">
            <dv-decoration-8 :color="['#568aea', '#000000']" style="width:200px;height:50px;" />
            <div class="title">
              <span class="title-text">Aircraft Cargo Blance System</span>
              <dv-decoration-6
                class="title-bototm"
                :reverse="true"
                :color="['#50e3c2', '#67a1e5']"
                style="width:250px;height:8px;"
              />
            </div>
            <dv-decoration-8
              :reverse="true"
              :color="['#568aea', '#000000']"
              style="width:200px;height:50px;"
            />
          </div>
          <dv-decoration-10 style="width:33.3%;height:5px;" /> -->
          <div class="nav">
            <div class="nav-text">
              <span class="wel">Welcome to </span>
              <span> Aircraft Cargo Blance System</span>
            </div>
            <div class="nav-img"></div>
            <div class="nav-shadow"></div>
          </div>

        <div class="body-box">
          <!-- 第三行数据 -->
          <div class="content-box">
            <div>
              <!-- <centreLeft1 /> -->
            </div>
            <!-- 中间 -->
            <div>
              <!-- <dv-border-box-12> -->
              <bottomLeft />
              <!-- </dv-border-box-12> -->
            </div>
            <!-- 右侧 -->
            <!-- <div>
              <center />
            </div> -->
          </div>
        </div>
      </div>
    </dv-full-screen-container>
  </div>
</template>

<script>
// import center from "./center";
import bottomLeft from "./bottomLeft";
// import centreLeft1 from "./centreLeft1";
export default {
  data() {
    return {
      loading: true
    };
  },
  components: {
    // center,
    bottomLeft,
    // centreLeft1
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