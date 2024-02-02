<template>
  <div>
    <div id="bottomLeftChart" style="width:900px;height:600px;"></div>
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
  mounted() {
    this.setData(
      0, 2, 0 ,3, 1, 0, 0, 0, 0, 0, 0, 1,
    );
  },
  methods: {
    setData(val1, val2, val3, val4, val5, val6, val7, val8, val9, val10, val11, val12) {
      let weight1 = [0, 0, val1]
      let weight2 = [0, 1, val2]
      let weight3 = [0, 2, val3]
      let weight4 = [0, 3, val4]
      let weight5 = [0, 4, val5]
      let weight6 = [0, 5, val6]
      let weight7 = [0, 6, val7]
      let weight8 = [0, 7, val8]
      let weight9 = [0, 8, val9]
      let weight10 = [0, 9, val10]
      let weight11 = [0, 10, val11]
      let weight12 = [0, 11, val12]

      let data = [
        // 仅使用12个数据点
        weight1, weight2, weight3, weight4, weight5, weight6, weight7, weight8, weight9, weight10, weight11, weight12
      ];
      this.drawPie(data)
    },
    drawPie(datas) {
      // 基于准备好的dom，初始化echarts实例
      let myChartPieLeft = echarts.init(
        document.getElementById("bottomLeftChart")
      );

      //  ----------------------------------------------------------------
      let hours = ['12a', '1a', '2a', '3a', '4a', '5a', '6a', '7a', '8a', '9a', '10a', '11a'];
      let days = ['conveyor']; // 仅使用一天
      let data = datas;

      let option = {
        tooltip: {},
        visualMap: {
          max: 20,
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

      myChartPieLeft.setOption(option);
      // -----------------------------------------------------------------
      // 响应式变化
      window.addEventListener("resize", () => myChartPieLeft.resize(), false);
    }
  },
  destroyed() {
    window.onresize = null;
  }
};
</script>

<style lang="scss" scoped>
</style>