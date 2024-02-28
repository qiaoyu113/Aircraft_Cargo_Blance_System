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
            center: ['50%', '75%'],
            radius: '90%',
            min: 0,
            max: 1,
            splitNumber: 8,
            axisLine: {
                lineStyle: {
                width: 6,
                color: [
                    [0.4, '#FF6E76'],
                    [0.5, '#7CFFB2'],
                    [0.6, '#7CFFB2'],
                    [1, '#FF6E76']
                ]
                }
            },
            pointer: {
                icon: 'path://M12.8,0.7l12,40.1H0.7L12.8,0.7z',
                length: '12%',
                width: 20,
                offsetCenter: [0, '-60%'],
                itemStyle: {
                color: 'auto'
                }
            },
            axisTick: {
                length: 12,
                lineStyle: {
                color: 'auto',
                width: 2
                }
            },
            splitLine: {
                length: 20,
                lineStyle: {
                color: 'auto',
                width: 5
                }
            },
            axisLabel: {
                color: '#464646',
                fontSize: 20,
                distance: -60,
                rotate: 'tangential',
                formatter: function (value) {
                if (value === 0.875) {
                    return 'Right-sided bias';
                } else if (value === 0.625) {
                    return 'Pass';
                } else if (value === 0.375) {
                    return 'Pass';
                } else if (value === 0.125) {
                    return 'Left-sided bias';
                }
                return '';
                }
            },
            title: {
                offsetCenter: [0, '-10%'],
                fontSize: 20
            },
            detail: {
                fontSize: 30,
                offsetCenter: [0, '-35%'],
                valueAnimation: true,
                formatter: function (value) {
                return Math.round(value * 100) + '';
                },
                color: 'inherit'
            },
            data: [
                {
                value: num / 100,
                name: 'Balance Rating'
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
        this.setData(30);
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