<template>
  <!-- alert窗口 -->
  <div id="loginAlert">
    <!-- 登录成功提示 -->
    <div v-show="loginSuccess" role="alert" class="alert alert-success mb-4 ease-in duration-200">
      <svg
        xmlns="http://www.w3.org/2000/svg"
        class="h-6 w-6 shrink-0 stroke-current"
        fill="none"
        viewBox="0 0 24 24"
      >
        <path
          stroke-linecap="round"
          stroke-linejoin="round"
          stroke-width="2"
          d="M9 12l2 2 4-4m6 2a9 9 0 11-18 0 9 9 0 0118 0z"
        />
      </svg>
      <span>登录成功！</span>
    </div>
    <!-- 登录失败提示 -->
    <div v-show="loginFail" role="alert" class="alert alert-error mb-4 ease-in duration-200">
      <svg
        xmlns="http://www.w3.org/2000/svg"
        class="h-6 w-6 shrink-0 stroke-current"
        fill="none"
        viewBox="0 0 24 24"
      >
        <path
          stroke-linecap="round"
          stroke-linejoin="round"
          stroke-width="2"
          d="M10 14l2-2m0 0l2-2m-2 2l-2-2m2 2l2 2m7-2a9 9 0 11-18 0 9 9 0 0118 0z"
        />
      </svg>
      <span>邮箱或密码错误</span>
    </div>
  </div>

  <form
    class="w-1/2 max-w-md flex flex-col justify-center items-center p-4 gap-2 shadow-bottom rounded-md"
    action="#"
    @submit.prevent="handleSubmit"
  >
    <div class="my-2 text-3xl font-semibold">
      <h1>登录</h1>
    </div>
    <!-- 邮箱 -->
    <label class="input validator">
      <svg class="h-[1em] opacity-50" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24">
        <g
          stroke-linejoin="round"
          stroke-linecap="round"
          stroke-width="2.5"
          fill="none"
          stroke="currentColor"
        >
          <rect width="20" height="16" x="2" y="4" rx="2"></rect>
          <path d="m22 7-8.97 5.7a1.94 1.94 0 0 1-2.06 0L2 7"></path>
        </g>
      </svg>
      <input v-model="email" type="email" placeholder="mail@site.com" required />
    </label>
    <div class="validator-hint hidden">请输入邮箱</div>
    <!-- 密码 -->
    <label class="input validator">
      <svg class="h-[1em] opacity-50" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24">
        <g
          stroke-linejoin="round"
          stroke-linecap="round"
          stroke-width="2.5"
          fill="none"
          stroke="currentColor"
        >
          <path
            d="M2.586 17.414A2 2 0 0 0 2 18.828V21a1 1 0 0 0 1 1h3a1 1 0 0 0 1-1v-1a1 1 0 0 1 1-1h1a1 1 0 0 0 1-1v-1a1 1 0 0 1 1-1h.172a2 2 0 0 0 1.414-.586l.814-.814a6.5 6.5 0 1 0-4-4z"
          ></path>
          <circle cx="16.5" cy="7.5" r=".5" fill="currentColor"></circle>
        </g>
      </svg>
      <input
        v-model="passwd"
        type="password"
        required
        placeholder="密码"
        minlength="8"
        pattern="(?=.*\d)(?=.*[a-z])(?=.*[A-Z]).{8,}"
        title="Must be more than 8 characters, including number, lowercase letter, uppercase letter"
      />
    </label>
    <p class="validator-hint hidden">
      Must be more than 8 characters, including
      <br />At least one number <br />At least one lowercase letter <br />At least one uppercase
      letter
    </p>
    <!-- 验证码 -->
    <!-- <input type="text" required placeholder="请输入验证码" class="input" /> -->

    <!-- 记住密码 -->
    <fieldset class="fieldset p-4 bg-base-100 border border-base-300 rounded-box w-64">
      <legend class="fieldset-legend">Login options</legend>
      <label class="fieldset-label">
        <input type="checkbox" class="checkbox checkbox-accent" />
        <div class="flex items-center w-full justify-between">
          <label for="rememberPw" class="text-black text-sm">记住我</label>
          <button class="btn btn-link">忘记密码？</button>
        </div>
      </label>
    </fieldset>

    <!-- 按钮 -->
    <button class="btn btn-outline btn-accent w-full max-w-[310px]">登录</button>
    <!-- 注册 -->
    <div class="flex items-center justify-center gap-1">
      <span>还没有账号？请</span>
      <RouterLink :to="{ name: 'signup' }">
        <span class="text-accent hover:text-green-500">注册</span>
      </RouterLink>
      <button
        :hidden="true"
        type="button"
        @click="forTest"
        class="bg-red-400 hover:bg-red-500 text-white font-bold py-2 px-4 rounded"
      >
        test
      </button>
    </div>
  </form>
</template>

<script setup>
import supabase from '@/utilities/supabase'
import axios from 'axios'
import { uid } from 'uid'
import { ref } from 'vue'
import { useRouter } from 'vue-router'
import { errorMessages } from 'vue/compiler-sfc'
const router = useRouter()

const email = ref('')
const passwd = ref('')

const loginSuccess = ref(false)
const loginFail = ref(false)

const handleSubmit = async () => {
  console.log('submitted!')
  const { data, error } = await supabase.auth.signInWithPassword({
    email: email.value,
    password: passwd.value,
  })
  if (error) {
    if (error.message === 'Invalid login credentials') {
      loginFail.value = !loginFail.value
    } else {
      alert('登录失败')
    }
  } else {
    loginSuccess.value = !loginSuccess.value
    setTimeout(() => {
      router.push({ name: 'chatView' })
    }, 2000)
  }
}
const forTest = async () => {
  const LocalUser = await supabase.auth.getSession()
  console.log(LocalUser)
}
</script>
