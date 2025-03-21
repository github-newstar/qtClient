import supabase from '@/utilities/supabase'
import { defineStore } from 'pinia'

export const useUserInfoStore = defineStore('userInfoStore', {
  state: () => ({
    username: '',
    email: '',
    password: '',
    avatar: '',
  }),
  getters: {},
  actions: {
    //将用户信息存储到Pinia
    setUserInfo(userInfo) {
      this.username = userInfo.username
      this.email = userInfo.email
      // this.password = userInfo.password
      // this.avatar = userInfo.avatar
    },
    //获取用户信息
    async getUserState(next) {
      const localUser = await supabase.auth.getSession()
      if (localUser.data.session == null) {
        next('/login')
      } else {
        next()
      }
    },
    //注销登录
    async logOut() {
      const { error } = await supabase.auth.signOut()
      this.username = ''
      this.email = ''
      // this.password = ''
      // this.avatar = ''
      if (error) {
        console.log(error)
      }
    },
  },
})
