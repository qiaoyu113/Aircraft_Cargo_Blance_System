<template>
  <div id="status">
    <div class="bg-color-black">
      <div class="d-flex pt-2 pl-2">
        <span style="color:#5cd9e8">
          <icon name="chart-area"></icon>
        </span>
        <div class="d-flex">
          <span class="fs-xl text mx-2">Conveyor Status</span>
          <!-- <div class="decoration2">
            <dv-decoration-3 style="width:300px;height:20px; position:relative;top:-3px;" />
          </div> -->
        </div>
      </div>
      <div>
        <light :status="conveyorStatus"/>
      </div>
      <div>
        <balance />
      </div>
    </div>
  </div>
</template>

<script>
// import bottomRightChart from "@/components/echart/bottom/bottomRightChart";
import light from "@/components/echart/light";
import balance from "@/components/echart/balance";
export default {
  data() {
    return {};
  },
  props: {
    // 声明接收来自父组件的参数
    conveyorStatus: Number,
  },
  components: {
    light,
    balance
  },
  mounted() {
  },
  methods: {}
};
</script>

<style lang="scss">
#status {
  padding: 1rem 1rem 0rem;
  height: 520px;
  min-width: 300px;
  border-radius: 5px;
  .bg-color-black {
    height: 495px;
    border-radius: 10px;
  }
  .text {
    color: #c3cbde;
    width: 120px;
  } //下滑线动态
  .decoration2 {
    position: relative;
    right: 10px;
    left: 10px;
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