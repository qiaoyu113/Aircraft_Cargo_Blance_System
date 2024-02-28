<template>
  <div id="bottomLeft">
    <div class="bg-color-black ">
      <div class="d-flex pt-2 pl-2">
        <span style="color:#5cd9e8">
          <icon name="chart-bar"></icon>
        </span>
        <div class="d-flex">
          <span class="fs-xl text mx-2">Gravity balance visualization</span>
        </div>
      </div>
      <div>
        <conveyorChart :conveyorData="conveyorData" />
      </div>
    </div>
  </div>
</template>

<script>
import conveyorChart from "@/components/echart/bottom/conveyorChart";
export default {
  data() {
    return {};
  },
  props: {
    // 声明接收来自父组件的参数
    conveyorData: Array,
  },
  components: {
    conveyorChart
  },
  mounted() {
  },
  methods: {}
};
</script>

<style lang="scss">
#bottomLeft {
  padding: 1.5rem 1rem;
  height: 520px;
  min-width: 300px;
  border-radius: 5px;
  .bg-color-black {
    height: 485px;
    border-radius: 10px;
  }
  .text {
    color: #c3cbde;
  }
  .chart-box {
    margin-top: 1rem;
    width: 170px;
    height: 170px;
    .active-ring-name {
      padding-top: 10px;
    }
  }
}
</style>