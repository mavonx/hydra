import { defineConfig } from 'vitepress';
import { withMermaid } from 'vitepress-plugin-mermaid';

export default withMermaid(
  defineConfig({
    base: '/hydra/',
    title: 'hydra',
    description: 'A fast, low-memory CLI for exploring massive CSV datasets without crashing.',
    lang: 'en-US',
    lastUpdated: true,
    cleanUrls: true,
    appearance: false,
    vite: {
      optimizeDeps: {
        include: ['fastdom', 'mermaid']
      }
    },
    head: [
      ['link', { rel: 'icon', type: 'image/png', href: '/hydra/favicon.png' }],
      ['meta', { property: 'og:title', content: 'hydra' }],
      ['meta', { property: 'og:description', content: 'A fast, low-memory CLI for exploring massive CSV datasets without crashing.' }],
      ['meta', { property: 'og:image', content: 'https://mavonx.github.io/hydra/logo.png' }],
      ['meta', { property: 'og:image:width', content: '1200' }],
      ['meta', { property: 'og:image:height', content: '630' }],
      ['meta', { property: 'twitter:card', content: 'summary_large_image' }],
      ['meta', { property: 'twitter:image', content: 'https://mavonx.github.io/hydra/logo.png' }]
    ],
    themeConfig: {
      siteTitle: 'hydra',
      logo: { src: '/logo.png', alt: 'hydra logo' },
      nav: [
        { text: 'Docs', link: '/docs' },
        { text: 'Installation', link: '/installation' },
        { text: 'Benchmarks', link: '/benchmarks' },
        { text: 'Examples', link: '/examples' },
        { text: 'Discord', link: 'https://discord.gg/your-invite-code' },
        { text: '4.4k', link: 'https://github.com/mavonx/hydra' }
      ],
      socialLinks: [
        { icon: 'github', link: 'https://github.com/mavonx/hydra' }
      ],
      footer: {
        copyright: `Copyright © ${new Date().getFullYear()} mavonx`
      }
    },
    mermaid: {
      theme: 'default'
    }
  })
);
