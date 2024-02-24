<template>
  <div id="index">
    <dv-full-screen-container class="bg">
        <button @click="changeConveyorStatus('warning')">warning</button>
        <button @click="changeConveyorStatus('normal')">normal</button>
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
              <simulation />
              <!-- </dv-border-box-12> -->
            </div>
            <!-- 右侧 -->
            <status :conveyorStatus="conveyorStatus"></status>
          </div>
        </div>
      </div>
    </dv-full-screen-container>
  </div>
</template>

<script>
// import center from "./center";
import simulation from "./simulation";
import status from "./status";
// import centreLeft1 from "./centreLeft1";
export default {
  data() {
    return {
      loading: true,
      ws: null,
      conveyorStatus:0
    };
  },
  components: {
    simulation,
    status
  },
  mounted() {
    this.cancelLoading();
  },
  created() {
    this.connect();
  },
  methods: {
    cancelLoading() {
      setTimeout(() => {
        this.loading = false;
      }, 2000);
    },
    connect() {
      this.ws = new WebSocket('ws://127.0.0.1:8090');
      this.ws.onmessage = (event) => {
        // 当收到消息时更新message
        const res = JSON.parse(event.data);
        console.log(res);
        if(res.action == 'button') {
          this.conveyorStatus = res.parameter
        }
      };
      this.ws.onopen = () => {
        console.log('WebSocket connection established');
      };
      this.ws.onerror = (error) => {
        console.error('WebSocket Error:', error);
      };
    },
    // conveyor status
    changeConveyorStatus(status) {
      if (this.ws.readyState === WebSocket.OPEN) {
        const message = {
          action: 'changeConveyorStatus',
          parameter: status
        };
        const messageString = JSON.stringify(message);
        this.ws.send(messageString);
      }
    }
  },
  beforeDestroy() {
    // 组件销毁前关闭WebSocket连接
    if (this.ws) {
      this.ws.close();
    }
  },
};
</script>

<style lang="scss" scoped>
@import "../assets/scss/index.scss";
</style>