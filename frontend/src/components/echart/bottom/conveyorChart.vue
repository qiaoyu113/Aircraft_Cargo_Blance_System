<template>
  <div>
    <div id="conveyorChart" style="width:900px;height:600px;"></div>
  </div>
</template>

<script>
import * as echarts from 'echarts';
import 'echarts-gl';
// const echarts = require('echarts/lib/echarts');
export default {
  data() {
    return {
      chartInstance: null,
      myChartPieLeft: null
    };
  },
  props: {
    // 声明接收来自父组件的参数
    conveyorData: Array,
  },
  watch: {
    // 监听conveyorStatus变化
    conveyorData: {
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
  },
  methods: {
    setData(arr) {
      console.log('arr', arr);
      let weight1 = [0, 0, arr[0]]
      let weight2 = [0, 1, arr[1]]
      let weight3 = [0, 2, arr[2]]
      let weight4 = [0, 3, arr[3]]
      let weight5 = [0, 4, arr[4]]
      let weight6 = [0, 5, arr[5]]
      let weight7 = [0, 6, arr[6]]
      let data = [
        // 仅使用7个数据点
        weight1, weight2, weight3, weight4, weight5, weight6, weight7
      ];
      this.drawPie(data)
    },
    drawPie(datas) {
      // 基于准备好的dom，初始化echarts实例
      if (!this.chartInstance) {
        this.chartInstance = echarts.init(
          document.getElementById("conveyorChart")
        );
      }

      //  ----------------------------------------------------------------
      let hours = ['1a', '2a', '3a', '4a', '5a', '6a', '7a'];
      let days = ['conveyor']; // 仅使用一天
      let data = datas;

      let option = {
        tooltip: {},
        visualMap: {
          max: 50,
          inRange: {
            color: [
              '#313695',
              '#4575b4',
              '#74add1',
              '#abd9e9',
              '#e0f3f8',
              '#ffffbf',
              '#fee090',
              '#fdae61',
              '#f46d43',
              '#d73027',
              '#a50026'
            ]
          }
        },
        xAxis3D: {
          type: 'category',
          data: hours
        },
        yAxis3D: {
          type: 'category',
          data: days
        },
        zAxis3D: {
          type: 'value'
        },
        grid3D: {
          boxWidth: 200,
          boxDepth: 80,
          viewControl: {
            // projection: 'orthographic'
            alpha: 20, // 绕x轴旋转角度
            beta: 0, // 绕y轴旋转角度
          },
          light: {
            main: {
              intensity: 1.2,
              shadow: true
            },
            ambient: {
              intensity: 0.3
            }
          }
        },
        series: [
          {
            type: 'bar3D',
            data: data.map(function (item) {
              return {
                value: [item[1], item[0], item[2]]
              };
            }),
            shading: 'lambert',
            label: {
              fontSize: 16,
              borderWidth: 1
            },
            emphasis: {
              label: {
                fontSize: 20,
                color: '#900'
              },
              itemStyle: {
                color: '#900'
              }
            }
          }
        ]
      };
      // this.chartInstance.clear()
      this.chartInstance.setOption(option, true);
      // -----------------------------------------------------------------
      // 响应式变化
      window.addEventListener("resize", () => this.chartInstance.resize(), false);
      // 重新渲染
      this.chartInstance.resize()
    },
    initChart() {
      if (!this.chartInstance) { // 检查实例是否已经存在
        this.chartInstance = echarts.init(document.getElementById("conveyorChart"));
        this.setData(
          [0, 0, 0 ,0, 0, 0, 0]
        );
      }
    },
    updateChart(arr) {
      // 确保图表实例存在
      if (!this.chartInstance) {
        this.initChart();
      } else {
        this.setData(arr)
      }
    },
  },
  destroyed() {
    window.onresize = null;
  }
};
</script>

<style lang="scss" scoped>
</style>