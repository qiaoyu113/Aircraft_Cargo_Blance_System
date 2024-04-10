<template>
  <div id="index">
    <dv-full-screen-container class="bg">
      <!-- <button @click="changeConveyorStatus('warning')">warning</button>
      <button @click="changeConveyorStatus('normal')">normal</button> -->
      <dv-loading v-if="loading">Loading...</dv-loading>
      <div v-else :class="platform == 'Linux' ? 'linux-body' : 'host-body'">
          <div class="nav">
            <div class="nav-text">
              <span class="wel">Welcome to </span>
              <span> Aircraft Cargo Blance System</span>
            </div>
            <dv-decoration-2 :reverse="false" :style="platform == 'Linux' ? 'width: 900px; height: 50px; position: relative; top: 360px; left: 200px; z-index: 1000;' : 'width: 300px; height: 5px; position: relative; top: 160px; left: 40px; z-index: 1000;'" />
            <div class="nav-img"></div>
            <div class="nav-shadow"></div>
          </div>

        <div class="body-box">
          <!-- 第三行数据 -->
          <div class="content-box">
            <!-- 左侧 -->
            <div>
              <!-- <dv-border-box-12> -->
              <simulation :conveyorData="conveyorData" />
              <!-- </dv-border-box-12> -->
            </div>
            <!-- 右侧 -->
            <status :conveyorStatus="conveyorStatus" :balanceRate="balanceRate"></status>
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
      platform: 'others',
      ws: null,
      conveyorStatus:0,
      balanceRate:0,
      conveyorData: [0, 0, 0, 0, 0] // 示例数据
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
    if(navigator.platform == 'Linux x86_64') {
      this.platform = 'Linux'
    } else {
      this.platform = 'others'
    }
  },
  methods: {
    cancelLoading() {
      setTimeout(() => {
        this.loading = false;
      }, 2000);
    },
    connect() {
      // this.ws = new WebSocket('ws://1.tcp.vip.cpolar.cn:22939');
      this.ws = new WebSocket('ws://2a5e9011.r7.cpolar.top');
      this.ws.onmessage = (event) => {
        // 当收到消息时更新message
        const res = JSON.parse(event.data);
        console.log(res);
        // 监听按钮时间
        if(res.action == 'button') {
          this.conveyorStatus = res.parameter
        // 接收传送带状态
        } else if(res.action == 'conveyorStatus') {
          this.conveyorStatus = res.parameter
        // 接收重力平衡数值
        } else if(res.action == 'balanceRate') {
          this.balanceRate = res.parameter
        // 监听w1传感器的数值
        } else if(res.action == 'visualization') {
          this.$set(this.conveyorData, 0, res.parameter[0])
          this.$set(this.conveyorData, 1, res.parameter[1])
          this.$set(this.conveyorData, 2, res.parameter[2])
          this.$set(this.conveyorData, 3, res.parameter[3])
          this.$set(this.conveyorData, 4, res.parameter[4])
          this.calculateController(res.parameter)
        }
      };
      this.ws.onopen = () => {
        console.log('WebSocket connection established');
      };
      this.ws.onerror = (error) => {
        console.error('WebSocket Error:', error);
      };
    },
    // calculateController
    calculateController(currentWeight) {
      this.calculateConveyorStatus(currentWeight);
      this.calculateBalanceRate(currentWeight);
    },
    // calculate conveyor balance rate
    calculateBalanceRate(values) {
      // 假设values是一个有5个元素的数组
      if (values.length !== 5) {
        console.error('The array must contain exactly 5 values.');
        return;
      }

      // 定义每个数值的权重，这里我们假设都相等
      const weights = [1, 1, 1, 1, 1]; // 可以根据需要调整权重
      
      // 为左侧、中心和右侧分配加权值
      // 我们将数组的第一个和第二个数值视为负值，第三个数值视为0，第四个和第五个数值视为正值
      let weightedSum = (values[0] * -weights[0]) +
                        (values[1] * -weights[1]) +
                        (values[2] * 0) +
                        (values[3] * weights[3]) +
                        (values[4] * weights[4]);

      // 计算加权和的总权重
      let totalWeight = weights.reduce((a, b) => a + b, 0);

      // 计算加权平均值
      let weightedAverage = weightedSum / totalWeight;

      // 由于ECharts仪表盘的值是从-1到1，我们需要将加权平均值归一化到这个范围内
      // 假设values数组中的数值已经是按比例分配的，且最小值和最大值分别为-1和1
      // 如果数值不在这个范围内，则需要相应地调整归一化过程

      // 返回仪表盘的值
      this.balanceRate = weightedAverage
    },
    // calculate conveyor status light
    calculateConveyorStatus(currentWeight) {
      if (currentWeight.length !== 5) {
          console.error("Error: Expected 5 weight readings.");
          return;
      }
      const weightAll = currentWeight.reduce((acc, curr) => acc + curr, 0);
      const d = 2;
      const weightSystem = 0;
      const rotationInertia = ((weightAll + weightSystem) * 4 * 4 * d * d) / 12;
      const torqueLeft = 9.8 * currentWeight[0] * 2 * d + 9.8 * currentWeight[1] * d;
      const torqueRight = 9.8 * currentWeight[4] * 2 * d + 9.8 * currentWeight[3] * d;
      const accLimit = 1.2; // Assuming accLimit is predefined

      if (currentWeight[0] + currentWeight[1] > currentWeight[3] + currentWeight[4]) {
          if (weightAll === 0) {
              this.conveyorStatus = 0;
          } else {
              const angleAcc = (torqueLeft - torqueRight) / rotationInertia;
              if (angleAcc <= accLimit) {
                  this.conveyorStatus = 0;
              } else {
                  if (currentWeight[4] !== 0) {
                      this.conveyorStatus = 0;
                  } else {
                      this.conveyorStatus = 1;
                  }
              }
          }
      }

      if (currentWeight[0] + currentWeight[1] < currentWeight[3] + currentWeight[4]) {
          if (weightAll === 0) {
              this.conveyorStatus = 0;
          } else {
              const angleAcc = (torqueRight - torqueLeft) / rotationInertia;
              if (angleAcc <= accLimit) {
                  this.conveyorStatus = 0;
              } else {
                  if (currentWeight[0] !== 0) {
                      this.conveyorStatus = 0;
                  } else {
                      this.conveyorStatus = 1;
                  }
              }
          }
      }

      if (currentWeight[0] + currentWeight[1] === currentWeight[3] + currentWeight[4]) {
          this.conveyorStatus = 0;
      }
    },
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