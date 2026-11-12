import DefaultTheme from 'vitepress/theme';

import stars from './stars';
import SidebarToggle from './SidebarToggle';

import { h } from 'vue';
import type { Theme } from 'vitepress';

import './custom.css';

export default {
  extends: DefaultTheme,
  Layout: () => h(
    DefaultTheme.Layout,
    null,
    {
      'nav-bar-content-after': () => h(stars),
      'layout-top': () => h(SidebarToggle)
    }
  )
} satisfies Theme;
