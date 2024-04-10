<template>
  <div style=" margin-left:80px;">
    <div id="balance" style="width:650px;height:600px;"></div>
  </div>
</template>

<script>
import * as echarts from 'echarts';
import 'echarts-gl';
// const echarts = require('echarts/lib/echarts');
export default {
  data() {
    return {};
  },
  props: {
    // 声明接收来自父组件的参数
    balanceRate: Number,
  },
  watch: {
    // 监听conveyorStatus变化
    balanceRate: {
      handler(newVal) {
        this.$nextTick(() => {
          this.updateChart(newVal);
        });
         // 调用方法更新图表
      },
      immediate: true, // 组件加载时立即调用一次
    }
  },
  mounted() {
    this.setData(
     
    );
  },
  methods: {
    setData(num) {
      this.drawPie(num)
    },
    drawPie(num) {
      // 基于准备好的dom，初始化echarts实例
      let myChartBalance = echarts.init(
        document.getElementById("balance")
      );


      let option = {
        series: [
          {
            type: 'gauge',
            startAngle: 180,
            endAngle: 0,
            center: ['50%', '60%'],
            radius: '90%',
            min: -1, // Set the minimum to -1 or any negative value you want
            max: 1,  // Set the maximum to 1 or any positive value you want
            splitNumber: 4, // You can adjust this based on how many splits you want
            axisLine: {
              lineStyle: {
                width: 6,
                color: [
                  [0.4, '#FF6E76'], // Adjust the color stops to 25% intervals
                  [0.5, '#7CFFB2'],
                  [0.6, '#7CFFB2'],
                  [1, '#FF6E76']
                ]
              }
            },
            // ... other properties remain the same
            title: {
              // Existing properties
              color: 'white', // Set the title color to white
            },
            axisLabel: {
              color: 'white',
              // Update the formatter to include negative values and maintain your labels
              formatter: function (value) {
                if (value === 0.875) {
                  return 'Right-sided bias';
                } else if (value === 0.625) {
                  return 'Pass';
                } else if (value === 0.5) {
                  return '0';
                } else if (value === 0.375) {
                  return 'Pass';
                } else if (value === 0.125) {
                  return 'Left-sided bias';
                } else if (value === 0.25) {
                  return '-50';
                } else if (value === 0.75) {
                  return '+50';
                }
                return '';
              }
            },
            detail: {
              color: 'white',
              // Update formatter to reflect the actual value including negative
              formatter: function (value) {
                return (value * 100).toFixed(0);
              }
            },
            data: [
              {
                value: num / 200, // You need to ensure that num is within the range -100 to 100
                name: 'Balance Rating',
              }
            ]
          }
        ]
      };

      myChartBalance.setOption(option, true);
      // -----------------------------------------------------------------
      // 响应式变化
      window.addEventListener("resize", () => myChartBalance.resize(), false);
    },
    initChart() {
      if (!this.myChartBalance) { // 检查实例是否已经存在
        this.myChartBalance = echarts.init(document.getElementById("balance"));
        this.setData(0);
      }
    },
    updateChart(num) {
      // 确保图表实例存在
      if (!this.myChartBalance) {
        this.initChart();
      } else {
        this.setData(num)
      }
    },
  },
  destroyed() {
    window.onresize = null;
  },
};
</script>

<style lang="scss" scoped>
</style>